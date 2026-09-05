/*
	MIT License

	Copyright (c) 2024 Truong Hy

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

	Version: 20240601
*/

#include "request.h"
#include "app_error_string.h"
#include "tru_exception.h"
#include "tru_buffer.h"
#include "hp_time_elapsed.h"
#include <iostream>
#include <format>

#define KB 1000.0f
#define MB 1000000.0f

static std::string format_rate(double rate){
	if(rate < (double)KB){
		return std::format("{0:.2f} B/s", rate);
	}else if(rate < (double)MB){
		return std::format("{0:.2f} KB/s", rate / KB);
	}else{
		return std::format("{0:.2f} MB/s", rate / MB);
	}
}

void tx_test_req(serial_com& serial_com, uint32_t wr_len, uint32_t rd_len, uint32_t num_runs){
	tru_buffer buf;
	uint32_t wr_xferred_len;
	hp_time_elapsed timer;
	double wr_elapsed;
	double wr_rate;

	buf.set_size((rd_len > wr_len) ? rd_len : wr_len);

	for(uint32_t i = 0; i < num_runs; i++){
		// Fill buffer
		memset(buf.buf_ptr(), 0, wr_len);
		buf.buf_ptr()[0] = REQ_TX_TEST;
		buf.buf_ptr()[1] = wr_len;
		buf.buf_ptr()[2] = wr_len >> 8;
		buf.buf_ptr()[3] = wr_len >> 16;
		buf.buf_ptr()[4] = wr_len >> 24;
		buf.buf_ptr()[5] = rd_len;
		buf.buf_ptr()[6] = rd_len >> 8;
		buf.buf_ptr()[7] = rd_len >> 16;
		buf.buf_ptr()[8] = rd_len >> 24;

		// Send data
		wr_rate = 0;
		timer.set_begin_point();
		wr_xferred_len = serial_com.write_port(buf.buf_ptr(), wr_len);
		timer.set_end_point();
		wr_elapsed = timer.elapsed_us();
		wr_rate = (wr_elapsed > 0) ? (double)wr_xferred_len * 1000000 / wr_elapsed : 0;
		if(wr_xferred_len < wr_len){
			std::cout << "Tx " << wr_xferred_len << " bytes" << std::endl;
			throw tru_exception(__func__, TRU_EXCEPT_SRC_VEN, APP_ERROR_TX_FAIL_ID, app_error_string::messages[APP_ERROR_TX_FAIL_ID], "");
		}

		std::cout << "Test " << i+1 << ": Tx " << format_rate(wr_rate) << " (Tx " << wr_xferred_len << " bytes" << " in " << wr_elapsed << " us" << std::endl;
	}
}

void echo_test_req(serial_com& serial_com, uint32_t wr_len, uint32_t rd_len, uint32_t num_runs){
	tru_buffer buf;
	uint32_t wr_xferred_len;
	uint32_t rd_xferred_len;
	hp_time_elapsed timer;
	double wr_elapsed;
	double rd_elapsed;
	double wr_rate;
	double rd_rate;
	uint32_t mismatch_count;
	uint8_t test_count;

	buf.set_size((rd_len > wr_len) ? rd_len : wr_len);

	for(uint32_t i = 0; i < num_runs; i++){
		std::cout << "Test " << i << std::endl;

		mismatch_count = 0;
		test_count = 0;

		// Fill buffer
		memset(buf.buf_ptr(), 0, wr_len);
		for(uint32_t j = 0; j < wr_len; j++){
			buf.buf_ptr()[j] = j;
		}

		wr_rate = 0;
		rd_rate = 0;

		// Write data
		timer.set_begin_point();
		wr_xferred_len = serial_com.write_port(buf.buf_ptr(), wr_len);
		timer.set_end_point();
		wr_elapsed = timer.elapsed_us();
		if(wr_xferred_len < wr_len){
			std::cout << "Tx " << wr_xferred_len << " bytes" << std::endl;
			throw tru_exception(__func__, TRU_EXCEPT_SRC_VEN, APP_ERROR_TX_FAIL_ID, app_error_string::messages[APP_ERROR_TX_FAIL_ID], "");
		}

		// Receive data
		//timer.set_begin_point();  // We cannot measure from this point because of no control flow, this would just measure the queue buffer because the device is so quick it has already sent the data
		rd_xferred_len = serial_com.read_port(buf.buf_ptr(), rd_len);
		timer.set_end_point();
		rd_elapsed = timer.elapsed_us() - wr_elapsed;
		if(rd_xferred_len < rd_len){
			std::cout << "Rx " << rd_xferred_len << " bytes" << std::endl;
			throw tru_exception(__func__, TRU_EXCEPT_SRC_VEN, APP_ERROR_RX_FAIL_ID, app_error_string::messages[APP_ERROR_RX_FAIL_ID], "");
		}

		wr_rate = (wr_elapsed > 0) ? (double)wr_xferred_len * 1000000.0 / wr_elapsed : 0;
		rd_rate = (rd_elapsed > 0) ? (double)rd_xferred_len * 1000000.0 / rd_elapsed : 0;

		for(uint32_t j = 0; j < rd_len; j++){
			if(buf.buf_ptr()[j] != test_count) mismatch_count++;
			test_count++;
		}
		if(mismatch_count){
			std::cout << "Verify failed. " << mismatch_count << " errors" << std::endl;
		}else{
			std::cout << "Verify passed. " << mismatch_count << " errors" << std::endl;
		}
		std::cout << "Rate: Tx " << format_rate(wr_rate) << ". Rx " << format_rate(rd_rate) << " (Tx " << wr_xferred_len << " bytes" << " in " << wr_elapsed << " us" << ". Rx " << rd_xferred_len << " bytes" << " in " << rd_elapsed << " us)" << std::endl;
	}
}

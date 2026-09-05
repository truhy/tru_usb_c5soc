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

#include "cmd_line.h"
#include "to_string.h"
#include "tru_exception.h"
#include <iostream>

void process_req(my_params &params){
	serial_com serial_com;

	serial_com.open_handle(params.dev_path);

	std::cout << "Setting com port timeout" << std::endl;
	serial_com.set_timeout(params.timeout_ms);

	std::cout << "Setting com port parameters" << std::endl;
	serial_com.set_params(params.baud_rate, 8, NOPARITY, ONESTOPBIT, false);
	
	//serial_com.purge();

	switch(params.cmdl_code){
		case CMDL_TX_TEST: tx_test_req(serial_com, params.tx_data_len, params.rx_data_len, params.num_runs); break;
		case CMDL_ECHO_TEST: echo_test_req(serial_com, params.tx_data_len, params.rx_data_len, params.num_runs); break;
	}
}

int main(int arg_c, char *const arg_v[]){
	my_params params;

	try{
		if(arg_c > 1){
			parse_params(arg_c, arg_v, params);
			process_req(params);
		}else{
			usage(arg_v[0]);
		}
	}catch(tru_exception &ex){
		std::cout << "Error: " << ex.get_error() << std::endl;
		return ex.get_code();
	}

	return 0;
}

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
#include "tru_exception.h"
#include "tru_buffer.h"
#include "hp_time_elapsed.h"
#include <libusb.h>
#include <cstdint>
#include <iostream>
#include <format>

#define VENDOR_ID  0x1209
#define PRODUCT_ID 0x0003

#define IE_CHOICE            1
#define OE_CHOICE            1
#define INTERFACE_CHOICE     0
#define INTERFACE_ALT_CHOICE 0
#define DEV_EXPECTED_RX_LEN  0xffffffffUL

my_params params;

static void read_dev_strings(libusb_device_handle *handle, libusb_device_descriptor *desc){
	unsigned char manufacturer[255];
	unsigned char product[255];
	unsigned char serial[255];
	int rc;

	rc = libusb_get_string_descriptor_ascii(handle, desc->iManufacturer, manufacturer, 255);
	if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_get_string_descriptor_ascii() failed", libusb_strerror(rc));

	rc = libusb_get_string_descriptor_ascii(handle, desc->iProduct, product, 255);
	if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_get_string_descriptor_ascii() failed", libusb_strerror(rc));

	rc = libusb_get_string_descriptor_ascii(handle, desc->iSerialNumber, serial, 255);
	if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_get_string_descriptor_ascii() failed", libusb_strerror(rc));

	std::cout << std::format("Manufacturer: {0}", std::string((char *)manufacturer)) << std::endl;
	std::cout << std::format("Product     : {0}", std::string((char *)product)) << std::endl;
	std::cout << std::format("Serial      : {0}", std::string((char *)serial)) << std::endl;
}

static libusb_device_handle *find_open_dev(libusb_context *ctx){
	libusb_device_handle *handle = NULL;
	libusb_device **list = NULL;
	int rc;

	ssize_t count = libusb_get_device_list(ctx, &list);
	for(ssize_t idx = 0; idx < count; idx++){
		libusb_device *dev = list[idx];

		struct libusb_device_descriptor desc;
		rc = libusb_get_device_descriptor(dev, &desc);
		if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_get_device_descriptor() failed", libusb_strerror(rc));

		if(desc.idVendor == VENDOR_ID && desc.idProduct == PRODUCT_ID){
			std::cout << std::format("VID PID: 0x{0:04x} 0x{1:04x}", desc.idVendor, desc.idProduct) << std::endl;
			std::cout << std::format("EP0 MPS: {0} (IN & OUT)", desc.bMaxPacketSize0) << std::endl;

			rc = libusb_open(dev, &handle);
			if(rc){
				libusb_free_device_list(list, 1);
				throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_open() failed", libusb_strerror(rc));
			}

			read_dev_strings(handle, &desc);

			break;  // Exit for loop
		}
	}

	libusb_free_device_list(list, 1);

	return handle;
}

static const libusb_endpoint_descriptor *find_ep_desc(libusb_device_handle *handle, int altsetting_idx, uint8_t ep_addr){
	int rc;

	libusb_device *dev = libusb_get_device(handle);
	if(dev == NULL) throw tru_exception(__func__, TRU_EXCEPT_SRC_VEN, 1, "libusb_get_device() failed", "");

	struct libusb_config_descriptor *config = NULL;
	rc = libusb_get_active_config_descriptor(dev, &config);
	if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_get_active_config_descriptor() failed", libusb_strerror(rc));

	for(int intf_num = 0; intf_num < config->bNumInterfaces; intf_num++){
		for(int alt_num = 0; alt_num < config->interface[intf_num].num_altsetting; alt_num++){
			if(config->interface[intf_num].altsetting[alt_num].bAlternateSetting == altsetting_idx){
				for(int ep_num = 0; ep_num < config->interface[intf_num].altsetting[alt_num].bNumEndpoints; ep_num++){
					if(config->interface[intf_num].altsetting[alt_num].endpoint[ep_num].bEndpointAddress == ep_addr){
						return config->interface[intf_num].altsetting[alt_num].endpoint + ep_num;
					}
				}
			}
		}
	}

	return NULL;
}

static void le_u32_to_buf(void *dst, uint32_t value){
	((uint8_t *)dst)[0] = value;
	((uint8_t *)dst)[1] = value >> 8;
	((uint8_t *)dst)[2] = value >> 16;
	((uint8_t *)dst)[3] = value >> 24;
}

#define KB 1000.0f
#define MB 1000000.0f

static std::string format_rate(double rate){
	if(rate < (float)KB){
		return std::format("{0:.2f} B/s", rate);
	}else if(rate < (float)MB){
		return std::format("{0:.2f} KB/s", rate / KB);
	}else{
		return std::format("{0:.2f} MB/s", rate / MB);
	}
}

static void bulk_xfer_rate_test(libusb_context *ctx, libusb_device_handle *handle, uint32_t write_len, uint32_t read_len){
	uint32_t buf_len = (write_len > read_len) ? write_len : read_len;
	tru_buffer data(buf_len);  // Allocate buffer
	int xferred;
	int total_xferred;
	int rc;
	hp_time_elapsed timer;
	uint32_t remain;
	uint32_t read_len_max;
	double rate_write;
	double avg_write = 0;
	double min_write = 0;
	double max_write = 0;
	double rate_read;
	double avg_read = 0;
	double min_read = 0;
	double max_read = 0;
	uint32_t mismatch_count = 0;
	uint8_t test_count = 0;

	std::cout << std::endl << "Test settings:" << std::endl;
	std::cout << std::format("OUT EP{0} transfer len: {1} bytes", OE_CHOICE, params.wlen) << std::endl;
	std::cout << std::format("IN  EP{0} transfer len: {1} bytes", IE_CHOICE, params.rlen) << std::endl;
	std::cout << std::format("Number of runs: {0}", params.num_runs) << std::endl << std::endl;

	/*
	// Test selecting interface
	rc = libusb_set_interface_alt_setting(handle, INTERFACE_CHOICE, 0);
	if(rc < 0) throw tru_exception(__func__, rc, "libusb_set_interface_alt_setting() failed");
	*/

	std::cout << "Transfer rate test:" << std::endl;
	std::cout << std::format("Endpoints: Write = OUT EP{0} Read = IN EP{1}", OE_CHOICE, IE_CHOICE) << std::endl;
	for(uint32_t i = 0; i < params.num_runs; i++){
		if(params.cmd == MSOS1_CMD_VERIFY_TEST){
			mismatch_count = 0;
			test_count = 0;
		}

		// =============
		// Setup command
		// =============

		data.buf_ptr()[0] = params.cmd;  // Command code
		le_u32_to_buf(data.buf_ptr() + 1, read_len);  // Data read length

		// =======================
		// Write command to device
		// =======================

		total_xferred = 0;

		timer.set_begin_point();
		rc = libusb_bulk_transfer(handle, OE_CHOICE | LIBUSB_ENDPOINT_OUT, data.buf_ptr(), write_len, &xferred, params.timeout_ms);
		if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_bulk_transfer() write failed", libusb_strerror(rc));
		total_xferred += xferred;

		// Determine if we need to end the write transfer early
		// If transferring less than device expected read len we need to send a ZLP
		if(write_len < DEV_EXPECTED_RX_LEN){
			rc = libusb_bulk_transfer(handle, OE_CHOICE | LIBUSB_ENDPOINT_OUT, nullptr, 0, &xferred, params.timeout_ms);
			if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_bulk_transfer() write failed", libusb_strerror(rc));
		}

		timer.set_end_point();
		rate_write = (timer.elapsed_ms() > 0) ? (double)total_xferred * 1000 / timer.elapsed_ms() : 0;
		avg_write = (i * avg_write + rate_write) / (i + 1);
		if(i == 0 || rate_write < min_write) min_write = rate_write;
		if(rate_write > max_write) max_write = rate_write;

		// =====================
		// Read data from device
		// =====================

		total_xferred = 0;
		remain = read_len;

		timer.set_begin_point();
		while(remain){
			read_len_max = (remain > buf_len) ? buf_len : remain;
			rc = libusb_bulk_transfer(handle, IE_CHOICE | LIBUSB_ENDPOINT_IN, data.buf_ptr(), read_len_max, &xferred, params.timeout_ms);
			if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_bulk_transfer() read failed", libusb_strerror(rc));

			if(params.cmd == MSOS1_CMD_VERIFY_TEST){
				for(int i = 0; i < xferred; i++){
					if(data.buf_ptr()[i] != test_count) mismatch_count++;
					test_count++;
				}
			}

			total_xferred += xferred;
			remain -= xferred;
		}
		timer.set_end_point();
		rate_read = (timer.elapsed_ms() > 0) ? (double)total_xferred * 1000 / timer.elapsed_ms() : 0;
		avg_read = (i * avg_read + rate_read) / (i + 1);
		if(i == 0 || rate_read < min_read) min_read = rate_read;
		if(rate_read > max_read) max_read = rate_read;

		if(params.cmd == MSOS1_CMD_VERIFY_TEST){
			if(mismatch_count){
				std::cout << std::format("Run {0:3d}: {1} {2}", i, format_rate(rate_write), format_rate(rate_read)) << " Verify failed. " << mismatch_count << " errors" << std::endl;
			}else{
				std::cout << std::format("Run {0:3d}: {1} {2}", i, format_rate(rate_write), format_rate(rate_read)) << " Verify passed. " << mismatch_count << " errors" << std::endl;
			}
		}else{
			std::cout << std::format("Run {0:3d}: {1} {2}", i, format_rate(rate_write), format_rate(rate_read)) << std::endl;
		}
	}

	std::cout << "Summary:" << std::endl;
	std::cout << std::format("Write avg: {0} (min: {1}, max: {2})", format_rate(avg_write), format_rate(min_write), format_rate(max_write)) << std::endl;
	std::cout << std::format("Read  avg: {0} (min: {1}, max: {2})", format_rate(avg_read), format_rate(min_read), format_rate(max_read)) << std::endl;
}

static std::string transfer_type(uint8_t attributes){
	switch(attributes & 0x03){
		case LIBUSB_ENDPOINT_TRANSFER_TYPE_CONTROL: return "Control"; break;
		case LIBUSB_ENDPOINT_TRANSFER_TYPE_ISOCHRONOUS: return "Isochronous"; break;
		case LIBUSB_ENDPOINT_TRANSFER_TYPE_BULK: return "Bulk"; break;
		case LIBUSB_ENDPOINT_TRANSFER_TYPE_INTERRUPT: return "Interrupt"; break;
	}
	return "Unknown";
}

static void test(libusb_context *ctx, libusb_device_handle *handle){
	int rc;

	params.iep_desc = find_ep_desc(handle, INTERFACE_ALT_CHOICE, IE_CHOICE | LIBUSB_ENDPOINT_IN);
	if(params.iep_desc == NULL) throw tru_exception(__func__, TRU_EXCEPT_SRC_VEN, 1, "Failed to find in endpoint descriptor", "");

	params.oep_desc = find_ep_desc(handle, INTERFACE_ALT_CHOICE, OE_CHOICE | LIBUSB_ENDPOINT_OUT);
	if(params.oep_desc == NULL) throw tru_exception(__func__, TRU_EXCEPT_SRC_VEN, 1, "Failed to find out endpoint descriptor", "");

	std::cout << std::format("IN  EP{0} transfer type: {1}", IE_CHOICE, transfer_type(params.iep_desc->bmAttributes)) << std::endl;
	std::cout << std::format("OUT EP{0} transfer type: {1}", OE_CHOICE, transfer_type(params.oep_desc->bmAttributes)) << std::endl;
	std::cout << std::format("IN  EP{0} MPS: {1}\n", IE_CHOICE, params.iep_desc->wMaxPacketSize);
	std::cout << std::format("OUT EP{0} MPS: {1}\n", OE_CHOICE, params.oep_desc->wMaxPacketSize);

	if(libusb_kernel_driver_active(handle, INTERFACE_CHOICE) == 1){
		rc = libusb_detach_kernel_driver(handle, INTERFACE_CHOICE); // detach driver
		if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_detach_kernel_driver() failed", libusb_strerror(rc));
	}

	rc = libusb_claim_interface(handle, INTERFACE_CHOICE);
	if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_claim_interface() failed", libusb_strerror(rc));

	bulk_xfer_rate_test(ctx, handle, params.wlen, params.rlen);
}

static void clean_up(libusb_context *ctx, libusb_device_handle *handle){
	int rc;

	if(handle){
		try{
			rc = libusb_release_interface(handle, 0);
			if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_release_interface() failed", libusb_strerror(rc));
		}catch(tru_exception &ex){
			std::cout << "Error: " << ex.get_error() << std::endl;
		}
	}

	if(ctx) libusb_exit(ctx);
}

int main(int arg_c, char *const arg_v[]){
	int rc = 0;
	libusb_context *ctx = NULL;
	libusb_device_handle *handle = NULL;

	try{
		if(arg_c > 1){
			parse_params(arg_c, arg_v, params);

			if(params.cmd == MSOS1_CMD_NONE) throw tru_exception(__func__, TRU_EXCEPT_SRC_VEN, rc, "Command line error", "No command specified");

			int rc = libusb_init(&ctx);
			if(rc < 0) throw tru_exception(__func__, TRU_EXCEPT_SRC_RTL, rc, "libusb_init() failed", libusb_strerror(rc));

			handle = find_open_dev(ctx);
			if(handle == NULL) throw tru_exception(__func__, TRU_EXCEPT_SRC_VEN, 1, "Device not found", std::format("VID PID: 0x{0:04x} 0x{1:04x}", VENDOR_ID, PRODUCT_ID));

			test(ctx, handle);
		}else{
			usage(arg_v[0]);
		}
	}catch(tru_exception &ex){
		std::cout << "Error: " << ex.get_error() << std::endl;
		rc = ex.get_code();
	}

	clean_up(ctx, handle);

	return rc;
}

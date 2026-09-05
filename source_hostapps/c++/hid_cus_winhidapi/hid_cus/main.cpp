/*
	MIT License

	Copyright (c) 2020 Truong Hy

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

	Version: 20260819
	Platform: Windows only
	
	Description:
	Uses Windows built-in HID API to read/write a vendor USB HID device.
*/

#include "cmd_line_and_vars.h"
#include "my_usb_enum.h"
#include "my_usb_dev.h"
#include "my_usb_request.h"
#include <stdio.h>

bool start(cl_my_params *my_params){
	cl_usb_dev usb_dev;
	cl_usb_hid_enum usb_hid_enum;

	if(my_params->cmdl_req == CMDL_REQ_DEV_LIST){
		usb_hid_enum.list_dev();
	}else{
		if(my_params->dev_path.size() == 0){
			if(my_params->product_name.size() > 0){
				// Find USB HID Windows device path by device name string
				if(!usb_hid_enum.find_hid_dev_path_by_product_name(my_params->product_name, true, my_params->dev_path)){
					printf("Error: Could not find device: %s\n", my_params->product_name.c_str());
					return false;
				}
			}else{
				// Find USB HID Windows device path by VID and PID
				if(!usb_hid_enum.find_hid_dev_path_by_vid_pid(my_params->vid, my_params->pid, true, my_params->dev_path)){
					printf("Error: Could not find device: VID PID: 0x%04x 0x%04x\n", my_params->vid, my_params->pid);
					return false;
				}
			}
		}
		
		printf("Attempting to open device: %s\n", my_params->dev_path.c_str());

		// Open USB device for read
		if(!usb_dev.open_read_handle(my_params->dev_path, true)){
			printf("Error: Could not open device for read mode\n");
			return false;
		}

		// Open USB device for write
		if(!usb_dev.open_write_handle(my_params->dev_path, true)){
			printf("Error: Could not open device for write mode\n");
			return false;
		}

		

		// Process a command
		switch(my_params->cmdl_req){
			case CMDL_REQ_REPORT: { process_report(my_params, &usb_dev); break; }
		}
	}

	return true;
}

int main(int arg_c, char *arg_v[]){
	cl_my_params my_params;

	if(arg_c > 1){
		parse_params(arg_c, arg_v, &my_params);
		start(&my_params);
	}else{
		usage(arg_v[0]);
	}

	return 0;
}

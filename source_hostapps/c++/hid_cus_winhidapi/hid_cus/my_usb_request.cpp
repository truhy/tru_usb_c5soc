/*
	Notes:

	We need to include 1 extra byte to the transmit and receive length for the HID driver, but
	(to be confirmed), it discards it and actually sends 1 less.

	I consider this a bug when transmitting, the driver always replaces the last byte with a zero,
	and so the device will always receive the last byte as 00, meaning you can't actually send the
	last byte!
*/

#include "my_usb_request.h"

void disp_msg_as_ascii(char *msg, int len){
	for(int i = 0; i < len; ++i){
		if((msg[i] >= 32 ) && (msg[i] <= 126)){
			printf("%c", msg[i]);
		}else{
			printf(" ");
		}
	}
}

void disp_msg_as_hex(unsigned char *msg, int len){
	for(int i = 0; i < len; ++i){
		printf("%2.2x", msg[i]);
	}
}

void process_report(cl_my_params *my_params, cl_usb_dev *usb_dev){
	cl_my_buf xferbuf;
	DWORD bytes_written;
	DWORD bytes_read;
	
	xferbuf.alloc_buf((my_params->wlen > my_params->rlen) ? my_params->wlen + REPORTID_PADDING : my_params->rlen + REPORTID_PADDING);
	printf("Tx/rx report:\n");

	// Transmit zeroes
	memset(xferbuf.get_buf(), 0, xferbuf.len());
	xferbuf.get_buf()[0] = 0x00;  // ReportID
	//m_buf.buf()[xferbuf.len() - 1] = 0;  // This last byte will be replaced by the HID driver!
	printf("Tx (hex): ");
	disp_msg_as_hex(xferbuf.get_buf() + REPORTID_PADDING, my_params->wlen);  // Exclude the Report ID
	printf("\n");
	if(!usb_dev->write_usb_async(xferbuf.get_buf(), my_params->wlen + REPORTID_PADDING, &bytes_written, my_params->usb_timeout_ms)){
		printf("Error: %s\n", m_error_usb_write);
		return;
	}

	// Receive
	memset(xferbuf.get_buf(), 0, xferbuf.len());
	if(usb_dev->read_usb_async(xferbuf.get_buf(), my_params->rlen + REPORTID_PADDING, &bytes_read, my_params->usb_timeout_ms)){
		printf("Rx (hex): ");
		disp_msg_as_hex(xferbuf.get_buf() + REPORTID_PADDING, my_params->rlen);  // Exclude the Report ID
		//printf("\nRx (ASCII): ");
		//disp_msg_as_ascii((char*)xferbuf.get_buf() + REPORTID_PADDING, my_params->rlen);  // Exclude the Report ID
		printf("\n");
	}else{
		printf("Error: %s\n", m_error_usb_read);
		return;
	}
}

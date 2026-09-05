/*
	Created on: 31 Dec 2022
	Author: Truong Hy

	Sample definition that implements a custom HID class device.

	This example demonstrates using 1x dedicated interrupt end-point and EP0
	control endpoint with setup command to transfer reports.

	This creates a vendor (custom reports) HID device with the following features:
		all speeds:
			2 reports:
				- INPUT report of 64 bytes
				- OUTPUT report of 64 bytes
		high speed:
			1 end-point for sending INPUT report:
				- IN EP1, interrupt data flow, 1024 max packet size (for INPUT report)
				- OUT EP0, control data flow, 64 max packet size (for OUTPUT report)
		full speed:
			1 end-point for sending INPUT report:
				- IN EP1, interrupt data flow, 64 max packet size (for INPUT report)
				- OUT EP0, control data flow, 64 max packet size (for OUTPUT report)
		low speed:
			1 end-point for sending INPUT report:
				- IN EP1, interrupt data flow, 8 max packet size (for INPUT report)
				- OUT EP0, control data flow, 8 max packet size (for OUTPUT report)

	The enumerated USB speed determines which of these descriptors is selected.

	Since there is only 1 end-point defined the host will need to send the
	OUTPUT report using the default control OUT EP0 using the HID setup command
	request "SET_REPORT".

	Notes:
		Host = for example your PC
		Data transfer direction is in the host's point of view, for example:
			- IN EP1 = Hosts input End-Point 1 for data transfers from device to
			  host
			- OUT EP0 = Hosts output End-Point 0 for data transfers from host to
			  device
			- INPUT report = a report going to the host, i.e. the host receives
			  this from the device
			- OUTPUT report = a report going out of the host, i.e. the host
			  sends this to the device
*/

#ifndef HID_CUSTOM_CTL_DEF_H
#define HID_CUSTOM_CTL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb/dclass/tru_usb_hid.h"
#include "tru_iom.h"
#include <stdint.h>

#define HID_CUS_CTL_HS_DESC_ENABLE 1

// VID PID for open-source use from https://pid.codes/pids/
#define HID_CUS_CTL_DEF_VID 0x1209
#define HID_CUS_CTL_DEF_PID 0x0001
#define HID_CUS_CTL_DEF_VER 0x0001

#define HID_CUS_CTL_USB_VER 0x0200
//#define HID_CUS_CTL_USB_VER 0x0110

#define HID_CUS_CTL_IN_REPORT_EPNUM          1
#define HID_CUS_CTL_REPORT_ID                0
#define HID_CUS_CTL_INPUT_REPORT_VARSIZE     8
#define HID_CUS_CTL_INPUT_REPORT_VARCOUNT    64
#define HID_CUS_CTL_INPUT_REPORT_SIZE_BITS   (HID_CUS_CTL_INPUT_REPORT_VARCOUNT*HID_CUS_CTL_INPUT_REPORT_VARSIZE)
#define HID_CUS_CTL_INPUT_REPORT_SIZE_BYTES  (INT_ALIGN_UP(HID_CUS_CTL_INPUT_REPORT_SIZE_BITS, 8)/8)
#define HID_CUS_CTL_OUTPUT_REPORT_VARSIZE    HID_CUS_CTL_INPUT_REPORT_VARSIZE
#define HID_CUS_CTL_OUTPUT_REPORT_VARCOUNT   64
#define HID_CUS_CTL_OUTPUT_REPORT_SIZE_BITS  (HID_CUS_CTL_OUTPUT_REPORT_VARCOUNT*HID_CUS_CTL_OUTPUT_REPORT_VARSIZE)
#define HID_CUS_CTL_OUTPUT_REPORT_SIZE_BYTES (INT_ALIGN_UP(HID_CUS_CTL_OUTPUT_REPORT_SIZE_BITS, 8)/8)

tru_usb_hid_pd_info_t *get_hid_cus_ctl_pd_info(void);

#ifdef __cplusplus
}
#endif

#endif

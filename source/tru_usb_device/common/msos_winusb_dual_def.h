/*
	Created on: 22 Apr 2023
	Author: Truong Hy

	Sample definition that implements a MSOS (Microsoft OS) class device to
	create a WinUSB device.  The compatibility string is set to "WinUSB".

	MSOS is a custom vendor USB class defined by Microsoft.  It is like a
	wrapper class, which presents itself as a MSOS device, but internally it is
	a generic WinUSB device.

	This device class enables Windows 10/11 to automatically install the WinUSB
	driver as soon as it is plugged in.  This makes it appear as a driver less
	device.  We can make generic USB function calls to it using the MS
	WinUSB (from WDK) or the open source libusb library.

	This definition creates a MSOS WinUSB device with the following descriptors:
		high speed:
			2x pair of end-points:
				IN EP1, bulk flow, 512 max packet size
				OUT EP1, bulk flow, 512 max packet size
				IN EP2, bulk flow, 512 max packet size
				OUT EP2, bulk flow, 512 max packet size
		full speed:
			2x pair of end-points:
				IN EP1, bulk flow, 64 max packet size
				OUT EP1, bulk flow, 64 max packet size
				IN EP2, bulk flow, 64 max packet size
				OUT EP2, bulk flow, 64 max packet size
		low speed:
			2x pair of end-points:
				IN EP1, interrupt flow, 8 max packet size
				OUT EP1, interrupt flow, 8 max packet size
				IN EP2, interrupt flow, 8 max packet size
				OUT EP2, interrupt flow, 8 max packet size

	The enumerated USB speed determines which of these descriptors is selected.

	Note: low speed does not support Bulk data flow so as alternative Interrupt
	data flow is configured for the data endpoints

	Normally, only 2 endpoints IN/OUT is sufficient, but for demonstration
	purposes, 2 endpoints are created to perform switch tests.
*/

#ifndef MSOS_WINUSB_DUAL_DEF_H
#define MSOS_WINUSB_DUAL_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb/dclass/tru_usb_msos.h"

#define MSOS_WINUSB_DUAL_HS_DESC_ENABLE 1

// VID PID for open-source use from https://pid.codes/pids/
#define MSOS_WINUSB_DUAL_DEF_VID 0x1209
#define MSOS_WINUSB_DUAL_DEF_PID 0x0003
#define MSOS_WINUSB_DUAL_DEF_VER 0x0001

#define MSOS_WINUSB_DUAL_USB_VER 0x0200
//#define MSOS_WINUSB_DUAL_USB_VER 0x0110  // 0x0110 = USB 1.1 will not work with MSOS

// Two pipes
#define MSOS_WINUSB_DUAL_P0_TXD_EPNUM 1
#define MSOS_WINUSB_DUAL_P0_RXD_EPNUM 1
#define MSOS_WINUSB_DUAL_P1_TXD_EPNUM 2
#define MSOS_WINUSB_DUAL_P1_RXD_EPNUM 2

tru_usb_msos_pd_info_t *get_msos_winusb_dual_pd_info(void);

#ifdef __cplusplus
}
#endif

#endif

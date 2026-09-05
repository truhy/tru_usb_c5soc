/*
	MIT License

	Copyright (c) 2025 Truong Hy

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

	Version: 20251212
	Target : ARM Cortex-A9 on the DE10-Nano Kit development board (Altera
	         Cyclone V SoC FPGA)
	Type   : Stand-alone C application

	Demonstrates the HPS USB2.0 OTG controller (Synopsys DWC2) using trulib
	custom standalone library.  Currently only device (peripheral) mode is
	supported.

	Various USB-UART debug messages can be enabled in the tru_user_config.h
	file.

	Notable features:
	- Interrupt driven
	- Supports all three modes:
	  1. Slave (manual FIFO)
	  2. Standard DMA
	  3. Scatter Gather DMA (aka descriptor list DMA)
	- Callbacks run inside the interrupt so don't create no long running code or
	  wait loops.  Currently, I do not have the time to add in task support,
	  such as FreeRTOS
	- Builtin chunking which enables fixed size data buffer to process large
	  transfers
	- MSOS WinUSB bulk mode throughput tests shows a whopping 47MBytes/s
	  (376Mbps) peak in receive and transmit using 1MB transfers in DMA mode

	Open source libraries used:
	- Arm CMSIS v6 (Core only)
	- Newlib (included with the GNU Toolchain for Arm)
*/

// Trulib includes
#include "tru_config.h"

// USB example demo includes.  Uncomment only one header at a time
#include "c5soc/usb_examples/device/hid_gamepad1_c5soc.h"
//#include "c5soc/usb_examples/device/hid_custom_c5soc.h"
//#include "c5soc/usb_examples/device/hid_custom_ctl_c5soc.h"
//#include "c5soc/usb_examples/device/cdcacm_c5soc.h"
//#include "c5soc/usb_examples/device/cdcacm_rr_c5soc.h"
//#include "c5soc/usb_examples/device/cdcacm_rr_multi_c5soc.h"
//#include "c5soc/usb_examples/device/msos_winusb_c5soc.h"
//#include "c5soc/usb_examples/device/msos_winusb_dual_c5soc.h"

// CMSIS includes
#include "RTE_Components.h"
#include CMSIS_device_header

int main(int argc, char **argv){
	tru_bsp_init();
	tru_bsp_usb_init(TRU_USB_U1_BASE, IRQ_MODE_CPU_0, GIC_IRQ_PRIORITY_LEVEL29_7);

	#if defined(HID_GAMEPAD1_H)
		hid_gamepad1_init_app();
	#elif defined(HID_CUSTOM_H)
		hid_cus_init_app();
	#elif defined(HID_CUSTOM_CTL_H)
		hid_cus_ctl_init_app();
	#elif defined(CDCACM_H)
		cdcacm_init_app();
	#elif defined(CDCACM_RR_H)
		cdcacm_rr_init_app();
	#elif defined(CDCACM_RR_MULTI_H)
		cdcacm_rr_multi_init_app();
	#elif defined(MSOS_WINUSB_H)
		msos_winusb_init_app();
	#elif defined(MSOS_WINUSB_DUAL_H)
		msos_winusb_dual_init_app();
	#else
		#error "No demo selected!  Uncomment a demo header"
	#endif

	while(1);

	#if defined(HID_GAMEPAD1_H)
		hid_gamepad1_deinit_app();
	#elif defined(HID_CUS_H)
		hid_cus_deinit_app();
	#elif defined(HID_CUS_CTL_H)
		hid_cus_ctl_deinit_app();
	#elif defined(CDCACM_H)
		cdcacm_deinit_app();
	#elif defined(CDCACM_RR_H)
		cdcacm_rr_deinit_app();
	#elif defined(CDCACM_RR_MULTI_H)
		cdcacm_rr_multi_deinit_app();
	#elif defined(MSOS_WINUSB_H)
		msos_winusb_deinit_app();
	#elif defined(MSOS_WINUSB_DUAL_H)
		msos_winusb_dual_deinit_app();
	#endif

	tru_bsp_usb_deinit(TRU_USB_U1_BASE);
	tru_bsp_deinit();

	return 0;
}

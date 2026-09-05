/*
	Created on: 04 Mar 2023
	Author: Truong Hy

	Sample definition that implements a CDC-ACM class device to create a single
	standard asynchronous serial port device, aka virtual COM port (VCP)
	device.

	Following descriptors are implemented:
		high speed:
			end-points:
				- notification: IN EP1, interrupt flow, 1024 max packet size
				- data:         IN EP2, bulk flow, 512 max packet size
				- data:         OUT EP2, bulk flow, 512 max packet size
		full speed:
			end-points:
				- notification: IN EP1, interrupt flow, 64 max packet size
				- data:         IN EP2, bulk flow, 64 max packet size
				- data:         OUT EP2, bulk flow, 64 max packet size
		low speed:
			end-points:
				- notification: IN EP1, interrupt flow, 8 max packet size
				- data:         IN EP2, interrupt flow, 8 max packet size
				- data:         OUT EP2, interrupt flow, 8 max packet size

	The enumerated USB speed determines which of these descriptors is selected.

	Note: low speed does not support Bulk data flow so as alternative Interrupt
	data flow is configured for the data endpoints

	IN EP1 is unused but is required, and is for the device to send Management
	Element Notifications.  IN EP2 and OUT EP2 is for the serial data transfers.

	Legend:
		CDC = Communications Device Class
		ACM = Abstract Control Model (this supports virtual serial COM)

	Notes:
		Host = for example your PC
		Data transfer direction is in the host's point of view, for example:
			- IN EP0 = Hosts input End-Point 0 for data transfers from device to
			  host
			- OUT EP0 = Hosts output End-Point 0 for data transfers from host to
			  device

	References:
		USB 2.0 base specification (usb_20_20240927.zip):
			- usb_20.pdf
		USB CDC 1.2 specification (CDC1.2_WMC1.1_012011.zip):
			- CDC120-20101103-track.pdf
			- PSTN120.pdf
*/

#ifndef CDCACM_RR_DEF_H
#define CDCACM_RR_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb/dclass/tru_usb_cdc.h"
#include <stdint.h>

#define CDCACM_RR_HS_DESC_ENABLE 1

/*
THe USB2.0 specification end of a USB transfer and the ZLP
==========================================================

ZLP is a specific packet which has zero data payload for ending a
transmission, known as Zero Length Packet and is one of the problem in Windows
serial driver (usbser.sys).  Let's look at the USB 2.0 specification.  In
bulk data flow, the packet size defines these constraints (quoting from the
USB 2.0 spec pdf):
A bulk transfer is complete when the endpoint does one of the following:
	1. Has transferred exactly the amount of data expected
	2. Transfers a packet with a payload size less than wMaxPacketSize or
	   transfers a zero-length packet

This means we send a ZLP when the transferred size is less than the amount of
data expected and the packet sent equals the maximum packet size.

Windows and Linux CDC-ACM serial driver problems
------------------------------------------------
Problem 1 (Device transmit): On Windows, the host does not want a ZLP when we
transfer data of length that is multiple of 4096 bytes, but because this
is a multiple of the MPS (Maximum Packet Size) a ZLP should be sent to end the
transmission.  Sending a ZLP to the host will cause this device to hang because
it stays waiting for the transfer complete interrupt, which will never happen
because Windows does not send the EP OUT token to accept the ZLP.  Depending
on your GetCommTimeouts() and SetCommTimeouts() settings (Win32 API functions),
Windows host application will:
	- timed out, then you lose data
	- wait forever until a ZLP or more data is received, no data loss
Windows USB serial driver (usbser.sys) always schedules URB requests (driver
to kernel requests) with 4096 bytes so it expects to receive 4K chunks, but
because our transfer is a stream consisting of multiple packets, the expected
length will be our total transfer size rounded up to the nearest 4096 bytes.

Workaround: Don't send a ZLP on transfers that are a multiple of 4K.  This
problem is not on Linux but it tolerates this workaround.
------------------------------------------------------------------------------
Problem 2 (Device transmit): On Linux and Windows.  The default driver will
discard overflowed data if the serial port is opened and we transmit too early
or if the host application is not able to consume the stream fast enough.  In
bidirectional mode when we receive and transmit at the same time we will be
transmitting too early (host hasn't even started a read), and if we send more
than one USB MPS packet some packets are discarded by the host driver.  The
host application read function will still be waiting for those discarded
packets because it has no idea the driver discarded some!  This does not seem
to be an issue when operating in unidirectional mode, perhaps because the host
shortly starts a read and is able to consume in time, this is demonstrated by
my request-response demo.  This issue is time and buffer sensitive, which lead
to reports that is working for some but not for others, simply because users
are using different serial configurations and transfer sizes.

Workaround: For bidirectional mode:
  - in high-speed send only a maximum of 512 bytes for each host read
  - in full-speed send only a maximum of 64 bytes for each host read
  - in low-speed bulk mode is not supported
------------------------------------------------------------------------------
Problem 3 (Device receive): On Linux and Windows, the host does not send a ZLP
when the transfer is multiple of the MPS (perhaps host never sends ZLP?).
When the device receives a transfer that is multiple of the MPS we expect the
host to send a ZLP as required by USB spec but no ZLP is sent.  This causes
the device to hang because it is waiting for a transfer complete interrupt on
the ZLP.

Workaround: Limit the EP transfer size to the MPS, which creates a transfer
complete interrupt on every received transfer.  This works because the
transfer is now always a short transfer or is exactly the expected transfer
size so we will never expect to wait for a ZLP.
------------------------------------------------------------------------------
Acronyms: ZLP = Zero Length Packet, EP = EndPoint, MPS = Maximum Packet Size
*/
#define CDCACM_RR_WIN_QUIRK_DEV_NOZLP4K  1  // Don't send a ZLP on 4K multiple transfers (required for Windows, tolerated on Linux)
#define CDCACM_RR_WIN_QUIRK_DEV_FORCEZLP 1  // Always send a ZLP (disabled if NOZLP4K is enabled).  Working on Linux but not Windows
#define CDCACM_RR_WIN_QUIRK_HST_NOZLP    1  // Limit receive to one MPS packet only (required for Linux and Windows)

// VID PID for open-source use from https://pid.codes/pids/
#define CDCACM_RR_VID 0x1209
#define CDCACM_RR_PID 0x0002
#define CDCACM_RR_VER 0x0001

#define CDCACM_RR_USB_VER 0x0200
//#define CDCACM_RR_USB_VER 0x0110

#define CDCACM_RR_NTF_ITFNUM 0
#define CDCACM_RR_NTF_EPNUM  1
#define CDCACM_RR_DAT_ITFNUM 1
#define CDCACM_RR_TXD_EPNUM  2
#define CDCACM_RR_RXD_EPNUM  2

#define CDCACM_RR_DEFAULT_BIT_RATE    128000
#define CDCACM_RR_DEFAULT_CHAR_FORMAT TRU_USB_CDC_LINECODING_STOPBITS_ONE
#define CDCACM_RR_DEFAULT_PARITY_TYPE TRU_USB_CDC_LINECODING_PARITY_NONE
#define CDCACM_RR_DEFAULT_DATA_BITS   8

tru_usb_cdc_pd_info_t *get_cdcacm_rr_pd_info(void);

#ifdef __cplusplus
}
#endif

#endif

/*
	Created on: 15 Nov 2024
	Author: Truong Hy

	Sample definition that implements a multiple standard asynchronous serial
	port device.  Multiple CDC-ACM device classes are combined together into
	a single Multi-Interface Function (MIF) device class, made possible using
	the Interface Association Descriptors (IAD).

	Number of serial ports:
	There is a define for the parameter to set the number desired serial ports.
	Each serial port requires 3x endpoints:
	- 1x notification IN endpoint,
	- 1x TX IN endpoint and
	- 1x RX OUT endpoint.

	The maximum number of serial ports is (rounding down):
	max_serial_ports = (max_endpoints_pairs - 1) / 2

	Example:
	The DE10-Nano Cyclone V SoC FPGA DWC2 OTG controller supports 16 endpoint
	pairs (IN/OUT), so the maximum number of serial ports is:
	max_serial_ports = (16 - 1) / 2 = 7

	References:
		USB 2.0 base specification (usb_20_20240927.zip):
			- usb_20.pdf
		USB CDC 1.2 specification (CDC1.2_WMC1.1_012011.zip):
			- CDC120-20101103-track.pdf
			- PSTN120.pdf
		USB Interface Association Descriptor Device Class and Use Model (IAD):
			- iadclasscode_r10.pdf
*/

#ifndef CDCACM_RR_MULTI_DEF_H
#define CDCACM_RR_MULTI_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb/dclass/tru_usb_cdc.h"
#include <stdint.h>

#define CDCACM_RR_MULTI_HS_DESC_ENABLE 1

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
#define CDCACM_RR_MULTI_WIN_QUIRK_DEV_NOZLP4K  1  // Don't send a ZLP on 4K multiple transfers (required for Windows, tolerated on Linux)
#define CDCACM_RR_MULTI_WIN_QUIRK_DEV_FORCEZLP 1  // Always send a ZLP (disabled if NOZLP4K is enabled).  Working on Linux but not Windows
#define CDCACM_RR_MULTI_WIN_QUIRK_HST_NOZLP    1  // Limit receive to one MPS packet only (required for Linux and Windows)

// VID PID for open-source use from https://pid.codes/pids/
#define CDCACM_RR_MULTI_VID 0x1209
#define CDCACM_RR_MULTI_PID 0x0002
#define CDCACM_RR_MULTI_VER 0x0002

#define CDCACM_RR_MULTI_USB_VER 0x0200
//#define CDCACM_RR_MULTI_USB_VER 0x0110

// Number of serial ports to implement
#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC
	#define CDCACM_RR_MULTI_NUM_PORTS 7
#elif defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_STM32H7
	#define CDCACM_RR_MULTI_NUM_PORTS 4
#elif defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_SG2002
	#define CDCACM_RR_MULTI_NUM_PORTS 7
#endif

#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	#define CDCACM_RR_MULTI_VCP1_NTF_ITFNUM          0
	#define CDCACM_RR_MULTI_VCP1_NTF_EPNUM           1
	#define CDCACM_RR_MULTI_VCP1_DAT_ITFNUM          1
	#define CDCACM_RR_MULTI_VCP1_TXD_EPNUM           2
	#define CDCACM_RR_MULTI_VCP1_RXD_EPNUM           2
	#define CDCACM_RR_MULTI_VCP1_DEFAULT_BIT_RATE    128000
	#define CDCACM_RR_MULTI_VCP1_DEFAULT_CHAR_FORMAT TRU_USB_CDC_LINECODING_STOPBITS_ONE
	#define CDCACM_RR_MULTI_VCP1_DEFAULT_PARITY_TYPE TRU_USB_CDC_LINECODING_PARITY_NONE
	#define CDCACM_RR_MULTI_VCP1_DEFAULT_DATA_BITS   8
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	#define CDCACM_RR_MULTI_VCP2_NTF_ITFNUM          2
	#define CDCACM_RR_MULTI_VCP2_NTF_EPNUM           3
	#define CDCACM_RR_MULTI_VCP2_DAT_ITFNUM          3
	#define CDCACM_RR_MULTI_VCP2_TXD_EPNUM           4
	#define CDCACM_RR_MULTI_VCP2_RXD_EPNUM           4
	#define CDCACM_RR_MULTI_VCP2_DEFAULT_BIT_RATE    128000
	#define CDCACM_RR_MULTI_VCP2_DEFAULT_CHAR_FORMAT TRU_USB_CDC_LINECODING_STOPBITS_ONE
	#define CDCACM_RR_MULTI_VCP2_DEFAULT_PARITY_TYPE TRU_USB_CDC_LINECODING_PARITY_NONE
	#define CDCACM_RR_MULTI_VCP2_DEFAULT_DATA_BITS   8
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	#define CDCACM_RR_MULTI_VCP3_NTF_ITFNUM          4
	#define CDCACM_RR_MULTI_VCP3_NTF_EPNUM           5
	#define CDCACM_RR_MULTI_VCP3_DAT_ITFNUM          5
	#define CDCACM_RR_MULTI_VCP3_TXD_EPNUM           6
	#define CDCACM_RR_MULTI_VCP3_RXD_EPNUM           6
	#define CDCACM_RR_MULTI_VCP3_DEFAULT_BIT_RATE    128000
	#define CDCACM_RR_MULTI_VCP3_DEFAULT_CHAR_FORMAT TRU_USB_CDC_LINECODING_STOPBITS_ONE
	#define CDCACM_RR_MULTI_VCP3_DEFAULT_PARITY_TYPE TRU_USB_CDC_LINECODING_PARITY_NONE
	#define CDCACM_RR_MULTI_VCP3_DEFAULT_DATA_BITS   8
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	#define CDCACM_RR_MULTI_VCP4_NTF_ITFNUM          6
	#define CDCACM_RR_MULTI_VCP4_NTF_EPNUM           7
	#define CDCACM_RR_MULTI_VCP4_DAT_ITFNUM          7
	#define CDCACM_RR_MULTI_VCP4_TXD_EPNUM           8
	#define CDCACM_RR_MULTI_VCP4_RXD_EPNUM           8
	#define CDCACM_RR_MULTI_VCP4_DEFAULT_BIT_RATE    128000
	#define CDCACM_RR_MULTI_VCP4_DEFAULT_CHAR_FORMAT TRU_USB_CDC_LINECODING_STOPBITS_ONE
	#define CDCACM_RR_MULTI_VCP4_DEFAULT_PARITY_TYPE TRU_USB_CDC_LINECODING_PARITY_NONE
	#define CDCACM_RR_MULTI_VCP4_DEFAULT_DATA_BITS   8
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	#define CDCACM_RR_MULTI_VCP5_NTF_ITFNUM          8
	#define CDCACM_RR_MULTI_VCP5_NTF_EPNUM           9
	#define CDCACM_RR_MULTI_VCP5_DAT_ITFNUM          9
	#define CDCACM_RR_MULTI_VCP5_TXD_EPNUM           10
	#define CDCACM_RR_MULTI_VCP5_RXD_EPNUM           10
	#define CDCACM_RR_MULTI_VCP5_DEFAULT_BIT_RATE    128000
	#define CDCACM_RR_MULTI_VCP5_DEFAULT_CHAR_FORMAT TRU_USB_CDC_LINECODING_STOPBITS_ONE
	#define CDCACM_RR_MULTI_VCP5_DEFAULT_PARITY_TYPE TRU_USB_CDC_LINECODING_PARITY_NONE
	#define CDCACM_RR_MULTI_VCP5_DEFAULT_DATA_BITS   8
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	#define CDCACM_RR_MULTI_VCP6_NTF_ITFNUM          10
	#define CDCACM_RR_MULTI_VCP6_NTF_EPNUM           11
	#define CDCACM_RR_MULTI_VCP6_DAT_ITFNUM          11
	#define CDCACM_RR_MULTI_VCP6_TXD_EPNUM           12
	#define CDCACM_RR_MULTI_VCP6_RXD_EPNUM           12
	#define CDCACM_RR_MULTI_VCP6_DEFAULT_BIT_RATE    128000
	#define CDCACM_RR_MULTI_VCP6_DEFAULT_CHAR_FORMAT TRU_USB_CDC_LINECODING_STOPBITS_ONE
	#define CDCACM_RR_MULTI_VCP6_DEFAULT_PARITY_TYPE TRU_USB_CDC_LINECODING_PARITY_NONE
	#define CDCACM_RR_MULTI_VCP6_DEFAULT_DATA_BITS   8
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	#define CDCACM_RR_MULTI_VCP7_NTF_ITFNUM          12
	#define CDCACM_RR_MULTI_VCP7_NTF_EPNUM           13
	#define CDCACM_RR_MULTI_VCP7_DAT_ITFNUM          13
	#define CDCACM_RR_MULTI_VCP7_TXD_EPNUM           14
	#define CDCACM_RR_MULTI_VCP7_RXD_EPNUM           14
	#define CDCACM_RR_MULTI_VCP7_DEFAULT_BIT_RATE    128000
	#define CDCACM_RR_MULTI_VCP7_DEFAULT_CHAR_FORMAT TRU_USB_CDC_LINECODING_STOPBITS_ONE
	#define CDCACM_RR_MULTI_VCP7_DEFAULT_PARITY_TYPE TRU_USB_CDC_LINECODING_PARITY_NONE
	#define CDCACM_RR_MULTI_VCP7_DEFAULT_DATA_BITS   8
#endif

// Expected receive transfer length (setting all bits to 1 indicates maximum)
#define CDCACM_RR_MULTI_RXD_MAX_EXP_LEN -1

tru_usb_cdc_pd_info_t *get_cdcacm_rr_multi_pd_info(void);

#ifdef __cplusplus
}
#endif

#endif

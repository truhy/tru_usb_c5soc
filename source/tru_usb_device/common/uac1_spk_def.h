/*
	Created on: 17 Apr 2025
	Author: Truong Hy

	UAC1 (USB Audio Class 1 standard (1998)) descriptor speaker example.

	This standard is limited to the full-speed data rate, more specifically the
	transfer frame is 1ms and also only one packet can be sent every millisecond
	frame for all speeds, the bandwidth is therefore limited by the isochronous
	maximum packet size:
		Full-speed = 1023 bytes per millisecond frame
		High-speed = 1024 bytes per millisecond frame

	Suppose we are using a high-speed device and the audio sampling is
	2 channel * 16 bit * 192000 Hz, the sample rate is then 768 byte/ms,
	which is supported because it fits within the max rate 1024 byte/ms.

	Suppose we are using a high-speed device and the audio sampling is
	2 channel * 24 bit * 192000 Hz, the sample rate is then 1152 byte/ms,
	which is not supported because is greater than the max rate 1024 byte/ms.
*/

#ifndef UAC1_SPK_DEF_H
#define UAC1_SPK_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb/dclass/tru_usb_uac.h"
#include "tru_lfrb.h"
#include <stdint.h>

#define UAC1_SPK_HS_DESC_ENABLE 1

#define UAC1_SPK_WIN_QUIRK_RANGEMIN_ROUND 1

#define UAC1_SPK_FB_BUFFER_THRESHOLD (1.0f/2.0f)  // Maintain data at half of buffer
//#define UAC1_SPK_FB_BUFFER_THRESHOLD (3.0f/4.0f)  // Maintain data at 3/4 of buffer

// VID PID for open-source use from https://pid.codes/pids/
#define UAC1_SPK_VID 0x1209
#define UAC1_SPK_PID 0x0005
#define UAC1_SPK_VER 0x0001

#define UAC1_SPK_USB_VER 0x0200
//#define UAC1_SPK_USB_VER 0x0110

// Notes:
//   Asynchronous: The device monitors number of audio samples referenced to the USB (micro)frame frequency and sends a feedback value (number of samples per (micro)frame) via a feedback endpoint for the host to adjust the data rate or number samples per transfer
//   Adaptive    : The host and device monitors the average number of audio samples and if the number changes host adjusts the data rate and device may resample
//   Synchronous : The host sends audio samples at a fixed data rate according to the current audio sample size and sampling frequency which is assumed to be aligned with the 1ms SOF (for full-speed) or 125us microframe (for high-speed)
// My simplified notes:
//   Asynchronous: Device sends feedback and the host adjusts its transmission rate to match with the feedback
//   Adaptive    : Host monitors its own transmission rate and adjusts, e.g. when transmission was delayed (slowed) because it was busy with other tasks it sends more to compensate
//   Synchronous : Host never adjusts, the data rate is fixed
#define UAC1_SPK_CFG_AUDOUT_EPSYC TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
//#define UAC1_SPK_CFG_AUDOUT_EPSYC TRU_USB_EP_ISO_SYNC_TYPE_ADAPT
//#define UAC1_SPK_CFG_AUDOUT_EPSYC TRU_USB_EP_ISO_SYNC_TYPE_SYNC

// Feedback packet size.  Note, UAC 1.0 on Windows require 3, MAC OS require 3, Linux can use 3 or 4
#define UAC1_SPK_CFG_AUDOUT_FB_EPPKT_FS 3
//#define UAC1_SPK_CFG_AUDOUT_FB_EPPKT_FS 4

// Feedback packet size.  Note, UAC 1.0 on Windows require 3, MAC OS require 3, Linux can use 3 or 4
#define UAC1_SPK_CFG_AUDOUT_FB_EPPKT_HS 3
//#define UAC1_SPK_CFG_AUDOUT_FB_EPPKT_HS 4

// Feedback format: 1 = Q10.14, 0 = Q16.16.  Note, UAC 1.0 on Windows require Q10.14
//#define UAC1_SPK_CFG_FB_Q1014_FS 0
#define UAC1_SPK_CFG_FB_Q1014_FS 1

// Feedback format: 1 = Q10.14, 0 = Q16.16.  Note, UAC 1.0 on Windows require Q10.14
//#define UAC1_SPK_CFG_FB_Q1014_HS 0
#define UAC1_SPK_CFG_FB_Q1014_HS 1

// Terminal/Unit ID.
// ITE = Input Terminal Unit
// OTE = Output Terminal Unit
// FE = Feature Unit
#define UAC1_SPK_ITE_UNIT_ID        1
#define UAC1_SPK_FE_UNIT_ID         2
#define UAC1_SPK_OTE_UNIT_ID        3

// Speaker Audio Control interface
#define UAC1_SPK_AUDCTL_ITF_NUM     0

// Speaker data endpoint.  Note, UAC 1.0 audio out endpoint on Windows only support an interval of 1 for FS and 4 for HS, and also MPS 1023 for HS
#define UAC1_SPK_AUDOUT_EPADR       0x01
#define UAC1_SPK_AUDOUT_EPNUM       (UAC1_SPK_AUDOUT_EPADR & 0xf)
#define UAC1_SPK_AUDOUT_EPMPS_FS    1023
#define UAC1_SPK_AUDOUT_EPMPS_HS    1023
#define UAC1_SPK_AUDOUT_EPSYC_FS    UAC1_SPK_CFG_AUDOUT_EPSYC
#define UAC1_SPK_AUDOUT_EPSYC_HS    UAC1_SPK_CFG_AUDOUT_EPSYC
#define UAC1_SPK_AUDOUT_EPINT_FS    1
#define UAC1_SPK_AUDOUT_EPINT_HS    4
#define UAC1_SPK_AUDOUT_EPREF_FS    1
#define UAC1_SPK_AUDOUT_EPREF_HS    1
#define UAC1_SPK_AUDOUT_ITF_NUM     1
#define UAC1_SPK_AUDOUT_NUM_ITF     1
#define UAC1_SPK_AUDOUT_NUM_CH      2

// Speaker feedback endpoint.  Note, UAC 1.0 feedback endpoint on Windows only support an interval of 1 for FS and 4 for HS
#define UAC1_SPK_AUDOUT_FB_EPADR    0x81
#define UAC1_SPK_AUDOUT_FB_EPNUM    (UAC1_SPK_AUDOUT_FB_EPADR & 0xf)
#define UAC1_SPK_AUDOUT_FB_EPMPS_FS UAC1_SPK_CFG_AUDOUT_FB_EPPKT_FS
#define UAC1_SPK_AUDOUT_FB_EPMPS_HS UAC1_SPK_CFG_AUDOUT_FB_EPPKT_HS
#define UAC1_SPK_AUDOUT_FB_EPINT_FS 1
#define UAC1_SPK_AUDOUT_FB_EPINT_HS 4
#define UAC1_SPK_AUDOUT_FB_EPREF_FS 1
#define UAC1_SPK_AUDOUT_FB_EPREF_HS 1

// Speaker 16bit interface parameters
#define UAC1_SPK_SMP_RES_16B_ENABLE 1
#define UAC1_SPK_SMP_RES_16B        16
#define UAC1_SPK_SMP_NUM_CH_16B     2
#define UAC1_SPK_ALT_NUM_16B        1
// Values must be in ascending order.  Set to 0 if an item is not needed
#define UAC1_SPK_SMP_FRQ_16B_1      44100
#define UAC1_SPK_SMP_FRQ_16B_2      48000
#define UAC1_SPK_SMP_FRQ_16B_3      88200
#define UAC1_SPK_SMP_FRQ_16B_4      96000
#define UAC1_SPK_SMP_FRQ_16B_5      176400
#define UAC1_SPK_SMP_FRQ_16B_6      192000
// Determine the number of sampling frequencies
#define UAC1_SPK_NUM_SMP_FRQ_16B ( \
	(UAC1_SPK_SMP_FRQ_16B_1 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_16B_2 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_16B_3 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_16B_4 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_16B_5 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_16B_6 ? 1 : 0))

// Speaker 24bit interface parameters
#define UAC1_SPK_SMP_RES_24B_ENABLE 1
#define UAC1_SPK_SMP_RES_24B        24
#define UAC1_SPK_SMP_NUM_CH_24B     2
#define UAC1_SPK_ALT_NUM_24B        2
// Values must be in ascending order.  Set to 0 if an item is not needed
#define UAC1_SPK_SMP_FRQ_24B_1      44100
#define UAC1_SPK_SMP_FRQ_24B_2      48000
#define UAC1_SPK_SMP_FRQ_24B_3      88200
#define UAC1_SPK_SMP_FRQ_24B_4      96000
#define UAC1_SPK_SMP_FRQ_24B_5      0
#define UAC1_SPK_SMP_FRQ_24B_6      0
// Determine the number of sampling frequencies
#define UAC1_SPK_NUM_SMP_FRQ_24B ( \
	(UAC1_SPK_SMP_FRQ_24B_1 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_24B_2 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_24B_3 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_24B_4 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_24B_5 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_24B_6 ? 1 : 0))

// Speaker 32bit interface parameters
#define UAC1_SPK_SMP_RES_32B_ENABLE 1
#define UAC1_SPK_SMP_RES_32B        32
#define UAC1_SPK_SMP_NUM_CH_32B     2
#define UAC1_SPK_ALT_NUM_32B        3
// Values must be in ascending order.  Set to 0 if an item is not needed
#define UAC1_SPK_SMP_FRQ_32B_1      44100
#define UAC1_SPK_SMP_FRQ_32B_2      48000
#define UAC1_SPK_SMP_FRQ_32B_3      88200
#define UAC1_SPK_SMP_FRQ_32B_4      96000
#define UAC1_SPK_SMP_FRQ_32B_5      0
#define UAC1_SPK_SMP_FRQ_32B_6      0
// Determine the number of sampling frequencies
#define UAC1_SPK_NUM_SMP_FRQ_32B ( \
	(UAC1_SPK_SMP_FRQ_32B_1 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_32B_2 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_32B_3 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_32B_4 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_32B_5 ? 1 : 0) + \
	(UAC1_SPK_SMP_FRQ_32B_6 ? 1 : 0))

// Please set these to match the sampling parameter options above
#define UAC1_SPK_MAX_SMP_FRQ        192000    // Max sampling frequency in Hz
#define UAC1_SPK_MAX_CHANNELS       2         // Max number of channels
#define UAC1_SPK_MAX_SMP_BYTES      (32 / 8)  // Max sample size in bytes

// Speaker controls configuration: 1 = Enable, 0 = Disable
#define UAC1_SPK_COPYPROTECT_CONTROL 1
#define UAC1_SPK_MUTE_CONTROL        1
#define UAC1_SPK_VOLUME_CONTROL      0
#define UAC1_SPK_SMP_FRQ_CONTROL     1
#define UAC1_SPK_PITCH_CONTROL       0

// Audio to millisecond bytes.  Note, integer division truncates fractional
#define UAC1_SPK_AUDIO_BYTES_MS(freq, channels, samp_bytes) ((freq) / 1000 * (channels) * (samp_bytes))
// Audio to centisecond bytes.  Note, divides by 100 to support non-multiple 1kHz frequencies
#define UAC1_SPK_AUDIO_BYTES_CS(freq, channels, samp_bytes) ((freq) / 100 * (channels) * (samp_bytes))

typedef struct{
	uint8_t samp_num_ch;
	uint8_t samp_res;
	uint32_t samp_freq;
	tru_lfrb_t aob;
	uint32_t aob_overrun;
	uint32_t i2s_underrun;
	uint32_t i2s_underrun_half_len_32bit;  // Aligned up to 32-bit
	uint32_t i2s_underrun_cplt_len_32bit;  // Aligned up to 32-bit
	tru_lfrb_t i2sb;
	uint32_t i2s_len;
	uint32_t i2s_half_len;
	uint32_t i2s_half_len_32bit;  // Aligned up to 32-bit
	volatile bool i2s_started;
	volatile bool i2s_stop_requested;
#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	float fb_min;
	float fb_max;
	float fb_nominal;
	float fb;
	uint32_t fb_fp;  // Fixed point format
#endif
}uac1_spk_t;

tru_usb_uac_pd_info_t *get_uac1_spk_pd_info(void);

#ifdef __cplusplus
}
#endif

#endif

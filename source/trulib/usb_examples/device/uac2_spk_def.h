/*
	Created on: 27 May 2025
	Author: Truong Hy

	USB Audio Class 2 standard (2009) descriptor speaker example.

	In standard mode, A standard UAC2 isochronous endpoint sends one packet per
	125us (microframe).  We can send up to 8 packets per millisecond.

	In high bandwith mode, UAC2 isochronous endpoint sends up to three packets
	per 125us.  We can send a maximum of 24 packets per millisecond.
*/

#ifndef UAC2_SPK_DEF_H
#define UAC2_SPK_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb/dclass/tru_usb_uac2.h"
#include "tru_lfrb.h"
#include <stdint.h>

#define UAC2_SPK_HS_DESC_ENABLE 1

#define UAC2_SPK_WIN_QUIRK_RANGEMIN_ROUND 1

#define UAC2_SPK_FB_BUFFER_THRESHOLD (1.0/2.0)  // Maintain data at half of buffer
//#define UAC2_SPK_FB_BUFFER_THRESHOLD (3.0/4.0)  // Maintain data at 3/4 of buffer

// VID PID for open-source use from https://pid.codes/pids/
#define UAC2_SPK_VID 0x1209
#define UAC2_SPK_PID 0x0006
#define UAC2_SPK_VER 0x0002

#define UAC2_SPK_USB_VER 0x0200
//#define UAC2_SPK_USB_VER 0x0110

// Notes:
//   Asynchronous: The device monitors number of audio samples referenced to the USB (micro)frame frequency and sends a feedback value (number of samples per (micro)frame) via a feedback endpoint for the host to adjust the data rate or number samples per transfer
//   Adaptive    : The host and device monitors the average number of audio samples and if the number changes host adjusts the data rate and device may resample
//   Synchronous : The host sends audio samples at a fixed data rate according to the current audio sample size and sampling frequency which is assumed to be aligned with the 1ms SOF (for full-speed) or 125us microframe (for high-speed)
// My simplified notes:
//   Asynchronous: Device sends feedback and the host adjusts its transmission rate to match with the feedback
//   Adaptive    : Host monitors its own transmission rate and adjusts, e.g. when transmission was delayed (slowed) because it was busy with other tasks it sends more to compensate
//   Synchronous : Host never adjusts, the data rate is fixed
#define UAC2_SPK_CFG_AUDOUT_EPSYC TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
//#define UAC2_SPK_CFG_AUDOUT_EPSYC TRU_USB_EP_ISO_SYNC_TYPE_ADAPT
//#define UAC2_SPK_CFG_AUDOUT_EPSYC TRU_USB_EP_ISO_SYNC_TYPE_SYNC

// Feedback max packet size.  Note, UAC 2.0 full-speed on Windows require 4, Linux can use 3 or 4
//#define UAC2_SPK_CFG_AUDOUT_FB_EPPKT_FS 3
#define UAC2_SPK_CFG_AUDOUT_FB_EPPKT_FS 4

// Feedback max packet size.  Note, UAC 2.0 high-speed mode on Windows require 4, Linux can use 3 or 4
//#define UAC2_SPK_CFG_AUDOUT_FB_EPPKT_HS 3
#define UAC2_SPK_CFG_AUDOUT_FB_EPPKT_HS 4

// Feedback format: 1 = Q10.14, 0 = Q16.16.  Note, UAC 2.0 on Windows require Q16.16, Linux can use Q10.14 or Q16.16
#define UAC2_SPK_CFG_FB_Q1014_FS 0

// Feedback format: 1 = Q10.14, 0 = Q16.16.  Note, UAC 2.0 on Windows require Q16.16, Linux can use Q10.14 or Q16.16
#define UAC2_SPK_CFG_FB_Q1014_HS 0

// Terminal/Unit ID
// ITE = Input Terminal Unit
// OTE = Output Terminal Unit
// FE = Feature Unit
#define UAC2_SPK_ITE_UNIT_ID          1
#define UAC2_SPK_FE_UNIT_ID           2
#define UAC2_SPK_OTE_UNIT_ID          3
#define UAC2_SPK_CLK_SRC_UNIT_ID      4
#define UAC2_SPK_CLK_SEL_UNIT_ID      5

// Speaker Audio Control interface
#define UAC2_SPK_AUDCTL_ITF_NUM       0

// Speaker data endpoint.  Note, UAC 2.0 audio out endpoint on Windows only support an interval of 1 for FS, and 1 to 4 (adaptive) and 4 (asynchronous) for HS
#define UAC2_SPK_AUDOUT_EPADR         0x01
#define UAC2_SPK_AUDOUT_EPNUM         (UAC2_SPK_AUDOUT_EPADR & 0xfU)
#define UAC2_SPK_AUDOUT_EPMPS_FS      1023
#define UAC2_SPK_AUDOUT_EPMPS_HS      1024
#define UAC2_SPK_AUDOUT_EPSYC_FS      UAC2_SPK_CFG_AUDOUT_EPSYC
#define UAC2_SPK_AUDOUT_EPSYC_HS      UAC2_SPK_CFG_AUDOUT_EPSYC
#define UAC2_SPK_AUDOUT_EPINT_FS      1
#define UAC2_SPK_AUDOUT_EPINT_HS      4
#define UAC2_SPK_AUDOUT_ITF_NUM       1
#define UAC2_SPK_AUDOUT_NUM_CH        2
#define UAC2_SPK_AUDOUT_SMP_FRQ_RANGE { \
	{ 44100,  44100,  0 }, \
	{ 48000,  48000,  0 }, \
	{ 88200,  88200,  0 }, \
	{ 96000,  96000,  0 }, \
	{ 176400, 176400, 0 }, \
	{ 192000, 192000, 0 }, \
	{ 352800, 352800, 0 }, \
	{ 384000, 384000, 0 }, \
}
// Please set these to match the sampling parameter options above
#define UAC2_SPK_AUDOUT_NUM_SMP_FRQ   8         // Number of sampling frequencies
#define UAC2_SPK_MAX_SMP_FRQ          384000    // Max sampling frequency in Hz
#define UAC2_SPK_MAX_CHANNELS         2         // Max number of channels
#define UAC2_SPK_MAX_SMP_BYTES        (32 / 8)  // Max sample size in bytes

// Speaker feedback endpoint.  Note, UAC 2.0 audio out endpoint on Windows only support an interval of 1 in full-speed mode, and 1 to 4 in high-speed mode
#define UAC2_SPK_AUDOUT_FB_EPADR      0x81
#define UAC2_SPK_AUDOUT_FB_EPNUM      (UAC2_SPK_AUDOUT_FB_EPADR & 0xfU)
#define UAC2_SPK_AUDOUT_FB_EPMPS_FS   UAC2_SPK_CFG_AUDOUT_FB_EPPKT_FS
#define UAC2_SPK_AUDOUT_FB_EPMPS_HS   UAC2_SPK_CFG_AUDOUT_FB_EPPKT_HS
#define UAC2_SPK_AUDOUT_FB_EPINT_FS   1
#define UAC2_SPK_AUDOUT_FB_EPINT_HS   4

// Speaker 16bit interface parameters
#define UAC2_SPK_SMP_RES_16B_ENABLE   1
#define UAC2_SPK_SMP_RES_16B          16
#define UAC2_SPK_SMP_FRAME_16B        (UAC2_SPK_SMP_RES_16B / 8)
#define UAC2_SPK_SMP_NUM_CH_16B       2
#define UAC2_SPK_ALT_NUM_16B          1

// Speaker 24bit interface parameters
#define UAC2_SPK_SMP_RES_24B_ENABLE   1
#define UAC2_SPK_SMP_RES_24B          24
#define UAC2_SPK_SMP_FRAME_24B        (UAC2_SPK_SMP_RES_24B / 8)
#define UAC2_SPK_SMP_NUM_CH_24B       2
#define UAC2_SPK_ALT_NUM_24B          2

// Speaker 32bit interface parameters
#define UAC2_SPK_SMP_RES_32B_ENABLE   1
#define UAC2_SPK_SMP_RES_32B          32
#define UAC2_SPK_SMP_FRAME_32B        (UAC2_SPK_SMP_RES_32B / 8)
#define UAC2_SPK_SMP_NUM_CH_32B       2
#define UAC2_SPK_ALT_NUM_32B          3

// Speaker controls configuration. The last characters selects the control: R = Read only, RW = Read/Write (programmable), NA = Not Available (not present)
#define UAC2_SPK_COPYPROTECT_CONTROL  TRU_USB_UAC2_CONTROL_RW
#define UAC2_SPK_MUTE_CONTROL         TRU_USB_UAC2_CONTROL_RW
#define UAC2_SPK_VOLUME_CONTROL       TRU_USB_UAC2_CONTROL_NA
#define UAC2_SPK_PITCH_CONTROL        TRU_USB_UAC2_CONTROL_NA

// Audio to millisecond bytes.  Note, integer division truncates fractional
#define UAC2_SPK_AUDIO_BYTES_MS(freq, channels, samp_bytes) ((freq) / 1000 * (channels) * (samp_bytes))
// Audio to centisecond bytes.  Note, divides by 100 to support non-multiple 1kHz frequencies
#define UAC2_SPK_AUDIO_BYTES_CS(freq, channels, samp_bytes) ((freq) / 100 * (channels) * (samp_bytes))

typedef struct __attribute__((packed)){
	uint16_t num_subranges;
	tru_usb_uac2_layout3_range_t range[];
}uac2_spk_clk_frq_range_t;

typedef struct{
	uint8_t samp_num_ch;
	uint8_t samp_res;
	uint32_t samp_freq;
	tru_lfrb_t aob;
	uint32_t aob_overrun;
	uint32_t i2s_underrun;
	uint32_t i2s_underrun_half_size_32bit;  // Aligned up to 32-bit
	uint32_t i2s_underrun_cplt_size_32bit;  // Aligned up to 32-bit
	tru_lfrb_t i2sb;
	uint32_t i2s_len;
	uint32_t i2s_half_len;
	uint32_t i2s_half_len_32bit;  // Aligned up to 32-bit
	volatile bool i2s_started;
	volatile bool i2s_stop_requested;
#if UAC2_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	float fb_min;
	float fb_max;
	float fb_nominal;
	float fb;
	uint32_t fb_fp;  // Fixed point format
#endif
}uac2_spk_t;

tru_usb_uac2_pd_info_t *get_uac2_spk_pd_info(void);

#ifdef __cplusplus
}
#endif

#endif

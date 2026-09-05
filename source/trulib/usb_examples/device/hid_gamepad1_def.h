/*
	Created on: 22 Mar 2025
	Author: Truong Hy
*/

#ifndef HID_GAMEPAD1_DEF_H
#define HID_GAMEPAD1_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb/dclass/tru_usb_hid.h"
#include "tru_iom.h"
#include <stdint.h>

#define HID_GAMEPAD1_HS_DESC_ENABLE 1

// VID PID for open-source use from https://pid.codes/pids/
#define HID_GAMEPAD1_DEV_VID 0x1209
#define HID_GAMEPAD1_DEV_PID 0x0004
#define HID_GAMEPAD1_DEV_VER 0x0001

#define HID_GAMEPAD1_USB_VER 0x0200
//#define HID_GAMEPAD1_USB_VER 0x0110

#define HID_GAMEPAD1_IN_REPORT_EPNUM  1
#define HID_GAMEPAD1_OUT_REPORT_EPNUM 1

#define HID_GAMEPAD1_POS_RES 0      // Bit resolution, valid values: 0, 8 or 16 (0 = disable)
#define HID_GAMEPAD1_POS_MIN -32768
#define HID_GAMEPAD1_POS_MAX 32767
//#define HID_GAMEPAD1_POS_MIN (-(1 << (HID_GAMEPAD1_POS_RES - 1)))
//#define HID_GAMEPAD1_POS_MAX ((1 << (HID_GAMEPAD1_POS_RES - 1)) - 1)

#define HID_GAMEPAD1_ROT_RES 16     // Bit resolution, valid values: 0, 8 or 16 (0 = disable)
#define HID_GAMEPAD1_ROT_MIN -32768
#define HID_GAMEPAD1_ROT_MAX 32767
//#define HID_GAMEPAD1_ROT_MIN (-(1 << (HID_GAMEPAD1_ROT_RES - 1)))
//#define HID_GAMEPAD1_ROT_MAX ((1 << (HID_GAMEPAD1_ROT_RES - 1)) - 1)

#define HID_GAMEPAD1_NUM_BUTTONS 6

#define HID_GAMEPAD1_INPUT_REPORT_ID         1
#define HID_GAMEPAD1_INPUT_REPORT_SIZE_BITS  (8 + 3*HID_GAMEPAD1_POS_RES + 3*HID_GAMEPAD1_ROT_RES + 8)
#define HID_GAMEPAD1_INPUT_REPORT_SIZE_BYTES (INT_ALIGN_UP(HID_GAMEPAD1_INPUT_REPORT_SIZE_BITS, 8)/8)

typedef union{
	uint8_t val;
	struct{
		uint8_t button1 : 1;
		uint8_t button2 : 1;
		uint8_t button3 : 1;
		uint8_t button4 : 1;
		uint8_t button5 : 1;
		uint8_t button6 : 1;
		uint8_t padding1 : 1;  // Padding to align to multiple of 8 bits
		uint8_t padding2 : 1;  // Padding to align to multiple of 8 bits
	}bits;
}tru_hid_gamepad1_buttons_t;

typedef struct __attribute__((packed)){
	uint8_t id;
#if HID_GAMEPAD1_POS_RES == 8
	int8_t x;
	int8_t y;
	int8_t z;
#elif HID_GAMEPAD1_POS_RES == 16
	int16_t x;
	int16_t y;
	int16_t z;
#endif
#if HID_GAMEPAD1_ROT_RES == 8
	int8_t rx;
	int8_t ry;
	int8_t rz;
#elif HID_GAMEPAD1_ROT_RES == 16
	int16_t rx;
	int16_t ry;
	int16_t rz;
#endif
	tru_hid_gamepad1_buttons_t buttons;
}tru_hid_gamepad1_input_report_t;

tru_usb_hid_pd_info_t *get_hid_gamepad1_pd_info(void);

#ifdef __cplusplus
}
#endif

#endif

/*
	Created on: 22 Mar 2025
	Author: Truong Hy
*/

#ifndef HID_GAMEPAD1_H
#define HID_GAMEPAD1_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hid_gamepad1_def.h"
#include <stdbool.h>

void hid_gamepad1_init(
	tru_usb_pc_t *pc,
	tru_usb_hid_t *hid,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode
);
void hid_gamepad1_deinit(tru_usb_hid_t *hid);

#ifdef __cplusplus
}
#endif

#endif

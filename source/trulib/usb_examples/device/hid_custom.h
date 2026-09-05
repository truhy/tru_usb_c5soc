/*
	Created on: 25 Dec 2022
	Author: Truong Hy
*/

#ifndef HID_CUSTOM_H
#define HID_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "hid_custom_def.h"

void hid_cus_init(
	tru_usb_pc_t *pc,
	tru_usb_hid_t *hid,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode
);
void hid_cus_deinit(tru_usb_hid_t *hid);

// Prototypes for callbacks to be defined in processor specific application level
void __attribute__((weak)) hid_cus_cb_setup_buffers(void);

#ifdef __cplusplus
}
#endif

#endif

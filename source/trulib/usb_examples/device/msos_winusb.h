/*
	Created on: 24 Apr 2023
	Author: Truong Hy
*/

#ifndef MSOS_WINUSB_H
#define MSOS_WINUSB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "msos_winusb_def.h"
#include <stdbool.h>

// Expected receive transfer length (setting all bits to 1 indicates maximum)
#define MSOS_WINUSB_RXD_MAX_EXP_LEN -1

void msos_winusb_init(
	tru_usb_pc_t *pc,
	tru_usb_msos_t *msos,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode
);
void msos_winusb_deinit(tru_usb_msos_t *msos);

// Prototypes for callbacks to be defined in processor specific application level
void __attribute__((weak)) msos_winusb_cb_setup_buffers(void);

#ifdef __cplusplus
}
#endif

#endif

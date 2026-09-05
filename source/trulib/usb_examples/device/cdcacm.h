/*
	Created on: 05 Mar 2023
	Author: Truong Hy
*/

#ifndef CDCACM_H
#define CDCACM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cdcacm_def.h"
#include <stdbool.h>

// Expected receive transfer length (setting all bits to 1 indicates maximum)
#define CDCACM_RXD_MAX_EXP_LEN -1

#define CDCACM_ECHO             0      // 0 = no echo, 1 = echo the data received
#define CDCACM_ECHO_BUFFER_SIZE 16384  // Echo buffer size for the echo, needed when the transmit is busy

void cdcacm_init(
	tru_usb_pc_t *pc,
	tru_usb_cdc_t *cdc,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode
);
void cdcacm_deinit(tru_usb_cdc_t *cdc);

// Prototypes for callbacks to be defined in processor specific application level
void __attribute__((weak)) cdcacm_cb_setup_buffers(void);

#ifdef __cplusplus
}
#endif

#endif

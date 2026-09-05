/*
	Created on: 15 Nov 2024
	Author: Truong Hy
*/

#ifndef CDCACM_RR_MULTI_H
#define CDCACM_RR_MULTI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cdcacm_rr_multi_def.h"
#include "cdcacm_rr_multi_vcp1.h"
#include "cdcacm_rr_multi_vcp2.h"
#include "cdcacm_rr_multi_vcp3.h"
#include "cdcacm_rr_multi_vcp4.h"
#include "cdcacm_rr_multi_vcp5.h"
#include "cdcacm_rr_multi_vcp6.h"
#include "cdcacm_rr_multi_vcp7.h"
#include <stdbool.h>

void cdcacm_rr_multi_init(
	tru_usb_pc_t *pc,
	tru_usb_cdc_t *cdc,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode
);
void cdcacm_rr_multi_deinit(tru_usb_cdc_t *cdc);

// Prototypes for callbacks to be defined in processor specific application level
void __attribute__((weak)) cdcacm_rr_multi_cb_setup_buffers(void);

#ifdef __cplusplus
}
#endif

#endif

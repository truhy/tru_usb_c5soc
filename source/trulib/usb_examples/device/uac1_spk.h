/*
	Created on: 19 Apr 2025
	Author: Truong Hy
*/

#ifndef UAC1_SPK_H
#define UAC1_SPK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "uac1_spk_def.h"
#include <stdbool.h>

void uac1_spk_init(
	tru_usb_pc_t *pc,
	tru_usb_uac_t *uac,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode,
	uac1_spk_t *spk
);
void uac1_spk_deinit(tru_usb_uac_t *uac);

// Callbacks defined here
void uac1_spk_cb_setup_buffers(void);
void uac1_spk_cb_audioinit(tru_usb_pc_epo_t *ep);
void uac1_spk_cb_audiofreq(tru_usb_pc_epo_t *ep);
void uac1_spk_cb_audioupdate(tru_usb_pc_epo_t *ep);
void uac1_spk_cb_audiostop(tru_usb_pc_epo_t *ep);
#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
void uac1_spk_prepare_fb(tru_usb_uac_t *uac);
void uac1_spk_update_fb(tru_usb_uac_t *uac);
#endif

#ifdef __cplusplus
}
#endif

#endif

/*
	Created on: 31 May 2025
	Author: Truong Hy
*/

#ifndef UAC2_SPK_H
#define UAC2_SPK_H

#ifdef __cplusplus
extern "C" {
#endif

#include "uac2_spk_def.h"
#include <stdbool.h>

void uac2_spk_init(
	tru_usb_pc_t *pc,
	tru_usb_uac2_t *uac,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode,
	uac2_spk_t *spk
);
void uac2_spk_deinit(tru_usb_uac2_t *uac);

// Callbacks defined here
void uac2_spk_cb_setup_buffers(void);
void uac2_spk_cb_audioinit(tru_usb_pc_epo_t *ep);
void uac2_spk_cb_audiofreq(tru_usb_interface_alt_setting_t *alt_setting);
void uac2_spk_cb_audioupdate(tru_usb_pc_epo_t *ep);
void uac2_spk_cb_audiostop(tru_usb_pc_epo_t *ep);
#if UAC2_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
void uac2_spk_prepare_fb(tru_usb_uac2_t *uac);
void uac2_spk_update_fb(tru_usb_uac2_t *uac);
#endif

#ifdef __cplusplus
}
#endif

#endif

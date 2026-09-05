#include "cdcacm_rr_multi.h"

static void cb_reset(tru_usb_cdc_t *cdc);
static void cb_enumdone(tru_usb_cdc_t *cdc);

void cdcacm_rr_multi_init(
	tru_usb_pc_t *pc,
	tru_usb_cdc_t *cdc,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode
){
	tru_usb_pc_init(
		pc,
		get_cdcacm_rr_multi_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);
	tru_usb_cdc_init(cdc, pc, get_cdcacm_rr_multi_pd_info());

	cdcacm_rr_multi_cb_setup_buffers();

#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	cdcacm_rr_multi_vcp1_init(cdc);
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	cdcacm_rr_multi_vcp2_init(cdc);
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	cdcacm_rr_multi_vcp3_init(cdc);
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	cdcacm_rr_multi_vcp4_init(cdc);
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	cdcacm_rr_multi_vcp5_init(cdc);
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	cdcacm_rr_multi_vcp6_init(cdc);
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	cdcacm_rr_multi_vcp7_init(cdc);
#endif

	// Register callback functions
	tru_usb_cdc_register_cb_reset(cdc, cb_reset);
	tru_usb_cdc_register_cb_enumdone(cdc, cb_enumdone);
}

void cdcacm_rr_multi_deinit(tru_usb_cdc_t *cdc){
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	cdcacm_rr_multi_vcp1_deinit();
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	cdcacm_rr_multi_vcp2_deinit();
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	cdcacm_rr_multi_vcp3_deinit();
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	cdcacm_rr_multi_vcp4_deinit();
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	cdcacm_rr_multi_vcp5_deinit();
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	cdcacm_rr_multi_vcp6_deinit();
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	cdcacm_rr_multi_vcp7_deinit();
#endif

	tru_usb_cdc_deinit(cdc);
	tru_usb_pc_deinit(cdc->pc);
}

// =========
// Callbacks
// =========

void cb_reset(tru_usb_cdc_t *cdc){
}

void cb_enumdone(tru_usb_cdc_t *cdc){
}

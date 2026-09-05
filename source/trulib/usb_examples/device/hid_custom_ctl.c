#include "hid_custom_ctl.h"
#include "tru_logger.h"
#include <stdlib.h>

// Function prototypes
static void cb_reset(tru_usb_hid_t *hid);
static bool cb_setup(tru_usb_hid_t *hid);
static void cb_set_report(tru_usb_hid_t *hid, tru_usb_hid_interface_ext_t *intf_ext, tru_usb_hid_report_info_t *report_info, uint8_t report_id, uint8_t report_type);

void hid_cus_ctl_init(
	tru_usb_pc_t *pc,
	tru_usb_hid_t *hid,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode
){
	tru_usb_pc_init(
		pc,
		get_hid_cus_ctl_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);
	tru_usb_hid_init(hid, pc, get_hid_cus_ctl_pd_info());

	// Register callback functions
	tru_usb_hid_register_cb_reset(hid, cb_reset);
	tru_usb_hid_register_cb_setup(hid, cb_setup);
	tru_usb_hid_register_cb_set_report(hid, cb_set_report);


	//tru_usb_pc_epi_t *rpt_epi = &pc.eps.epis[HID_CUS_CTL_REPORT_EPNUM];
	//tru_usb_lxfer_register_sgdma_descs(&rpt_epi->lxfer, dma_descs, 1);
}

void hid_cus_ctl_deinit(tru_usb_hid_t *hid){
	tru_usb_hid_deinit(hid);
	tru_usb_pc_deinit(hid->pc);
}

// Callback when USB resets
void cb_reset(tru_usb_hid_t *hid){
}

// Callback when a USB setup request is received on end-point 0
// Set the return value to true if a setup request was handled here, otherwise false
bool cb_setup(tru_usb_hid_t *hid){
	return false;  // No setup request was handled here
}

// Callback when USB device receives a setup request SET_REPORT data from the host
void cb_set_report(tru_usb_hid_t *hid, tru_usb_hid_interface_ext_t *intf_ext, tru_usb_hid_report_info_t *report_info, uint8_t report_id, uint8_t report_type){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: SET REPORT\n");
#endif

	// ===============
	// Read HID report
	// ===============

#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	// Which report type received?
	switch(report_type){
		case TRU_USB_HID_REQ_REPORT_TYPE_INPUT:
			LOG("CB: RX INPUT REPORT ID %u LEN %lu: ", report_id, report_info->size);
			break;
		case TRU_USB_HID_REQ_REPORT_TYPE_OUTPUT:
			LOG("CB: RX OUTPUT REPORT ID %u LEN %lu: ", report_id, report_info->size);
			break;
		case TRU_USB_HID_REQ_REPORT_TYPE_FEATURE:
			LOG("CB: RX FEATURE REPORT ID %u LEN %lu: ", report_id, report_info->size);
			break;
	}

	for(uint32_t i = 0; i < report_info->size; i++){
		LOG("%.2x", rd8_unaligned((uint8_t *)report_info->report + i));
	}
	LOG("\n");
#endif

	if(report_type == TRU_USB_HID_REQ_REPORT_TYPE_OUTPUT){
		// =====-================
		// Write HID input report
		// ======================

		// Variables
		tru_usb_pc_epi_t *epin = tru_hid_get_report_epi_from_intf_ext(hid, intf_ext);  // Get the report in endpoint using the report out endpoint
		tru_usb_hid_report_info_t *input_report_info = tru_hid_get_next_input_report_info(epin, hid->pc->dma_mode);  // Get the next input report.  Ensure this is executed only once per transmit

		// Put message into the input report buffer
		memset(input_report_info->report, 0, input_report_info->size);
		TRU_MEMCPY(input_report_info->report, "Hello HID report", 16);

		tru_usb_pc_transmit(hid->pc, epin->num, input_report_info->size, input_report_info->size);

		#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
			LOG("CB: TX INPUT REPORT LEN %lu: ", epin->lxfer.whole.total_xfer_size);
			for(uint32_t i = 0; i < epin->lxfer.whole.total_xfer_size; i++){
				LOG("%.2x", rd8_unaligned((uint8_t *)epin->lxfer.chunk.buffers[0].buf + i));
			}
			LOG("\n");
		#endif
	}
}

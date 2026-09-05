#include "hid_custom.h"
#include "tru_logger.h"

// Function prototypes
static void cb_reset(tru_usb_hid_t *hid);
static void cb_enumdone(tru_usb_hid_t *hid);
static bool cb_setup(tru_usb_hid_t *hid);
static void cb_set_report(tru_usb_hid_t *hid, tru_usb_hid_interface_ext_t *intf_ext, tru_usb_hid_report_info_t *report_info, uint8_t report_id, uint8_t report_type);
static void cb_config(tru_usb_hid_t *hid, tru_usb_config_t *config, bool is_activated);
static void cb_output_report_act(tru_usb_hid_t *hid, tru_usb_pc_epo_t *ep, bool is_activated);
static void cb_input_report_act(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep, bool is_activated);
static void cb_output_report_compl(tru_usb_hid_t *hid, tru_usb_pc_epo_t *ep);
static void cb_input_report_compl(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep);

void hid_cus_init(
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
		get_hid_cus_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);
	tru_usb_hid_init(hid, pc, get_hid_cus_pd_info());

	hid_cus_cb_setup_buffers();

	// Register callback functions
	tru_usb_hid_register_cb_reset(hid, cb_reset);
	tru_usb_hid_register_cb_enumdone(hid, cb_enumdone);
	tru_usb_hid_register_cb_setup(hid, cb_setup);
	tru_usb_hid_register_cb_set_report(hid, cb_set_report);
	tru_usb_hid_register_cb_cfg_act(hid, cb_config);
	tru_usb_hid_register_cb_epo_act(hid, HID_CUS_OUT_REPORT_EPNUM, cb_output_report_act);
	tru_usb_hid_register_cb_epi_act(hid, HID_CUS_IN_REPORT_EPNUM, cb_input_report_act);
	tru_usb_hid_register_cb_epo_compl(hid, HID_CUS_OUT_REPORT_EPNUM, cb_output_report_compl);
	tru_usb_hid_register_cb_epi_compl(hid, HID_CUS_IN_REPORT_EPNUM, cb_input_report_compl);
}

void hid_cus_deinit(tru_usb_hid_t *hid){
	tru_usb_hid_deinit(hid);
	tru_usb_pc_deinit(hid->pc);
}


// Callback when USB resets
void cb_reset(tru_usb_hid_t *hid){
}

// Callback when USB enumeration is done
void cb_enumdone(tru_usb_hid_t *hid){
}

// The library will call this back when a USB setup request is received on end-point 0
// Set the return value to true if a setup request was handled here, otherwise false
bool cb_setup(tru_usb_hid_t *hid){
	return false;  // No setup request was handled here
}

// Callback when USB device receives a setup request SET_REPORT data from the host
void cb_set_report(tru_usb_hid_t *hid, tru_usb_hid_interface_ext_t *intf_ext, tru_usb_hid_report_info_t *report_info, uint8_t report_id, uint8_t report_type){
	// Which report type received?
	switch(report_type){
		case TRU_USB_HID_REQ_REPORT_TYPE_INPUT:
			break;
		case TRU_USB_HID_REQ_REPORT_TYPE_OUTPUT:
			break;
		case TRU_USB_HID_REQ_REPORT_TYPE_FEATURE:
			break;
	}
}

// Callback when USB configuration has changed
void cb_config(tru_usb_hid_t *hid, tru_usb_config_t *config, bool is_activated){
}

void cb_output_report_act(tru_usb_hid_t *hid, tru_usb_pc_epo_t *ep, bool is_activated){
	if(is_activated){
		#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
			LOG("CB: EP1 RX ACTIVATED\n");
		#endif

		// ========================
		// Receive an output report
		// ========================

		tru_usb_pc_receive(hid->pc, ep->num, HID_CUS_OUTPUT_REPORT_VARCOUNT, HID_CUS_OUTPUT_REPORT_VARCOUNT);
	}
}

void cb_input_report_act(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep, bool is_activated){
}

void cb_output_report_compl(tru_usb_hid_t *hid, tru_usb_pc_epo_t *ep){
	#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
		LOG("CB: EP1 RX COMPL\n");

		/*
		if(ep->lxfer.chunk.total_xferred_size > 0){
			for(uint32_t i = 0; i < ep->lxfer.chunk.num_registered; i++){
				LOG("CB: RX OUTPUT REPORT LEN %lu: ", ep->lxfer.chunk.total_xferred_size);
				for(uint32_t j = 0; j < ep->lxfer.chunk.total_xferred_size; j++){
					LOG("%.2x", rd8_unaligned((uint8_t *)ep->lxfer.chunk.buffers[i].buf + j));
				}
				LOG("\n");
			}
		}
		*/

		// ==============================
		// Display received output report
		// ==============================

		tru_usb_hid_report_info_t *output_report = tru_hid_get_output_report_info(ep);  // Get the received output report
		LOG("CB: RX OUTPUT REPORT LEN %lu: ", output_report->size);
		for(uint32_t j = 0; j < output_report->size; j++){
			LOG("%.2x", rd8_unaligned(output_report->report + j));
		}
		LOG("\n");
	#endif

	// ========================
	// Transmit an input report
	// ========================

	// Variables
	tru_usb_pc_epi_t *epin = tru_hid_get_report_epi_from_epo(hid, ep);
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

	// ========================================
	// Prepare to receive another output report
	// ========================================

	tru_usb_pc_receive(hid->pc, ep->num, HID_CUS_OUTPUT_REPORT_VARCOUNT, HID_CUS_OUTPUT_REPORT_VARCOUNT);
}

void cb_input_report_compl(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep){
}

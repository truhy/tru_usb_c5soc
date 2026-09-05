#include "hid_gamepad1.h"
#include "tru_logger.h"
#include <stdlib.h>

// Function prototypes
void __attribute__((weak)) hid_gamepad1_update_controller(tru_hid_gamepad1_input_report_t *report);
void hid_gamepad1_transmit_report(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep);
static void cb_reset(tru_usb_hid_t *hid);
static void cb_enumdone(tru_usb_hid_t *hid);
static bool cb_setup(tru_usb_hid_t *hid);
static void cb_set_report(tru_usb_hid_t *hid, tru_usb_hid_interface_ext_t *intf_ext, tru_usb_hid_report_info_t *report_info, uint8_t report_id, uint8_t report_type);
static void cb_config(tru_usb_hid_t *hid, tru_usb_config_t *config, bool is_activated);
static void cb_output_report_act(tru_usb_hid_t *hid, tru_usb_pc_epo_t *ep, bool is_activated);
static void cb_input_report_act(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep, bool is_activated);
static void cb_output_report_compl(tru_usb_hid_t *hid, tru_usb_pc_epo_t *ep);
static void cb_input_report_compl(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep);

void hid_gamepad1_init(
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
		get_hid_gamepad1_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);

	tru_usb_hid_init(hid, pc, get_hid_gamepad1_pd_info());

	// Register callback functions
	tru_usb_hid_register_cb_reset(hid, cb_reset);
	tru_usb_hid_register_cb_enumdone(hid, cb_enumdone);
	tru_usb_hid_register_cb_setup(hid, cb_setup);
	tru_usb_hid_register_cb_set_report(hid, cb_set_report);
	tru_usb_hid_register_cb_cfg_act(hid, cb_config);
	tru_usb_hid_register_cb_epo_act(hid, HID_GAMEPAD1_OUT_REPORT_EPNUM, cb_output_report_act);
	tru_usb_hid_register_cb_epi_act(hid, HID_GAMEPAD1_IN_REPORT_EPNUM, cb_input_report_act);
	tru_usb_hid_register_cb_epo_compl(hid, HID_GAMEPAD1_OUT_REPORT_EPNUM, cb_output_report_compl);
	tru_usb_hid_register_cb_epi_compl(hid, HID_GAMEPAD1_IN_REPORT_EPNUM, cb_input_report_compl);
}

void hid_gamepad1_deinit(tru_usb_hid_t *hid){
	tru_usb_hid_deinit(hid);
	tru_usb_pc_deinit(hid->pc);
}

void hid_gamepad1_init_controller(void){
}

// Weak function for application layer
void hid_gamepad1_update_controller(tru_hid_gamepad1_input_report_t *report){
	/*
	report->buttons.val = 0;
	#if HID_GAMEPAD1_POS_RES
		report->x = 0;
		report->y = 0;
		report->z = 0;
	#endif
	#if HID_GAMEPAD1_ROT_RES
		report->rx = 0;
		report->ry = 0;
		report->rz = 0;
	#endif
	*/
}

void hid_gamepad1_transmit_report(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep){
	// ========================
	// Transmit an input report
	// ========================

	tru_usb_hid_report_info_t *input_report_info = tru_hid_get_next_input_report_info(ep, hid->pc->dma_mode);  // Get the next input report.  Ensure this is executed only once per transmit

	// Update the report
	switch(input_report_info->id){
		case HID_GAMEPAD1_INPUT_REPORT_ID:
			hid_gamepad1_update_controller((tru_hid_gamepad1_input_report_t *)input_report_info->report);
			break;
		default:
	}

	tru_usb_pc_transmit(hid->pc, ep->num, input_report_info->size, input_report_info->size);
}

// =========
// Callbacks
// =========

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
}

void cb_input_report_act(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep, bool is_activated){
	if(is_activated){
		hid_gamepad1_transmit_report(hid, ep);
	}
}

void cb_output_report_compl(tru_usb_hid_t *hid, tru_usb_pc_epo_t *ep){
}

void cb_input_report_compl(tru_usb_hid_t *hid, tru_usb_pc_epi_t *ep){
	hid_gamepad1_transmit_report(hid, ep);
}

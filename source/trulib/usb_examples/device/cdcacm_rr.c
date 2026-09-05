#include "cdcacm_rr.h"
#include "tru_logger.h"

typedef enum{
	CDCACM_RR_REQ_NONE,
	CDCACM_RR_REQ_RATE_TEST,
	CDCACM_RR_REQ_VERIFY_TEST
}cdcacm_rr_req_t;

static void fill_sample_data(void);
static void receive_data(tru_usb_pc_t *pc, uint8_t ep_num);
static void transmit_data(tru_usb_pc_t *pc, uint8_t ep_num);
static void extract_cmd_params(void);
static void process_cmd(tru_usb_cdc_t *cdc);
static void cb_reset(tru_usb_cdc_t *cdc);
static void cb_enumdone(tru_usb_cdc_t *cdc);
static void cb_ntf_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated);
static void cb_txd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated);
static void cb_rxd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep, bool is_activated);
static void cb_ntf_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep);
static void cb_ntf_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep);
static void cb_rxd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep);
static void cb_rxd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep);
static void cb_txd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep);
static void cb_txd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep);
static void cb_setlinecontrol(tru_usb_cdc_t *cdc, tru_usb_interface_alt_setting_t *alt_setting, tru_usb_cdc_linecontrol_t *linecontrol);
static void cb_sendbreak(tru_usb_cdc_t *cdc, tru_usb_interface_alt_setting_t *alt_setting, uint16_t dur_ms);

static tru_usb_pc_epi_t *ntf_ep;
static tru_usb_pc_epo_t *rxd_ep;
static tru_usb_pc_epi_t *txd_ep;

static uint8_t cmd;
static uint32_t cmd_param_read_len;
static uint32_t cmd_param_write_len;

void cdcacm_rr_init(
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
		get_cdcacm_rr_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);
	tru_usb_cdc_init(cdc, pc, get_cdcacm_rr_pd_info());

	cdcacm_rr_cb_setup_buffers();

	ntf_ep = &pc->eps.epis[CDCACM_RR_NTF_EPNUM];
	txd_ep = &pc->eps.epis[CDCACM_RR_TXD_EPNUM];
	rxd_ep = &pc->eps.epos[CDCACM_RR_RXD_EPNUM];

	cmd_param_read_len = 0;

	fill_sample_data();

	// Register callback functions
	tru_usb_cdc_register_cb_reset(cdc, cb_reset);
	tru_usb_cdc_register_cb_enumdone(cdc, cb_enumdone);
	tru_usb_cdc_register_cb_epi_act(cdc, CDCACM_RR_NTF_EPNUM, cb_ntf_act);
	tru_usb_cdc_register_cb_epo_act(cdc, CDCACM_RR_RXD_EPNUM, cb_rxd_act);
	tru_usb_cdc_register_cb_epi_act(cdc, CDCACM_RR_TXD_EPNUM, cb_txd_act);
	tru_usb_cdc_register_cb_epi_chunk(cdc, CDCACM_RR_NTF_EPNUM, cb_ntf_chunk);
	tru_usb_cdc_register_cb_epi_compl(cdc, CDCACM_RR_NTF_EPNUM, cb_ntf_compl);
	tru_usb_cdc_register_cb_epo_chunk(cdc, CDCACM_RR_RXD_EPNUM, cb_rxd_chunk);
	tru_usb_cdc_register_cb_epo_compl(cdc, CDCACM_RR_RXD_EPNUM, cb_rxd_compl);
	tru_usb_cdc_register_cb_epi_chunk(cdc, CDCACM_RR_TXD_EPNUM, cb_txd_chunk);
	tru_usb_cdc_register_cb_epi_compl(cdc, CDCACM_RR_TXD_EPNUM, cb_txd_compl);
	tru_usb_cdc_register_cb_setlinecontrol(cdc, cb_setlinecontrol);
	tru_usb_cdc_register_cb_sendbreak(cdc, cb_sendbreak);
}

void cdcacm_rr_deinit(tru_usb_cdc_t *cdc){
	tru_usb_cdc_deinit(cdc);
	tru_usb_pc_deinit(cdc->pc);
}

void fill_sample_data(void){
	uint8_t k = 0;

	for(uint32_t i = 0; i < txd_ep->lxfer.chunk.num_registered; i++){
		for(uint32_t j = 0; j < txd_ep->lxfer.chunk.buffers[i].buf_size; j++){
			w8_unaligned(txd_ep->lxfer.chunk.buffers[i].buf + j, k);
			k++;
		}
	}
}

void receive_data(tru_usb_pc_t *pc, uint8_t ep_num){
	#if defined(CDCACM_RR_WIN_QUIRK_HST_NOZLP) && CDCACM_RR_WIN_QUIRK_HST_NOZLP == 1
		rxd_ep->lxfer.chunk.xfer_limit = rxd_ep->mps;  // Limit transfer to one MPS packet only
	#endif
	cmd_param_read_len = 0;
	tru_usb_pc_receive(pc, ep_num, CDCACM_RR_RXD_MAX_EXP_LEN, CDCACM_RR_RXD_MAX_EXP_LEN);
}

/*
	Oracle VirtualBox USB 2.0 guest emulation bug
	=============================================

	I think there is a bug in the buffer threshold scheme used for passing data to the guest.   The scheme is greedy, it
	wants more data than the requested transfer size.  For example, when we have completely sent out data, VirtualBox
	continues and repeatedly sends out the USB IN token request, but our USB device has no more data to send!

	This issue causes the serial application within the VM guest (Ubuntu) to either:
	a. hang when timeout is set to infinity, or
	b. time out waiting for the data
	Our data is completely transferred to VirtualBox - I see a transfer complete interrupt is triggered by our USB controller,
	but the data is not passed onto the guest (Ubuntu), it is held (buffered) by VirtualBox.  Data is passed only when enough
	data is received that reaches its own buffer threshold level.

	This bug is caused by VirtualBox, everything works correctly in Ubuntu on a real machine.
*/
void transmit_data(tru_usb_pc_t *pc, uint8_t ep_num){
	#if defined(CDCACM_RR_WIN_QUIRK_DEV_NOZLP4K) && CDCACM_RR_WIN_QUIRK_DEV_NOZLP4K == 1
		tru_usb_pc_transmit(pc, ep_num, cmd_param_write_len, INT_ALIGN_UP(cmd_param_write_len, 4096));  // Working on Linux and Windows (see Windows expected transfer length)
	#elif defined(CDCACM_RR_WIN_QUIRK_DEV_FORCEZLP) && CDCACM_RR_WIN_QUIRK_DEV_FORCEZLP == 1
		tru_usb_pc_transmit(pc, ep_num, cmd_param_write_len, 0);  // Ignores condition 1.  Always send a ZLP.  Working on Linux but not Windows
	#else
		tru_usb_pc_transmit(pc, ep_num, cmd_param_write_len, cmd_param_write_len);  // This is correct to the USB spec, but does not work on Linux and Windows when the transfer size is MPS!
	#endif
}

void extract_cmd_params(void){
	if(cmd_param_read_len == 0){
		if(rxd_ep->lxfer.whole.total_xferred_size > 0){  // Not a ZLP?
			if(rxd_ep->lxfer.whole.offset == 0){  // Beginning of data?
				// Extract parameters from the received data
				uint8_t *data = rxd_ep->lxfer.chunk.buffers[0].buf;
				cmd = U32_B0(data[0]);
				cmd_param_read_len = buf_le_to_u32(data + 1);
				cmd_param_write_len = buf_le_to_u32(data + 1 + 4);

				rxd_ep->lxfer.whole.total_xfer_size = cmd_param_read_len;  // Set to the actual transfer length
				rxd_ep->lxfer.chunk.xfer_limit = 0;  // Remove limit
			}
		}
	}
}

void process_cmd(tru_usb_cdc_t *cdc){
	if(cmd_param_read_len > 0 && rxd_ep->lxfer.whole.total_xferred_size >= cmd_param_read_len){
		switch(cmd){
			case CDCACM_RR_REQ_RATE_TEST:
				transmit_data(cdc->pc, txd_ep->num);
				receive_data(cdc->pc, rxd_ep->num);
				break;
			case CDCACM_RR_REQ_VERIFY_TEST:
				transmit_data(cdc->pc, txd_ep->num);
				receive_data(cdc->pc, rxd_ep->num);
				break;
		}
	}
}

// ==========
// Call backs
// ==========

// Is called when USB resets
void cb_reset(tru_usb_cdc_t *cdc){
}

// Callback when USB enumeration is done
void cb_enumdone(tru_usb_cdc_t *cdc){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: ENUMDONE\n");
#endif
}

void cb_ntf_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	if(is_activated){
		LOG("CB: NOTIF EP ACTIVATED\n");
	}else{
		LOG("CB: NOTIF EP DEACTIVATED\n");
	}
#endif
}

void cb_txd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	if(is_activated){
		LOG("CB: WRITE EP ACTIVATED\n");
	}else{
		LOG("CB: WRITE EP DEACTIVATED\n");
	}
#endif

	if(is_activated){
		process_cmd(cdc);
	}
}

void cb_rxd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep, bool is_activated){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	if(is_activated){
		LOG("CB: READ EP ACTIVATED\n");
	}else{
		LOG("CB: READ EP DEACTIVATED\n");
	}
#endif

	if(is_activated){
		receive_data(cdc->pc, rxd_ep->num);

		tru_usb_cdc_uartstate_t uartstate = tru_usb_cdc_get_serial_state(cdc, CDCACM_RR_NTF_ITFNUM);
		uartstate.bits.dsr = 1;  // DSR high typically used for indicating the terminal side that this device is ready to accept data
		tru_usb_cdc_set_serial_state(cdc, CDCACM_RR_NTF_ITFNUM, &uartstate);
		tru_usb_cdc_tx_notif_serial_state(cdc, CDCACM_RR_NTF_EPNUM, CDCACM_RR_NTF_ITFNUM, true);  // Transmit serial state notification if it has changed
	}else{
		cmd_param_read_len = 0;
	}
}

void cb_ntf_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
}

void cb_ntf_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: COMPL (NTF EP), XFERRED=%lu\n", ep->lxfer.chunk.total_xferred_size);
#endif
}

void cb_rxd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: CHUNK (RX DATA EP), XFERRED=%lu\n", rxd_ep->lxfer.chunk.total_xferred_size);
#endif

	extract_cmd_params();
}

void cb_rxd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: COMPL (RX DATA EP), XFERRED=%lu\n", rxd_ep->lxfer.whole.total_xferred_size);
#endif

	process_cmd(cdc);
}

void cb_txd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: CHUNK (TX DATA EP), XFERRED=%lu\n", ep->lxfer.chunk.total_xferred_size);
#endif
}

void cb_txd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: COMPL (TX DATA EP), XFERRED=%lu\n", ep->lxfer.whole.total_xferred_size);
#endif
}

void cb_setlinecontrol(tru_usb_cdc_t *cdc, tru_usb_interface_alt_setting_t *alt_setting, tru_usb_cdc_linecontrol_t *linecontrol){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: SET_LINE_CONTROL ITF=%u ALT=%u DTR=%u RTS=%u\n", alt_setting->interface_num, alt_setting->alt_setting_num, linecontrol->bits.dtr, linecontrol->bits.rts);
#endif
}

void cb_sendbreak(tru_usb_cdc_t *cdc, tru_usb_interface_alt_setting_t *alt_setting, uint16_t dur_ms){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: SEND_BREAK ITF=%u ALT=%u DUR=%u ms\n", alt_setting->interface_num, alt_setting->alt_setting_num, dur_ms);
#endif
}

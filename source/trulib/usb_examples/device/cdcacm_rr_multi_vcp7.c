#include "cdcacm_rr_multi_vcp7.h"

#if CDCACM_RR_MULTI_NUM_PORTS >= 7
typedef enum cdcacm_rr_multi_vcp7_cmd_e{
	CDCACM_RR_MULTI_VCP7_REQ_NONE,
	CDCACM_RR_MULTI_VCP7_REQ_RATE_TEST,
	CDCACM_RR_MULTI_VCP7_REQ_VERIFY_TEST
}cdcacm_rr_multi_vcp7_req_t;

static void fill_sample_data(void);
static void receive_data(tru_usb_pc_t *pc, uint8_t ep_num);
static void transmit_data(tru_usb_pc_t *pc, uint8_t ep_num);
static void extract_cmd_params(void);
static void process_cmd(tru_usb_cdc_t *cdc);
static void cb_ntf_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated);
static void cb_rxd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep, bool is_activated);
static void cb_txd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated);
static void cb_ntf_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep);
static void cb_ntf_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep);
static void cb_rxd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep);
static void cb_rxd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep);
static void cb_txd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep);
static void cb_txd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep);

static tru_usb_pc_epi_t *ntf_ep;
static tru_usb_pc_epo_t *rxd_ep;
static tru_usb_pc_epi_t *txd_ep;

static uint8_t cmd;
static uint32_t cmd_param_read_len;
static uint32_t cmd_param_write_len;

void cdcacm_rr_multi_vcp7_init(tru_usb_cdc_t *cdc){
	ntf_ep = &cdc->pc->eps.epis[CDCACM_RR_MULTI_VCP7_NTF_EPNUM];
	rxd_ep = &cdc->pc->eps.epos[CDCACM_RR_MULTI_VCP7_RXD_EPNUM];
	txd_ep = &cdc->pc->eps.epis[CDCACM_RR_MULTI_VCP7_TXD_EPNUM];

	cmd_param_read_len = 0;

	fill_sample_data();

	// Register callback functions
	tru_usb_cdc_register_cb_epi_act(cdc, CDCACM_RR_MULTI_VCP7_NTF_EPNUM, cb_ntf_act);
	tru_usb_cdc_register_cb_epo_act(cdc, CDCACM_RR_MULTI_VCP7_RXD_EPNUM, cb_rxd_act);
	tru_usb_cdc_register_cb_epi_act(cdc, CDCACM_RR_MULTI_VCP7_TXD_EPNUM, cb_txd_act);
	tru_usb_cdc_register_cb_epi_chunk(cdc, CDCACM_RR_MULTI_VCP7_NTF_EPNUM, cb_ntf_chunk);
	tru_usb_cdc_register_cb_epi_compl(cdc, CDCACM_RR_MULTI_VCP7_NTF_EPNUM, cb_ntf_compl);
	tru_usb_cdc_register_cb_epo_chunk(cdc, CDCACM_RR_MULTI_VCP7_RXD_EPNUM, cb_rxd_chunk);
	tru_usb_cdc_register_cb_epo_compl(cdc, CDCACM_RR_MULTI_VCP7_RXD_EPNUM, cb_rxd_compl);
	tru_usb_cdc_register_cb_epi_chunk(cdc, CDCACM_RR_MULTI_VCP7_TXD_EPNUM, cb_txd_chunk);
	tru_usb_cdc_register_cb_epi_compl(cdc, CDCACM_RR_MULTI_VCP7_TXD_EPNUM, cb_txd_compl);
}

void cdcacm_rr_multi_vcp7_deinit(void){
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
	#if defined(CDCACM_RR_MULTI_WIN_QUIRK_HST_NOZLP) && CDCACM_RR_MULTI_WIN_QUIRK_HST_NOZLP == 1
		rxd_ep->lxfer.chunk.xfer_limit = rxd_ep->mps;
	#endif
	cmd_param_read_len = 0;
	tru_usb_pc_receive(pc, ep_num, CDCACM_RR_MULTI_RXD_MAX_EXP_LEN, CDCACM_RR_MULTI_RXD_MAX_EXP_LEN);
}

void transmit_data(tru_usb_pc_t *pc, uint8_t ep_num){
	#if defined(CDCACM_RR_MULTI_WIN_QUIRK_DEV_NOZLP4K) && CDCACM_RR_MULTI_WIN_QUIRK_DEV_NOZLP4K == 1
		tru_usb_pc_transmit(pc, ep_num, cmd_param_write_len, INT_ALIGN_UP(cmd_param_write_len, 4096));  // Working on Linux and Windows (see Windows expected transfer length)
	#elif defined(CDCACM_RR_MULTI_WIN_QUIRK_DEV_FORCEZLP) && CDCACM_RR_MULTI_WIN_QUIRK_DEV_FORCEZLP == 1
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
				cmd = data[0];
				cmd_param_read_len = buf_le_to_u32(data + 1);
				cmd_param_write_len = buf_le_to_u32(data + 1 + 4);

				// Set to the actual transfer length
				rxd_ep->lxfer.whole.total_xfer_size = cmd_param_read_len;
				rxd_ep->lxfer.chunk.xfer_limit = 0;
			}
		}
	}
}

void process_cmd(tru_usb_cdc_t *cdc){
	if(cmd_param_read_len > 0 && rxd_ep->lxfer.whole.total_xferred_size >= cmd_param_read_len){
		switch(cmd){
			case CDCACM_RR_MULTI_VCP7_REQ_RATE_TEST:
				transmit_data(cdc->pc, txd_ep->num);
				receive_data(cdc->pc, rxd_ep->num);
				break;
			case CDCACM_RR_MULTI_VCP7_REQ_VERIFY_TEST:
				transmit_data(cdc->pc, txd_ep->num);
				receive_data(cdc->pc, rxd_ep->num);
				break;
		}
	}
}

// =========
// Callbacks
// =========

// Is called when the endpoint has activated
void cb_ntf_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated){
}

// Is called when the endpoint has activated
void cb_rxd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep, bool is_activated){
	if(is_activated){
		receive_data(cdc->pc, ep->num);

		tru_usb_cdc_uartstate_t uartstate = tru_usb_cdc_get_serial_state(cdc, CDCACM_RR_MULTI_VCP7_NTF_ITFNUM);
		uartstate.bits.dsr = 1;  // DSR high indicates to the terminal this device is ready to accept data
		tru_usb_cdc_set_serial_state(cdc, CDCACM_RR_MULTI_VCP7_NTF_ITFNUM, &uartstate);
		tru_usb_cdc_tx_notif_serial_state(cdc, CDCACM_RR_MULTI_VCP7_NTF_EPNUM, CDCACM_RR_MULTI_VCP7_NTF_ITFNUM, true);  // Transmit serial state notification if it has changed
	}else{
		cmd_param_read_len = 0;
	}
}

// Is called when the endpoint has activated
void cb_txd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated){
	if(is_activated){
		process_cmd(cdc);
	}
}

void cb_ntf_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
}

void cb_ntf_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
}

void cb_rxd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep){
	extract_cmd_params();
}

void cb_rxd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep){
	process_cmd(cdc);
}

void cb_txd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
}

void cb_txd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
}

#endif

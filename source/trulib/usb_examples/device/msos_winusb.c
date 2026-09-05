#include "msos_winusb.h"
#include "tru_logger.h"
#include "tru_util.h"

typedef enum msos_winusb_cmd_e{
	MSOS_WINUSB_REQ_NONE,
	MSOS_WINUSB_REQ_RATE_TEST,
	MSOS_WINUSB_REQ_VERIFY_TEST
}msos_winusb_req_t;

// Function prototypes
static void fill_sample_data(void);
static void cb_reset(tru_usb_msos_t *msos);
static void cb_enumdone(tru_usb_msos_t *msos);
static void cb_rxd_act(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep, bool is_activated);
static void cb_txd_act(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep, bool is_activated);
static void cb_rxd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep);
static void cb_rxd_compl(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep);
static void cb_txd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep);
static void cb_txd_compl(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep);

static tru_usb_pc_epo_t *rxd_ep;
static tru_usb_pc_epi_t *txd_ep;

static uint8_t cmd;
static uint32_t cmd_param_write_len;

void msos_winusb_init(
	tru_usb_pc_t *pc,
	tru_usb_msos_t *msos,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode
){
	tru_usb_pc_init(
		pc,
		get_msos_winusb_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);
	tru_usb_msos_init(msos, pc, get_msos_winusb_pd_info());

	msos_winusb_cb_setup_buffers();

	rxd_ep = &msos->pc->eps.epos[MSOS_WINUSB_RXD_EPNUM];
	txd_ep = &msos->pc->eps.epis[MSOS_WINUSB_TXD_EPNUM];

	cmd = MSOS_WINUSB_REQ_NONE;
	cmd_param_write_len = 0;

	fill_sample_data();

	// Register callback functions
	tru_usb_msos_register_cb_reset(msos, cb_reset);
	tru_usb_msos_register_cb_enumdone(msos, cb_enumdone);
	tru_usb_msos_register_cb_epo_act(msos, MSOS_WINUSB_RXD_EPNUM, cb_rxd_act);
	tru_usb_msos_register_cb_epi_act(msos, MSOS_WINUSB_TXD_EPNUM, cb_txd_act);
	tru_usb_msos_register_cb_epo_chunk(msos, MSOS_WINUSB_RXD_EPNUM, cb_rxd_chunk);
	tru_usb_msos_register_cb_epo_compl(msos, MSOS_WINUSB_RXD_EPNUM, cb_rxd_compl);
	tru_usb_msos_register_cb_epi_chunk(msos, MSOS_WINUSB_TXD_EPNUM, cb_txd_chunk);
	tru_usb_msos_register_cb_epi_compl(msos, MSOS_WINUSB_TXD_EPNUM, cb_txd_compl);
}

void msos_winusb_deinit(tru_usb_msos_t *msos){
	tru_usb_msos_deinit(msos);
	tru_usb_pc_deinit(msos->pc);
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

// ==========
// Call backs
// ==========

void cb_reset(tru_usb_msos_t *msos){
}

void cb_enumdone(tru_usb_msos_t *msos){
}

void cb_rxd_act(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep, bool is_activated){
	if(is_activated){
		tru_usb_pc_receive(msos->pc, rxd_ep->num, MSOS_WINUSB_RXD_MAX_EXP_LEN, MSOS_WINUSB_RXD_MAX_EXP_LEN);
	}
}

void cb_txd_act(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep, bool is_activated){
}

void cb_rxd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP1 RX CHUNK, XFERRED=%lu\n", ep->lxfer.chunk.total_xferred_size);
#endif

	if(msos->pc->eps.epos[MSOS_WINUSB_RXD_EPNUM].lxfer.whole.total_xferred_size > 0){  // Not a ZLP?
		if(rxd_ep->lxfer.whole.offset == 0){  // Beginning of data?
			// Extract parameters from the received data
			uint8_t *data = rxd_ep->lxfer.chunk.buffers[0].buf;
			cmd = data[0];
			cmd_param_write_len = buf_le_to_u32(data + 1);
		}
	}
}

void cb_rxd_compl(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP1 RX LONG COMPL, XFERRED=%lu\n", ep->lxfer.whole.total_xferred_size);
#endif

	if(ep->lxfer.whole.total_xferred_size > 0){  // Not a ZLP?
		if(rxd_ep->lxfer.whole.offset == 0){  // Beginning of data?
			// Extract parameters from the received data
			uint8_t *data = rxd_ep->lxfer.chunk.buffers[0].buf;
			cmd = data[0];
			cmd_param_write_len = buf_le_to_u32(data + 1);
		}

		switch(cmd){
			case MSOS_WINUSB_REQ_RATE_TEST:
				tru_usb_pc_transmit(msos->pc, txd_ep->num, cmd_param_write_len, cmd_param_write_len);
				break;
			case MSOS_WINUSB_REQ_VERIFY_TEST:
				tru_usb_pc_transmit(msos->pc, txd_ep->num, cmd_param_write_len, cmd_param_write_len);
				break;
		}
	}

	tru_usb_pc_receive(msos->pc, rxd_ep->num, MSOS_WINUSB_RXD_MAX_EXP_LEN, MSOS_WINUSB_RXD_MAX_EXP_LEN);
}

void cb_txd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep){
}

void cb_txd_compl(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP1 TX LONG COMPL, XFERRED=%lu\n", ep->lxfer.whole.total_xferred_size);
#endif
}

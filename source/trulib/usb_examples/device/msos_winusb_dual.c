#include "msos_winusb_dual.h"
#include "tru_logger.h"
#include "tru_util.h"

typedef enum msos_winusb_dual_req_e{
	MSOS_WINUSB_DUAL_REQ_NONE,
	MSOS_WINUSB_DUAL_REQ_RATE_TEST,
	MSOS_WINUSB_DUAL_REQ_VERIFY_TEST
}msos_winusb_dual_req_t;

// Function prototypes
static void p0_fill_sample_data(void);
static void p1_fill_sample_data(void);
static void cb_reset(tru_usb_msos_t *msos);
static void cb_enumdone(tru_usb_msos_t *msos);
static void p0_cb_rxd_act(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep, bool is_activated);
static void p0_cb_txd_act(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep, bool is_activated);
static void p0_cb_rxd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep);
static void p0_cb_rxd_compl(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep);
static void p0_cb_txd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep);
static void p0_cb_txd_compl(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep);
static void p1_cb_rxd_act(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep, bool is_activated);
static void p1_cb_txd_act(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep, bool is_activated);
static void p1_cb_rxd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep);
static void p1_cb_rxd_compl(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep);
static void p1_cb_txd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep);
static void p1_cb_txd_compl(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep);

static tru_usb_pc_epo_t *p0_rxd_ep;
static tru_usb_pc_epi_t *p0_txd_ep;
static tru_usb_pc_epo_t *p1_rxd_ep;
static tru_usb_pc_epi_t *p1_txd_ep;

static uint8_t p0_cmd;
static uint32_t p0_cmd_param_write_len;
static uint8_t p1_cmd;
static uint32_t p1_cmd_param_write_len;

void msos_winusb_dual_init(
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
		get_msos_winusb_dual_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);
	tru_usb_msos_init(msos, pc, get_msos_winusb_dual_pd_info());

	msos_winusb_multi_cb_setup_buffers();

	p0_rxd_ep = &msos->pc->eps.epos[MSOS_WINUSB_DUAL_P0_RXD_EPNUM];
	p0_txd_ep = &msos->pc->eps.epis[MSOS_WINUSB_DUAL_P0_TXD_EPNUM];
	p1_rxd_ep = &msos->pc->eps.epos[MSOS_WINUSB_DUAL_P1_RXD_EPNUM];
	p1_txd_ep = &msos->pc->eps.epis[MSOS_WINUSB_DUAL_P1_TXD_EPNUM];

	p0_cmd = MSOS_WINUSB_DUAL_REQ_NONE;
	p0_cmd_param_write_len = 0;
	p1_cmd = MSOS_WINUSB_DUAL_REQ_NONE;
	p1_cmd_param_write_len = 0;

	p0_fill_sample_data();
	p1_fill_sample_data();

	// Register callback functions
	tru_usb_msos_register_cb_reset(msos, cb_reset);
	tru_usb_msos_register_cb_enumdone(msos, cb_enumdone);
	tru_usb_msos_register_cb_epo_act(msos, MSOS_WINUSB_DUAL_P0_RXD_EPNUM, p0_cb_rxd_act);
	tru_usb_msos_register_cb_epi_act(msos, MSOS_WINUSB_DUAL_P0_TXD_EPNUM, p0_cb_txd_act);
	tru_usb_msos_register_cb_epo_chunk(msos, MSOS_WINUSB_DUAL_P0_RXD_EPNUM, p0_cb_rxd_chunk);
	tru_usb_msos_register_cb_epo_compl(msos, MSOS_WINUSB_DUAL_P0_RXD_EPNUM, p0_cb_rxd_compl);
	tru_usb_msos_register_cb_epi_chunk(msos, MSOS_WINUSB_DUAL_P0_TXD_EPNUM, p0_cb_txd_chunk);
	tru_usb_msos_register_cb_epi_compl(msos, MSOS_WINUSB_DUAL_P0_TXD_EPNUM, p0_cb_txd_compl);
	tru_usb_msos_register_cb_epo_act(msos, MSOS_WINUSB_DUAL_P1_RXD_EPNUM, p1_cb_rxd_act);
	tru_usb_msos_register_cb_epi_act(msos, MSOS_WINUSB_DUAL_P1_TXD_EPNUM, p1_cb_txd_act);
	tru_usb_msos_register_cb_epo_chunk(msos, MSOS_WINUSB_DUAL_P1_RXD_EPNUM, p1_cb_rxd_chunk);
	tru_usb_msos_register_cb_epo_compl(msos, MSOS_WINUSB_DUAL_P1_RXD_EPNUM, p1_cb_rxd_compl);
	tru_usb_msos_register_cb_epi_chunk(msos, MSOS_WINUSB_DUAL_P1_TXD_EPNUM, p1_cb_txd_chunk);
	tru_usb_msos_register_cb_epi_compl(msos, MSOS_WINUSB_DUAL_P1_TXD_EPNUM, p1_cb_txd_compl);
}

void msos_winusb_dual_deinit(tru_usb_msos_t *msos){
	tru_usb_msos_deinit(msos);
	tru_usb_pc_deinit(msos->pc);
}

void p0_fill_sample_data(void){
	uint8_t k = 0;

	for(uint32_t i = 0; i < p0_txd_ep->lxfer.chunk.num_registered; i++){
		for(uint32_t j = 0; j < p0_txd_ep->lxfer.chunk.buffers[i].buf_size; j++){
			w8_unaligned(p0_txd_ep->lxfer.chunk.buffers[i].buf + j, k);
			k++;
		}
	}
}

void p1_fill_sample_data(void){
	uint8_t k = 0;

	for(uint32_t i = 0; i < p1_txd_ep->lxfer.chunk.num_registered; i++){
		for(uint32_t j = 0; j < p1_txd_ep->lxfer.chunk.buffers[i].buf_size; j++){
			w8_unaligned(p1_txd_ep->lxfer.chunk.buffers[i].buf + j, k);
			k++;
		}
	}
}

void p1_inc_sample_data(void){
	for(uint32_t i = 0; i < p1_txd_ep->lxfer.chunk.num_registered; i++){
		for(uint32_t j = 0; j < p1_txd_ep->lxfer.chunk.buffers[i].buf_size; j++){
			for(uint32_t j = 0; j < p1_txd_ep->lxfer.chunk.buffers[i].xfer_size; j++){
				p1_txd_ep->lxfer.chunk.buffers[i].buf[j]++;
			}
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

void p0_cb_rxd_act(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep, bool is_activated){
	if(is_activated){
		tru_usb_pc_receive(msos->pc, p0_rxd_ep->num, MSOS_WINUSB_DUAL_RXD_MAX_EXP_LEN, MSOS_WINUSB_DUAL_RXD_MAX_EXP_LEN);
	}
}

void p0_cb_txd_act(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep, bool is_activated){
}

void p0_cb_rxd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP1 RX CHUNK\n");
#endif

	if(ep->lxfer.whole.total_xferred_size > 0){  // Not a ZLP?
		if(p0_rxd_ep->lxfer.whole.offset == 0){  // Beginning of data?
			uint8_t *data = p0_rxd_ep->lxfer.chunk.buffers[0].buf;

			// Extract parameters from the received data
			p0_cmd = data[0];
			p0_cmd_param_write_len = buf_le_to_u32(data + 1);
		}
	}
}

void p0_cb_rxd_compl(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP1 RX COMPL\n");
#endif

	if(ep->lxfer.whole.total_xferred_size > 0){  // Not a ZLP?
		if(p0_rxd_ep->lxfer.whole.offset == 0){  // Beginning of data?
			uint8_t *data = p0_rxd_ep->lxfer.chunk.buffers[0].buf;

			// Extract parameters from the received data
			p0_cmd = data[0];
			p0_cmd_param_write_len = buf_le_to_u32(data + 1);
		}

		switch(p0_cmd){
			case MSOS_WINUSB_DUAL_REQ_RATE_TEST:
				tru_usb_pc_transmit(msos->pc, p0_txd_ep->num, p0_cmd_param_write_len, p0_cmd_param_write_len);
				break;
			case MSOS_WINUSB_DUAL_REQ_VERIFY_TEST:
				tru_usb_pc_transmit(msos->pc, p0_txd_ep->num, p0_cmd_param_write_len, p0_cmd_param_write_len);
				break;
		}
	}

	tru_usb_pc_receive(msos->pc, p0_rxd_ep->num, MSOS_WINUSB_DUAL_RXD_MAX_EXP_LEN, MSOS_WINUSB_DUAL_RXD_MAX_EXP_LEN);
}

void p0_cb_txd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep){
}

void p0_cb_txd_compl(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP1 TX COMPL\n");
#endif
}

void p1_cb_rxd_act(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep, bool is_activated){
	if(is_activated){
		tru_usb_pc_receive(msos->pc, p1_rxd_ep->num, MSOS_WINUSB_DUAL_RXD_MAX_EXP_LEN, MSOS_WINUSB_DUAL_RXD_MAX_EXP_LEN);
	}
}

void p1_cb_txd_act(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep, bool is_activated){
}

void p1_cb_rxd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP1 RX CHUNK\n");
#endif

	if(ep->lxfer.whole.total_xferred_size > 0){  // Not a ZLP?
		if(p1_rxd_ep->lxfer.whole.offset == 0){  // Beginning of data?
			uint8_t *data = p1_rxd_ep->lxfer.chunk.buffers[0].buf;

			// Extract parameters from the received data
			p1_cmd = data[0];
			p1_cmd_param_write_len = buf_le_to_u32(data + 1);
		}
	}
}

void p1_cb_rxd_compl(tru_usb_msos_t *msos, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP2 RX COMPL\n");
#endif

	if(ep->lxfer.whole.total_xferred_size > 0){  // Not a ZLP?
		if(p1_rxd_ep->lxfer.whole.offset == 0){  // Beginning of data?
			uint8_t *data = p1_rxd_ep->lxfer.chunk.buffers[0].buf;

			// Extract parameters from the received data
			p1_cmd = data[0];
			p1_cmd_param_write_len = buf_le_to_u32(data + 1);
		}

		switch(p1_cmd){
			case MSOS_WINUSB_DUAL_REQ_RATE_TEST:
				tru_usb_pc_transmit(msos->pc, p1_txd_ep->num, p1_cmd_param_write_len, p1_cmd_param_write_len);
				break;
			case MSOS_WINUSB_DUAL_REQ_VERIFY_TEST:
				p1_inc_sample_data();
				tru_usb_pc_transmit(msos->pc, p1_txd_ep->num, p1_cmd_param_write_len, p1_cmd_param_write_len);
				break;
		}
	}

	tru_usb_pc_receive(msos->pc, p1_rxd_ep->num, MSOS_WINUSB_DUAL_RXD_MAX_EXP_LEN, MSOS_WINUSB_DUAL_RXD_MAX_EXP_LEN);
}

void p1_cb_txd_chunk(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep){
}

void p1_cb_txd_compl(tru_usb_msos_t *msos, tru_usb_pc_epi_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: EP2 TX COMPL\n");
#endif
}

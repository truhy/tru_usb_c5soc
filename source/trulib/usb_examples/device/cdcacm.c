#include "cdcacm.h"
#include "tru_logger.h"

#if defined(CDCACM_ECHO) && CDCACM_ECHO == 1
static NONCACHEABLE_SECTION uint8_t rxd_holding_buffer[CDCACM_ECHO_BUFFER_SIZE];
static uint32_t rxd_holding_woffset = 0;

static uint32_t transmit_data(tru_usb_pc_t *pc, uint8_t ep_num, uint32_t write_len);
static void echo(tru_usb_cdc_t *cdc, bool holding_buffer);
#endif

static uint32_t receive_data(tru_usb_pc_t *pc, uint8_t ep_num);
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

void cdcacm_init(
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
		get_cdcacm_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);
	tru_usb_cdc_init(cdc, pc, get_cdcacm_pd_info());

	cdcacm_cb_setup_buffers();

	ntf_ep = &pc->eps.epis[CDCACM_NTF_EPNUM];
	txd_ep = &pc->eps.epis[CDCACM_TXD_EPNUM];
	rxd_ep = &pc->eps.epos[CDCACM_RXD_EPNUM];

	// Register callback functions
	tru_usb_cdc_register_cb_reset(cdc, cb_reset);
	tru_usb_cdc_register_cb_enumdone(cdc, cb_enumdone);
	tru_usb_cdc_register_cb_epi_act(cdc, CDCACM_NTF_EPNUM, cb_ntf_act);
	tru_usb_cdc_register_cb_epo_act(cdc, CDCACM_RXD_EPNUM, cb_rxd_act);
	tru_usb_cdc_register_cb_epi_act(cdc, CDCACM_TXD_EPNUM, cb_txd_act);
	tru_usb_cdc_register_cb_epi_chunk(cdc, CDCACM_NTF_EPNUM, cb_ntf_chunk);
	tru_usb_cdc_register_cb_epi_compl(cdc, CDCACM_NTF_EPNUM, cb_ntf_compl);
	tru_usb_cdc_register_cb_epo_chunk(cdc, CDCACM_RXD_EPNUM, cb_rxd_chunk);
	tru_usb_cdc_register_cb_epo_compl(cdc, CDCACM_RXD_EPNUM, cb_rxd_compl);
	tru_usb_cdc_register_cb_epi_chunk(cdc, CDCACM_TXD_EPNUM, cb_txd_chunk);
	tru_usb_cdc_register_cb_epi_compl(cdc, CDCACM_TXD_EPNUM, cb_txd_compl);
	tru_usb_cdc_register_cb_setlinecontrol(cdc, cb_setlinecontrol);
	tru_usb_cdc_register_cb_sendbreak(cdc, cb_sendbreak);
}

void cdcacm_deinit(tru_usb_cdc_t *cdc){
	tru_usb_cdc_deinit(cdc);
	tru_usb_pc_deinit(cdc->pc);
}

uint32_t receive_data(tru_usb_pc_t *pc, uint8_t ep_num){
	#if defined(CDCACM_WIN_QUIRK_HST_NOZLP) && CDCACM_WIN_QUIRK_HST_NOZLP == 1
		rxd_ep->lxfer.chunk.xfer_limit = rxd_ep->mps;  // Limit transfer to one MPS packet only
	#endif
	return tru_usb_pc_receive(pc, ep_num, CDCACM_RXD_MAX_EXP_LEN, CDCACM_RXD_MAX_EXP_LEN);
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
#if defined(CDCACM_ECHO) && CDCACM_ECHO == 1
uint32_t transmit_data(tru_usb_pc_t *pc, uint8_t ep_num, uint32_t write_len){
	#if defined(CDCACM_WIN_QUIRK_DEV_NOZLP4K) && CDCACM_WIN_QUIRK_DEV_NOZLP4K == 1
		return tru_usb_pc_transmit(pc, ep_num, write_len, INT_ALIGN_UP(write_len, 4096));  // Working on Linux and Windows (see Windows expected transfer length)
	#elif defined(CDCACM_WIN_QUIRK_DEV_FORCEZLP) && CDCACM_WIN_QUIRK_DEV_FORCEZLP == 1
		return tru_usb_pc_transmit(pc, ep_num, write_len, 0);  // Ignores condition 1.  Always send a ZLP.  Working on Linux but not Windows
	#else
		return tru_usb_pc_transmit(pc, ep_num, write_len, write_len);  // This is correct to the USB spec, but does not work on Linux and Windows when the transfer size is MPS!
	#endif
}
#endif

#if defined(CDCACM_ECHO) && CDCACM_ECHO == 1
void echo(tru_usb_cdc_t *cdc, bool holding_buffer){
	if(holding_buffer){
		uintptr_t remain = sizeof(rxd_holding_buffer) - rxd_holding_woffset;
		uintptr_t xfer_size;

		if(tru_dwc2_is_epin_busy(cdc->pc->base_addr, txd_ep->num || txd_ep->deferred.is_epena_pending)){
			if(remain){
				// ===============================================================================
				// Store received data into holding buffer to be echoed later when ep is available
				// ===============================================================================
				for(uint32_t i = 0; i < rxd_ep->lxfer.chunk.num_registered; i++){
					xfer_size = (rxd_ep->lxfer.chunk.buffers[i].xferred_size > remain) ? remain : rxd_ep->lxfer.chunk.buffers[i].xferred_size;
					memcpy(rxd_holding_buffer + rxd_holding_woffset, rxd_ep->lxfer.chunk.buffers[i].buf, rxd_ep->lxfer.chunk.buffers[i].xferred_size);
					rxd_holding_woffset += xfer_size;
					remain -= xfer_size;
					if(remain == 0) break;
				}
			}
		}else{
			if(rxd_holding_woffset == 0){
				// =======================
				// Echo from received data
				// =======================
				for(uint32_t i = 0; i < rxd_ep->lxfer.chunk.num_registered; i++){
					memcpy(txd_ep->lxfer.chunk.buffers[i].buf, rxd_ep->lxfer.chunk.buffers[i].buf, rxd_ep->lxfer.chunk.buffers[i].xferred_size);
				}
				transmit_data(cdc->pc, txd_ep->num, rxd_ep->lxfer.chunk.total_xferred_size);
			}else{
				uintptr_t roffset = 0;
				uintptr_t xfer_size;

				// ========================
				// Echo from holding buffer
				// ========================
				for(uint32_t i = 0; i < rxd_ep->lxfer.chunk.num_registered; i++){
					xfer_size = (txd_ep->lxfer.chunk.buffers[i].buf_size > rxd_holding_woffset) ? rxd_holding_woffset : txd_ep->lxfer.chunk.buffers[i].buf_size;
					memcpy(txd_ep->lxfer.chunk.buffers[i].buf, rxd_holding_buffer + roffset, xfer_size);
					roffset += xfer_size;
					rxd_holding_woffset -= xfer_size;
					if(rxd_holding_woffset == 0) break;
				}
				transmit_data(cdc->pc, txd_ep->num, roffset);

				if(remain){
					// ===============================================================================
					// Store received data into holding buffer to be echoed later when ep is available
					// ===============================================================================
					for(uint32_t i = 0; i < rxd_ep->lxfer.chunk.num_registered; i++){
						xfer_size = (rxd_ep->lxfer.chunk.buffers[i].xferred_size > remain) ? remain : rxd_ep->lxfer.chunk.buffers[i].xferred_size;
						memcpy(rxd_holding_buffer + rxd_holding_woffset, rxd_ep->lxfer.chunk.buffers[i].buf, rxd_ep->lxfer.chunk.buffers[i].xferred_size);
						rxd_holding_woffset += xfer_size;
						remain -= xfer_size;
						if(remain == 0) break;
					}
				}
			}
		}
	}else{
		if(tru_dwc2_is_epin_busy(cdc->pc->base_addr, txd_ep->num) || txd_ep->deferred.is_epena_pending){
			if(rxd_holding_woffset){
				uintptr_t roffset = 0;
				uintptr_t xfer_size;

				// ========================
				// Echo from holding buffer
				// ========================
				for(uint32_t i = 0; i < rxd_ep->lxfer.chunk.num_registered; i++){
					xfer_size = (txd_ep->lxfer.chunk.buffers[i].buf_size > rxd_holding_woffset) ? rxd_holding_woffset : txd_ep->lxfer.chunk.buffers[i].buf_size;
					memcpy(txd_ep->lxfer.chunk.buffers[i].buf, rxd_holding_buffer + roffset, xfer_size);
					roffset += xfer_size;
					rxd_holding_woffset -= xfer_size;
					if(rxd_holding_woffset == 0) break;
				}
				transmit_data(cdc->pc, txd_ep->num, roffset);
			}
		}
	}
}
#endif

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
	tru_usb_interface_alt_setting_t *alt_setting = ep->curr_alt_setting;

	if(is_activated){
		LOG("CB: NOTIF EP ACTIVATED ITF=%u\n", alt_setting->interface_num);
	}else{
		LOG("CB: NOTIF EP DEACTIVATED\n");
	}
#endif
}

void cb_txd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep, bool is_activated){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	tru_usb_interface_alt_setting_t *alt_setting = ep->curr_alt_setting;

	if(is_activated){
		LOG("CB: WRITE EP ACTIVATED ITF=%u\n", alt_setting->interface_num);
	}else{
		LOG("CB: WRITE EP DEACTIVATED\n");
	}
#endif

	if(is_activated){
		// Place your transmit code here
	}else{
#if defined(CDCACM_ECHO) && CDCACM_ECHO == 1
		rxd_holding_woffset = 0;
#endif
	}
}

void cb_rxd_act(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep, bool is_activated){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	tru_usb_interface_alt_setting_t *alt_setting = ep->curr_alt_setting;

	if(is_activated){
		LOG("CB: READ EP ACTIVATED ITF=%u\n", alt_setting->interface_num);
	}else{
		LOG("CB: READ EP DEACTIVATED\n");
	}
#endif

	if(is_activated){
		receive_data(cdc->pc, rxd_ep->num);

		tru_usb_cdc_uartstate_t uartstate = tru_usb_cdc_get_serial_state(cdc, CDCACM_NTF_ITFNUM);
		uartstate.bits.dsr = 1;  // DSR high typically used for indicating the terminal side that this device is ready to accept data
		tru_usb_cdc_set_serial_state(cdc, CDCACM_NTF_ITFNUM, &uartstate);
		tru_usb_cdc_tx_notif_serial_state(cdc, CDCACM_NTF_EPNUM, CDCACM_NTF_ITFNUM, true);  // Transmit serial state notification if it has changed
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

	uint8_t *data = rxd_ep->lxfer.chunk.buffers[0].buf;
	LOG("Rx: ");
	for(uint32_t i = 0; i < rxd_ep->lxfer.chunk.total_xferred_size; i++){
		LOG("%.2x", *data++);
	}
	LOG("\n");
#endif

#if defined(CDCACM_ECHO) && CDCACM_ECHO == 1
	echo(cdc, true);
#endif
}

void cb_rxd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: COMPL (RX DATA EP), XFERRED=%lu\n", rxd_ep->lxfer.whole.total_xferred_size);
#endif

	receive_data(cdc->pc, rxd_ep->num);
}

void cb_txd_chunk(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: CHUNK (TX DATA EP), XFERRED=%lu\n", ep->lxfer.chunk.total_xferred_size);
#endif

#if defined(CDCACM_ECHO) && CDCACM_ECHO == 1
	echo(cdc, false);
#endif
}

void cb_txd_compl(tru_usb_cdc_t *cdc, tru_usb_pc_epi_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: COMPL (TX DATA EP), XFERRED=%lu\n", ep->lxfer.whole.total_xferred_size);
#endif
}

void cb_setlinecontrol(tru_usb_cdc_t *cdc, tru_usb_interface_alt_setting_t *alt_setting, tru_usb_cdc_linecontrol_t *linecontrol){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: SET_LINE_CONTROL DTR=%u RTS=%u\n", linecontrol->bits.dtr, linecontrol->bits.rts);
#endif
}

void cb_sendbreak(tru_usb_cdc_t *cdc, tru_usb_interface_alt_setting_t *alt_setting, uint16_t dur_ms){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: SEND_BREAK DUR=%u ms\n", dur_ms);
#endif
}

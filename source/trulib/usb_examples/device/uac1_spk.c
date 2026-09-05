#include "uac1_spk.h"
#include "tru_logger.h"

static uac1_spk_t *uac1_spk;
static uint32_t sof_count;
static tru_usb_pc_epo_t *rxd_ep;
#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	static tru_usb_pc_epi_t *fb_ep;
#endif

// Prototypes for callbacks
static void cb_reset(tru_usb_uac_t *uac);
static void cb_enumdone(tru_usb_uac_t *uac);
static void cb_rxd_act(tru_usb_uac_t *uac, tru_usb_pc_epo_t *ep, bool is_activated);
static void cb_rxd_compl(tru_usb_uac_t *uac, tru_usb_pc_epo_t *ep);
#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	static void cb_fb_compl(tru_usb_uac_t *uac, tru_usb_pc_epi_t *ep);
#endif
static void cb_sof(tru_usb_uac_t *uac);
static void cb_rxd_set_smpfrq(tru_usb_uac_t *uac, tru_usb_pc_epo_t *ep);

void uac1_spk_init(
	tru_usb_pc_t *pc,
	tru_usb_uac_t *uac,
	uintptr_t usb_base_addr,
	tru_dwc2_phy_t phy,
	uint8_t speed_sel,
	bool otg_id_pin_supported,
	bool enable_sof_trigger,
	tru_dwc2_dma_mode_t dma_mode,
	uac1_spk_t *spk
){
	uac1_spk = spk;

	tru_usb_pc_init(
		pc,
		get_uac1_spk_pd_info()->pd,
		usb_base_addr,
		phy,
		speed_sel,
		otg_id_pin_supported,
		enable_sof_trigger,
		dma_mode,
		1
	);
	tru_usb_uac_init(uac, pc, get_uac1_spk_pd_info());

	uac1_spk_cb_setup_buffers();

	rxd_ep = &pc->eps.epos[UAC1_SPK_AUDOUT_EPNUM];
#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	fb_ep = &pc->eps.epis[UAC1_SPK_AUDOUT_FB_EPNUM];
#endif

	// Register callback functions
	tru_usb_uac_register_cb_reset(uac, cb_reset);
	tru_usb_uac_register_cb_enumdone(uac, cb_enumdone);
	tru_usb_uac_register_cb_epo_act(uac, UAC1_SPK_AUDOUT_EPNUM, cb_rxd_act);
	tru_usb_uac_register_cb_epo_compl(uac, UAC1_SPK_AUDOUT_EPNUM, cb_rxd_compl);
#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_uac_register_cb_epi_compl(uac, UAC1_SPK_AUDOUT_FB_EPNUM, cb_fb_compl);
#endif
	tru_usb_uac_register_cb_sof(uac, cb_sof);
	tru_usb_uac_register_cb_epo_set_smpfrq(uac, cb_rxd_set_smpfrq);
}

void uac1_spk_deinit(tru_usb_uac_t *uac){
	tru_usb_uac_deinit(uac);
	tru_usb_pc_deinit(uac->pc);
}

void __attribute__((weak)) uac1_spk_cb_setup_buffers(void){

}

void __attribute__((weak)) uac1_spk_cb_audioinit(tru_usb_pc_epo_t *ep){

}

void __attribute__((weak)) uac1_spk_cb_audiofreq(tru_usb_pc_epo_t *ep){

}

void __attribute__((weak)) uac1_spk_cb_audioupdate(tru_usb_pc_epo_t *ep){

}

void __attribute__((weak)) uac1_spk_cb_i2supdate(void){

}

void __attribute__((weak)) uac1_spk_cb_audiostop(tru_usb_pc_epo_t *ep){

}

#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
void uac1_spk_prepare_fb(tru_usb_uac_t *uac){
	// ================================================================================================================
	// Calculate the allowed min and max feedback values, i.e. the allowed min and max number of samples in a USB frame
	// ================================================================================================================

	// Note, in Windows, the reference frequency is always 1ms for full and high speed so the formula is: fb = samp_freq / 1000
	uint32_t ref_freq = 1000;
	// In full speed mode the frame is 1ms, so ref_freq = 1000
	// In high speed mode the frame is 125us, so ref_freq = 8000
	//uint32_t ref_freq = uac->pc->sof_per_sec

	// The formula for feedback (before fixed point conversion, i.e. decimal) is: fb = samp_freq / ref_freq
	// where fb = feedback in samples, samp_freq = sampling frequency in Hz, ref_freq is number of USB frames per second

	// The USB specification defines the feedback range to be -1/+1 sample.
	// Example, in full speed mode (sof_per_pec = 1000) the compliant range is:
	// Freq (Hz)     Feedback range (decimal)
	// 44100         43.1  ~ 45.1
	// 48000         47    ~ 49
	// 88200         87.2  ~ 89.2
	// 96000         95    ~ 97
	// 176400        175.4 ~ 177.4
	// 192000        191   ~ 193

	// On Windows it is compliant only for frequencies that are a multiple of 1kHz,
	// for other frequencies e.g. 44100 the minimum range value is rounded down (truncated) instead.
	// Example:
	// Freq (Hz)     Feedback range (decimal)
	// 44100         44  ~ 45.1
	// 48000         47  ~ 49
	// 88200         88  ~ 89.2
	// 96000         95  ~ 97
	// 176400        176 ~ 177.4
	// 192000        191 ~ 193
#if defined(UAC1_SPK_WIN_QUIRK_RANGEMIN_ROUND) && UAC1_SPK_WIN_QUIRK_RANGEMIN_ROUND == 1
	if(uac1_spk->samp_freq % 1000){
		uac1_spk->fb_min = (float)uac1_spk->samp_freq / ref_freq;  // Integer truncate
	}else{
		uac1_spk->fb_min = (float)uac1_spk->samp_freq / ref_freq - 1;  // -1 sample
	}
#else
	uac1_spk->fb_min = (float)uac1_spk->samp_freq / ref_freq - 1;  // -1 sample
#endif

	uac1_spk->fb_max = (float)uac1_spk->samp_freq / ref_freq + 1;  // +1 sample

	// The nominal feedback in sample units (not bytes) which depends on the sampling frequency
	uac1_spk->fb_nominal = (float)uac1_spk->samp_freq / ref_freq;
}
#endif

#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
/*
	Feedback calculation for Asynchronous USB mode.

	In a USB UAC device, audio samples are sent by the host to the device through a data endpoint (Audio Stream endpoint).
	In Asynchronous USB mode the device also sends feedback (explicit feedback) data to the host through another endpoint (feedback endpoint),
	which enables the host to adjust its transmission rate to the specified feedback rate.

	Data rate control via the feedback value:
	1. If the device wants a normal data rate, it sends the nominal feedback value, requesting the host to send samples equal to the audio
	   sampling frequency per USB frame.
	2. If the device wants a slower data rate, it sends a lower than nominal feedback value, requesting the host send less samples per USB frame.
	3. If the device wants a faster data rate, it sends a higher than nominal feedback value, requesting the host send more samples per USB frame.

	So the feedback value is the desired host to device audio flow rate with respect to the USB SOF (Start Of Frame), i.e. the number of
	samples per SOF.  The SOF rate depends on the speed mode: in full-speed mode it is 1ms, and in high-speed mode it is 125us.

	The final feedback value is converted into the fixed-point format (a real number with integer and fractional parts) and then sent to the host.
	It is more useful if we discuss the feedback value before the conversion, i.e. in decimal.

	The USB spec defines the feedback deviation to +1/-1 sample from the nominal feedback.

	Example in full-speed mode with audio sampling frequency 48kHz, the SOF period is 1ms, so the nominal feedback value (in decimal format) is:
	nominal_feedback = freq_hz / usb_fs_frame_millisec_per_sec
	= 48000 / 1000
	= 48
	So the valid feedback range is: 47 to 49

	Note: Windows feedback range is compliant only for frequencies that are a multiple of 1kHz.
*/
void uac1_spk_update_fb(tru_usb_uac_t *uac){
	// Calculate offset adjustment value (floating point) for the nominal feedback to maintain buffer at specified threshold filled level
	float fb_offset = (uac1_spk->aob.len * UAC1_SPK_FB_BUFFER_THRESHOLD - tru_lfrb_used(&uac1_spk->aob)) / (uac1_spk->aob.len * UAC1_SPK_FB_BUFFER_THRESHOLD);

	// Apply fractional offset adjustment to the nominal feedback
	uac1_spk->fb = uac1_spk->fb_nominal + fb_offset;

	// Clamp feedback to OS quirk range limits
	if(uac1_spk->fb < uac1_spk->fb_min){
		uac1_spk->fb = uac1_spk->fb_min;
	}else if(uac1_spk->fb > uac1_spk->fb_max){
		uac1_spk->fb = uac1_spk->fb_max;
	}

	// Convert feedback float (in samples per USB SOF frame) to fixed-point format
	// Note, because of OS quirks the code is a little messy
	switch(uac->pc->speed){
		case TRU_DWC2_DSTS_ENUMSPD_FS3060:
		case TRU_DWC2_DSTS_ENUMSPD_FS48:
			#if UAC1_SPK_CFG_FB_Q1014_FS == 1
				#if UAC1_SPK_CFG_AUDOUT_FB_EPPKT_FS == 3
					// 3 byte feedback
					uac1_spk->fb_fp = uac1_spk->fb * (1 << 14);  // Q10.14 fixed-point format
					fb_ep->lxfer.chunk.buffers[0].buf[0] = uac1_spk->fb_fp & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[1] = (uac1_spk->fb_fp >> 8) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[2] = (uac1_spk->fb_fp >> 16) & 0xff;
					tru_usb_pc_transmit(uac->pc, fb_ep->num, 3, 3);
				#else
					// 4 byte feedback
					uac1_spk->fb_fp = uac1_spk->fb * (1 << 14);  // Q10.14 fixed-point format
					// Send 10.14 in a four byte packet
					fb_ep->lxfer.chunk.buffers[0].buf[0] = uac1_spk->fb_fp & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[1] = (uac1_spk->fb_fp >> 8) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[2] = (uac1_spk->fb_fp >> 16) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[3] = (uac1_spk->fb_fp >> 24) & 0xff;
					tru_usb_pc_transmit(uac->pc, fb_ep->num, 4, 4);
				#endif
			#else
				#if UAC1_SPK_CFG_AUDOUT_FB_EPPKT_FS == 3
					// 3 byte feedback - this is not really sufficient for Q16.16
					uac1_spk->fb_fp = uac1_spk->fb * (1 << 16);  // Q16.16 fixed-point format
					fb_ep->lxfer.chunk.buffers[0].buf[0] = uac1_spk->fb_fp & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[1] = (uac1_spk->fb_fp >> 8) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[2] = (uac1_spk->fb_fp >> 16) & 0xff;
					tru_usb_pc_transmit(uac->pc, fb_ep->num, 3, 3);
				#else
					// 4 byte feedback
					uac1_spk->fb_fp = uac1_spk->fb * (1 << 16);  // Q16.16 fixed-point format
					fb_ep->lxfer.chunk.buffers[0].buf[0] = uac1_spk->fb_fp & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[1] = (uac1_spk->fb_fp >> 8) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[2] = (uac1_spk->fb_fp >> 16) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[3] = (uac1_spk->fb_fp >> 24) & 0xff;
					tru_usb_pc_transmit(uac->pc, fb_ep->num, 4, 4);
				#endif
			#endif
			break;
		case TRU_DWC2_DSTS_ENUMSPD_HS3060:
		default:
			#if UAC1_SPK_CFG_FB_Q1014_HS == 1
				#if UAC1_SPK_CFG_AUDOUT_FB_EPPKT_HS == 3
					// 3 byte feedback
					uac1_spk->fb_fp = uac1_spk->fb * (1 << 14);  // Q10.14 fixed-point format
					fb_ep->lxfer.chunk.buffers[0].buf[0] = uac1_spk->fb_fp & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[1] = (uac1_spk->fb_fp >> 8) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[2] = (uac1_spk->fb_fp >> 16) & 0xff;
					tru_usb_pc_transmit(uac->pc, fb_ep->num, 3, 3);
				#else
					// 4 byte feedback
					uac1_spk->fb_fp = uac1_spk->fb * (1 << 14);  // Q10.14 fixed-point format
					fb_ep->lxfer.chunk.buffers[0].buf[0] = uac1_spk->fb_fp & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[1] = (uac1_spk->fb_fp >> 8) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[2] = (uac1_spk->fb_fp >> 16) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[3] = (uac1_spk->fb_fp >> 24) & 0xff;
					tru_usb_pc_transmit(uac->pc, fb_ep->num, 4, 4);
				#endif
			#else
				#if UAC1_SPK_CFG_AUDOUT_FB_EPPKT_HS == 3
					// 3 byte feedback - this is not really sufficient for Q16.16
					uac1_spk->fb_fp = uac1_spk->fb * (1 << 16);  // Q16.16 fixed-point format
					fb_ep->lxfer.chunk.buffers[0].buf[0] = uac1_spk->fb_fp & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[1] = (uac1_spk->fb_fp >> 8) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[2] = (uac1_spk->fb_fp >> 16) & 0xff;
					tru_usb_pc_transmit(uac->pc, fb_ep->num, 3, 3);
				#else
					// 4 byte feedback
					uac1_spk->fb_fp = uac1_spk->fb * (1 << 16);  // Q16.16 fixed-point format
					fb_ep->lxfer.chunk.buffers[0].buf[0] = uac1_spk->fb_fp & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[1] = (uac1_spk->fb_fp >> 8) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[2] = (uac1_spk->fb_fp >> 16) & 0xff;
					fb_ep->lxfer.chunk.buffers[0].buf[3] = (uac1_spk->fb_fp >> 24) & 0xff;
					tru_usb_pc_transmit(uac->pc, fb_ep->num, 4, 4);
				#endif
			#endif
	}
}
#endif

// ==========
// Call backs
// ==========

// Is called when USB resets
void cb_reset(tru_usb_uac_t *uac){
}

// Callback when USB enumeration is done
void cb_enumdone(tru_usb_uac_t *uac){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	LOG("CB: ENUMDONE\n");
#endif
}

void cb_rxd_act(tru_usb_uac_t *uac, tru_usb_pc_epo_t *ep, bool is_activated){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	tru_usb_interface_alt_setting_t *alt_setting = ep->curr_alt_setting;

	if(is_activated){
		LOG("CB: READ EPO%u, ITF %u, ALT %u ACTIVATED\n", ep->num, alt_setting->interface_num, alt_setting->alt_setting_num);
	}else{
		LOG("CB: READ EPO%u, ITF %u, ALT %u DEACTIVATED\n", ep->num, alt_setting->interface_num, alt_setting->alt_setting_num);
	}
#endif

	if(is_activated){
		sof_count = 0;

		uac1_spk_cb_audioinit(ep);
		//tru_usb_pc_receive(uac->pc, rxd_ep->num, uac1_spk->samp_res / 8, uac1_spk->samp_res / 8);
		//tru_usb_pc_receive(uac->pc, rxd_ep->num, uac1_spk->aob_frame_size, uac1_spk->aob_frame_size);
		tru_usb_pc_receive(uac->pc, rxd_ep->num, ep->mps, ep->mps);
	}else{
		uac1_spk_cb_audiostop(rxd_ep);

#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
		LOG("ISO OUT INCOMPL COUNT %lu\n", rxd_ep->iso_incomplete);
#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
		LOG("ISO IN INCOMPL COUNT %lu\n", fb_ep->iso_incomplete);
#endif
#endif
	}
}

void cb_rxd_compl(tru_usb_uac_t *uac, tru_usb_pc_epo_t *ep){
#if defined(TRU_CFG_USB_LOG_CALLBACK) && TRU_CFG_USB_LOG_CALLBACK == 1
	//LOG("CB: COMPL (RX DATA EP), XFERRED=%lu\n", rxd_ep->lxfer.whole.total_xferred_size);
#endif

	uac1_spk_cb_audioupdate(rxd_ep);
	//tru_usb_pc_receive(uac->pc, rxd_ep->num, uac1_spk->samp_res / 8, uac1_spk->samp_res / 8);
	//tru_usb_pc_receive(uac->pc, rxd_ep->num, uac1_spk->aob_frame_size, uac1_spk->aob_frame_size);
	tru_usb_pc_receive(uac->pc, rxd_ep->num, ep->mps, ep->mps);
}

#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
// Feedback transfer completed
void cb_fb_compl(tru_usb_uac_t *uac, tru_usb_pc_epi_t *ep){
	//LOG("%.8lx %.8lx\n", fb_ep->lxfer.chunk.sgdma.dma_descs[0].status.val, TRU_DWC2_DIEPCTL_REG(uac->pc->base_addr, fb_ep->num)->val);
}
#endif

// USB SOF (USB Start Of Frame) callback
// The rate of the SOF interrupt is determined by the enumerated USB speed:
// - in high-speed it is the microframe which has a rate of 125us per frame
// - in low-speed or full-speed it is the milliframe which has a rate of 1ms per frame
void cb_sof(tru_usb_uac_t *uac){
	sof_count++;

#if UAC1_SPK_CFG_AUDOUT_EPSYC == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	if(rxd_ep->is_activated && fb_ep->is_activated){
		if(!tru_dwc2_is_epin_enabled(uac->pc->base_addr, fb_ep->num)){
			uac1_spk_update_fb(uac);
		}//else if(uac->pc->dma_mode == TRU_DWC2_DMA_MODE_SG && tru_dwc2_sgdma_is_last_dma_done(&fb_ep->lxfer.chunk.sgdma)){
			//uac1_spk_update_fb(uac);
		//}
	}
#endif

#if defined(TRU_CFG_USB_LOG_UAC_FB) && TRU_CFG_USB_LOG_UAC_FB == 1
	if(sof_count % uac->pc->sof_per_sec == 0){
		if(rxd_ep->is_activated){
			uint32_t debug_used = tru_lfrb_used(&uac1_spk->aob);
			//LOG("%lu %i%%\n", debug_used, (int)((float)debug_used/uac1_spk->aob.len*100.0f));
			LOG("%lu %i%% %lu\n", debug_used, (int)((float)debug_used/uac1_spk->aob.len*100.0f), uac1_spk->i2s_underrun);
		}
	}
#endif
}

void cb_rxd_set_smpfrq(tru_usb_uac_t *uac, tru_usb_pc_epo_t *ep){
	uac1_spk_cb_audiofreq(ep);
}

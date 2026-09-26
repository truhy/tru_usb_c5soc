#include "msos_winusb_dual_c5soc.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

static tru_usb_pc_t pc;
static tru_usb_msos_t msos;

// Transfer buffers for chunk transfers
#if defined(MSOS_WINUSB_DUAL_DMA_MODE_CHOICE) && MSOS_WINUSB_DUAL_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
	NONCACHEABLE_SECTION static uint8_t p0_txd_buffer[MSOS_WINUSB_DUAL_P0_SG_NUM_TXBUF][32768];
	NONCACHEABLE_SECTION static uint8_t p0_rxd_buffer[MSOS_WINUSB_DUAL_P0_SG_NUM_RXBUF][32768];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t p0_txd_dma_descs[MSOS_WINUSB_DUAL_P0_SG_NUM_TXBUF];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t p0_rxd_dma_descs[MSOS_WINUSB_DUAL_P0_SG_NUM_RXBUF];

	NONCACHEABLE_SECTION static uint8_t p1_txd_buffer[MSOS_WINUSB_DUAL_P1_SG_NUM_TXBUF][32768];
	NONCACHEABLE_SECTION static uint8_t p1_rxd_buffer[MSOS_WINUSB_DUAL_P1_SG_NUM_RXBUF][32768];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t p1_txd_dma_descs[MSOS_WINUSB_DUAL_P1_SG_NUM_TXBUF];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t p1_rxd_dma_descs[MSOS_WINUSB_DUAL_P1_SG_NUM_RXBUF];
#else
	NONCACHEABLE_SECTION static uint8_t p0_txd_buffer[65536];
	NONCACHEABLE_SECTION static uint8_t p0_rxd_buffer[65536];

	NONCACHEABLE_SECTION static uint8_t p1_txd_buffer[65536];
	NONCACHEABLE_SECTION static uint8_t p1_rxd_buffer[65536];
#endif

static void p0_setup_buffers(tru_usb_pc_t *pc){
	tru_usb_pc_epi_t *p0_txd_ep = &pc->eps.epis[MSOS_WINUSB_DUAL_P0_TXD_EPNUM];
	tru_usb_pc_epo_t *p0_rxd_ep = &pc->eps.epos[MSOS_WINUSB_DUAL_P0_RXD_EPNUM];

	#if defined(MSOS_WINUSB_DUAL_DMA_MODE_CHOICE) && MSOS_WINUSB_DUAL_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		// Register transfer buffers
		for(uint32_t i = 0; i < MSOS_WINUSB_DUAL_P0_SG_NUM_TXBUF; i++){
			tru_usb_lxfer_register_buffer(&p0_txd_ep->lxfer, p0_txd_buffer[i], sizeof(p0_txd_buffer[i]));
		}
		for(uint32_t i = 0; i < MSOS_WINUSB_DUAL_P0_SG_NUM_RXBUF; i++){
			tru_usb_lxfer_register_buffer(&p0_rxd_ep->lxfer, p0_rxd_buffer[i], sizeof(p0_rxd_buffer[i]));
		}
		// Register SG DMA descriptor lists
		tru_usb_lxfer_register_sgdma_descs(&p0_txd_ep->lxfer, p0_txd_dma_descs, sizeof(p0_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		tru_usb_lxfer_register_sgdma_descs(&p0_rxd_ep->lxfer, p0_rxd_dma_descs, sizeof(p0_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
	#else
		tru_usb_lxfer_register_buffer(&p0_txd_ep->lxfer, p0_txd_buffer, sizeof(p0_txd_buffer));
		tru_usb_lxfer_register_buffer(&p0_rxd_ep->lxfer, p0_rxd_buffer, sizeof(p0_rxd_buffer));
	#endif
}

static void p1_setup_buffers(tru_usb_pc_t *pc){
	tru_usb_pc_epi_t *p1_txd_ep = &pc->eps.epis[MSOS_WINUSB_DUAL_P1_TXD_EPNUM];
	tru_usb_pc_epo_t *p1_rxd_ep = &pc->eps.epos[MSOS_WINUSB_DUAL_P1_RXD_EPNUM];

	#if defined(MSOS_WINUSB_DUAL_DMA_MODE_CHOICE) && MSOS_WINUSB_DUAL_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		// Register transfer buffers
		for(uint32_t i = 0; i < MSOS_WINUSB_DUAL_P1_SG_NUM_TXBUF; i++){
			tru_usb_lxfer_register_buffer(&p1_txd_ep->lxfer, p1_txd_buffer[i], sizeof(p1_txd_buffer[i]));
		}
		for(uint32_t i = 0; i < MSOS_WINUSB_DUAL_P1_SG_NUM_RXBUF; i++){
			tru_usb_lxfer_register_buffer(&p1_rxd_ep->lxfer, p1_rxd_buffer[i], sizeof(p1_rxd_buffer[i]));
		}
		// Register SG DMA descriptor lists
		tru_usb_lxfer_register_sgdma_descs(&p1_txd_ep->lxfer, p1_txd_dma_descs, sizeof(p1_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		tru_usb_lxfer_register_sgdma_descs(&p1_rxd_ep->lxfer, p1_rxd_dma_descs, sizeof(p1_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
	#else
		tru_usb_lxfer_register_buffer(&p1_txd_ep->lxfer, p1_txd_buffer, sizeof(p1_txd_buffer));
		tru_usb_lxfer_register_buffer(&p1_rxd_ep->lxfer, p1_rxd_buffer, sizeof(p1_rxd_buffer));
	#endif
}

// Override weak function
void msos_winusb_multi_cb_setup_buffers(void){
	p0_setup_buffers(&pc);
	p1_setup_buffers(&pc);
}

void msos_winusb_dual_init_app(void){
	tru_dwc2_phy_t phy = {
		.speed = TRU_DWC2_PHYSPEED_HS,
		.iftype = TRU_DWC2_PHYIFTYPE_INTERNAL,
		.rate = TRU_DWC2_PHYRATE_SDR,
		.width = TRU_DWC2_PHYWIDTH_8BIT
	};

	msos_winusb_dual_init(
		&pc,
		&msos,
		TRU_USB_U1_BASE,
		phy,
		TRU_DWC2_DCFG_DEVSPD_USBHS20,
		true,
		false,
		MSOS_WINUSB_DUAL_DMA_MODE_CHOICE
	);

	tru_usb_pc_start(&pc);
}

void msos_winusb_dual_deinit_app(void){
	msos_winusb_dual_deinit(&msos);
}

#endif

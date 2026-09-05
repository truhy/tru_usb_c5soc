#include "msos_winusb_c5soc.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

static tru_usb_pc_t pc;
static tru_usb_msos_t msos;

// Transfer buffers for chunk transfers
#if defined(MSOS_WINUSB_DMA_MODE_CHOICE) && MSOS_WINUSB_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
	NONCACHEABLE_SECTION static uint8_t txd_buffer[MSOS_WINUSB_SG_NUM_TXBUF][32768];
	NONCACHEABLE_SECTION static uint8_t rxd_buffer[MSOS_WINUSB_SG_NUM_RXBUF][32768];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t txd_dma_descs[MSOS_WINUSB_SG_NUM_TXBUF];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t rxd_dma_descs[MSOS_WINUSB_SG_NUM_RXBUF];
#else
	NONCACHEABLE_SECTION static uint8_t txd_buffer[65536];
	NONCACHEABLE_SECTION static uint8_t rxd_buffer[65536];
#endif

// Override weak function
void msos_winusb_cb_setup_buffers(void){
	tru_usb_pc_epi_t *txd_ep = &pc.eps.epis[MSOS_WINUSB_TXD_EPNUM];
	tru_usb_pc_epo_t *rxd_ep = &pc.eps.epos[MSOS_WINUSB_RXD_EPNUM];

	#if defined(MSOS_WINUSB_DMA_MODE_CHOICE) && MSOS_WINUSB_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		// Register transfer buffers
		for(uint32_t i = 0; i < MSOS_WINUSB_SG_NUM_TXBUF; i++){
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, txd_buffer[i], sizeof(txd_buffer[i]));
		}
		for(uint32_t i = 0; i < MSOS_WINUSB_SG_NUM_RXBUF; i++){
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, rxd_buffer[i], sizeof(rxd_buffer[i]));
		}
		// Register SG DMA descriptor lists
		tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, txd_dma_descs, sizeof(txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, rxd_dma_descs, sizeof(rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
	#else
		tru_usb_lxfer_register_buffer(&txd_ep->lxfer, txd_buffer, sizeof(txd_buffer));
		tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, rxd_buffer, sizeof(rxd_buffer));
	#endif
}

void msos_winusb_init_app(void){
	tru_dwc2_phy_t phy = {
		.speed = TRU_DWC2_PHYSPEED_HS,
		.iftype = TRU_DWC2_PHYIFTYPE_INTERNAL,
		.rate = TRU_DWC2_PHYRATE_SDR,
		.width = TRU_DWC2_PHYWIDTH_8BIT
	};

	msos_winusb_init(
		&pc,
		&msos,
		TRU_USB_U1_BASE,
		phy,
		TRU_DWC2_DCFG_DEVSPD_USBHS20,
		true,
		false,
		MSOS_WINUSB_DMA_MODE_CHOICE
	);

	tru_usb_pc_start(&pc);
}

void msos_winusb_deinit_app(void){
	msos_winusb_deinit(&msos);
}

#endif

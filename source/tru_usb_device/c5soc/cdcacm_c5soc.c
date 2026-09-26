#include "cdcacm_c5soc.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

static tru_usb_pc_t pc;
static tru_usb_cdc_t cdc;

// Transfer buffers for chunk transfers
#if defined(CDCACM_DMA_MODE_CHOICE) && CDCACM_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
	NONCACHEABLE_SECTION static uint8_t ntf_buffer[16];
	NONCACHEABLE_SECTION static uint8_t txd_buffer[CDCACM_SG_NUM_TXBUF][32768];
	NONCACHEABLE_SECTION static uint8_t rxd_buffer[CDCACM_SG_NUM_RXBUF][32768];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t ntf_dma_descs[1];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t txd_dma_descs[CDCACM_SG_NUM_TXBUF];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t rxd_dma_descs[CDCACM_SG_NUM_RXBUF];
#else
	NONCACHEABLE_SECTION static uint8_t ntf_buffer[16];
	NONCACHEABLE_SECTION static uint8_t txd_buffer[65536];
	NONCACHEABLE_SECTION static uint8_t rxd_buffer[65536];
#endif

// Override weak function
void cdcacm_cb_setup_buffers(void){
	tru_usb_pc_epi_t *ntf_ep = &pc.eps.epis[CDCACM_NTF_EPNUM];
	tru_usb_pc_epi_t *txd_ep = &pc.eps.epis[CDCACM_TXD_EPNUM];
	tru_usb_pc_epo_t *rxd_ep = &pc.eps.epos[CDCACM_RXD_EPNUM];

	#if defined(CDCACM_DMA_MODE_CHOICE) && CDCACM_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		// Register transfer buffers
		tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, ntf_buffer, sizeof(ntf_buffer));
		for(uint32_t i = 0; i < CDCACM_SG_NUM_TXBUF; i++){
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, txd_buffer[i], sizeof(txd_buffer[i]));
		}
		for(uint32_t i = 0; i < CDCACM_SG_NUM_RXBUF; i++){
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, rxd_buffer[i], sizeof(rxd_buffer[i]));
		}
		// Register SG DMA descriptor lists
		tru_usb_lxfer_register_sgdma_descs(&ntf_ep->lxfer, ntf_dma_descs, sizeof(ntf_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, txd_dma_descs, sizeof(txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, rxd_dma_descs, sizeof(rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
	#else
		tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, ntf_buffer, sizeof(ntf_buffer));
		tru_usb_lxfer_register_buffer(&txd_ep->lxfer, txd_buffer, sizeof(txd_buffer));
		tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, rxd_buffer, sizeof(rxd_buffer));
	#endif
}

void cdcacm_init_app(void){
	tru_dwc2_phy_t phy = {
		.speed = TRU_DWC2_PHYSPEED_HS,
		.iftype = TRU_DWC2_PHYIFTYPE_INTERNAL,
		.rate = TRU_DWC2_PHYRATE_SDR,
		.width = TRU_DWC2_PHYWIDTH_8BIT
	};

	cdcacm_init(
		&pc,
		&cdc,
		TRU_USB_U1_BASE,
		phy,
		TRU_DWC2_DCFG_DEVSPD_USBHS20,
		true,
		false,
		CDCACM_DMA_MODE_CHOICE
	);

	tru_usb_pc_start(&pc);
}

void cdcacm_deinit_app(void){
	cdcacm_deinit(&cdc);
}

#endif

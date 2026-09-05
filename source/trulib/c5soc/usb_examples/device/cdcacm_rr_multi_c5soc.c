#include "cdcacm_rr_multi_c5soc.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

static tru_usb_pc_t pc;
static tru_usb_cdc_t cdc;

#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	// Transfer buffers for chunk transfers
	#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		NONCACHEABLE_SECTION static uint8_t vcp1_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp1_txd_buffer[CDCACM_RR_MULTI_VCP1_SG_NUM_TXBUF][512];
		NONCACHEABLE_SECTION static uint8_t vcp1_rxd_buffer[CDCACM_RR_MULTI_VCP1_SG_NUM_RXBUF][512];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp1_ntf_dma_descs[1];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp1_txd_dma_descs[CDCACM_RR_MULTI_VCP1_SG_NUM_TXBUF];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp1_rxd_dma_descs[CDCACM_RR_MULTI_VCP1_SG_NUM_RXBUF];
	#else
		NONCACHEABLE_SECTION static uint8_t vcp1_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp1_txd_buffer[1024];
		NONCACHEABLE_SECTION static uint8_t vcp1_rxd_buffer[1024];
	#endif

	static void vcp1_setup_buffers(tru_usb_pc_t *pc){
		tru_usb_pc_epi_t *ntf_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP1_NTF_EPNUM];
		tru_usb_pc_epi_t *txd_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP1_TXD_EPNUM];
		tru_usb_pc_epo_t *rxd_ep = &pc->eps.epos[CDCACM_RR_MULTI_VCP1_RXD_EPNUM];

		#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
			// Register transfer buffers
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp1_ntf_buffer, sizeof(vcp1_ntf_buffer));
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP1_SG_NUM_TXBUF; i++){
				tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp1_txd_buffer[i], sizeof(vcp1_txd_buffer[i]));
			}
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP1_SG_NUM_RXBUF; i++){
				tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp1_rxd_buffer[i], sizeof(vcp1_rxd_buffer[i]));
			}
			// Register SG DMA descriptor lists
			tru_usb_lxfer_register_sgdma_descs(&ntf_ep->lxfer, vcp1_ntf_dma_descs, sizeof(vcp1_ntf_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, vcp1_txd_dma_descs, sizeof(vcp1_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, vcp1_rxd_dma_descs, sizeof(vcp1_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		#else
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp1_ntf_buffer, sizeof(vcp1_ntf_buffer));
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp1_txd_buffer, sizeof(vcp1_txd_buffer));
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp1_rxd_buffer, sizeof(vcp1_rxd_buffer));
		#endif
	}
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	// Transfer buffers for chunk transfers
	#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		NONCACHEABLE_SECTION static uint8_t vcp2_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp2_txd_buffer[CDCACM_RR_MULTI_VCP2_SG_NUM_TXBUF][512];
		NONCACHEABLE_SECTION static uint8_t vcp2_rxd_buffer[CDCACM_RR_MULTI_VCP2_SG_NUM_RXBUF][512];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp2_ntf_dma_descs[1];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp2_txd_dma_descs[CDCACM_RR_MULTI_VCP2_SG_NUM_TXBUF];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp2_rxd_dma_descs[CDCACM_RR_MULTI_VCP2_SG_NUM_RXBUF];
	#else
		NONCACHEABLE_SECTION static uint8_t vcp2_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp2_txd_buffer[1024];
		NONCACHEABLE_SECTION static uint8_t vcp2_rxd_buffer[1024];
	#endif

	static void vcp2_setup_buffers(tru_usb_pc_t *pc){
		tru_usb_pc_epi_t *ntf_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP2_NTF_EPNUM];
		tru_usb_pc_epi_t *txd_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP2_TXD_EPNUM];
		tru_usb_pc_epo_t *rxd_ep = &pc->eps.epos[CDCACM_RR_MULTI_VCP2_RXD_EPNUM];

		#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
			// Register transfer buffers
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp2_ntf_buffer, sizeof(vcp2_ntf_buffer));
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP2_SG_NUM_TXBUF; i++){
				tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp2_txd_buffer[i], sizeof(vcp2_txd_buffer[i]));
			}
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP2_SG_NUM_RXBUF; i++){
				tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp2_rxd_buffer[i], sizeof(vcp2_rxd_buffer[i]));
			}
			// Register SG DMA descriptor lists
			tru_usb_lxfer_register_sgdma_descs(&ntf_ep->lxfer, vcp2_ntf_dma_descs, sizeof(vcp2_ntf_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, vcp2_txd_dma_descs, sizeof(vcp2_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, vcp2_rxd_dma_descs, sizeof(vcp2_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		#else
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp2_ntf_buffer, sizeof(vcp2_ntf_buffer));
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp2_txd_buffer, sizeof(vcp2_txd_buffer));
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp2_rxd_buffer, sizeof(vcp2_rxd_buffer));
		#endif
	}
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	// Transfer buffers for chunk transfers
	#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		NONCACHEABLE_SECTION static uint8_t vcp3_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp3_txd_buffer[CDCACM_RR_MULTI_VCP3_SG_NUM_TXBUF][512];
		NONCACHEABLE_SECTION static uint8_t vcp3_rxd_buffer[CDCACM_RR_MULTI_VCP3_SG_NUM_RXBUF][512];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp3_ntf_dma_descs[1];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp3_txd_dma_descs[CDCACM_RR_MULTI_VCP3_SG_NUM_TXBUF];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp3_rxd_dma_descs[CDCACM_RR_MULTI_VCP3_SG_NUM_RXBUF];
	#else
		NONCACHEABLE_SECTION static uint8_t vcp3_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp3_txd_buffer[1024];
		NONCACHEABLE_SECTION static uint8_t vcp3_rxd_buffer[1024];
	#endif

	static void vcp3_setup_buffers(tru_usb_pc_t *pc){
		tru_usb_pc_epi_t *ntf_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP3_NTF_EPNUM];
		tru_usb_pc_epi_t *txd_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP3_TXD_EPNUM];
		tru_usb_pc_epo_t *rxd_ep = &pc->eps.epos[CDCACM_RR_MULTI_VCP3_RXD_EPNUM];

		#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
			// Register transfer buffers
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp3_ntf_buffer, sizeof(vcp3_ntf_buffer));
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP3_SG_NUM_TXBUF; i++){
				tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp3_txd_buffer[i], sizeof(vcp3_txd_buffer[i]));
			}
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP3_SG_NUM_RXBUF; i++){
				tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp3_rxd_buffer[i], sizeof(vcp3_rxd_buffer[i]));
			}
			// Register SG DMA descriptor lists
			tru_usb_lxfer_register_sgdma_descs(&ntf_ep->lxfer, vcp3_ntf_dma_descs, sizeof(vcp3_ntf_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, vcp3_txd_dma_descs, sizeof(vcp3_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, vcp3_rxd_dma_descs, sizeof(vcp3_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		#else
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp3_ntf_buffer, sizeof(vcp3_ntf_buffer));
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp3_txd_buffer, sizeof(vcp3_txd_buffer));
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp3_rxd_buffer, sizeof(vcp3_rxd_buffer));
		#endif
	}
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	// Transfer buffers for chunk transfers
	#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		NONCACHEABLE_SECTION static uint8_t vcp4_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp4_txd_buffer[CDCACM_RR_MULTI_VCP4_SG_NUM_TXBUF][512];
		NONCACHEABLE_SECTION static uint8_t vcp4_rxd_buffer[CDCACM_RR_MULTI_VCP4_SG_NUM_RXBUF][512];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp4_ntf_dma_descs[1];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp4_txd_dma_descs[CDCACM_RR_MULTI_VCP4_SG_NUM_TXBUF];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp4_rxd_dma_descs[CDCACM_RR_MULTI_VCP4_SG_NUM_RXBUF];
	#else
		NONCACHEABLE_SECTION static uint8_t vcp4_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp4_txd_buffer[1024];
		NONCACHEABLE_SECTION static uint8_t vcp4_rxd_buffer[1024];
	#endif

	static void vcp4_setup_buffers(tru_usb_pc_t *pc){
		tru_usb_pc_epi_t *ntf_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP4_NTF_EPNUM];
		tru_usb_pc_epi_t *txd_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP4_TXD_EPNUM];
		tru_usb_pc_epo_t *rxd_ep = &pc->eps.epos[CDCACM_RR_MULTI_VCP4_RXD_EPNUM];

		#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
			// Register transfer buffers
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp4_ntf_buffer, sizeof(vcp4_ntf_buffer));
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP4_SG_NUM_TXBUF; i++){
				tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp4_txd_buffer[i], sizeof(vcp4_txd_buffer[i]));
			}
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP4_SG_NUM_RXBUF; i++){
				tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp4_rxd_buffer[i], sizeof(vcp4_rxd_buffer[i]));
			}
			// Register SG DMA descriptor lists
			tru_usb_lxfer_register_sgdma_descs(&ntf_ep->lxfer, vcp4_ntf_dma_descs, sizeof(vcp4_ntf_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, vcp4_txd_dma_descs, sizeof(vcp4_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, vcp4_rxd_dma_descs, sizeof(vcp4_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		#else
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp4_ntf_buffer, sizeof(vcp4_ntf_buffer));
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp4_txd_buffer, sizeof(vcp4_txd_buffer));
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp4_rxd_buffer, sizeof(vcp4_rxd_buffer));
		#endif
	}
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	// Transfer buffers for chunk transfers
	#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		NONCACHEABLE_SECTION static uint8_t vcp5_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp5_txd_buffer[CDCACM_RR_MULTI_VCP5_SG_NUM_TXBUF][512];
		NONCACHEABLE_SECTION static uint8_t vcp5_rxd_buffer[CDCACM_RR_MULTI_VCP5_SG_NUM_RXBUF][512];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp5_ntf_dma_descs[1];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp5_txd_dma_descs[CDCACM_RR_MULTI_VCP5_SG_NUM_TXBUF];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp5_rxd_dma_descs[CDCACM_RR_MULTI_VCP5_SG_NUM_RXBUF];
	#else
		NONCACHEABLE_SECTION static uint8_t vcp5_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp5_txd_buffer[1024];
		NONCACHEABLE_SECTION static uint8_t vcp5_rxd_buffer[1024];
	#endif

	static void vcp5_setup_buffers(tru_usb_pc_t *pc){
		tru_usb_pc_epi_t *ntf_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP5_NTF_EPNUM];
		tru_usb_pc_epi_t *txd_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP5_TXD_EPNUM];
		tru_usb_pc_epo_t *rxd_ep = &pc->eps.epos[CDCACM_RR_MULTI_VCP5_RXD_EPNUM];

		#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
			// Register transfer buffers
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp5_ntf_buffer, sizeof(vcp5_ntf_buffer));
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP5_SG_NUM_TXBUF; i++){
				tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp5_txd_buffer[i], sizeof(vcp5_txd_buffer[i]));
			}
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP5_SG_NUM_RXBUF; i++){
				tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp5_rxd_buffer[i], sizeof(vcp5_rxd_buffer[i]));
			}
			// Register SG DMA descriptor lists
			tru_usb_lxfer_register_sgdma_descs(&ntf_ep->lxfer, vcp5_ntf_dma_descs, sizeof(vcp5_ntf_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, vcp5_txd_dma_descs, sizeof(vcp5_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, vcp5_rxd_dma_descs, sizeof(vcp5_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		#else
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp5_ntf_buffer, sizeof(vcp5_ntf_buffer));
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp5_txd_buffer, sizeof(vcp5_txd_buffer));
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp5_rxd_buffer, sizeof(vcp5_rxd_buffer));
		#endif
	}
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	// Transfer buffers for chunk transfers
	#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		NONCACHEABLE_SECTION static uint8_t vcp6_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp6_txd_buffer[CDCACM_RR_MULTI_VCP6_SG_NUM_TXBUF][512];
		NONCACHEABLE_SECTION static uint8_t vcp6_rxd_buffer[CDCACM_RR_MULTI_VCP6_SG_NUM_RXBUF][512];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp6_ntf_dma_descs[1];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp6_txd_dma_descs[CDCACM_RR_MULTI_VCP6_SG_NUM_TXBUF];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp6_rxd_dma_descs[CDCACM_RR_MULTI_VCP6_SG_NUM_RXBUF];
	#else
		NONCACHEABLE_SECTION static uint8_t vcp6_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp6_txd_buffer[1024];
		NONCACHEABLE_SECTION static uint8_t vcp6_rxd_buffer[1024];
	#endif

	static void vcp6_setup_buffers(tru_usb_pc_t *pc){
		tru_usb_pc_epi_t *ntf_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP6_NTF_EPNUM];
		tru_usb_pc_epi_t *txd_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP6_TXD_EPNUM];
		tru_usb_pc_epo_t *rxd_ep = &pc->eps.epos[CDCACM_RR_MULTI_VCP6_RXD_EPNUM];

		#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
			// Register transfer buffers
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp6_ntf_buffer, sizeof(vcp6_ntf_buffer));
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP6_SG_NUM_TXBUF; i++){
				tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp6_txd_buffer[i], sizeof(vcp6_txd_buffer[i]));
			}
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP6_SG_NUM_RXBUF; i++){
				tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp6_rxd_buffer[i], sizeof(vcp6_rxd_buffer[i]));
			}
			// Register SG DMA descriptor lists
			tru_usb_lxfer_register_sgdma_descs(&ntf_ep->lxfer, vcp6_ntf_dma_descs, sizeof(vcp6_ntf_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, vcp6_txd_dma_descs, sizeof(vcp6_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, vcp6_rxd_dma_descs, sizeof(vcp6_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		#else
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp6_ntf_buffer, sizeof(vcp6_ntf_buffer));
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp6_txd_buffer, sizeof(vcp6_txd_buffer));
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp6_rxd_buffer, sizeof(vcp6_rxd_buffer));
		#endif
	}
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	// Transfer buffers for chunk transfers
	#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		NONCACHEABLE_SECTION static uint8_t vcp7_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp7_txd_buffer[CDCACM_RR_MULTI_VCP7_SG_NUM_TXBUF][512];
		NONCACHEABLE_SECTION static uint8_t vcp7_rxd_buffer[CDCACM_RR_MULTI_VCP7_SG_NUM_RXBUF][512];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp7_ntf_dma_descs[1];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp7_txd_dma_descs[CDCACM_RR_MULTI_VCP7_SG_NUM_TXBUF];
		NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t vcp7_rxd_dma_descs[CDCACM_RR_MULTI_VCP7_SG_NUM_RXBUF];
	#else
		NONCACHEABLE_SECTION static uint8_t vcp7_ntf_buffer[16];
		NONCACHEABLE_SECTION static uint8_t vcp7_txd_buffer[1024];
		NONCACHEABLE_SECTION static uint8_t vcp7_rxd_buffer[1024];
	#endif

	static void vcp7_setup_buffers(tru_usb_pc_t *pc){
		tru_usb_pc_epi_t *ntf_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP7_NTF_EPNUM];
		tru_usb_pc_epi_t *txd_ep = &pc->eps.epis[CDCACM_RR_MULTI_VCP7_TXD_EPNUM];
		tru_usb_pc_epo_t *rxd_ep = &pc->eps.epos[CDCACM_RR_MULTI_VCP7_RXD_EPNUM];

		#if defined(CDCACM_RR_MULTI_DMA_MODE_CHOICE) && CDCACM_RR_MULTI_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
			// Register transfer buffers
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp7_ntf_buffer, sizeof(vcp7_ntf_buffer));
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP7_SG_NUM_TXBUF; i++){
				tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp7_txd_buffer[i], sizeof(vcp7_txd_buffer[i]));
			}
			for(uint32_t i = 0; i < CDCACM_RR_MULTI_VCP7_SG_NUM_RXBUF; i++){
				tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp7_rxd_buffer[i], sizeof(vcp7_rxd_buffer[i]));
			}
			// Register SG DMA descriptor lists
			tru_usb_lxfer_register_sgdma_descs(&ntf_ep->lxfer, vcp7_ntf_dma_descs, sizeof(vcp7_ntf_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&txd_ep->lxfer, vcp7_txd_dma_descs, sizeof(vcp7_txd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
			tru_usb_lxfer_register_sgdma_descs(&rxd_ep->lxfer, vcp7_rxd_dma_descs, sizeof(vcp7_rxd_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
		#else
			tru_usb_lxfer_register_buffer(&ntf_ep->lxfer, vcp7_ntf_buffer, sizeof(vcp7_ntf_buffer));
			tru_usb_lxfer_register_buffer(&txd_ep->lxfer, vcp7_txd_buffer, sizeof(vcp7_txd_buffer));
			tru_usb_lxfer_register_buffer(&rxd_ep->lxfer, vcp7_rxd_buffer, sizeof(vcp7_rxd_buffer));
		#endif
	}
#endif

// Override weak function
void cdcacm_rr_multi_cb_setup_buffers(void){
	#if CDCACM_RR_MULTI_NUM_PORTS >= 1
		vcp1_setup_buffers(&pc);
	#endif
	#if CDCACM_RR_MULTI_NUM_PORTS >= 2
		vcp2_setup_buffers(&pc);
	#endif
	#if CDCACM_RR_MULTI_NUM_PORTS >= 3
		vcp3_setup_buffers(&pc);
	#endif
	#if CDCACM_RR_MULTI_NUM_PORTS >= 4
		vcp4_setup_buffers(&pc);
	#endif
	#if CDCACM_RR_MULTI_NUM_PORTS >= 5
		vcp5_setup_buffers(&pc);
	#endif
	#if CDCACM_RR_MULTI_NUM_PORTS >= 6
		vcp6_setup_buffers(&pc);
	#endif
	#if CDCACM_RR_MULTI_NUM_PORTS >= 7
		vcp7_setup_buffers(&pc);
	#endif
}

void cdcacm_rr_multi_init_app(void){
	tru_dwc2_phy_t phy = {
		.speed = TRU_DWC2_PHYSPEED_HS,
		.iftype = TRU_DWC2_PHYIFTYPE_INTERNAL,
		.rate = TRU_DWC2_PHYRATE_SDR,
		.width = TRU_DWC2_PHYWIDTH_8BIT
	};

	cdcacm_rr_multi_init(
		&pc,
		&cdc,
		TRU_USB_U1_BASE,
		phy,
		TRU_DWC2_DCFG_DEVSPD_USBHS20,
		true,
		false,
		CDCACM_RR_MULTI_DMA_MODE_CHOICE
	);

	tru_usb_pc_start(&pc);
}

void cdcacm_rr_multi_deinit_app(void){
	cdcacm_rr_multi_deinit(&cdc);
}

#endif

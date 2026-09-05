#include "hid_custom_c5soc.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

static tru_usb_pc_t pc;
static tru_usb_hid_t hid;

// Transfer buffers for chunk transfers
#if defined(HID_CUS_DMA_MODE_CHOICE) && HID_CUS_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
	NONCACHEABLE_SECTION static uint8_t output_report_buffer[HID_CUS_SG_NUM_OUTREPORTBUF][HID_CUS_OUTPUT_REPORT_VARCOUNT];
	NONCACHEABLE_SECTION static tru_dwc2_dev_sgdma_desc_reg_t output_report_dma_descs[HID_CUS_SG_NUM_OUTREPORTBUF];
#else
	NONCACHEABLE_SECTION static uint8_t output_report_buffer[HID_CUS_OUTPUT_REPORT_VARCOUNT];
#endif

// Override weak function
void hid_cus_cb_setup_buffers(void){
	tru_usb_pc_epo_t *outrep__ep = &pc.eps.epos[HID_CUS_OUT_REPORT_EPNUM];

	#if defined(HID_CUS_DMA_MODE_CHOICE) && HID_CUS_DMA_MODE_CHOICE == _TRU_DWC2_DMA_MODE_SG
		// Register transfer buffers
		for(uint32_t i = 0; i < HID_CUS_SG_NUM_OUTREPORTBUF; i++){
			tru_usb_lxfer_register_buffer(&outrep__ep->lxfer, output_report_buffer[i], sizeof(output_report_buffer[i]));
		}
		// Register SG DMA descriptor lists
		tru_usb_lxfer_register_sgdma_descs(&outrep__ep->lxfer, output_report_dma_descs, sizeof(output_report_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t));
	#else
		tru_usb_lxfer_register_buffer(&outrep__ep->lxfer, output_report_buffer, sizeof(output_report_buffer));
	#endif
}

void hid_cus_init_app(void){
	tru_dwc2_phy_t phy = {
		.speed = TRU_DWC2_PHYSPEED_HS,
		.iftype = TRU_DWC2_PHYIFTYPE_INTERNAL,
		.rate = TRU_DWC2_PHYRATE_SDR,
		.width = TRU_DWC2_PHYWIDTH_8BIT
	};

	hid_cus_init(
		&pc,
		&hid,
		TRU_USB_U1_BASE,
		phy,
		TRU_DWC2_DCFG_DEVSPD_USBHS20,
		true,
		false,
		HID_CUS_DMA_MODE_CHOICE
	);

	tru_usb_pc_start(&pc);
}

void hid_cus_deinit_app(void){
	hid_cus_deinit(&hid);
}

#endif

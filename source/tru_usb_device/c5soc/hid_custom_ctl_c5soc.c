#include "hid_custom_ctl_c5soc.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

static tru_usb_pc_t pc;
static tru_usb_hid_t hid;

void hid_cus_ctl_init_app(void){
	tru_dwc2_phy_t phy = {
		.speed = TRU_DWC2_PHYSPEED_HS,
		.iftype = TRU_DWC2_PHYIFTYPE_INTERNAL,
		.rate = TRU_DWC2_PHYRATE_SDR,
		.width = TRU_DWC2_PHYWIDTH_8BIT
	};

	hid_cus_ctl_init(
		&pc,
		&hid,
		TRU_USB_U1_BASE,
		phy,
		TRU_DWC2_DCFG_DEVSPD_USBHS20,
		true,
		false,
		HID_CUS_CTL_DMA_MODE_CHOICE
	);

	tru_usb_pc_start(&pc);
}

void hid_cus_ctl_deinit_app(void){
	hid_cus_ctl_deinit(&hid);
}

#endif

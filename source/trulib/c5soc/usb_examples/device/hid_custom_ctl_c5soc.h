/*
	Created on: 16 Apr 2025
	Author: Truong Hy
*/

#ifndef HID_CUSTOM_CTL_C5SOC_H
#define HID_CUSTOM_CTL_C5SOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tru_config.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

#include "usb_examples/device/hid_custom_ctl.h"

//#define HID_CUS_CTL_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_FF
#define HID_CUS_CTL_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_SB
//#define HID_CUS_CTL_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_SG

void hid_cus_ctl_init_app(void);
void hid_cus_ctl_deinit_app(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

/*
	Created on: 16 Apr 2025
	Author: Truong Hy
*/

#ifndef MSOS_WINUSB_DUAL_C5SOC_H
#define MSOS_WINUSB_DUAL_C5SOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tru_config.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

#include "usb_examples/device/msos_winusb_dual.h"

// The last 2 characters selects the DMA mode:  FF = FIFO slave mode (DMA off), SB = Single Buffer DMA, SG = Scatter Gather DMA
//#define MSOS_WINUSB_DUAL_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_FF
#define MSOS_WINUSB_DUAL_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_SB
//#define MSOS_WINUSB_DUAL_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_SG

// Number of DMA SG buffers
#define MSOS_WINUSB_DUAL_P0_SG_NUM_TXBUF 2
#define MSOS_WINUSB_DUAL_P0_SG_NUM_RXBUF 2
#define MSOS_WINUSB_DUAL_P1_SG_NUM_TXBUF 2
#define MSOS_WINUSB_DUAL_P1_SG_NUM_RXBUF 2

void msos_winusb_dual_init_app(void);
void msos_winusb_dual_deinit_app(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

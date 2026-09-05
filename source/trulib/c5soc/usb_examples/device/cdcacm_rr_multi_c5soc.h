/*
	Created on: 16 Apr 2025
	Author: Truong Hy
*/

#ifndef CDCACM_RR_MULTI_C5SOC_H
#define CDCACM_RR_MULTI_C5SOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tru_config.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

#include "usb_examples/device/cdcacm_rr_multi.h"

// The last 2 characters selects the DMA mode:  FF = FIFO slave mode (DMA off), SB = Single Buffer DMA, SG = Scatter Gather DMA
//#define CDCACM_RR_MULTI_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_FF
#define CDCACM_RR_MULTI_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_SB
//#define CDCACM_RR_MULTI_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_SG

// Number of DMA SG buffers
#define CDCACM_RR_MULTI_VCP1_SG_NUM_TXBUF 2
#define CDCACM_RR_MULTI_VCP1_SG_NUM_RXBUF 2
#define CDCACM_RR_MULTI_VCP2_SG_NUM_TXBUF 2
#define CDCACM_RR_MULTI_VCP2_SG_NUM_RXBUF 2
#define CDCACM_RR_MULTI_VCP3_SG_NUM_TXBUF 2
#define CDCACM_RR_MULTI_VCP3_SG_NUM_RXBUF 2
#define CDCACM_RR_MULTI_VCP4_SG_NUM_TXBUF 2
#define CDCACM_RR_MULTI_VCP4_SG_NUM_RXBUF 2
#define CDCACM_RR_MULTI_VCP5_SG_NUM_TXBUF 2
#define CDCACM_RR_MULTI_VCP5_SG_NUM_RXBUF 2
#define CDCACM_RR_MULTI_VCP6_SG_NUM_TXBUF 2
#define CDCACM_RR_MULTI_VCP6_SG_NUM_RXBUF 2
#define CDCACM_RR_MULTI_VCP7_SG_NUM_TXBUF 2
#define CDCACM_RR_MULTI_VCP7_SG_NUM_RXBUF 2

void cdcacm_rr_multi_init_app(void);
void cdcacm_rr_multi_deinit_app(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

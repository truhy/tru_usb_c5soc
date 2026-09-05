/*
	Created on: 15 Nov 2024
	Author: Truong Hy
*/

#ifndef CDCACM_RR_MULTI_VCP3_H
#define CDCACM_RR_MULTI_VCP3_H

#ifdef __cplusplus
extern "C" {
#endif

#include "cdcacm_rr_multi_def.h"

#if CDCACM_RR_MULTI_NUM_PORTS >= 3

void cdcacm_rr_multi_vcp3_init(tru_usb_cdc_t *cdc);
void cdcacm_rr_multi_vcp3_deinit(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

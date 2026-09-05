/*
	Created on: 7 Apr 2025
	Author: Truong Hy
*/

#ifndef HID_GAMEPAD1_C5SOC_H
#define HID_GAMEPAD1_C5SOC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tru_config.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

#include "usb_examples/device/hid_gamepad1.h"

//#define HID_GAMEPAD1_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_FF
#define HID_GAMEPAD1_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_SB
//#define HID_GAMEPAD1_DMA_MODE_CHOICE _TRU_DWC2_DMA_MODE_SG

// FIFO options
#define OPT_ADXL345_FIFO_ENABLE       0                         // 0 = Bypass (don't use FIFO), 1 = FIFO mode (use FIFO)
#define OPT_ADXL345_WATERLEVEL        1                         // 1 to 31 = sets the number of entries that will start a trigger
// Rate and range options
#define OPT_ADXL345_RATE              TRU_ADXL345_RATE_3P13_HZ  // See tru_adxl345_ll.h for the list of rates
#define OPT_ADXL345_RANGE             TRU_ADXL345_RANGE_2G      // See tru_adxl345_ll.h for the list of ranges
#define OPT_ADXL345_FULLRES           1                         // 0 = 10bit, 1 = fullres (2g = 10bit, 4g = 11bit, 8g = 12bit, 16g = 13bit)
// Calibration offset options
#define OPT_ADXL345_OFSX              0                         // OFFSETX = OFSX * 15.6mg
#define OPT_ADXL345_OFSY              0                         // OFFSETY = OFSY * 15.6mg
#define OPT_ADXL345_OFSZ              0                         // OFFSETZ = OFSZ * 15.6mg

typedef struct{
	int16_t x;
	int16_t y;
	int16_t z;
}tru_adxl345_data;

typedef struct{
	uint32_t l4_sp_clock_freq_hz;
	uint32_t sample_count;
	tru_adxl345_data sample;
}tru_adxl345_accel_t;

void hid_gamepad1_init_app(void);
void hid_gamepad1_deinit_app(void);

#endif

#ifdef __cplusplus
}
#endif

#endif

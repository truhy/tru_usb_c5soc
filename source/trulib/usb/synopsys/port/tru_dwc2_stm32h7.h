/*
	MIT License

	Copyright (c) 2025 Truong Hy

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

	Version: 20260208

	USB 2.0 OTG controller low-level support for STMicroelectronics STM32H7.
	This is actually a Synopsys DWC2 USB 2.0 OTG controller.
 */

#ifndef TRU_DWC2_STM32H7_H
#define TRU_DWC2_STM32H7_H

#ifdef __cplusplus
extern "C" {
#endif

#include "tru_config.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_STM32H7

// ====================
// Hardware limitations
// ====================

// There is a bug in STM32H7 DWC2 version 3.30a in slave mode (manual FIFO transfer mode), only a maximum of seven packets can be pushed into the TXFIFO - most likely related to the 3-bit packet counter size of the DIEPTSIZ register
// This doesn't affect the DMA modes.
#define TRU_DWC2_DEV_MAX_TXFIFO_PACKETS 7

// ========
// Hardware
// ========

#define TRU_USB_U0_BASE 0x40040000  // STM32H7 USB OTG HS1 (alias USB1 OTG HS) controller is renamed as USB0 controller for convenience
#define TRU_USB_U1_BASE 0x40080000  // STM32H7 USB OTG HS2 (alias USB2 OTG_FS) controller is renamed as USB1 controller for convenience

#endif

#ifdef __cplusplus
}
#endif

#endif

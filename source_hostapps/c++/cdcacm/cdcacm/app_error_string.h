/*
	MIT License

	Copyright (c) 2024 Truong Hy

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

	Version: 20240601
*/

#ifndef APP_ERROR_STRING_H
#define APP_ERROR_STRING_H

#include "tru_macro.h"
#include <cstdint>

// Error message list
#define APP_ERROR_LIST(item) \
	item(APP_ERROR_NONE_ID,    "") \
	item(APP_ERROR_TX_FAIL_ID, "Transmit failed") \
	item(APP_ERROR_RX_FAIL_ID, "Received failed") \
	item(APP_ERROR_XFER_INFO_ID, "Requested {} byte(s) but {} transferred")

// Create enum from error message list
CREATE_ENUM(app_error_e, APP_ERROR_LIST)

class app_error_string{
public:
	INIT_INLINE_CLASS_ARRAY_ENUM(static constexpr char const *, messages, APP_ERROR_LIST)
};

#endif

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

	This is for Windows which helps for converting between std::string vs TCHAR strings.
*/

#ifndef TC_STRING_H
#define TC_STRING_H

#if defined(WIN32) || defined(WIN64)

#include <tchar.h>
#include <string>
#include <sstream>
#include <iomanip>

// TCHAR versions of std::string and std::ostringstream.
typedef std::basic_string< TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tc_string;
typedef std::basic_ostringstream< TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR> > tc_ostringstream;

namespace string_utils_ns{
	tc_string str_to_tc(std::string m_arg_str);
	std::string tc_to_str(tc_string m_arg_tc_str);
}

#endif

#endif

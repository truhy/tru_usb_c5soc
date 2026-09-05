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

#include "align.h"

/*
	Integer round up.
	Rounds up to the next multiple.
	E.g.
		Value  Align_to  Result
		0      4         0
		1      4         4
		2      4         4
		3      4         4
		4      4         4
		5      4         8
		6      4         8
*/
uint32_t align_ns::align_up(uint32_t m_arg_value, uint16_t m_arg_align_divisor){
	if( (m_arg_align_divisor == 0) || (m_arg_align_divisor == 1) ){
		return m_arg_value;
	}else{
		return ((m_arg_value + (m_arg_align_divisor - 1)) & ~(m_arg_align_divisor - 1));
	}
}

/*
	Integer round down.
	Rounds down to the previous multiple.
	E.g.
		Value  Align_to  Result
		0      4         0
		1      4         0
		2      4         0
		3      4         0
		4      4         4
		5      4         4
		6      4         4
*/
uint32_t align_ns::align_down(uint32_t m_arg_value, uint16_t m_arg_align_divisor){
	if( (m_arg_align_divisor == 0) || (m_arg_align_divisor == 1) ){
		return m_arg_value;
	}else{
		return (m_arg_value & ~(m_arg_align_divisor - 1));
	}
}

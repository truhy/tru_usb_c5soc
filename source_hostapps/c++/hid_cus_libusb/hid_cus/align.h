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

#ifndef ALIGN_H
#define ALIGN_H

#include <cstdint>

namespace align_ns{
	uint32_t align_up(uint32_t m_arg_value, uint16_t m_arg_align_divisor);
	uint32_t align_down(uint32_t m_arg_value, uint16_t m_arg_align_divisor);
	// Template version of integer round up
	template<class T>
	T align_up_t(T m_arg_value, uint16_t m_arg_align_divisor){
		if( (m_arg_align_divisor == 0) || (m_arg_align_divisor == 1) ){
			return m_arg_value;
		}else{
			return ((m_arg_value + ((T)m_arg_align_divisor - 1)) & ~((T)m_arg_align_divisor - 1));
		}
	};
	// Template version of integer round down
	template<class T>
	T align_down_t(T m_arg_value, uint16_t m_arg_align_divisor){
		if( (m_arg_align_divisor == 0) || (m_arg_align_divisor == 1) ){
			return m_arg_value;
		}else{
			return (m_arg_value & ~((T)m_arg_align_divisor - 1));
		}
	};
	// Template version of integer round up that is compatible with pointers
	template<class T>
	T ptr_align_up_t(T m_arg_value, uintptr_t m_arg_align_divisor){
		uintptr_t m_arg_align_mod;

		if( (m_arg_align_divisor == 0) || (m_arg_align_divisor == 1) ){
			return m_arg_value;
		}else{
			m_arg_align_mod = (uintptr_t)m_arg_value % m_arg_align_divisor;

			if(m_arg_align_mod == 0){
				return m_arg_value;
			}else{
				return (m_arg_value + (m_arg_align_divisor - m_arg_align_mod));
			}
		}
	};
	// Template version of integer round down that is compatible with pointers
	template<class T>
	T ptr_align_down_t(T m_arg_value, uintptr_t m_arg_align_divisor){
		uintptr_t m_arg_align_mod;

		if( (m_arg_align_divisor == 0) || (m_arg_align_divisor == 1) ){
			return m_arg_value;
		}else{
			m_arg_align_mod = (uintptr_t)m_arg_value % m_arg_align_divisor;

			if(m_arg_align_mod == 0){
				return m_arg_value;
			}else{
				return (m_arg_value - m_arg_align_mod);
			}
		}
	};
}

#endif

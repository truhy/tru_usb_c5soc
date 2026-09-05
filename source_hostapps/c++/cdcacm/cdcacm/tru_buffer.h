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

	A class for data buffer of fixed size.
*/

#ifndef TRU_BUFFER_H
#define TRU_BUFFER_H

#include "align.h"
#include <cstddef>

class tru_buffer{
protected:
	unsigned char *m_actual_buf;
	size_t m_actual_buf_size;
	unsigned char *m_buf_ptr;
	size_t m_size;
	size_t m_used;
	size_t m_start_align_up_div;

	void copy(const tru_buffer &m_arg_buf);

public:
	//Constructor.
	tru_buffer();
	//Constructor.
	tru_buffer(size_t m_arg_buf_size);
	//Constructor.
	tru_buffer(const void *m_arg_buf_ptr, size_t m_arg_buf_size);
	//Copy constructor.
	tru_buffer(const tru_buffer &m_arg_buf);
	//Destructor.
	~tru_buffer();

	unsigned char *actual_buf();
	unsigned char *buf_ptr();
	size_t size();
	size_t used();
	size_t start_align_up_div();
	bool set_size(size_t m_arg_buf_size, size_t m_arg_align_div = 1);
	bool resize(size_t m_arg_buf_size, size_t m_arg_align_div = 1);
	void set_used(size_t m_arg_buf_used);
	void set_size_zero();
	void store(const void *m_arg_buf_ptr, size_t m_arg_buf_size);
	void store_val(unsigned char m_arg_val, size_t m_arg_buf_size);
	void append(const void *m_arg_buf_ptr, size_t m_arg_buf_size);
	void append_val(unsigned char m_arg_val, size_t m_arg_buf_size);
	void insert(const void *m_arg_buf_ptr, size_t m_arg_buf_size);
	void insert_val(unsigned char m_arg_val, size_t m_arg_buf_size);
	void trim_right(size_t m_arg_trim_size);
	void trim_left(size_t m_arg_trim_size);
	bool cmp_buf(const void *m_arg_buf_ptr, size_t m_arg_buf_size);
	tru_buffer &operator=(const tru_buffer &m_arg_buf);
	bool operator==(const tru_buffer &m_arg_buf) const;
	bool operator!=(const tru_buffer &m_arg_buf) const;
};

#endif

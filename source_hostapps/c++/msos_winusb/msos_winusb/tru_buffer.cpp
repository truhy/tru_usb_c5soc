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

#include "tru_buffer.h"
#include "tru_exception.h"
#include <malloc.h>
#include <string.h>

tru_buffer::tru_buffer() :
	m_actual_buf(NULL),
	m_actual_buf_size(0),
	m_buf_ptr(NULL),
	m_size(0),
	m_used(0),
	m_start_align_up_div(1){
}

tru_buffer::tru_buffer(size_t m_arg_buf_size) :
	m_actual_buf(NULL),
	m_actual_buf_size(0),
	m_buf_ptr(NULL),
	m_size(0),
	m_used(0),
	m_start_align_up_div(1){
	set_size(m_arg_buf_size);
}

tru_buffer::tru_buffer(const void *m_arg_buf_ptr, size_t m_arg_buf_size) :
	m_actual_buf(NULL),
	m_actual_buf_size(0),
	m_buf_ptr(NULL),
	m_size(0),
	m_used(0),
	m_start_align_up_div(1){
	set_size(m_arg_buf_size);
	store(m_arg_buf_ptr, m_arg_buf_size);
}

tru_buffer::tru_buffer(const tru_buffer &m_arg_buf) :
	m_actual_buf(NULL),
	m_actual_buf_size(0),
	m_buf_ptr(NULL),
	m_size(0),
	m_used(0),
	m_start_align_up_div(1){
	copy(m_arg_buf);
}

tru_buffer::~tru_buffer(){
	set_size_zero();
}

void tru_buffer::copy(const tru_buffer &m_arg_buf){
	if(m_arg_buf.m_size == 0){
		set_size_zero();
	}else{
		set_size(m_arg_buf.m_size, m_arg_buf.m_start_align_up_div);
		store(m_arg_buf.m_buf_ptr, m_arg_buf.m_size);
		m_start_align_up_div = m_arg_buf.m_start_align_up_div;
	}
}

unsigned char *tru_buffer::actual_buf(){
	return m_actual_buf;
}

unsigned char *tru_buffer::buf_ptr(){
	return m_buf_ptr;
}

size_t tru_buffer::size(){
	return m_size;
}

size_t tru_buffer::used(){
	return m_used;
}

size_t tru_buffer::start_align_up_div(){
	return m_start_align_up_div;
}

bool tru_buffer::set_size(size_t m_arg_buf_size, size_t m_arg_align_div){
	bool m_success = false;
	void *m_new_buf;

	if(m_arg_align_div < 1){
		m_arg_align_div = 1;
	}

	if(m_arg_buf_size <= 0){
		set_size_zero();
		m_success = true;
	}else if(
		(m_size == m_arg_buf_size) &&
		(m_start_align_up_div == m_arg_align_div)
	){
		m_success = true;
	}else{
		m_new_buf = (unsigned char *)malloc(m_arg_buf_size + m_arg_align_div - 1);
		if(m_new_buf != NULL){
			set_size_zero();
			m_actual_buf = (unsigned char*)m_new_buf;
			if(m_arg_align_div == 1){
				m_buf_ptr = m_actual_buf;
			}else{
				//m_buf_ptr = (unsigned char *)align_up((size_t)m_actual_buf, m_arg_align_div);
				m_buf_ptr = align_ns::ptr_align_up_t(m_actual_buf, m_arg_align_div);
			}
			m_size = m_arg_buf_size;
			m_start_align_up_div = m_arg_align_div;
			m_success = true;
		}else{
			errno = ENOMEM;
			throw tru_exception::get_clib_last_error(__func__, "");
		}
	}

	return m_success;
}

bool tru_buffer::resize(size_t m_arg_buf_size, size_t m_arg_align_div){
	bool m_success = false;
	void *m_new_buf;

	if(m_arg_align_div < 1){
		m_arg_align_div = 1;
	}

	if(m_arg_buf_size <= 0){
		set_size_zero();
		m_success = true;
	}else if(
		(m_size == m_arg_buf_size) &&
		(m_start_align_up_div == m_arg_align_div)
	){
		m_success = true;
	}else{
		m_new_buf = realloc(m_actual_buf, m_arg_buf_size + m_arg_align_div - 1);
		if(m_new_buf != NULL){
			m_actual_buf = (unsigned char*)m_new_buf;
			if(m_arg_align_div == 1){
				m_buf_ptr = m_actual_buf;
			}else{
				//m_buf_ptr = (unsigned char *)align_up((size_t)m_actual_buf, m_arg_align_div);
				m_buf_ptr = align_ns::ptr_align_up_t(m_actual_buf, m_arg_align_div);
			}
			m_size = m_arg_buf_size;
			m_start_align_up_div = m_arg_align_div;
			//Re-adjust used.
			if(m_used > m_size){ m_used = m_size; }
			m_success = true;
		}
	}

	return m_success;
}

void tru_buffer::set_used(size_t m_arg_buf_used){
	if(m_arg_buf_used <= m_size){
		m_used = m_arg_buf_used;
	}else{
		m_used = m_size;
	}
}

void tru_buffer::set_size_zero(){
	if(m_actual_buf != NULL){
		free(m_actual_buf);
		m_actual_buf = NULL;
		m_buf_ptr = NULL;
	}

	m_size = 0;
	m_used = 0;
	m_start_align_up_div = 1;
}

/*
	Stores new data into the buffer. Old data will be lost.
*/
void tru_buffer::store(const void *m_arg_buf_ptr, size_t m_arg_buf_size){
	if((m_arg_buf_ptr == NULL) || (m_arg_buf_size <= 0)){
		m_used = 0;
	}else if(m_arg_buf_size <= m_size){
		memcpy(m_buf_ptr, m_arg_buf_ptr, m_arg_buf_size);
		m_used = m_arg_buf_size;
	}
}

/*
	Stores new data as a repeating value into the buffer. Old data will be lost.
*/
void tru_buffer::store_val(unsigned char m_arg_val, size_t m_arg_buf_size){
	if(m_arg_buf_size <= 0){
		m_used = 0;
	}else if(m_arg_buf_size <= m_size){
		memset(m_buf_ptr, m_arg_val, m_arg_buf_size);
		m_used = m_arg_buf_size;
	}
}

/*
	Appends data to the buffer.
*/
void tru_buffer::append(const void *m_arg_buf_ptr, size_t m_arg_buf_size){
	if((m_arg_buf_ptr == NULL) || (m_arg_buf_size <= 0)){
		//Do nothing.
	}else if(m_arg_buf_size <= (m_size - m_used)){
		memcpy(m_buf_ptr + m_used, m_arg_buf_ptr, m_arg_buf_size);
		m_used += m_arg_buf_size;
	}
}

void tru_buffer::append_val(unsigned char m_arg_val, size_t m_arg_buf_size){
	if(m_arg_buf_size <= 0){
		//Do nothing.
	}else if(m_arg_buf_size <= (m_size - m_used)){
		memset(m_buf_ptr + m_used, m_arg_val, m_arg_buf_size);
		m_used += m_arg_buf_size;
	}
}

void tru_buffer::insert(const void *m_arg_buf_ptr, size_t m_arg_buf_size){
	if((m_arg_buf_ptr == NULL) || (m_arg_buf_size <= 0)){
		//Do nothing.
	}else if(m_arg_buf_size <= (m_size - m_used)){
		memmove(m_buf_ptr + m_arg_buf_size, m_buf_ptr, m_used);
		memcpy(m_buf_ptr, m_arg_buf_ptr, m_arg_buf_size);
		m_used += m_arg_buf_size;
	}
}

void tru_buffer::insert_val(unsigned char m_arg_val, size_t m_arg_buf_size){
	if(m_arg_buf_size <= 0){
		//Do nothing.
	}else if(m_arg_buf_size <= (m_size - m_used)){
		memmove(m_buf_ptr + m_arg_buf_size, m_buf_ptr, m_used);
		memset(m_buf_ptr, m_arg_val, m_arg_buf_size);
		m_used += m_arg_buf_size;
	}
}

/*
	Deletes data of given size from the end of the buffer (right).
*/
void tru_buffer::trim_right(size_t m_arg_trim_size){
	if(m_arg_trim_size <= 0){
		//Do nothing.
	}else if(m_buf_ptr == NULL){
		//Do nothing.
	}else if(m_arg_trim_size >= m_used){
		m_used = 0;
	}else{
		m_used -= m_arg_trim_size;
	}
}

/*
	Deletes data of given size from the start of the buffer (left).
*/
void tru_buffer::trim_left(size_t m_arg_trim_size){
	if(m_arg_trim_size <= 0){
		//Do nothing.
	}else if(m_buf_ptr == NULL){
		//Do nothing.
	}else if(m_arg_trim_size >= m_used){
		m_used = 0;
	}else{
		memmove(m_buf_ptr, m_buf_ptr + m_arg_trim_size, m_used - m_arg_trim_size);
		m_used -= m_arg_trim_size;
	}
}

/*
	Compares the buffers and returns true if same, else false.
*/
bool tru_buffer::cmp_buf(const void *m_arg_buf_ptr, size_t m_arg_buf_size){
	bool m_same = false;
	/*size_t m_i;

	if(m_size == m_arg_buf_size){
		m_same = true;

		for(m_i = 0; m_i < m_size; m_i++){
			if(m_buf_ptr[m_i] != ((unsigned char *)m_arg_buf_ptr)[m_i]){
				m_same = false;

				//Exit for loop.
				break;
			}
		}
	}
	*/

	if(memcmp(m_buf_ptr, m_arg_buf_ptr, m_arg_buf_size) == 0){
		m_same = true;
	}

	return m_same;
}

/*
	Assignment operator overload so it does same as store().
*/
tru_buffer &tru_buffer::operator=(const tru_buffer &m_arg_buf){
	if(this != &m_arg_buf){
		copy(m_arg_buf);
	}

	return *this;
}

bool tru_buffer::operator==(const tru_buffer &m_arg_buf) const{
	if(this == &m_arg_buf){
		return true;
	}else{
		//Below compares contents of this with input class object..

		if(
			(m_actual_buf_size != m_arg_buf.m_actual_buf_size) ||
			(m_size != m_arg_buf.m_size) ||
			(m_used != m_arg_buf.m_used) ||
			(m_start_align_up_div != m_arg_buf.m_start_align_up_div)
		){
			return false;
		}else if(memcmp(m_buf_ptr, m_arg_buf.m_buf_ptr, m_arg_buf.m_used) != 0){
			return false;
		}else{
			return true;
		}
	}
}

bool tru_buffer::operator!=(const tru_buffer &m_arg_buf) const{
	return !((*this) == m_arg_buf);
}

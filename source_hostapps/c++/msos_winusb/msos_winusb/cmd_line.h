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

#ifndef CMD_LINE_H
#define CMD_LINE_H

#include <libusb.h>
#include <cstdint>
#include <string>

typedef enum msos1_cmd_e{
	MSOS1_CMD_NONE,
	MSOS1_CMD_RATE_TEST,
	MSOS1_CMD_VERIFY_TEST
}msos1_cmd_t;

class my_params{
public:
	msos1_cmd_t cmd;
	uint32_t timeout_ms;
	uint32_t rlen;
	uint32_t wlen;
	uint32_t num_runs;
	const libusb_endpoint_descriptor *iep_desc;
	const libusb_endpoint_descriptor *oep_desc;

	my_params() :
		cmd(MSOS1_CMD_NONE),
		timeout_ms(5000),
		rlen(4096),
		wlen(64),
		num_runs(1),
		iep_desc(NULL),
		oep_desc(NULL){
	}
};

template<class T>
bool parse_param_val(std::string m_arg_param, std::string m_arg_key_word, T &m_arg_val){
	std::string m_param_val_str;

	//Len of param is correct or longer?
	if(m_arg_param.size() >= (m_arg_key_word.size() + 1)){
		//Compares param to key word.
		if(m_arg_param.compare(0, m_arg_key_word.size(), m_arg_key_word) == 0){
			m_param_val_str = m_arg_param.substr(m_arg_key_word.size(), m_arg_param.size());
			if(!m_param_val_str.empty()){
				//m_arg_val = str_to_num<T>(m_param_val_str);
				//m_arg_val = (T)strtol(m_param_val_str.c_str(), NULL, 0);
				m_arg_val = (T)atof(m_param_val_str.c_str());
			}else{
				m_arg_val = 0;
			}

			return true;
		}
	}

	return false;
}

template<class T>
bool parse_param_val_int(std::string m_arg_param, std::string m_arg_key_word, T &m_arg_val){
	std::string m_param_val_str;

	//Len of param is correct or longer?
	if(m_arg_param.size() >= (m_arg_key_word.size() + 1)){
		//Compares param to key word.
		if(m_arg_param.compare(0, m_arg_key_word.size(), m_arg_key_word) == 0){
			m_param_val_str = m_arg_param.substr(m_arg_key_word.size(), m_arg_param.size());
			if(!m_param_val_str.empty()){
				//m_arg_val = str_to_num<T>(m_param_val_str);
				m_arg_val = (T)strtol(m_param_val_str.c_str(), NULL, 0);
				//m_arg_val = (T)atof(m_param_val_str.c_str());
			}else{
				m_arg_val = 0;
			}

			return true;
		}
	}

	return false;
}

template<class T>
bool parse_param_val_uint(std::string m_arg_param, std::string m_arg_key_word, T &m_arg_val){
	std::string m_param_val_str;

	//Len of param is correct or longer?
	if(m_arg_param.size() >= (m_arg_key_word.size() + 1)){
		//Compares param to key word.
		if(m_arg_param.compare(0, m_arg_key_word.size(), m_arg_key_word) == 0){
			m_param_val_str = m_arg_param.substr(m_arg_key_word.size(), m_arg_param.size());
			if(!m_param_val_str.empty()){
				//m_arg_val = str_to_num<T>(m_param_val_str);
				m_arg_val = (T)strtoul(m_param_val_str.c_str(), NULL, 0);
				//m_arg_val = (T)atof(m_param_val_str.c_str());
			}else{
				m_arg_val = 0;
			}

			return true;
		}
	}

	return false;
}

bool parse_param_exist(std::string m_arg_param, std::string m_arg_key_word);
bool parse_param_str(std::string m_arg_param, std::string m_arg_key_word, std::string &m_arg_data_str);
bool parse_param_yn(std::string m_arg_param, std::string m_arg_key_word, bool &m_arg_yn);
bool parse_param_hex_str(std::string m_arg_param, std::string m_arg_key_word, std::string &m_arg_str);
void usage(char *m_arg_0);
bool parse_params_search(char *m_arg_cmdl_param, my_params &m_arg_my_params);
void parse_params(int m_arg_c, char *const m_arg_v[], my_params &m_arg_my_params);

#endif

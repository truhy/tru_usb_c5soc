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

#include "cmd_line.h"

bool parse_param_exist(std::string m_arg_param, std::string m_arg_key_word){
	// Len of param is correct or longer?
	if(m_arg_param.size() == m_arg_key_word.size()){
		// Compare param with key word
		if(m_arg_param.compare(0, m_arg_key_word.size(), m_arg_key_word) == 0){
			return true;
		}
	}

	return false;
}

bool parse_param_str(std::string m_arg_param, std::string m_arg_key_word, std::string &m_arg_data_str){
	// Len of param is correct or longer?
	if(m_arg_param.size() >= (m_arg_key_word.size() + 1)){
		// Compare param with key word
		if(m_arg_param.compare(0, m_arg_key_word.size(), m_arg_key_word) == 0){
			m_arg_data_str = m_arg_param.substr(m_arg_key_word.size(), m_arg_param.size());

			return true;
		}
	}

	return false;
}

bool parse_param_yn(std::string m_arg_param, std::string m_arg_key_word, bool &m_arg_yn){
	// Len of param is correct or longer?
	if(m_arg_param.size() >= (m_arg_key_word.size() + 1)){
		// Compare param with key word
		if(m_arg_param.compare(0, m_arg_key_word.size(), m_arg_key_word) == 0){
			if(m_arg_param.substr(m_arg_key_word.size(), 1) == "y"){
				m_arg_yn = true;
			}else{
				m_arg_yn = false;
			}

			return true;
		}
	}

	return false;
}

bool parse_param_hex_str(std::string m_arg_param, std::string m_arg_key_word, std::string &m_arg_str){
	char m_char;
	std::string::size_type m_i;

	m_arg_str.clear();
	// Len of param is correct or longer?
	if(m_arg_param.size() >= (m_arg_key_word.size() + 1)){
		// Compare param to key word
		if(m_arg_param.compare(0, m_arg_key_word.size(), m_arg_key_word) == 0){
			for(m_i = 0; m_i < (m_arg_param.size() - m_arg_key_word.size()); m_i += 2){
				m_char = (char)strtoul(m_arg_param.substr(m_arg_key_word.size() + m_i, 2).c_str(), NULL, 16);
				m_arg_str += m_char;
			}

			return true;
		}
	}

	return false;
}

void usage(char *m_arg_0){
	printf("%s v20240706\n", m_arg_0);
	printf("Usage:\n");
	printf("%s <params>\n\n", m_arg_0);
	printf("\n");
	printf("<params>:\n");
	printf(" [cmd=<s>]     : command string\n");
	printf(" [rlen=<n>]    : read len\n");
	printf(" [wlen=<n>]    : write len\n");
	printf(" [runs=<n>]    : number of runs\n");
	printf(" [timeout=<n>] : n ms timeout\n");
}

bool parse_params_search(char *m_arg_cmdl_param, my_params &m_arg_my_params){
	std::string m_str;

	if(parse_param_str(m_arg_cmdl_param, "cmd=", m_str)){
		if(m_str == "rate"){ m_arg_my_params.cmd = MSOS1_CMD_RATE_TEST; return true; }
		if(m_str == "verify"){ m_arg_my_params.cmd = MSOS1_CMD_VERIFY_TEST; return true; }
	}
	if(parse_param_val_uint(m_arg_cmdl_param, "rlen=", m_arg_my_params.rlen)) return true;
	if(parse_param_val_uint(m_arg_cmdl_param, "wlen=", m_arg_my_params.wlen)) return true;
	if(parse_param_val_uint(m_arg_cmdl_param, "runs=", m_arg_my_params.num_runs)) return true;
	if(parse_param_val_uint(m_arg_cmdl_param, "timeout=", m_arg_my_params.timeout_ms)) return true;

	return false;
}

void parse_params(int m_arg_c, char *const m_arg_v[], my_params &m_arg_my_params){
	int m_i;

	// Iterate to search for parameters
	for(m_i = 1; m_i < m_arg_c; m_i++){
		parse_params_search(m_arg_v[m_i], m_arg_my_params);
	}
}

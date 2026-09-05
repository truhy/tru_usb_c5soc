#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include "to_string.h"
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string>
#include <list>
#include <vector>
#include <functional>
#include <algorithm>
#include <locale>
#include <cctype>
#ifdef OS_WINDOWS
	//#include <regex>
#else
	//#include <tr1/regex>
#endif

#define CHAR_CR (char)13
#define CHAR_LF (char)10
#define STR_CRLF std::string(1, CHAR_CR) + CHAR_LF
#define STR_NEWLINE STR_CRLF

namespace ns_string_utils{
	#define STRING_SPLIT_DELIM_STYLE_EXCLUDE  0
	#define STRING_SPLIT_DELIM_STYLE_LEADING  1
	#define STRING_SPLIT_DELIM_STYLE_TRAILING 2

	std::string str_find_chars_replace_to_hxx(std::string m_arg_str, std::string m_arg_search_chars);
	std::string str_find_replace_hxx_to_char(std::string m_arg_str);
	std::string str_find_chars_replace(std::string m_arg_str, std::string m_arg_search_chars, std::string m_arg_rep_str);
	std::string str_find_chars_insert(std::string m_arg_str, std::string m_arg_search_chars, std::string m_arg_rep_str);
	std::string str_find_chars_erase(std::string m_arg_str, std::string m_arg_search_chars);
	std::string str_find_replace(std::string m_arg_str, std::string m_arg_search_str, std::string m_arg_rep_str);
	std::list<std::string> stringsplit(std::string m_arg_str, std::string m_arg_delimiters, uint8_t m_arg_delim_style, bool m_arg_want_empty);
	int nocase_cmp(std::string m_arg_str_1, std::string m_arg_str_2);
	std::string to_upper_str(std::string m_arg_str);
	std::string to_lower_str(std::string m_arg_str);
	std::string buf_to_hex_str(unsigned char* m_arg_buf, size_t m_arg_buf_len, bool m_arg_is_big_endian);
	std::string buf_to_hex_up_str(unsigned char* m_arg_buf, size_t m_arg_buf_len, bool m_arg_is_big_endian);
	std::string buf_to_ascii_alphanum_str(unsigned char* m_arg_buf, size_t m_arg_buf_len);
	std::string buf_to_ascii_printable_str(unsigned char* m_arg_buf, size_t m_arg_buf_len);
	std::string word_wrap(std::string m_arg_str, size_t m_arg_line_width, std::string m_arg_new_line_str);
	std::string str_dbc_to_sbc(std::string m_arg_dbc_str, bool m_arg_is_big_endian, std::string m_arg_replacement, std::string m_arg_terminator);
	std::string str_sbc_to_dbc(std::string m_arg_sbc_str, bool m_arg_is_big_endian);
	std::string ltrim(std::string m_arg_str);
	std::string rtrim(std::string m_arg_str);
	std::string trim(std::string m_arg_str);
	int strcasecmp(const char* m_s1, const char* m_s2);
	int strncasecmp(const char* m_s1, const char* m_s2, size_t m_n);
	std::string append_if_not_empty(std::string m_arg_input_str, std::string m_arg_append_str);
}

#endif

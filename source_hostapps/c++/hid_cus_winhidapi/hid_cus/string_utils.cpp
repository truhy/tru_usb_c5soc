#include "string_utils.h"

/*
	Find any characters in the search string and replaces them to the form &HXX, where
	XX is ASCII code of character.

	Example:

	Replaces comma, colon and new line.

	str_chars_replace_to_hxx(m_arg_in_out_str, ",:\n");

	Before: m_arg_in_out_str = "Error: 01, 3746465ABC\nHello"
	After:  m_arg_in_out_str = "Error&H3A 01&H2C 3746465ABC&H0AHello"

	The example replaced the following characters:

	Character  ASCII code  Replaced with
	,          0x3A        &H3A
	:          0x2C        &H2C
	\n         0x0A        &H0A

*/
std::string ns_string_utils::str_find_chars_replace_to_hxx(std::string m_arg_str, std::string m_arg_search_chars){
	std::string::size_type m_pos = m_arg_str.find_first_of(m_arg_search_chars);

	while(m_pos != std::string::npos){
		m_arg_str.replace(m_pos, 1, "&H" + ns_to_string_utils::to_string_right_hex_up((int)(m_arg_str.at(m_pos)), 2, '0'));
		m_pos = m_arg_str.find_first_of(m_arg_search_chars, m_pos + 4);
	}

	return m_arg_str;
}

std::string ns_string_utils::str_find_replace_hxx_to_char(std::string m_arg_str){
	std::string::size_type m_pos;
	std::string m_hxx_val_str;
	long m_val;
	std::string m_val_str;
	bool m_convert_yn;

	//Find first.
	m_pos = m_arg_str.find("&H");

	//A valid position?
	while(m_pos != std::string::npos){
		m_convert_yn = true;

		//Check whether we should skip conversion.
		if(m_pos > 0){
			if(m_arg_str.substr(m_pos - 1, 1) == "&"){
				m_convert_yn = false;
				m_pos++;
			}
		}

		//Do conversion?
		if(m_convert_yn){
			if((m_pos + 2) < m_arg_str.size()){
				m_hxx_val_str = m_arg_str.substr(m_pos + 2, 2);
			}else{
				m_hxx_val_str = m_arg_str.substr(m_pos + 2, m_arg_str.size());
			}
			m_val = strtol(m_hxx_val_str.c_str(), NULL, 16);
			m_val_str = (char)m_val;
			m_arg_str.replace(m_pos, m_hxx_val_str.size() + 2, m_val_str);
		}

		//Find next.
		m_pos = m_arg_str.find("&H", m_pos + 1);
	}

	return m_arg_str;
}

/*
	Find any characters in the search string and replaces them with the replacement string.

	Example:

	str_find_chars_replace(m_arg_str, ",:", "abc");

	Before: "Error: 01, 3746465ABC"
	After:  "Errorabc 01abc 3746465ABC"
*/
std::string ns_string_utils::str_find_chars_replace(std::string m_arg_str, std::string m_arg_search_chars, std::string m_arg_rep_str){
	std::string::size_type m_pos = m_arg_str.find_first_of(m_arg_search_chars);

	while(m_pos != std::string::npos){
		m_arg_str.replace(m_pos, 1, m_arg_rep_str);
		m_pos = m_arg_str.find_first_of(m_arg_search_chars, m_pos + m_arg_rep_str.size());
	}

	return m_arg_str;
}

std::string ns_string_utils::str_find_chars_insert(std::string m_arg_str, std::string m_arg_search_chars, std::string m_arg_rep_str){
	std::string::size_type m_pos = m_arg_str.find_first_of(m_arg_search_chars);

	while(m_pos != std::string::npos){
		m_arg_str.insert(m_pos, m_arg_rep_str);
		m_pos = m_arg_str.find_first_of(m_arg_search_chars, m_pos + m_arg_rep_str.size() + 1);
	}

	return m_arg_str;
}

std::string ns_string_utils::str_find_chars_erase(std::string m_arg_str, std::string m_arg_search_chars){
	std::string::size_type m_pos = m_arg_str.find_first_of(m_arg_search_chars);

	while(m_pos != std::string::npos){
		m_arg_str.erase(m_pos, 1);
		m_pos = m_arg_str.find_first_of(m_arg_search_chars, m_pos);
	}

	return m_arg_str;
}

/*
	Find the search string and replaces with the replacement string.

	Example:

	str_find_replace(m_arg_str, "Dave", "Chris Brown");

	Before: "Hello Dave, and how are you Dave?"
	After:  "Hello Chris Brown, and how are you Chris Brown?"
*/
std::string ns_string_utils::str_find_replace(std::string m_arg_str, std::string m_arg_search_str, std::string m_arg_rep_str){
	std::string::size_type m_pos = m_arg_str.find(m_arg_search_str);

	while(m_pos != std::string::npos){
		m_arg_str.replace(m_pos, m_arg_search_str.size(), m_arg_rep_str, 0, m_arg_rep_str.size());
		m_pos = m_arg_str.find(m_arg_search_str, m_pos + m_arg_rep_str.size());
	}

	return m_arg_str;
}

/*
	Splits (some call it tokenize) up a given string using any characters found in the given delimiter string.

	Example 1: will tokenize into 1 string containing Hello:
	  stringsplit(m_arg_in_out_str, "\n\nHello", "\n", STRING_SPLIT_DELIM_STYLE_EXCLUDE, false);

	Example 2: will tokenize into 2 empty strings and 1 string with Hello:
	  stringsplit_empty(m_arg_in_out_str, "\n\nHello", "\n", STRING_SPLIT_DELIM_STYLE_EXCLUDE, true);
*/
std::list<std::string> ns_string_utils::stringsplit(std::string m_arg_str, std::string m_arg_delimiters, uint8_t m_arg_delim_style, bool m_arg_want_empty){
	std::list<std::string> m_substrs;
	std::string::size_type m_pos_1;
	std::string::size_type m_pos_2;
	std::string::size_type m_pos_3;

	switch(m_arg_delim_style){
		case STRING_SPLIT_DELIM_STYLE_EXCLUDE:{
			// Find first delimiter character position
			m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, 0);
			if((m_pos_2 != std::string::npos) || (m_arg_str.length() > 0)){
				// Start position
				m_pos_1 = 0;
			}else{
				m_pos_1 = std::string::npos;
			}

			while(m_pos_1 != std::string::npos){
				if(((m_pos_2 - m_pos_1) > 0) && (m_pos_1 < m_arg_str.length())){
					// Store substring
					m_substrs.push_back(m_arg_str.substr(m_pos_1, m_pos_2 - m_pos_1));
				}else if(m_arg_want_empty){
					// Store empty substring
					m_substrs.push_back(std::string());
				}
				if(m_pos_2 != std::string::npos){
					// Next start position
					m_pos_1 = m_pos_2 + 1;
					// Find next delimiter character position
					m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, m_pos_2 + 1);
				}else{
					m_pos_1 = std::string::npos;
				}
			}

			break;
		}
		case STRING_SPLIT_DELIM_STYLE_LEADING:{
			// Find first delimiter character position
			m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, 0);
			if(m_pos_2 != std::string::npos){
				// Start position
				m_pos_1 = 0;
			}else if(m_arg_str.length() > 0){
				// Store substring
				m_substrs.push_back(m_arg_str);
				m_pos_1 = std::string::npos;
			}else{
				m_pos_1 = std::string::npos;
			}

			while(m_pos_1 != std::string::npos){
				if(m_pos_2 != std::string::npos){
					m_pos_3 = m_pos_2;
				}else{
					m_pos_3 = m_arg_str.length();
				}
				if(((m_pos_3 - m_pos_1) > 1) && (m_pos_1 < m_arg_str.length())){
					// Store substring
					m_substrs.push_back(m_arg_str.substr(m_pos_1, m_pos_3 - m_pos_1));
				}else if(m_arg_want_empty){
					// Store just the delimiter for empty substring
					m_substrs.push_back(m_arg_str.substr(m_pos_1, m_pos_3 - m_pos_1));
				}
				if(m_pos_2 != std::string::npos){
					// Next start position
					m_pos_1 = m_pos_2;
					// Find next delimiter character position
					m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, m_pos_2 + 1);
				}else{
					m_pos_1 = std::string::npos;
				}
			}

			break;
		}
		case STRING_SPLIT_DELIM_STYLE_TRAILING:{
			// Find first delimiter character position
			m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, 0);
			if(m_pos_2 != std::string::npos){
				// Start position
				m_pos_1 = 0;
			}else if(m_arg_str.length() > 0){
				// Store substring
				m_substrs.push_back(m_arg_str);
				m_pos_1 = std::string::npos;
			}else{
				m_pos_1 = std::string::npos;
			}

			while(m_pos_1 != std::string::npos){
				if(m_pos_2 != std::string::npos){
					m_pos_3 = m_pos_2;
				}else{
					m_pos_3 = m_arg_str.length();
				}
				if(((m_pos_3 - m_pos_1) > 0) && (m_pos_1 < m_arg_str.length())){
					// Store substring
					m_substrs.push_back(m_arg_str.substr(m_pos_1, m_pos_3 - m_pos_1 + 1));
				}else if(m_arg_want_empty){
					// Store just the delimiter for empty substring
					m_substrs.push_back(m_arg_str.substr(m_pos_1, m_pos_3 - m_pos_1 + 1));
				}
				if(m_pos_2 != std::string::npos){
					// Next start position
					m_pos_1 = m_pos_2 + 1;
					// Find next delimiter character position
					m_pos_2 = m_arg_str.find_first_of(m_arg_delimiters, m_pos_2 + 1);
				}else{
					m_pos_1 = std::string::npos;
				}
			}

			break;
		}
	}

	return m_substrs;
}

/*
	Case insensitive comparison of 2 strings and returns one of the following:
		- Equal returns 0.
		- String 1 is higher than string 2 then returns 1.
		- String 1 is lower than string 2 then returns -1.
	Because it uses standard C toupper function the comparison is affected by the current locale set.
*/
int ns_string_utils::nocase_cmp(std::string m_arg_str_1, std::string m_arg_str_2){
	std::string::const_iterator m_it_1 = m_arg_str_1.begin();
	std::string::const_iterator m_it_2 = m_arg_str_2.begin();

	while((m_it_1 != m_arg_str_1.end()) && (m_it_2 != m_arg_str_2.end())){
		// Does character differ?
		if(toupper(*m_it_1) != toupper(*m_it_2)){
			// Return -1 to indicate smaller than, else 1 for bigger
			return (toupper(*m_it_1) < toupper(*m_it_2)) ? -1 : 1;
		}

		// Next character
		m_it_1++;
		m_it_2++;
	}
	// Cache lengths
	size_t m_size_1 = m_arg_str_1.size();
	size_t m_size_2 = m_arg_str_2.size();

	// Return -1, 0 or 1 according to strings' lengths
	if(m_size_1 == m_size_2){
		return 0;
	}
	return (m_size_1 < m_size_2) ? -1 : 1;
}

/*
	Converts a string to upper case letters.
	Because it uses standard C toupper function it is affected by the current locale set.
*/
std::string ns_string_utils::to_upper_str(std::string m_arg_str){
	std::transform(m_arg_str.begin(), m_arg_str.end(), m_arg_str.begin(), toupper);
	return m_arg_str;
}

/*
	Converts a string to lower case letters.
	Because it uses standard C tolower function it is affected by the current locale set.
*/
std::string ns_string_utils::to_lower_str(std::string m_arg_str){
	std::transform(m_arg_str.begin(), m_arg_str.end(), m_arg_str.begin(), tolower);
	return m_arg_str;
}

// Converts bytes from a buffer to a hex string
std::string ns_string_utils::buf_to_hex_str(unsigned char* m_arg_buf, size_t m_arg_buf_len, bool m_arg_is_big_endian){
	std::string hex_str;
	size_t m_i;

	if(m_arg_is_big_endian){
		for(m_i = 0; m_i < m_arg_buf_len; m_i++){
			hex_str += ns_to_string_utils::to_string_right_hex((int)(m_arg_buf[m_i]), 2, '0');
		}
	}else{
		m_i = m_arg_buf_len;
		do{
			--m_i;
			hex_str += ns_to_string_utils::to_string_right_hex((int)(m_arg_buf[m_i]), 2, '0');
		}while(m_i > 0);
	}

	return hex_str;
}

// Converts bytes from a buffer to a hex uppercase string
std::string ns_string_utils::buf_to_hex_up_str(unsigned char* m_arg_buf, size_t m_arg_buf_len, bool m_arg_is_big_endian){
	std::string hex_str;
	size_t m_i;

	if(m_arg_is_big_endian){
		for(m_i = 0; m_i < m_arg_buf_len; m_i++){
			hex_str += ns_to_string_utils::to_string_right_hex_up((int)(m_arg_buf[m_i]), 2, '0');
		}
	}else{
		m_i = m_arg_buf_len;
		do{
			--m_i;
			hex_str += ns_to_string_utils::to_string_right_hex_up((int)(m_arg_buf[m_i]), 2, '0');
		}while(m_i > 0);
	}

	return hex_str;
}

// Converts bytes from a buffer to alphanumeric string
std::string ns_string_utils::buf_to_ascii_alphanum_str(unsigned char* m_arg_buf, size_t m_arg_buf_len){
	std::string m_str;
	size_t m_i;

	for(m_i = 0; m_i < m_arg_buf_len; m_i++){
		if(isalnum(m_arg_buf[m_i])){ m_str.append(1, (char)m_arg_buf[m_i]); }
	}

	return m_str;
}

// Converts bytes from a buffer to printable string
std::string ns_string_utils::buf_to_ascii_printable_str(unsigned char* m_arg_buf, size_t m_arg_buf_len){
	std::string m_str;
	size_t m_i;

	for(m_i = 0; m_i < m_arg_buf_len; m_i++){
		if(isprint(m_arg_buf[m_i])){ m_str.append(1, (char)m_arg_buf[m_i]); }
	}

	return m_str;
}

std::string ns_string_utils::word_wrap(std::string m_arg_str, size_t m_arg_line_width, std::string m_arg_new_line_str){
	std::string m_new_str;
	std::string::size_type m_pos;
	std::string::size_type m_pos_prev;

	m_pos = 0;

	while(m_pos < m_arg_str.size()){
		m_pos_prev = m_pos;
		m_pos += m_arg_line_width;

		m_new_str += m_arg_str.substr(m_pos_prev, m_pos - m_pos_prev);

		if(m_pos != m_arg_str.size()){
			m_new_str += m_arg_new_line_str;
		}
	}

	return m_new_str;
}

/*
	Double-byte character string to single-byte character string.
	If a double-byte character code is higher than 255 then it is replaced
	with the specified replacement string.
*/
std::string ns_string_utils::str_dbc_to_sbc(std::string m_arg_dbc_str, bool m_arg_is_big_endian, std::string m_arg_replacement, std::string m_arg_terminator){
	uint8_t m_i;
	std::string::iterator m_dbc_str_it;
	std::string m_sbc_str;
	uint8_t m_sbc;
	std::string::size_type m_pos;

	if(m_arg_terminator.size() > 0){
		m_pos = m_arg_dbc_str.find(m_arg_terminator);
		if(m_pos != std::string::npos){
			// Erase everyting from the terminator to the end
			m_arg_dbc_str.erase(m_pos, m_arg_dbc_str.size() - m_pos);
		}
	}

	m_i = 0;
	if(m_arg_is_big_endian){
		for(m_dbc_str_it = m_arg_dbc_str.begin(); m_dbc_str_it != m_arg_dbc_str.end(); ++m_dbc_str_it){
			if(m_i == 0){
				// Save character temporarily
				m_sbc = *m_dbc_str_it;
			}else{
				// Double-byte code is 255 or less?
				if(m_sbc == 0){
					// Append new character
					m_sbc_str += *m_dbc_str_it;
				}else{
					// Append replacement
					m_sbc_str += m_arg_replacement;
				}
			}
			m_i = (m_i + 1) % 2;
		}
	}else{
		for(m_dbc_str_it = m_arg_dbc_str.begin(); m_dbc_str_it != m_arg_dbc_str.end(); ++m_dbc_str_it){
			if(m_i == 0){
				// Save character temporarily
				m_sbc = *m_dbc_str_it;
			}else{
				// Double-byte code is 255 or less?
				if(*m_dbc_str_it == 0){
					// Append new character
					m_sbc_str += m_sbc;
				}else{
					// Append replacement
					m_sbc_str += m_arg_replacement;
				}
			}
			m_i = (m_i + 1) % 2;
		}

		// Handle odd length double-byte character string
		// Non empty string?
		if(m_arg_dbc_str.size() > 0){
			// String length is not double-byte (not multiple of 2)?
			if((m_arg_dbc_str.size() % 2) != 0){
				// Store last double-byte truncated character (assume it is originally a code of 255 or less)
				m_sbc_str += m_sbc;
			}
		}
	}

	return m_sbc_str;
}

/*
	Single-byte character string to double-byte character string.
*/
std::string ns_string_utils::str_sbc_to_dbc(std::string m_arg_sbc_str, bool m_arg_is_big_endian){
	std::string m_dbc_str;
	std::string::iterator m_sbc_str_it;
	std::string m_null_char;

	m_null_char.push_back((char)0);
	if(m_arg_is_big_endian){
		for(m_sbc_str_it = m_arg_sbc_str.begin(); m_sbc_str_it != m_arg_sbc_str.end(); ++m_sbc_str_it){
			// Append new character
			m_dbc_str += m_null_char + *m_sbc_str_it;
		}
	}else{
		for(m_sbc_str_it = m_arg_sbc_str.begin(); m_sbc_str_it != m_arg_sbc_str.end(); ++m_sbc_str_it){
			// Append new character
			m_dbc_str += *m_sbc_str_it + m_null_char;
		}
	}

	return m_dbc_str;
}

// Trim white space from start
std::string ns_string_utils::ltrim(std::string m_arg_str){
	m_arg_str.erase(m_arg_str.begin(), std::find_if(m_arg_str.begin(), m_arg_str.end(), std::not_fn(isspace)));
	return m_arg_str;
}

// Trim white space from end
std::string ns_string_utils::rtrim(std::string m_arg_str){
	m_arg_str.erase(std::find_if(m_arg_str.rbegin(), m_arg_str.rend(), std::not_fn(isspace)).base(), m_arg_str.end());
	return m_arg_str;
}

// Trim white space from both ends
std::string ns_string_utils::trim(std::string m_arg_str){
	return ltrim(rtrim(m_arg_str));
}

int ns_string_utils::strcasecmp(const char* m_s1, const char* m_s2){
    const unsigned char* m_us1 = (const unsigned char*)m_s1;
    const unsigned char* m_us2 = (const unsigned char*)m_s2;

    while(tolower(*m_us1) == tolower(*m_us2++)){
        if(*m_us1++ == '\0'){ return (0); }
	}
    return (tolower(*m_us1) - tolower(*--m_us2));
}

int ns_string_utils::strncasecmp(const char* m_s1, const char* m_s2, size_t m_n){
	if(m_n != 0){
		const unsigned char* m_us1 = (const unsigned char*)m_s1;
		const unsigned char* m_us2 = (const unsigned char*)m_s2;

		do{
			if(tolower(*m_us1) != tolower(*m_us2++)){ return (tolower(*m_us1) - tolower(*--m_us2)); }
			if(*m_us1++ == '\0') break;
		}while(--m_n != 0);
    }
    return 0;
}

std::string ns_string_utils::append_if_not_empty(std::string m_arg_input_str, std::string m_arg_append_str){
	if(m_arg_input_str.size() > 0){
		m_arg_input_str += m_arg_append_str;
	}
	return m_arg_input_str;
}

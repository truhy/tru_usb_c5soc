#ifndef CMD_LINE_AND_VARS_H
#define CMD_LINE_AND_VARS_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>

// Command line codes
typedef enum{
	CMDL_REQ_NONE,
	CMDL_REQ_DEV_LIST,
	CMDL_REQ_REPORT
}cmdl_request;

class cl_my_params{
public:
	std::string dev_path;
	std::string product_name;
	uint16_t vid;
	uint16_t pid;
	uint8_t cmdl_req;
	unsigned long usb_timeout_ms;
	uint32_t rlen;
	uint32_t wlen;

	cl_my_params() :
		vid(0),
		pid(0),
		cmdl_req(CMDL_REQ_NONE),
		usb_timeout_ms(INFINITE),
		rlen(64),
		wlen(64){
	}
};

template<class T>
bool parse_param_val(std::string param, std::string key, T &value){
	std::string param_substr;

	// Len of param is correct or longer?
	if(param.size() >= (key.size() + 1)){
		// Compares param to key word
		if(param.compare(0, key.size(), key) == 0){
			param_substr = param.substr(key.size(), param.size());
			if(!param_substr.empty()){
				//value = str_to_num<T>(param_substr);
				//value = (T)strtol(param_substr.c_str(), NULL, 0);
				value = (T)atof(param_substr.c_str());
			}else{
				value = 0;
			}

			return true;
		}
	}

	return false;
}

template<class T>
bool parse_param_val_int(std::string param, std::string key, T &value){
	std::string param_substr;

	// Len of param is correct or longer?
	if(param.size() >= (key.size() + 1)){
		// Compares param to key word
		if(param.compare(0, key.size(), key) == 0){
			param_substr = param.substr(key.size(), param.size());
			if(!param_substr.empty()){
				//value = str_to_num<T>(param_substr);
				value = (T)strtol(param_substr.c_str(), NULL, 0);
				//value = (T)atof(param_substr.c_str());
			}else{
				value = 0;
			}

			return true;
		}
	}

	return false;
}

template<class T>
bool parse_param_val_uint(std::string param, std::string key, T &value){
	std::string param_substr;
	
	// Len of param is correct or longer?
	if(param.size() >= (key.size() + 1)){
		// Compares param to key word
		if(param.compare(0, key.size(), key) == 0){
			param_substr = param.substr(key.size(), param.size());
			if(!param_substr.empty()){
				//value = str_to_num<T>(param_substr);
				value = (T)strtoul(param_substr.c_str(), NULL, 0);
				//value = (T)atof(param_substr.c_str());
			}else{
				value = 0;
			}

			return true;
		}
	}

	return false;
}

bool parse_param_exist(std::string param, std::string key);
bool parse_param_str(std::string param, std::string key, std::string &value);
bool parse_param_yn(std::string param, std::string key, bool &value);
bool parse_param_hex_str(std::string param, std::string key, std::string &value);
void usage(char *arg_0);
bool parse_params_search(char *cmdl_param, cl_my_params *my_params);
void parse_params(int arg_c, char *arg_v[], cl_my_params *my_params);

#endif

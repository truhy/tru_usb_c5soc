#include "cmd_line_and_vars.h"

bool parse_param_exist(std::string param, std::string key){
	// Len of param is correct or longer?
	if(param.size() == key.size()){
		// Compares param to key word
		if(param.compare(0, key.size(), key) == 0){
			return true;
		}
	}

	return false;
}

bool parse_param_str(std::string param, std::string key, std::string &value){
	// Len of param is correct or longer?
	if(param.size() >= (key.size() + 1)){
		// Compares param to key word
		if(param.compare(0, key.size(), key) == 0){
			value = param.substr(key.size(), param.size());

			return true;
		}
	}

	return false;
}

bool parse_param_yn(std::string param, std::string key, bool &value){
	// Len of param is correct or longer?
	if(param.size() >= (key.size() + 1)){
		// Compares param to key word
		if(param.compare(0, key.size(), key) == 0){
			if(param.substr(key.size(), 1) == "y"){
				value = true;
			}else{
				value = false;
			}

			return true;
		}
	}

	return false;
}

bool parse_param_hex_str(std::string param, std::string key, std::string &value){
	char ch;
	std::string::size_type i;

	value.clear();
	// Len of param is correct or longer?
	if(param.size() >= (key.size() + 1)){
		// Compares param to key word
		if(param.compare(0, key.size(), key) == 0){
			for(i = 0; i < (param.size() - key.size()); i += 2){
				ch = (char)strtoul(param.substr(key.size() + i, 2).c_str(), NULL, 16);
				value += ch;
			}
			return true;
		}
	}
	return false;
}

void usage(char *arg_0){
	printf("%s v20260819\n", arg_0);
	printf("Usage:\n");
	printf(" %s <Device> <Parameters>\n\n", arg_0);
	printf("Device:\n");
	printf("list            : list USB HID devices\n");
	printf("path=<x>        : open Windows device path string\n");
	printf("product=<x>     : open USB HID device product string\n\n");
	printf("vid=<x> pid=<x> : open USB Vendor ID & Product ID\n");
	printf("\n");
	printf("Parameters:\n");
	printf("req=report    : tx/rx report\n");
	printf(" [rlen=<n>]    : read len\n");
	printf(" [wlen=<n>]    : write len\n");
	printf(" [timeout=<x>] : wait timeout\n");
}

bool parse_params_search(char *cmdl_param, cl_my_params *my_params){
	std::string m_str;

	if(parse_param_str(cmdl_param, "path=", my_params->dev_path)) return true;
	if(parse_param_str(cmdl_param, "product=", my_params->product_name)) return true;
	if(parse_param_val_uint(cmdl_param, "vid=", my_params->vid)) return true;
	if(parse_param_val_uint(cmdl_param, "pid=", my_params->pid)) return true;
	if(parse_param_exist(cmdl_param, "list")){
		my_params->cmdl_req = CMDL_REQ_DEV_LIST;
		return true;
	}
	if(parse_param_str(cmdl_param, "req=", m_str)){
		if(m_str == "report"){ my_params->cmdl_req = CMDL_REQ_REPORT; return true; }
	}
	if(parse_param_val_uint(cmdl_param, "timeout=", my_params->usb_timeout_ms)) return true;
	if(parse_param_val_uint(cmdl_param, "rlen=", my_params->rlen)) return true;
	if(parse_param_val_uint(cmdl_param, "wlen=", my_params->wlen)) return true;

	return false;
}

void parse_params(int arg_c, char *arg_v[], cl_my_params *my_params){
	int i;

	// Iterate to search for parameters
	for(i = 1; i < arg_c; i++){
		parse_params_search(arg_v[i], my_params);
	}
}

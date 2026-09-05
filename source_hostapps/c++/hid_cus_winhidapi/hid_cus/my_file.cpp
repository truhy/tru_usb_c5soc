#include "my_file.h"

cl_my_file::cl_my_file() :
	_file(NULL){
	_line = (char*)malloc(MAX_FILE_LINE_LEN);
}

cl_my_file::~cl_my_file(){
	close_file();
	if(_line != NULL){
		free(_line);
	}
}

std::string cl_my_file::last_err_msg(){
	return _last_err;
}

size_t cl_my_file::last_err_msg_len(){
	return _last_err.length();
}

bool cl_my_file::open_file(std::string filefullpath, std::string open_mode){
	_last_err.clear();
	
	close_file();

	// Open file
	fopen_s(&_file, filefullpath.c_str(), open_mode.c_str());
	if(_file == NULL){
		_last_err = "Error: could not open file " + filefullpath;
		return false;
	}

	return true;
}

bool cl_my_file::read_file_line(std::string &line){
	_last_err.clear();

	_line[0] = 0;
	fgets(_line, 300, _file);

	// File error?
	if(ferror(_file)){
		char errmsg[255]; 
		strerror_s(errmsg, 255, errno);
		_last_err.assign(errmsg);
		_last_err = "Error: " + _last_err;
		return false;
	}else{
		line.assign(_line);
		// Erase newline character at end of line
		if(line.size() > 0){
			if(line.substr(line.size() - 1, 1).compare("\n") == 0){
				line.erase(line.size() - 1);
			}
		}
	}

	return true;
}

bool cl_my_file::read_file(void *buf, size_t rlen, size_t &bytes_rd){
	_last_err.clear();

	// Read block bytes
	bytes_rd = fread(buf, 1, rlen, _file);

	// File error?
	if(ferror(_file)){
		char errmsg[255]; 
		strerror_s(errmsg, 255, errno);
		_last_err.assign(errmsg);
		_last_err = "Error: " + _last_err;
		return false;
	}else if(bytes_rd != rlen){
		_last_err = "Error: some bytes failed to read!";
		return false;
	}

	return true;
}

bool cl_my_file::write_file(const void *buf, size_t wlen, size_t &bytes_wr){
	_last_err.clear();

	// Write block bytes
	bytes_wr = fwrite(buf, 1, wlen, _file);

	// File error?
	if(ferror(_file)){
		char errmsg[255]; 
		strerror_s(errmsg, 255, errno);
		_last_err.assign(errmsg);
		_last_err = "Error: " + _last_err;
		return false;
	}else if(bytes_wr != wlen){
		_last_err = "Error: some bytes failed to write!";
		return false;
	}

	return true;
}

long cl_my_file::length(){
	long prev = ftell(_file);
	long len;
	fseek(_file, 0, SEEK_END);
	len = ftell(_file);
	fseek(_file, prev, SEEK_SET);

	return len;
}

void cl_my_file::close_file(){
	_last_err.clear();

	if(_file != NULL){
		fclose(_file);
		_file = NULL;
	}
}

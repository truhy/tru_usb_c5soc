#ifndef MY_BUF_H
#define MY_BUF_H

class cl_my_buf{
protected:
	unsigned char *_buf;
	size_t _len;

public:
	cl_my_buf() :
		_buf(NULL),
		_len(0){
	}
	~cl_my_buf(){
		if(_buf != NULL){
			free(_buf);
			_buf = NULL;
			_len = 0;
		}
	}
	unsigned char* get_buf(){
		return _buf;
	}
	bool alloc_buf(uint32_t m_arg_len){
		if(_buf != NULL){
			free(_buf);
			_buf = NULL;
			_len = 0;
		}

		_buf = (unsigned char*)malloc(m_arg_len);
		if(_buf == NULL){
			return false;
		}
		_len = m_arg_len;
		return true;
	}
	size_t len(){
		return _len;
	}
};

#endif

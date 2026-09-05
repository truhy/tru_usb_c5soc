#ifndef MY_USB_DEV_H
#define MY_USB_DEV_H

#include <windows.h>
#include <string>

class cl_usb_dev{
private:
	HANDLE read_handle;
	HANDLE write_handle;

public:
	cl_usb_dev() :
		read_handle(INVALID_HANDLE_VALUE),
		write_handle(INVALID_HANDLE_VALUE){
	}
	~cl_usb_dev(){
		close_handles();
	}
	HANDLE dev_read_handle();
	HANDLE dev_write_handle();
	BOOL open_read_handle(std::string device_path, BOOL is_async);
	BOOL open_write_handle(std::string device_path, BOOL is_async);
	void close_read_handle();
	void close_write_handle();
	void close_handles();
	BOOL read(void *buf, DWORD len, LPDWORD bytes_read);
	BOOL write(void *buf, DWORD len, LPDWORD bytes_written);
	BOOL read_usb_async(void *buf, DWORD rlen, LPDWORD bytes_read, DWORD timeout_ms);
	BOOL write_usb_async(void *buf, DWORD wlen, LPDWORD bytes_written, DWORD timeout_ms);
};

#endif

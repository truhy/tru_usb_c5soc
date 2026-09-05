#include "my_usb_dev.h"

HANDLE cl_usb_dev::dev_read_handle(){
	return read_handle;
}
HANDLE cl_usb_dev::dev_write_handle(){
	return write_handle;
}

BOOL cl_usb_dev::open_read_handle(std::string device_path, BOOL is_async){
	if(is_async){
		read_handle = CreateFile(device_path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	}else{
		read_handle = CreateFile(device_path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	}
	if(read_handle != INVALID_HANDLE_VALUE){
		return true;
	}
	return false;
}

BOOL cl_usb_dev::open_write_handle(std::string device_path, BOOL is_async){
	if(is_async){
		write_handle = CreateFile(device_path.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 0);
	}else{
		write_handle = CreateFile(device_path.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	}
	if(write_handle != INVALID_HANDLE_VALUE){
		return true;
	}
	return false;
}

void cl_usb_dev::close_read_handle(){
	if(read_handle != INVALID_HANDLE_VALUE){
		CloseHandle(read_handle);
		read_handle = INVALID_HANDLE_VALUE;
	}
}

void cl_usb_dev::close_write_handle(){
	if(write_handle != INVALID_HANDLE_VALUE){
		CloseHandle(write_handle);
		write_handle = INVALID_HANDLE_VALUE;
	}
}

void cl_usb_dev::close_handles(){
	if(read_handle != INVALID_HANDLE_VALUE){
		CloseHandle(read_handle);
		read_handle = INVALID_HANDLE_VALUE;
	}
	if(write_handle != INVALID_HANDLE_VALUE){
		CloseHandle(write_handle);
		write_handle = INVALID_HANDLE_VALUE;
	}
}

BOOL cl_usb_dev::read(void *buf, DWORD rlen, LPDWORD bytes_read){
	return ReadFile(read_handle, buf, rlen, bytes_read, NULL);
}

BOOL cl_usb_dev::write(void *buf, DWORD wlen, LPDWORD bytes_written){
	return WriteFile(write_handle, buf, wlen, bytes_written, NULL);
}

BOOL cl_usb_dev::read_usb_async(void *buf, DWORD len, LPDWORD bytes_read, DWORD timeout_ms){
	DWORD overlapped_bytes_read;
	OVERLAPPED overlapped;
	DWORD wait_result;
	BOOL read_result;
	DWORD read_error;
	BOOL result = true;

	*bytes_read = 0;
	memset(&overlapped, 0, sizeof(overlapped));

	overlapped.hEvent = CreateEvent(NULL, true, false, NULL);
	// Bad result?
	if(!overlapped.hEvent){
		result = false;
	}else{
		// Read device asynchronously
		read_result = ReadFile(read_handle, buf, len, bytes_read, &overlapped);
		// Bad result?
		if(!read_result){
			read_error = GetLastError();
			switch(read_error){
				case ERROR_HANDLE_EOF:  // End of file reached!
					break;

				case ERROR_IO_PENDING:  // IO is still pending
					// Wait some time until overlapped read event is triggered or timed-out
					wait_result = WaitForSingleObject(overlapped.hEvent, timeout_ms);
					switch(wait_result){
						case WAIT_OBJECT_0:  // Overlapped read event was triggered
							// Get overlapped result info
							result = GetOverlappedResult(read_handle, &overlapped, &overlapped_bytes_read, false);
							// Bad result?
							if(!result){
								read_error = GetLastError();
								switch(read_error){
									case ERROR_HANDLE_EOF: break;  // End of file reached!
									case ERROR_IO_INCOMPLETE: break;
									case ERROR_IO_PENDING: CancelIo(read_handle); break;  // IO is still pending, cancel the read
								}
							}
							*bytes_read += overlapped_bytes_read;
							break;

						case WAIT_ABANDONED:
						case WAIT_TIMEOUT:  // Timed-out
							CancelIo(read_handle);  // Cancel the read
							break;

						case WAIT_FAILED:
							break;
					}
					break;
			}
		}

		CloseHandle(overlapped.hEvent);
	}

	return result;
}

BOOL cl_usb_dev::write_usb_async(void *buf, DWORD len, LPDWORD bytes_written, DWORD timeout_ms){
	DWORD overlapped_bytes_written;
	OVERLAPPED overlapped;
	DWORD wait_result;
	DWORD write_error;
	BOOL result = true;

	*bytes_written = 0;
	memset(&overlapped, 0, sizeof(overlapped));

	overlapped.hEvent = CreateEvent(NULL, true, false, NULL);
	if(!overlapped.hEvent){
		result = false;
	}else{
		// Write device asynchronously
		result = WriteFile(write_handle, buf, len, bytes_written, &overlapped);
		// Bad result?
		if(!result){
			write_error = GetLastError();
			switch(write_error){
				case ERROR_IO_PENDING:  // IO is still pending
					// Wait some time until overlapped read event is triggered or timed-out
					wait_result = WaitForSingleObject(overlapped.hEvent, timeout_ms);
					switch(wait_result){
						case WAIT_OBJECT_0:  // Overlapped read event was triggered
							// Get overlapped result info
							result = GetOverlappedResult(write_handle, &overlapped, &overlapped_bytes_written, false);
							// Bad result?
							if(!result){
								write_error = GetLastError();
								switch(write_error){
									case ERROR_IO_INCOMPLETE: break;  // IO is still pending
									case ERROR_IO_PENDING: CancelIo(read_handle); break;  // IO is still pending, cancel the read
								}
							}
							*bytes_written += overlapped_bytes_written;
							break;
						
						case WAIT_ABANDONED:
						case WAIT_TIMEOUT:  // Timed-out
							// Cancel the write
							CancelIo(write_handle);
							break;
						
						case WAIT_FAILED:
							break;
					}
					break;
			}
		}

		CloseHandle(overlapped.hEvent);
	}

	return result;
}

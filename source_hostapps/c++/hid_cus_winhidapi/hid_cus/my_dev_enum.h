#ifndef MY_DEV_ENUM_H
#define MY_DEV_ENUM_H

#include "to_string.h"
#include "string_utils.h"
#include <windows.h>
#include <setupapi.h> // For SetupDixxx functions
#include <string>
#include <list>

#pragma comment(lib, "setupapi.lib") // For setupapi.h

class cl_dev_enum_item{
public:
	std::string dev_path;
	SP_DEVINFO_DATA devinfo_data;
	std::string driver_key_name;
};

class cl_dev_enum{
protected:
	std::string last_err_msg;

public:
	std::list<cl_dev_enum_item> dev_list;

	BOOL get_dev(
		HDEVINFO dev_info_set,
		DWORD index,
		GUID *class_guid,
		std::string &dev_path,
		SP_DEVINFO_DATA &devinfo_data
	);
	BOOL get_dev_list(GUID *arg_di_class_guid);
	BOOL get_usb_dev_driver_key_name(HDEVINFO dev_info_handle, SP_DEVINFO_DATA &devinfo_data, std::string &driver_key_name);
	HDEVINFO open_dev_info_handle(GUID *di_class_guid);
	void close_dev_info_handle(HDEVINFO dev_info_handle);
};

#endif

#include "my_dev_enum.h"

BOOL cl_dev_enum::get_dev(
	HDEVINFO dev_info_set,
	DWORD index,
	GUID *di_class_guid,
	std::string &dev_path,
	SP_DEVINFO_DATA &devinfo_data
){
	BOOL                             status;
	SP_DEVICE_INTERFACE_DATA         interface_data;
	PSP_DEVICE_INTERFACE_DETAIL_DATA interface_detail_data;
	DWORD                            interface_detail_data_size;
	DWORD                            req_size;
	DWORD                            error_code;

	// Required for SetupDiEnumDeviceInterfaces
	interface_data.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
	// Get device interface data
	status =
		SetupDiEnumDeviceInterfaces( 
			dev_info_set,        // Interface Device Info list
			NULL,                // Device Info data
			di_class_guid,       // Interface registered by driver
			index,               // Which device in the list to retrieve
			&interface_data      // Device Interface Data
		 );
	if(!status){
		error_code = GetLastError();
		if(error_code == ERROR_NO_MORE_ITEMS){
			// No more interfaces
		}else{
			last_err_msg = "Error: SetupDiEnumDeviceInterfaces failed with error code: " + ns_to_string_utils::to_string(error_code);
		}
		return false;
	}
	
	// Call once to find out the required buffer size
	status =
		SetupDiGetDeviceInterfaceDetail(
			dev_info_set,     // Interface Device info list
			&interface_data,  // Interface data for the event class
			NULL,             // Checking for buffer size
			0,                // Checking for buffer size
			&req_size,        // Buffer size required to get the detail data
			NULL              // Checking for buffer size
		 );
	// Finding out the required buffer size will give error of ERROR_INSUFFICIENT_BUFFER, so ignore it
	if(status == false){
		error_code = GetLastError();
		if(error_code != ERROR_INSUFFICIENT_BUFFER){
			last_err_msg = "Error: SetupDiGetDeviceInterfaceDetail failed with error code: " + ns_to_string_utils::to_string(error_code);
			return false;
		}
	}

	// Check if required buffer size is valid
	if(req_size > 0){
		// Allocate space..
		interface_detail_data_size = req_size;
		interface_detail_data = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(interface_detail_data_size);
		if(interface_detail_data == NULL){
			last_err_msg = "Error: Unable to allocate memory to get the interface detail data";
			return false;
		}
	}else{
		last_err_msg = "Error: SetupDiGetDeviceInterfaceDetail failed: Did not return the required buffer size";
		return false;
	}

	// Required for SetupDiGetDeviceInterfaceDetail
	interface_detail_data->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
	devinfo_data.cbSize = sizeof(SP_DEVINFO_DATA);

	// Call again to get the actual Device Detail Data
	status =
		SetupDiGetDeviceInterfaceDetail(
			dev_info_set,                // Interface Device info
			&interface_data,             // Interface data for the event class
			interface_detail_data,       // Interface detail data
			interface_detail_data_size,  // Interface detail data size
			&req_size,                   // Buffer size required to get the detail data
			&devinfo_data                // Interface device info
		 );

	if(!status){
		free(interface_detail_data);
		last_err_msg = "Error: SetupDiGetDeviceInterfaceDetail failed with error code: " + ns_to_string_utils::to_string(GetLastError());
		return false;
	}

	dev_path = interface_detail_data->DevicePath;

	free(interface_detail_data);

	return true;
}

BOOL cl_dev_enum::get_dev_list(GUID *arg_di_class_guid)
{
	HDEVINFO dev_info_handle;
	cl_dev_enum dev_enum;
	DWORD index;
	cl_dev_enum_item dev_enum_item;

	// Get handle to the list of devices belonging to a class GUID
	dev_info_handle = open_dev_info_handle(arg_di_class_guid);
	if(dev_info_handle == INVALID_HANDLE_VALUE){
		return false;
	}
	
	// A loop to enumerate device list on the system
	index = 0;
	do{
		if(
			dev_enum.get_dev(
				dev_info_handle,
				index,
				arg_di_class_guid,
				dev_enum_item.dev_path,
				dev_enum_item.devinfo_data
			)
		){
			dev_enum.get_usb_dev_driver_key_name(dev_info_handle, dev_enum_item.devinfo_data, dev_enum_item.driver_key_name);
			dev_list.push_back(dev_enum_item);
		}else{
			break;
		}
		index++;
	}while(true);

	close_dev_info_handle(dev_info_handle);

	return true;
}

BOOL cl_dev_enum::get_usb_dev_driver_key_name(HDEVINFO dev_info_handle, SP_DEVINFO_DATA &devinfo_data, std::string& driver_key_name){
	BOOL result;
	char* driver_key_name_ptr;
	DWORD reg_type;
	DWORD req_size;

	driver_key_name.clear();

	reg_type = REG_SZ;
	result =
		SetupDiGetDeviceRegistryProperty(
			dev_info_handle,
			&devinfo_data,
			SPDRP_DRIVER,
			&reg_type,
			NULL,
			0,
			&req_size
		);
	if((result) || (!result && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))){
		if(req_size > 0){
			driver_key_name_ptr = (char*)malloc(req_size);
			if(driver_key_name_ptr != NULL){
				result =
					SetupDiGetDeviceRegistryProperty(
						dev_info_handle,
						&devinfo_data,
						SPDRP_DRIVER,
						&reg_type,
						(PBYTE)driver_key_name_ptr,
						req_size,
						&req_size
					);
				if(result){
					if(req_size > 0){
						driver_key_name.assign(driver_key_name_ptr, req_size - 1);
					}
				}else{
					last_err_msg = "Error: SetupDiGetDeviceRegistryProperty+SPDRP_DRIVER failed with error code: " + ns_to_string_utils::to_string(GetLastError());
				}

				free(driver_key_name_ptr);
			}else{
				last_err_msg = "Error: Memory allocation failed!";
			}
		}else{
			result = false;
			last_err_msg = "Error: 0 length received by SetupDiGetDeviceRegistryProperty+SPDRP_DRIVER!";
		}
	}else{
		last_err_msg = "Error: SetupDiGetDeviceRegistryProperty+SPDRP_DRIVER failed with error code: " + ns_to_string_utils::to_string(GetLastError());
	}

	return result;
}

HDEVINFO cl_dev_enum::open_dev_info_handle(GUID *arg_di_class_guid){
	HDEVINFO dev_info_handle;

	// Get handle to the list of devices belonging to a class GUID
	dev_info_handle =
		SetupDiGetClassDevs(
			arg_di_class_guid,
			NULL,
			0,
			DIGCF_PRESENT | DIGCF_INTERFACEDEVICE
		);
	if(dev_info_handle == INVALID_HANDLE_VALUE){
		last_err_msg = "Error: SetupDiGetClassDevs failed with error code: " + ns_to_string_utils::to_string(GetLastError());
	}
	return dev_info_handle;
}

void cl_dev_enum::close_dev_info_handle(HDEVINFO dev_info_handle){
	if(dev_info_handle != INVALID_HANDLE_VALUE){
		// Release the list of devices
		SetupDiDestroyDeviceInfoList(dev_info_handle);
	}
}

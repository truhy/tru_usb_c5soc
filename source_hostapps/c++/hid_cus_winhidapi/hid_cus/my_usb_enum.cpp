#include "my_usb_enum.h"

void cl_usb_enum::list_dev(){
	cl_dev_enum m_dev_enum;
	std::list<cl_dev_enum_item>::iterator m_dev_list_it;
	HANDLE m_dev_handle;
	unsigned char m_buf[256];
	std::string m_dbc_str;
	std::string m_str;
	HIDD_ATTRIBUTES m_attrib;
	PHIDP_PREPARSED_DATA m_preparsed_data;
	HIDP_CAPS m_caps;

	if(m_dev_enum.get_dev_list((GUID*)&m_di_usb_dev_guid)){
		for(m_dev_list_it = m_dev_enum.dev_list.begin(); m_dev_list_it != m_dev_enum.dev_list.end(); ++m_dev_list_it){
			printf("Device path: %s\n", m_dev_list_it->dev_path.c_str());

			m_dev_handle = CreateFile(m_dev_list_it->dev_path.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if(m_dev_handle != INVALID_HANDLE_VALUE){
				if(HidD_GetAttributes(m_dev_handle, &m_attrib)){
					printf("Vendor ID: %4.4X\n", m_attrib.VendorID);
					printf("Product ID: %4.4X\n", m_attrib.ProductID);
					printf("Version Nr: %4.4X\n", m_attrib.VersionNumber);
				}
				if(HidD_GetManufacturerString(m_dev_handle, m_buf, sizeof(m_buf))){
					m_dbc_str.assign((char*)m_buf, sizeof(m_buf));
					m_str = ns_string_utils::str_dbc_to_sbc(m_dbc_str, false, "", "");
					printf("Manufacturer: %s\n", m_str.c_str());
				}
				if(HidD_GetProductString(m_dev_handle, m_buf, sizeof(m_buf))){
					m_dbc_str.assign((char*)m_buf, sizeof(m_buf));
					m_str = ns_string_utils::str_dbc_to_sbc(m_dbc_str, false, "", "");
					printf("Product: %s\n", m_str.c_str());
				}
				if(HidD_GetSerialNumberString(m_dev_handle, m_buf, sizeof(m_buf))){
					m_dbc_str.assign((char*)m_buf, sizeof(m_buf));
					m_str = ns_string_utils::str_dbc_to_sbc(m_dbc_str, false, "", "");
					printf("Serial: %s\n", m_str.c_str());
				}
				if(HidD_GetPreparsedData(m_dev_handle, &m_preparsed_data)){
					if(HidP_GetCaps(m_preparsed_data, &m_caps) == HIDP_STATUS_SUCCESS){
						printf("Number of linked nodes: %lu\n", m_caps.NumberLinkCollectionNodes);
						printf("Input report size: %lu\n", m_caps.InputReportByteLength);
						printf("Output report size: %lu\n", m_caps.OutputReportByteLength);
					}
				}
				CloseHandle(m_dev_handle);
			}
		}
	}
}

BOOL cl_usb_enum::get_usb_root_hub_name(HANDLE m_arg_hc_handle, std::string &m_arg_root_hub_name){
	BOOL m_result;
	USB_HCD_DRIVERKEY_NAME m_driver_key_name;
	PUSB_HCD_DRIVERKEY_NAME m_driver_key_name_ptr;
	DWORD m_bytes_returned;
	std::string m_driver_key_name_unicode_str;

	m_result =
		DeviceIoControl(
			m_arg_hc_handle,
			IOCTL_USB_GET_ROOT_HUB_NAME,
			NULL,
			0,
			&m_driver_key_name,
			sizeof(m_driver_key_name),
			&m_bytes_returned,
			NULL
		);
	if(m_result){
		if(m_driver_key_name.ActualLength > 4){
			m_driver_key_name_ptr = (PUSB_HCD_DRIVERKEY_NAME)malloc(m_driver_key_name.ActualLength);
			if(m_driver_key_name_ptr != NULL){
				m_result =
					DeviceIoControl(
						m_arg_hc_handle,
						IOCTL_USB_GET_ROOT_HUB_NAME,
						NULL,
						0,
						m_driver_key_name_ptr,
						m_driver_key_name.ActualLength,
						&m_bytes_returned,
						NULL
					);
				if(m_result){
					if(m_driver_key_name_ptr->ActualLength > 4){
						// Name is unicode. Let's treat it as double-byte which is converted to single-byte
						//m_driver_key_name_unicode_str.assign((char*)m_driver_key_name_ptr->DriverKeyName, m_driver_key_name_ptr->ActualLength - 4);
						//printf("USB root hub name: %s\n", str_dbc_to_sbc(m_driver_key_name_unicode_str, false, "").c_str());
						//printf("USB root hub driver key name:\n%ws\n", m_driver_key_name_ptr->DriverKeyName);

						m_driver_key_name_unicode_str.assign((char*)m_driver_key_name_ptr->DriverKeyName, m_driver_key_name_ptr->ActualLength - 4);
						m_arg_root_hub_name = ns_string_utils::str_dbc_to_sbc(m_driver_key_name_unicode_str, false, "", "");
					}
				}else{
					m_last_err_msg = "Error: IOCTL_USB_GET_ROOT_HUB_NAME failed with error code: " + ns_to_string_utils::to_string(GetLastError());
				}

				free(m_driver_key_name_ptr);
			}else{
				m_last_err_msg = "Error: Memory allocation failed!";
			}
		}else{
			m_result = false;
			m_last_err_msg = "Error: Incorrect length received by IOCTL_USB_GET_ROOT_HUB_NAME!";
		}
	}else{
		m_last_err_msg = "Error: IOCTL_USB_GET_ROOT_HUB_NAME failed with error code: " + ns_to_string_utils::to_string(GetLastError());
	}

	return m_result;
}

BOOL cl_usb_enum::get_usb_dev_driver_key_name_by_root_hub(HANDLE m_arg_rh_handle, ULONG m_arg_port_index, std::string &m_arg_driver_key_name){
	BOOL m_result;
	USB_NODE_CONNECTION_NAME m_driver_key_name;
	PUSB_NODE_CONNECTION_NAME m_driver_key_name_ptr;
	DWORD m_bytes_returned;
	std::string m_driver_key_name_unicode_str;

	m_driver_key_name.ConnectionIndex = m_arg_port_index;
	m_result =
		DeviceIoControl(
			m_arg_rh_handle,
			IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME,
			&m_driver_key_name,
			sizeof(m_driver_key_name),
			&m_driver_key_name,
			sizeof(m_driver_key_name),
			&m_bytes_returned,
			NULL
		);
	if(m_result){
		if(m_driver_key_name.ActualLength > 12){
			m_driver_key_name_ptr = (PUSB_NODE_CONNECTION_NAME)malloc(m_driver_key_name.ActualLength);
			if(m_driver_key_name_ptr != NULL){
				m_driver_key_name_ptr->ConnectionIndex = m_arg_port_index;
				m_result =
					DeviceIoControl(
						m_arg_rh_handle,
						IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME,
						&m_driver_key_name,
						sizeof(m_driver_key_name),
						m_driver_key_name_ptr,
						m_driver_key_name.ActualLength,
						&m_bytes_returned,
						NULL
					);
				if(m_result){
					if(m_driver_key_name_ptr->ActualLength > 12){
						m_driver_key_name_unicode_str.assign((char*)m_driver_key_name_ptr->NodeName, m_driver_key_name_ptr->ActualLength - 12);
						m_arg_driver_key_name = ns_string_utils::str_dbc_to_sbc(m_driver_key_name_unicode_str, false, "", "");
					}
				}else{
					m_last_err_msg = "Error: IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME failed with error code: " + ns_to_string_utils::to_string(GetLastError());
				}

				free(m_driver_key_name_ptr);
			}else{
				m_last_err_msg = "Error: Memory allocation failed!";
			}
		}else{
			m_result = false;
			m_last_err_msg = "Error: Incorrect length received by IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME!";
		}
	}else{
		m_last_err_msg = "Error: IOCTL_USB_GET_NODE_CONNECTION_DRIVERKEY_NAME failed with error code: \n" + ns_to_string_utils::to_string(GetLastError());
	}

	return m_result;
}

BOOL cl_usb_enum::get_usb_node_info(HANDLE m_arg_usb_rh_handle, USB_NODE_INFORMATION &m_arg_node_info){
	BOOL m_result;
	DWORD m_bytes_returned;

	m_result =
		DeviceIoControl(
			m_arg_usb_rh_handle,
			IOCTL_USB_GET_NODE_INFORMATION,
			NULL,
			0,
			&m_arg_node_info,
			sizeof(m_arg_node_info),
			&m_bytes_returned,
			NULL
		);
	if(!m_result){
		m_last_err_msg = "Error: IOCTL_USB_GET_NODE_INFORMATION failed with error code: " + ns_to_string_utils::to_string(GetLastError());
	}

	return m_result;
}

BOOL cl_usb_enum::get_usb_node_conn_info(
	HANDLE m_arg_usb_rh_handle,
	UCHAR m_arg_port_index,
	PUSB_NODE_CONNECTION_INFORMATION m_arg_node_conn_info,
	DWORD m_arg_node_conn_info_size
){
	BOOL m_result;
	DWORD m_bytes_returned;

	memset(m_arg_node_conn_info, 0, m_arg_node_conn_info_size);
	m_arg_node_conn_info->ConnectionIndex = m_arg_port_index;
	m_result =
		DeviceIoControl(
			m_arg_usb_rh_handle,
			IOCTL_USB_GET_NODE_CONNECTION_INFORMATION,
			m_arg_node_conn_info,
			m_arg_node_conn_info_size,
			m_arg_node_conn_info,
			m_arg_node_conn_info_size,
			&m_bytes_returned,
			NULL
		);
	if(!m_result){
		m_last_err_msg = "Error: IOCTL_USB_GET_NODE_CONNECTION_INFORMATION failed with error code: " + ns_to_string_utils::to_string(GetLastError());
	}

	return m_result;
}

BOOL cl_usb_enum::get_usb_node_conn_descriptor(
	HANDLE m_arg_rh_handle,
	UCHAR m_arg_port_index,
	unsigned short m_arg_packet_value,
	unsigned short m_arg_packet_index,
	unsigned short m_arg_packet_length,
	void *m_arg_dest_packet_data_buf
){
	BOOL m_result;
	PUSB_DESCRIPTOR_REQUEST m_desc_req_ptr;
	DWORD m_bytes_returned;

	m_desc_req_ptr = (PUSB_DESCRIPTOR_REQUEST)malloc(12 + m_arg_packet_length);
	if(m_desc_req_ptr != NULL){
		memset(m_desc_req_ptr, 0, 12 + m_arg_packet_length);

		m_desc_req_ptr->ConnectionIndex = m_arg_port_index;
		m_desc_req_ptr->SetupPacket.bRequest = USB_REQUEST_GET_DESCRIPTOR;
		m_desc_req_ptr->SetupPacket.bmRequest = 0x80;
		m_desc_req_ptr->SetupPacket.wValue = m_arg_packet_value;
		m_desc_req_ptr->SetupPacket.wIndex = m_arg_packet_index;
		m_desc_req_ptr->SetupPacket.wLength = m_arg_packet_length;
		m_result =
			DeviceIoControl(
				m_arg_rh_handle,
				IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION,
				m_desc_req_ptr,
				12 + m_arg_packet_length,
				m_desc_req_ptr,
				12 + m_arg_packet_length,
				&m_bytes_returned,
				NULL
			);
		if(m_result){
			memcpy(m_arg_dest_packet_data_buf, m_desc_req_ptr->Data, m_arg_packet_length);
		}else{
			m_last_err_msg = "Error: IOCTL_USB_GET_DESCRIPTOR_FROM_NODE_CONNECTION failed with error code: " + ns_to_string_utils::to_string(GetLastError());
		}

		free(m_desc_req_ptr);
	}else{
		m_result = false;
		m_last_err_msg = "Error: Memory allocation failed!";
	}

	return m_result;
}

BOOL cl_usb_enum::find_usb_dev_path_by_product_name(
	std::string m_arg_product_name,
	BOOL m_arg_is_product_name_sbc,
	std::string &m_arg_dev_path
){
	cl_dev_enum m_dev_enum;
	cl_dev_enum m_host_ctrl_dev_enum;
	std::list<cl_dev_enum_item>::iterator m_host_ctrl_dev_list_it;
	std::list<cl_dev_enum_item>::iterator m_dev_list_it;
	HANDLE m_usb_host_ctrl_handle;
	std::string m_root_hub_name;
	HANDLE m_usb_root_hub_handle;
	USB_NODE_INFORMATION m_node_info;
	UCHAR m_port_index;
	USB_NODE_CONNECTION_INFORMATION m_node_conn_info;
	unsigned char m_packet_data[255];
	std::string m_unicode_str;
	std::string m_str;
	std::string m_dev_driver_key_name;

	if(m_host_ctrl_dev_enum.get_dev_list((GUID*)&m_di_usb_host_ctrl_guid)){
		for(m_host_ctrl_dev_list_it = m_host_ctrl_dev_enum.dev_list.begin(); m_host_ctrl_dev_list_it != m_host_ctrl_dev_enum.dev_list.end(); ++m_host_ctrl_dev_list_it){
			m_usb_host_ctrl_handle = CreateFile(m_host_ctrl_dev_list_it->dev_path.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if(m_usb_host_ctrl_handle != INVALID_HANDLE_VALUE){
				m_root_hub_name.clear();
				if(get_usb_root_hub_name(m_usb_host_ctrl_handle, m_root_hub_name)){
					//printf("Root hub name: %s\n", m_root_hub_name.c_str());
					m_usb_root_hub_handle = CreateFile(std::string("\\\\?\\" + m_root_hub_name).c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
					if(m_usb_root_hub_handle != INVALID_HANDLE_VALUE){
						// Get USB root hub infomation
						if(get_usb_node_info(m_usb_root_hub_handle, m_node_info)){
							//printf("N ports: %i\n", m_node_info.u.HubInformation.HubDescriptor.bNumberOfPorts);
							for(m_port_index = 1; m_port_index < m_node_info.u.HubInformation.HubDescriptor.bNumberOfPorts + 1; ++m_port_index){
								if(get_usb_node_conn_info(m_usb_root_hub_handle, m_port_index, &m_node_conn_info, sizeof(m_node_conn_info))){
									if(
										get_usb_node_conn_descriptor(
											m_usb_root_hub_handle,
											m_port_index,
											((unsigned short)USB_STRING_DESCRIPTOR_TYPE << 8) | m_node_conn_info.DeviceDescriptor.iProduct,
											0x0409,
											sizeof(m_packet_data),
											m_packet_data
										)
									){
										if(m_packet_data[0] > 2){
											m_unicode_str.assign((char*)m_packet_data + 2, m_packet_data[0] - 2);
											if(m_arg_is_product_name_sbc){
												m_str = ns_string_utils::str_dbc_to_sbc(m_unicode_str, false, "", "");
											}else{
												m_str = m_unicode_str;
											}
											if(m_arg_product_name == m_str){
												if(get_usb_dev_driver_key_name_by_root_hub(m_usb_root_hub_handle, m_port_index, m_dev_driver_key_name)){
													m_dev_enum.dev_list.clear();
													if(m_dev_enum.get_dev_list((GUID*)&m_di_usb_dev_guid)){
														for(m_dev_list_it = m_dev_enum.dev_list.begin(); m_dev_list_it != m_dev_enum.dev_list.end(); ++m_dev_list_it){
															if(m_dev_list_it->driver_key_name == m_dev_driver_key_name){
																m_arg_dev_path = m_dev_list_it->dev_path;
																CloseHandle(m_usb_root_hub_handle);
																CloseHandle(m_usb_host_ctrl_handle);
																return true;
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
						CloseHandle(m_usb_root_hub_handle);
					}
				}
				CloseHandle(m_usb_host_ctrl_handle);
			}
		}
	}

	return false;
}

void cl_usb_hid_enum::list_dev(){
	cl_dev_enum m_hid_dev_enum;
	std::list<cl_dev_enum_item>::iterator m_hid_dev_list_it;
	HANDLE m_hid_handle;
	unsigned char m_buf[256];
	std::string m_dbc_str;
	std::string m_str;
	HIDD_ATTRIBUTES m_attrib;
	PHIDP_PREPARSED_DATA m_preparsed_data;
	HIDP_CAPS m_caps;

	if(m_hid_dev_enum.get_dev_list((GUID*)&m_di_usb_hid_guid)){
		for(m_hid_dev_list_it = m_hid_dev_enum.dev_list.begin(); m_hid_dev_list_it != m_hid_dev_enum.dev_list.end(); ++m_hid_dev_list_it){
			printf("Device path: %s\n", m_hid_dev_list_it->dev_path.c_str());
			//printf("Device driver key name: %s\n", m_hid_dev_list_it->m_driver_key_name.c_str());

			m_hid_handle = CreateFile(m_hid_dev_list_it->dev_path.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if(m_hid_handle != INVALID_HANDLE_VALUE){
				if(HidD_GetAttributes(m_hid_handle, &m_attrib)){
					printf("Vendor ID: %4.4X\n", m_attrib.VendorID);
					printf("Product ID: %4.4X\n", m_attrib.ProductID);
					printf("Version Nr: %4.4X\n", m_attrib.VersionNumber);
				}
				if(HidD_GetManufacturerString(m_hid_handle, m_buf, sizeof(m_buf))){
					m_dbc_str.assign((char*)m_buf, sizeof(m_buf));
					m_str = ns_string_utils::str_dbc_to_sbc(m_dbc_str, false, "", "");
					printf("Manufacturer: %s\n", m_str.c_str());
				}
				if(HidD_GetProductString(m_hid_handle, m_buf, sizeof(m_buf))){
					m_dbc_str.assign((char*)m_buf, sizeof(m_buf));
					m_str = ns_string_utils::str_dbc_to_sbc(m_dbc_str, false, "", "");
					printf("Product: %s\n", m_str.c_str());
				}
				if(HidD_GetSerialNumberString(m_hid_handle, m_buf, sizeof(m_buf))){
					m_dbc_str.assign((char*)m_buf, sizeof(m_buf));
					m_str = ns_string_utils::str_dbc_to_sbc(m_dbc_str, false, "", "");
					printf("Serial: %s\n", m_str.c_str());
				}
				if(HidD_GetPreparsedData(m_hid_handle, &m_preparsed_data)){
					if(HidP_GetCaps(m_preparsed_data, &m_caps) == HIDP_STATUS_SUCCESS){
						printf("Number of linked nodes: %lu\n", m_caps.NumberLinkCollectionNodes);
						printf("Input report size: %lu\n", m_caps.InputReportByteLength);
						printf("Output report size: %lu\n", m_caps.OutputReportByteLength);
					}
				}
				CloseHandle(m_hid_handle);
			}
		}
	}
}

BOOL cl_usb_hid_enum::find_hid_dev_path_by_product_name(
	std::string m_arg_product_name,
	BOOL m_arg_is_product_name_sbc,
	std::string &m_arg_dev_path
){
	cl_dev_enum m_hid_dev_enum;
	std::list<cl_dev_enum_item>::iterator m_hid_dev_list_it;
	HANDLE m_hid_handle;
	unsigned char m_buf[256];
	std::string m_dbc_str;
	std::string m_str;

	if(m_hid_dev_enum.get_dev_list((GUID*)&m_di_usb_hid_guid)){
		for(m_hid_dev_list_it = m_hid_dev_enum.dev_list.begin(); m_hid_dev_list_it != m_hid_dev_enum.dev_list.end(); ++m_hid_dev_list_it){
			m_hid_handle = CreateFile(m_hid_dev_list_it->dev_path.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if(m_hid_handle != INVALID_HANDLE_VALUE){
				memset(m_buf, 0, sizeof(m_buf));
				if(HidD_GetProductString(m_hid_handle, m_buf, sizeof(m_buf))){
					m_dbc_str.assign((char*)m_buf, sizeof(m_buf));
					if(m_arg_is_product_name_sbc){
						m_str = ns_string_utils::str_dbc_to_sbc(m_dbc_str, false, "", "");
						// Convert to null terminated string
						m_str = m_str.c_str();
					}else{
						m_str = m_dbc_str;
					}
					if(m_arg_product_name == m_str){
						m_arg_dev_path = m_hid_dev_list_it->dev_path;
						CloseHandle(m_hid_handle);
						return true;
					}
				}
				CloseHandle(m_hid_handle);
			}
		}
	}

	return false;
}

BOOL cl_usb_hid_enum::find_hid_dev_path_by_vid_pid(
	unsigned short m_arg_vid,
	unsigned short m_arg_pid,
	BOOL m_arg_is_product_name_sbc,
	std::string &m_arg_dev_path
){
	cl_dev_enum m_hid_dev_enum;
	std::list<cl_dev_enum_item>::iterator m_hid_dev_list_it;
	HANDLE m_hid_handle;
	HIDD_ATTRIBUTES m_attrib;

	if(m_hid_dev_enum.get_dev_list((GUID*)&m_di_usb_hid_guid)){
		for(m_hid_dev_list_it = m_hid_dev_enum.dev_list.begin(); m_hid_dev_list_it != m_hid_dev_enum.dev_list.end(); ++m_hid_dev_list_it){
			m_hid_handle = CreateFile(m_hid_dev_list_it->dev_path.c_str(), 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
			if(m_hid_handle != INVALID_HANDLE_VALUE){
				if(HidD_GetAttributes(m_hid_handle, &m_attrib)){
					if((m_attrib.VendorID == m_arg_vid) && (m_attrib.ProductID == m_arg_pid)){
						m_arg_dev_path = m_hid_dev_list_it->dev_path;
						CloseHandle(m_hid_handle);
						return true;
					}
				}
				CloseHandle(m_hid_handle);
			}
		}
	}

	return false;
}

#ifndef MY_USB_ENUM_H
#define MY_USB_ENUM_H

#include "my_dev_enum.h"
#include "to_string.h"
#include "string_utils.h"
#include <windows.h>
#include "ms_wdk/usbioctl.h"
extern "C"{
	#include "ms_wdk/hidsdi.h"
}
#include <string>

#pragma comment(lib, "ms_wdk/hid.lib")  // For hidsdi.h

static const GUID m_di_usb_host_ctrl_guid = { 0x3ABF6F2DL, 0x71C4, 0x462A, { 0x8A, 0x92, 0x1E, 0x68, 0x61, 0xE6, 0xAF, 0x27 } };
static const GUID m_di_usb_dev_guid       = { 0xA5DCBF10L, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } };
static const GUID m_di_usb_hid_guid       = { 0x4D1E55B2L, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } };

class cl_usb_enum{
protected:
	std::string m_last_err_msg;

public:
	void list_dev();
	BOOL get_usb_root_hub_name(HANDLE m_arg_hc_handle, std::string &m_arg_root_hub_name);
	BOOL get_usb_dev_driver_key_name_by_root_hub(HANDLE m_arg_rh_handle, ULONG m_arg_port_index, std::string &m_arg_driver_key_name);
	BOOL get_usb_node_info(HANDLE m_arg_usb_rh_handle, USB_NODE_INFORMATION &m_arg_node_info);
	BOOL get_usb_node_conn_info(
		HANDLE m_arg_usb_rh_handle,
		UCHAR m_arg_port_index,
		PUSB_NODE_CONNECTION_INFORMATION m_arg_node_conn_info,
		DWORD m_arg_node_conn_info_size
	);
	BOOL get_usb_node_conn_descriptor(
		HANDLE m_arg_rh_handle,
		UCHAR m_arg_port_index,
		unsigned short m_arg_packet_value,
		unsigned short m_arg_packet_index,
		unsigned short m_arg_packet_length,
		void *m_arg_dest_packet_data_buf
	);
	BOOL find_usb_dev_path_by_product_name(
		std::string m_arg_product_name,
		BOOL m_arg_is_product_name_sbc,
		std::string& m_arg_dev_path
	);
};

class cl_usb_hid_enum{
protected:
	std::string m_last_err_msg;

public:
	void list_dev();
	BOOL find_hid_dev_path_by_product_name(
		std::string m_arg_product_name,
		BOOL m_arg_is_product_name_sbc,
		std::string &m_arg_dev_path
	);
	BOOL find_hid_dev_path_by_vid_pid(
		unsigned short m_arg_vid,
		unsigned short m_arg_pid,
		BOOL m_arg_is_product_name_sbc,
		std::string &m_arg_dev_path
	);
};

#endif

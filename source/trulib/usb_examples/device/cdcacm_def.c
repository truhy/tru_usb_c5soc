#include "cdcacm_def.h"

// ==============================================
// Class specific interface extension descriptors
// ==============================================

// ============================================
// CDC-ACM class interface extension structures
// ============================================

// Line coding for each interface
tru_usb_cdc_linecoding_t cdcacm_linecoding_1_0_0 = {
	.dte_rate = CDCACM_DEFAULT_BIT_RATE,
	.char_format = CDCACM_DEFAULT_CHAR_FORMAT,
	.parity_type = CDCACM_DEFAULT_PARITY_TYPE,
	.data_bits = CDCACM_DEFAULT_DATA_BITS
};

// Line control for each interface
tru_usb_cdc_linecontrol_t cdcacm_linecontrol_1_0_0 = { .val = 0 };

// Encapsulated buffer for each interface
tru_usb_cdc_encap_t cdcacm_encap_1_0_0 = {
	.encap_cmd = NULL,
	.encap_cmd_buf_size = 0,
	.encap_resp = NULL,
	.encap_resp_buf_size = 0
};

// Notification UART state
tru_usb_cdc_uartstate_t cdcacm_uartstate_1_0_0 = { .val = 0 };

// =================================================================================================
// CDC-ACM class interface extensions array of all configurations, interfaces and alternate settings
// =================================================================================================

// Array of all CDC-ACM interface extensions.  Each entry starts with the Configuration number, Interface number, Alternate setting number
const tru_usb_cdc_interface_ext_t cdcacm_interface_exts[] = {
	{ .ext_hdr = { .config_num = 1, .interface_num = 0, .alt_setting_num = 0 }, .linecoding = &cdcacm_linecoding_1_0_0, .linecontrol = &cdcacm_linecontrol_1_0_0, .encap = &cdcacm_encap_1_0_0, .uartstate = &cdcacm_uartstate_1_0_0 },
	{ .ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 0 }, .linecoding = &cdcacm_linecoding_1_0_0, .linecontrol = &cdcacm_linecontrol_1_0_0, .encap = &cdcacm_encap_1_0_0, .uartstate = &cdcacm_uartstate_1_0_0 },
};

// ==========================
// Low speed mode descriptors
// ==========================

// =========================
// Configuration descriptors
// =========================

// Configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t                   config_0;
	tru_usb_interface_desc_t                interface_0_0_0;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_0_0_0;
	tru_usb_cdc_func_desc_acm_t             func_acm_0_0_0;
	tru_usb_cdc_func_desc_union_t           func_union_0_0_0;
	tru_usb_cdc_func_desc_call_management_t func_call_man_0_0_0;
	tru_usb_ep_desc_t                       ep_comm_msg_0_0_0;
	tru_usb_interface_desc_t                interface_0_1_0;
	tru_usb_ep_desc_t                       ep_data_in_0_1_0;
	tru_usb_ep_desc_t                       ep_data_out_0_1_0;
}cdcacm_ls_config1_desc_t;

/*
	CDC configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 CDC descriptor per interface,
				0 or more endpoint descriptor(s) per interface

	Note:
		CDC class descriptors are not included (i.e. report, physical or vendor) inside the configuration set of descriptors,
		instead they should be stored as a separate set using a class specific extension.
*/
const cdcacm_ls_config1_desc_t cdcacm_ls_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(cdcacm_ls_config1_desc_t),  // Total length of data in this configuration
		.num_interfaces = 2,  // Number of interfaces (counting only alternate setting == 0) in this configuration
		.config_num = 1,
		.string_index = 0,  // Index of configuration string (0 = no string)
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},

	// Interface descriptor for the Communications Interface
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,  // Number of endpoints in this interface (excluding endpoint zero)
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_NTF_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_INTERRUPT,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_LS_INTERRUPT_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 1  // Host polling interval
	},

	// Interface descriptor for the Data Interface
	.interface_0_1_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,  // Number of endpoints in this interface (excluding endpoint zero)
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_0_1_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_TXD_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_INTERRUPT,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_LS_INTERRUPT_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 1  // Host polling interval
	},

	// Endpoint descriptor for Data Messages (host to device)
	.ep_data_out_0_1_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RXD_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_INTERRUPT,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_LS_INTERRUPT_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 1  // Host polling interval
	}
};

// Array of all configuration descriptor sets (pointers and sizes) for low speed mode
const tru_usb_config_desc_set_t cdcacm_ls_config_descs[] = {
	{ .desc = (uint8_t *)&cdcacm_ls_config1_desc, .size = sizeof(cdcacm_ls_config1_desc) }
};

// Total number of configurations for low speed mode
#define CDCACM_LS_NUM_OF_CONFIGS (sizeof(cdcacm_ls_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for low speed mode
const tru_usb_dev_desc_t cdcacm_ls_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = CDCACM_USB_VER,  // USB specification version number (BCD format)
	.dev_class = TRU_USB_DEVICE_CLASS_CDC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_LS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = CDCACM_VID,
	.pid = CDCACM_PID,
	.product_ver = CDCACM_VER,
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = CDCACM_LS_NUM_OF_CONFIGS
};

// ===========================
// Full speed mode descriptors
// ===========================

// =========================
// Configuration descriptors
// =========================

// Configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t                   config_0;
	tru_usb_interface_desc_t                interface_0_0_0;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_0_0_0;
	tru_usb_cdc_func_desc_acm_t             func_acm_0_0_0;
	tru_usb_cdc_func_desc_union_t           func_union_0_0_0;
	tru_usb_cdc_func_desc_call_management_t func_call_man_0_0_0;
	tru_usb_ep_desc_t                       ep_comm_msg_0_0_0;
	tru_usb_interface_desc_t                interface_0_1_0;
	tru_usb_ep_desc_t                       ep_data_in_0_1_0;
	tru_usb_ep_desc_t                       ep_data_out_0_1_0;
}cdcacm_fs_config1_desc_t;

/*
	CDC configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 CDC descriptor per interface,
				0 or more endpoint descriptor(s) per interface

	Note:
		CDC class descriptors are not included (i.e. report, physical or vendor) inside the configuration set of descriptors,
		instead they should be stored as a separate set using a class specific extension.
*/
const cdcacm_fs_config1_desc_t cdcacm_fs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(cdcacm_fs_config1_desc_t),  // Total length of data in this configuration
		.num_interfaces = 2,  // Number of interfaces (counting only alternate setting == 0) in this configuration
		.config_num = 1,
		.string_index = 0,  // Index of configuration string (0 = no string)
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},

	// Interface descriptor for the Communications Interface
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,  // Number of endpoints in this interface (excluding endpoint zero)
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},
	
	// Union functional descriptor
	.func_union_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_DAT_ITFNUM  // Interface number of the subordinate
	},
	
	// Call Management functional descriptor
	.func_call_man_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_NTF_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_INTERRUPT,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_FS_INTERRUPT_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 1  // Host polling interval
	},

	// Interface descriptor for the Data Interface
	.interface_0_1_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,  // Number of endpoints in this interface (excluding endpoint zero)
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_0_1_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_TXD_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_BULK,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_FS_BULK_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 0  // Host polling interval
	},

	// Endpoint descriptor for Data Messages (host to device)
	.ep_data_out_0_1_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RXD_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_BULK,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_FS_BULK_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 0  // Host polling interval
	}
};

// Array of all configuration descriptor sets (pointers and sizes) for full speed mode
const tru_usb_config_desc_set_t cdcacm_fs_config_descs[] = {
	{ .desc = (uint8_t *)&cdcacm_fs_config1_desc, .size = sizeof(cdcacm_fs_config1_desc) }
};

// Total number of configurations for full speed mode
#define CDCACM_FS_NUM_OF_CONFIGS (sizeof(cdcacm_fs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for full s.peed mode
const tru_usb_dev_desc_t cdcacm_fs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = CDCACM_USB_VER,  // USB specification version number (BCD format)
	.dev_class = TRU_USB_DEVICE_CLASS_CDC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = CDCACM_VID,
	.pid = CDCACM_PID,
	.product_ver = CDCACM_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = CDCACM_FS_NUM_OF_CONFIGS
};

#if CDCACM_HS_DESC_ENABLE == 1

// ===========================
// High speed mode descriptors
// ===========================

// =========================
// Configuration descriptors
// =========================

// Configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t                   config_0;
	tru_usb_interface_desc_t                interface_0_0_0;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_0_0_0;
	tru_usb_cdc_func_desc_acm_t             func_acm_0_0_0;
	tru_usb_cdc_func_desc_union_t           func_union_0_0_0;
	tru_usb_cdc_func_desc_call_management_t func_call_man_0_0_0;
	tru_usb_ep_desc_t                       ep_comm_msg_0_0_0;
	tru_usb_interface_desc_t                interface_0_1_0;
	tru_usb_ep_desc_t                       ep_data_in_0_1_0;
	tru_usb_ep_desc_t                       ep_data_out_0_1_0;
}cdcacm_hs_config1_desc_t;

/*
	CDC configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 CDC descriptor per interface,
				0 or more endpoint descriptor(s) per interface
*/
const cdcacm_hs_config1_desc_t cdcacm_hs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(cdcacm_hs_config1_desc_t),
		.num_interfaces = 2,  // Number of interfaces (counting only alternate setting == 0) in this configuration
		.config_num = 1,
		.string_index = 0,  // Index of configuration string (0 = no string)
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},

	// Interface descriptor for the Communications Interface
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,  // Number of endpoints in this interface (excluding endpoint zero)
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of configuration string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0110  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_0_0_0 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_NTF_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_INTERRUPT,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_HS_INTERRUPT_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 4  // Host polling interval
	},

	// Interface descriptor for the Data Interface
	.interface_0_1_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,  // Number of endpoints in this interface (excluding endpoint zero)
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_0_1_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_TXD_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_BULK,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_HS_BULK_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 0  // Host polling interval
	},

	// Endpoint descriptor for Data Messages (host to device)
	.ep_data_out_0_1_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RXD_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_BULK,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = {
			.bits.mps = TRU_USB_EP_HS_BULK_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 0  // Host polling interval
	}
};

// Array of all configuration descriptor sets (pointers and sizes) for high speed mode
const tru_usb_config_desc_set_t cdcacm_hs_config_descs[] = {
	{ .desc = (uint8_t *)&cdcacm_hs_config1_desc, .size = sizeof(cdcacm_hs_config1_desc) }
};

// Total number of configurations for high speed mode
#define CDCACM_HS_NUM_OF_CONFIGS (sizeof(cdcacm_hs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for high speed mode
const tru_usb_dev_desc_t cdcacm_hs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = CDCACM_USB_VER,  // USB specification version number (BCD format)
	.dev_class = TRU_USB_DEVICE_CLASS_CDC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = CDCACM_VID,
	.pid = CDCACM_PID,
	.product_ver = CDCACM_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = CDCACM_HS_NUM_OF_CONFIGS
};

// Device qualifier descriptor for full speed mode (describes other speed, i.e. high speed mode)
const tru_usb_dev_qual_desc_t cdcacm_fs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = CDCACM_USB_VER,  // USB release number
	.dev_class = TRU_USB_DEVICE_CLASS_CDC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = CDCACM_HS_NUM_OF_CONFIGS,
	.reserved = 0
};

// Device qualifier descriptor for high speed mode (describes other speed, i.e. full speed mode)
const tru_usb_dev_qual_desc_t cdcacm_hs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = CDCACM_USB_VER,  // USB release number
	.dev_class = TRU_USB_DEVICE_CLASS_CDC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = CDCACM_FS_NUM_OF_CONFIGS,
	.reserved = 0
};

#endif

// ==================
// String descriptors
// ==================

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t lang_id[1];
}cdcacm_string_lang_ids_t;

// Supported language IDs string descriptor
const cdcacm_string_lang_ids_t cdcacm_lang_string_desc = {
	.length = sizeof(cdcacm_lang_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.lang_id = { TRU_USB_LANG_ID_ENGLISH_US }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}cdcacm_string_manuf_t;

// Manufacturer string descriptor
const cdcacm_string_manuf_t cdcacm_manuf_string_desc = {
	.length = sizeof(cdcacm_manuf_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[12];
}cdcacm_string_product_t;

// Product string descriptor
const cdcacm_string_product_t cdcacm_prod_string_desc = {
	.length = sizeof(cdcacm_prod_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', 'C', 'D', 'C', 'A', 'C', 'M', 'B', 'l', 'k' }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}cdcacm_string_serial_t;

// Serial number string descriptor
const cdcacm_string_serial_t cdcacm_ser_string_desc = {
	.length = sizeof(cdcacm_ser_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { '1', '2', '3' }
};

// An array of all the indexes & language IDs mapped to string descriptor pointers
// Note: this is made up and not in the USB specification but it is needed in practice
const tru_usb_string_desc_info_t cdcacm_string_descs[] = {
	{ .index = 0, .lang_id = TRU_USB_LANG_ID_NONE,       .desc = (void *)&cdcacm_lang_string_desc },
	{ .index = 1, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&cdcacm_manuf_string_desc },
	{ .index = 2, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&cdcacm_prod_string_desc },
	{ .index = 3, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&cdcacm_ser_string_desc }
};

// ==========================================================================
// Final CDC peripheral device descriptors (pointers to all structures above)
// ==========================================================================

// Common
tru_usb_pd_info_t cdcacm_base_pd_info = {
#if CDCACM_HS_DESC_ENABLE == 1
	.hs_dev_desc = (tru_usb_dev_desc_t *)&cdcacm_hs_dev_desc,
#else
	.hs_dev_desc = NULL,
#endif
	.fs_dev_desc = (tru_usb_dev_desc_t *)&cdcacm_fs_dev_desc,
	.ls_dev_desc = (tru_usb_dev_desc_t *)&cdcacm_ls_dev_desc,

#if CDCACM_HS_DESC_ENABLE == 1
	.hs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&cdcacm_hs_dev_qual_desc,
	.fs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&cdcacm_fs_dev_qual_desc,
#else
	.hs_dev_qual_desc = NULL,
	.fs_dev_qual_desc = NULL,
#endif

#if CDCACM_HS_DESC_ENABLE == 1
	.hs_config_descs = (tru_usb_config_desc_set_t *)cdcacm_hs_config_descs, .hs_config_descs_num_entries = sizeof(cdcacm_hs_config_descs) / sizeof(tru_usb_config_desc_set_t),
#else
	.hs_config_descs = NULL, .hs_config_descs_num_entries = 0,
#endif
	.fs_config_descs = (tru_usb_config_desc_set_t *)cdcacm_fs_config_descs, .fs_config_descs_num_entries = sizeof(cdcacm_fs_config_descs) / sizeof(tru_usb_config_desc_set_t),
	.ls_config_descs = (tru_usb_config_desc_set_t *)cdcacm_ls_config_descs, .ls_config_descs_num_entries = sizeof(cdcacm_ls_config_descs) / sizeof(tru_usb_config_desc_set_t),

	.string_descs = (tru_usb_string_desc_info_t *)cdcacm_string_descs, .string_descs_num_entries = sizeof(cdcacm_string_descs) / sizeof(tru_usb_string_desc_info_t)
};

// Common + class
tru_usb_cdc_pd_info_t cdcacm_cdc_pd_info = {
	.pd = &cdcacm_base_pd_info,

#if CDCACM_HS_DESC_ENABLE == 1
	.hs_cdc_interface_exts = (tru_usb_cdc_interface_ext_t *)cdcacm_interface_exts, .hs_cdc_interface_exts_num_entries = sizeof(cdcacm_interface_exts) / sizeof(tru_usb_cdc_interface_ext_t),
#else
	.hs_cdc_interface_exts = NULL, .hs_cdc_interface_exts_num_entries = 0,
#endif
	.fs_cdc_interface_exts = (tru_usb_cdc_interface_ext_t *)cdcacm_interface_exts, .fs_cdc_interface_exts_num_entries = sizeof(cdcacm_interface_exts) / sizeof(tru_usb_cdc_interface_ext_t),
	.ls_cdc_interface_exts = (tru_usb_cdc_interface_ext_t *)cdcacm_interface_exts, .ls_cdc_interface_exts_num_entries = sizeof(cdcacm_interface_exts) / sizeof(tru_usb_cdc_interface_ext_t),
};

tru_usb_cdc_pd_info_t *get_cdcacm_pd_info(void){
	return (tru_usb_cdc_pd_info_t *)&cdcacm_cdc_pd_info;
}

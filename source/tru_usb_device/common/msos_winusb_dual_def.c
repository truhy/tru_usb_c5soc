#include "msos_winusb_dual_def.h"

// ==============================================
// Class specific interface extension descriptors
// ==============================================

// =========================================
// MSOS class interface extension structures
// =========================================

// Array of Function sections (of Microsoft OS Extended Compatibility ID feature descriptor) for device level
const tru_usb_msos_ecid_feature_func_section_desc_t msos_winusb_dual_dev_ecid_func_sections[] = {
	{
		.first_intf_num = 0,  // First Interface number or Function number. For this instance is the Interface number
		.reserved = 0x01,  // Reserved. Set to 0x01
		.cid = "WINUSB",  // Compatible ID string
		.scid = "",  // Subcompatible ID string
		.reserved2 = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }  // Reserved. Set all to 0x00
	}
};

const tru_usb_msos_ep_feature_hdr_desc_t msos_winusb_dual_ep_feature_hdr = {
	.length = sizeof(tru_usb_msos_ep_feature_hdr_desc_t) + 0,  // Total size of EP feature descriptor (header + sections)
	.bcd_ver = 0x0100,  // version (BCD) of EP feature descriptor
	.index = TRU_USB_MSOS_EP_FEATURE_INDEX,  // Index of EP feature descriptor
	.count = 0  // Number of Property sections
};

// EP (Extended Properties) feature descriptor, which consists of header + pointer to Property sections (array of Property sections)
const tru_usb_msos_ep_feature_t msos_winusb_dual_ep_feature = {
	.hdr = (tru_usb_msos_ep_feature_hdr_desc_t *)&msos_winusb_dual_ep_feature_hdr,
	.sections = NULL
};

const tru_usb_msos_ecid_feature_hdr_desc_t msos_winusb_dual_ecid_feature_hdr = {
	.length = sizeof(tru_usb_msos_ecid_feature_hdr_desc_t) + sizeof(msos_winusb_dual_dev_ecid_func_sections),  // Total size of ECID feature descriptor (header + sections)
	.bcd_ver = 0x0100,  // Version (BCD) of ECID feature descriptor
	.index = TRU_USB_MSOS_ECID_FEATURE_INDEX,  // Index of ECID feature descriptor
	.count = sizeof(msos_winusb_dual_dev_ecid_func_sections) / sizeof(tru_usb_msos_ecid_feature_func_section_desc_t),  // Number of Function sections
	.reserved = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }  // Reserved. Set all to 0x00
};

// ECID (Extended Compatibility ID) feature descriptor, which consists of header + pointer to Function sections (array of Function sections)
const tru_usb_msos_ecid_feature_t msos_winusb_dual_ecid_feature = {
	.hdr = (tru_usb_msos_ecid_feature_hdr_desc_t *)&msos_winusb_dual_ecid_feature_hdr,
	.sections = (tru_usb_msos_ecid_feature_func_section_desc_t *)msos_winusb_dual_dev_ecid_func_sections  // Array of ECID feature descriptor Function sections
};

const tru_usb_msos_dev_ext_t msos_winusb_dual_dev_ext = {
	.ecid_feature = (tru_usb_msos_ecid_feature_t *)&msos_winusb_dual_ecid_feature,
	.ep_feature = (tru_usb_msos_ep_feature_t *)&msos_winusb_dual_ep_feature
};

const tru_usb_msos_ep_feature_hdr_desc_t msos_winusb_dual_ep_feature_hdr_1_0_0 = {
	.length = sizeof(tru_usb_msos_ep_feature_hdr_desc_t) + 0,  // Total size of EP feature descriptor (header + sections)
	.bcd_ver = 0x0100,  // version (BCD) of EP feature descriptor
	.index = TRU_USB_MSOS_EP_FEATURE_INDEX,  // Index of EP feature descriptor
	.count = 0  // Number of Property sections
};

// EP (Extended Properties) feature descriptor, which consists of header + pointer to Property sections (array of Property sections)
const tru_usb_msos_ep_feature_t msos_winusb_dual_ep_feature_1_0_0 = {
	.hdr = (tru_usb_msos_ep_feature_hdr_desc_t *)&msos_winusb_dual_ep_feature_hdr_1_0_0,
	.sections = NULL
};

// ========================================================================================
// MSOS interface extensions array of all configurations, interfaces and alternate settings
// ========================================================================================

// Array of all MSOS interface extensions.  Each entry starts with the Configuration number, Interface number, Alternate setting number
const tru_usb_msos_interface_ext_t msos_winusb_dual_interface_exts[] = {
	{ .ext_hdr = { .config_num = 1, .interface_num = 0, .alt_setting_num = 0 }, .ep_feature = (tru_usb_msos_ep_feature_t *)&msos_winusb_dual_ep_feature_1_0_0 }
};

// ==========================
// Low speed mode descriptors
// ==========================

// =========================
// Configuration descriptors
// =========================

// Configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t    config_0;
	tru_usb_interface_desc_t interface_0_0_0;
	tru_usb_ep_desc_t        ep0_0_0_0;
	tru_usb_ep_desc_t        ep1_0_0_0;
	tru_usb_ep_desc_t        ep2_0_0_0;
	tru_usb_ep_desc_t        ep3_0_0_0;
}msos_winusb_dual_ls_config1_desc_t;

/*
	MSOS configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 CDC descriptor per interface,
				0 or more endpoint descriptor(s) per interface
*/
const msos_winusb_dual_ls_config1_desc_t msos_winusb_dual_ls_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(msos_winusb_dual_ls_config1_desc_t),
		.num_interfaces = 1,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED
	},

	// Interface 0 alternate setting 0 descriptor for the Communications Interface
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 0,
		.alt_setting_num = 0,
		.num_endpoints = 4,
		.interface_class = TRU_USB_VENDOR_INTERFACE_CLASS,
		.interface_subclass = 0x00,
		.interface_protocol = 0x00,
		.string_index = 0
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep0_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P0_TXD_EPNUM,
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
	.ep1_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P0_RXD_EPNUM,
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
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep2_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P1_TXD_EPNUM,
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
	.ep3_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P1_RXD_EPNUM,
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
const tru_usb_config_desc_set_t msos_winusb_dual_ls_config_descs[] = {
	{ .desc = (uint8_t *)&msos_winusb_dual_ls_config1_desc, .size = sizeof(msos_winusb_dual_ls_config1_desc) }
};

// Total number of configurations for low speed mode
#define MSOS_WINUSB_DUAL_LS_NUM_OF_CONFIGS (sizeof(msos_winusb_dual_ls_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for low speed mode
const tru_usb_dev_desc_t msos_winusb_dual_ls_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = MSOS_WINUSB_DUAL_USB_VER,  // USB specification version number (BCD format)
	.dev_class = 0x00,
	.dev_subclass = 0x00,
	.dev_protocol = 0x00,
	.mps = TRU_USB_EP_LS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = MSOS_WINUSB_DUAL_DEF_VID,
	.pid = MSOS_WINUSB_DUAL_DEF_PID,
	.product_ver = MSOS_WINUSB_DUAL_DEF_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = MSOS_WINUSB_DUAL_LS_NUM_OF_CONFIGS
};

// ===========================
// Full speed mode descriptors
// ===========================

// =========================
// Configuration descriptors
// =========================

// Configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t    config_0;
	tru_usb_interface_desc_t interface_0_0_0;
	tru_usb_ep_desc_t        ep0_0_0_0;
	tru_usb_ep_desc_t        ep1_0_0_0;
	tru_usb_ep_desc_t        ep2_0_0_0;
	tru_usb_ep_desc_t        ep3_0_0_0;
}msos_winusb_dual_fs_config1_desc_t;

/*
	MSOS configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 CDC descriptor per interface,
				0 or more endpoint descriptor(s) per interface
*/
const msos_winusb_dual_fs_config1_desc_t msos_winusb_dual_fs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(msos_winusb_dual_fs_config1_desc_t),
		.num_interfaces = 1,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED
	},

	// Interface 0 alternate setting 0 descriptor for the Communications Interface
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 0,
		.alt_setting_num = 0,
		.num_endpoints = 4,
		.interface_class = TRU_USB_VENDOR_INTERFACE_CLASS,
		.interface_subclass = 0x00,
		.interface_protocol = 0x00,
		.string_index = 0
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep0_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P0_TXD_EPNUM,
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
	.ep1_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P0_RXD_EPNUM,
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
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep2_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P1_TXD_EPNUM,
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
	.ep3_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P1_RXD_EPNUM,
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
const tru_usb_config_desc_set_t msos_winusb_dual_fs_config_descs[] = {
	{ .desc = (uint8_t *)&msos_winusb_dual_fs_config1_desc, .size = sizeof(msos_winusb_dual_fs_config1_desc) }
};

// Total number of configurations for full speed mode
#define MSOS_WINUSB_DUAL_FS_NUM_OF_CONFIGS (sizeof(msos_winusb_dual_fs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for full speed mode
const tru_usb_dev_desc_t msos_winusb_dual_fs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = MSOS_WINUSB_DUAL_USB_VER,  // USB specification version number (BCD format)
	.dev_class = 0x00,
	.dev_subclass = 0x00,
	.dev_protocol = 0x00,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = MSOS_WINUSB_DUAL_DEF_VID,
	.pid = MSOS_WINUSB_DUAL_DEF_PID,
	.product_ver = MSOS_WINUSB_DUAL_DEF_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = MSOS_WINUSB_DUAL_FS_NUM_OF_CONFIGS
};

#if MSOS_WINUSB_DUAL_HS_DESC_ENABLE == 1

// ===========================
// High speed mode descriptors
// ===========================

// =========================
// Configuration descriptors
// =========================

// Configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t    config_0;
	tru_usb_interface_desc_t interface_0_0_0;
	tru_usb_ep_desc_t        ep0_0_0_0;
	tru_usb_ep_desc_t        ep1_0_0_0;
	tru_usb_ep_desc_t        ep2_0_0_0;
	tru_usb_ep_desc_t        ep3_0_0_0;
}msos_winusb_dual_hs_config1_desc_t;

/*
	MSOS configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 CDC descriptor per interface,
				0 or more endpoint descriptor(s) per interface
*/
const msos_winusb_dual_hs_config1_desc_t msos_winusb_dual_hs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(msos_winusb_dual_hs_config1_desc_t),
		.num_interfaces = 1,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED
	},

	// Interface 0 alternate setting 0 descriptor for the Communications Interface
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 0,
		.alt_setting_num = 0,
		.num_endpoints = 4,
		.interface_class = TRU_USB_VENDOR_INTERFACE_CLASS,
		.interface_subclass = 0x00,
		.interface_protocol = 0x00,
		.string_index = 0
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep0_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P0_TXD_EPNUM,
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
	.ep1_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P0_RXD_EPNUM,
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
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep2_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P1_TXD_EPNUM,
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
	.ep3_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = MSOS_WINUSB_DUAL_P1_RXD_EPNUM,
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
const tru_usb_config_desc_set_t msos_winusb_dual_hs_config_descs[] = {
	{ .desc = (uint8_t *)&msos_winusb_dual_hs_config1_desc, .size = sizeof(msos_winusb_dual_hs_config1_desc) }
};

// Total number of configurations for high speed mode
#define MSOS_WINUSB_DUAL_HS_NUM_OF_CONFIGS (sizeof(msos_winusb_dual_hs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for high high speed mode
const tru_usb_dev_desc_t msos_winusb_dual_hs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = MSOS_WINUSB_DUAL_USB_VER,  // USB specification version number (BCD format)
	.dev_class = 0x00,
	.dev_subclass = 0x00,
	.dev_protocol = 0x00,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = MSOS_WINUSB_DUAL_DEF_VID,
	.pid = MSOS_WINUSB_DUAL_DEF_PID,
	.product_ver = MSOS_WINUSB_DUAL_DEF_VER,
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = MSOS_WINUSB_DUAL_HS_NUM_OF_CONFIGS
};

// Device qualifier descriptor for full speed mode (describes other speed, i.e. high speed mode)
const tru_usb_dev_qual_desc_t msos_winusb_dual_fs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = MSOS_WINUSB_DUAL_USB_VER,  // USB release number
	.dev_class = 0x00,
	.dev_subclass = 0x00,
	.dev_protocol = 0x00,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = MSOS_WINUSB_DUAL_HS_NUM_OF_CONFIGS,
	.reserved = 0
};

// Device qualifier descriptor for high speed mode (describes other speed, i.e. full speed mode)
const tru_usb_dev_qual_desc_t msos_winusb_dual_hs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = MSOS_WINUSB_DUAL_USB_VER,  // USB release number
	.dev_class = 0x00,
	.dev_subclass = 0x00,
	.dev_protocol = 0x00,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = MSOS_WINUSB_DUAL_FS_NUM_OF_CONFIGS,
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
}msos_winusb_dual_string_desc_lang_ids_t;

// Supported language IDs string descriptor
const msos_winusb_dual_string_desc_lang_ids_t msos_winusb_dual_lang_string_desc = {
	.length = sizeof(msos_winusb_dual_lang_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.lang_id = { TRU_USB_LANG_ID_ENGLISH_US }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}msos_winusb_dual_string_desc_manuf_t;

// Manufacturer string descriptor descriptor
const msos_winusb_dual_string_desc_manuf_t msos_winusb_dual_manuf_string_desc = {
	.length = sizeof(msos_winusb_dual_manuf_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u' }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[17];
}msos_winusb_dual_string_desc_product_t;

// Product string descriptor
const msos_winusb_dual_string_desc_product_t msos_winusb_dual_prod_string_desc = {
	.length = sizeof(msos_winusb_dual_prod_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', 'M', 'S', 'O', 'S', 'W', 'i', 'n', 'U', 'S', 'B', 'D', 'u', 'a', 'l' }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}msos_winusb_dual_string_desc_serial_t;

// Serial number string descriptor
const msos_winusb_dual_string_desc_serial_t msos_winusb_dual_ser_string_desc = {
	.length = sizeof(msos_winusb_dual_ser_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { '1', '2', '3' }
};

// Microsoft OS vendor string descriptor
const tru_usb_msos_string_desc_vendor_t msos_winusb_dual_os_string_desc = {
	.length = sizeof(msos_winusb_dual_os_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.signature = { 'M', 'S', 'F', 'T', '1', '0', '0' },
	.vendor_code = TRU_USB_MSOS_VENDOR_CODE,
	.padding = 0x01
};

// An array of all the indexes & language IDs mapped to string descriptor pointers
// Note: this is made up and not in the USB specification but it is needed in practice
const tru_usb_string_desc_info_t msos_winusb_dual_string_descs[] = {
	{ .index = 0,                              .lang_id = TRU_USB_LANG_ID_NONE,       .desc = (void *)&msos_winusb_dual_lang_string_desc },
	{ .index = 1,                              .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&msos_winusb_dual_manuf_string_desc },
	{ .index = 2,                              .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&msos_winusb_dual_prod_string_desc },
	{ .index = 3,                              .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&msos_winusb_dual_ser_string_desc },
	{ .index = TRU_USB_MSOS_STRING_DESC_INDEX, .lang_id = TRU_USB_LANG_ID_NONE,       .desc = (void *)&msos_winusb_dual_os_string_desc }
};


// ===========================================================================
// Final MSOS peripheral device descriptors (pointers to all structures above)
// ===========================================================================

// Common
tru_usb_pd_info_t msos_winusb_dual_base_pd_info = {
#if MSOS_WINUSB_DUAL_HS_DESC_ENABLE == 1
	.hs_dev_desc = (tru_usb_dev_desc_t *)&msos_winusb_dual_hs_dev_desc,
#else
	.hs_dev_desc = NULL,
#endif
	.fs_dev_desc = (tru_usb_dev_desc_t *)&msos_winusb_dual_fs_dev_desc,
	.ls_dev_desc = (tru_usb_dev_desc_t *)&msos_winusb_dual_ls_dev_desc,

#if MSOS_WINUSB_DUAL_HS_DESC_ENABLE == 1
	.hs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&msos_winusb_dual_hs_dev_qual_desc,
	.fs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&msos_winusb_dual_fs_dev_qual_desc,
#else
	.hs_dev_qual_desc = NULL,
	.fs_dev_qual_desc = NULL,
#endif

#if MSOS_WINUSB_DUAL_HS_DESC_ENABLE == 1
	.hs_config_descs = (tru_usb_config_desc_set_t *)msos_winusb_dual_hs_config_descs, .hs_config_descs_num_entries = sizeof(msos_winusb_dual_hs_config_descs) / sizeof(tru_usb_config_desc_set_t),
#else
	.hs_config_descs = NULL, .hs_config_descs_num_entries = 0,
#endif
	.fs_config_descs = (tru_usb_config_desc_set_t *)msos_winusb_dual_fs_config_descs, .fs_config_descs_num_entries = sizeof(msos_winusb_dual_fs_config_descs) / sizeof(tru_usb_config_desc_set_t),
	.ls_config_descs = (tru_usb_config_desc_set_t *)msos_winusb_dual_ls_config_descs, .ls_config_descs_num_entries = sizeof(msos_winusb_dual_ls_config_descs) / sizeof(tru_usb_config_desc_set_t),

	.string_descs = (tru_usb_string_desc_info_t *)msos_winusb_dual_string_descs, .string_descs_num_entries = sizeof(msos_winusb_dual_string_descs) / sizeof(tru_usb_string_desc_info_t)
};

// Common + class
tru_usb_msos_pd_info_t msos_winusb_dual_pd_info = {
	.pd = &msos_winusb_dual_base_pd_info,

#if MSOS_WINUSB_DUAL_HS_DESC_ENABLE == 1
	.hs_msos_dev_ext = (tru_usb_msos_dev_ext_t *)&msos_winusb_dual_dev_ext,
#else
	.hs_msos_dev_ext = NULL,
#endif
	.fs_msos_dev_ext = (tru_usb_msos_dev_ext_t *)&msos_winusb_dual_dev_ext,
	.ls_msos_dev_ext = (tru_usb_msos_dev_ext_t *)&msos_winusb_dual_dev_ext,

#if MSOS_WINUSB_DUAL_HS_DESC_ENABLE == 1
	.hs_msos_interface_exts = (tru_usb_msos_interface_ext_t *)msos_winusb_dual_interface_exts, .hs_msos_interface_exts_num_entries = sizeof(msos_winusb_dual_interface_exts) / sizeof(tru_usb_msos_interface_ext_t),
#else
	.hs_msos_interface_exts = NULL, .hs_msos_interface_exts_num_entries = 0,
#endif
	.fs_msos_interface_exts = (tru_usb_msos_interface_ext_t *)msos_winusb_dual_interface_exts, .fs_msos_interface_exts_num_entries = sizeof(msos_winusb_dual_interface_exts) / sizeof(tru_usb_msos_interface_ext_t),
	.ls_msos_interface_exts = (tru_usb_msos_interface_ext_t *)msos_winusb_dual_interface_exts, .ls_msos_interface_exts_num_entries = sizeof(msos_winusb_dual_interface_exts) / sizeof(tru_usb_msos_interface_ext_t),
};

tru_usb_msos_pd_info_t *get_msos_winusb_dual_pd_info(void){
	return (tru_usb_msos_pd_info_t *)&msos_winusb_dual_pd_info;
}

#include "hid_custom_def.h"

// ==============================================
// Class specific interface extension descriptors
// ==============================================

// ========================================
// HID class interface extension structures
// ========================================

// HID Report descriptor for interface: configuration 1, interface 0 and alternate setting 0
const uint8_t hid_cus_report_desc_1_0_0[] = {
	0x06, 0x00, 0xff,                      // USAGE_PAGE (Vendor Defined Page 1)
	0x09, 0x01,                            //   USAGE (Vendor Usage 1)
	0xa1, 0x01,                            //   COLLECTION (Application)
	0x09, 0x01,                            //     USAGE (Vendor Usage 1) = Input report is vendor usage
	0x15, 0x00,                            //     LOGICAL_MINIMUM (0)
	0x26, 0xff, 0x00,                      //     LOGICAL_MAXIMUM (255)
	0x75, HID_CUS_INPUT_REPORT_VARSIZE,    //     REPORT_SIZE (n) = Set report size variable to specified number of bits (bits per count)
	0x95, HID_CUS_INPUT_REPORT_VARCOUNT,   //     REPORT_COUNT (n) = Set the report count variable to specified number of bytes
	0x81, 0x00,                            //     INPUT (Data, Var, Abs) = Create input report from above settings (variables)
	0x09, 0x01,                            //     USAGE (Vendor Usage 1) = Output report is vendor usage
	0x95, HID_CUS_OUTPUT_REPORT_VARCOUNT,  //     REPORT_COUNT (n) = Set the report count variable to specified number of bytes
	0x91, 0x00,                            //     OUTPUT (Data, Var, Abs) = Create output report from above settings (variables)
	0xc0                                   //   END COLLECTION
};

// Report buffers
NONCACHEABLE_SECTION uint8_t hid_cus_report_input_1_0_0[HID_CUS_INPUT_REPORT_SIZE_BYTES];
NONCACHEABLE_SECTION uint8_t hid_cus_report_output_1_0_0[HID_CUS_OUTPUT_REPORT_SIZE_BYTES];
NONCACHEABLE_SECTION tru_dwc2_dev_sgdma_desc_reg_t hid_cus_rpt_epi_dma_descs[1];
NONCACHEABLE_SECTION tru_dwc2_dev_sgdma_desc_reg_t hid_cus_rpt_epo_dma_descs[1];

tru_usb_hid_report_info_t hid_cus_report_info_inputs_1_0_0[] = {
	{ .id = HID_CUS_REPORT_ID, .report = hid_cus_report_input_1_0_0, .size_bits = HID_CUS_INPUT_REPORT_SIZE_BITS, .size = sizeof(hid_cus_report_input_1_0_0), .idle_rate = 0 },
};

tru_usb_hid_report_info_t hid_cus_report_info_outputs_1_0_0[] = {
	{ .id = HID_CUS_REPORT_ID, .report = hid_cus_report_output_1_0_0, .size_bits = HID_CUS_OUTPUT_REPORT_SIZE_BITS, .size = sizeof(hid_cus_report_output_1_0_0), .idle_rate = 0 },
};

tru_usb_hid_reports_info_set_t hid_cus_reports_info_set_1_0_0 = {
	.inputs = hid_cus_report_info_inputs_1_0_0, .num_input_reports = sizeof(hid_cus_report_info_inputs_1_0_0) / sizeof(tru_usb_hid_report_info_t),
	.outputs = hid_cus_report_info_outputs_1_0_0, .num_output_reports = sizeof(hid_cus_report_info_outputs_1_0_0) / sizeof(tru_usb_hid_report_info_t),
	.features = NULL, .num_feature_reports = 0,
	.epi_dma_descs = hid_cus_rpt_epi_dma_descs, .epi_num_descs = sizeof(hid_cus_rpt_epi_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t),
	.epo_dma_descs = hid_cus_rpt_epo_dma_descs, .epo_num_descs = sizeof(hid_cus_rpt_epo_dma_descs) / sizeof(tru_dwc2_dev_sgdma_desc_reg_t),
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
	tru_usb_hid_desc_t       hid_0_0_0;
	tru_usb_ep_desc_t        ep_data_in_0_0_0;
	tru_usb_ep_desc_t        ep_data_out_0_0_0;
}hid_cus_ls_config1_desc_t;

/*
	HID configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 HID descriptor per interface,
				0 or more endpoint descriptor(s) per interface

	Note:
		HID class descriptors are not included (i.e. report, physical or vendor) inside the configuration set of descriptors,
		instead they are stored separately.

		HID only supports Interrupt flow on EP1 and Control flow on EP0.
		IN EP1 is required and must be declared - this is used by the device to transmit Report data to the host.
		OUT EP1 is optional, if not declared then Reports are transmitted to a device through the Control OUT EP0 using Set_Report(Output) requests.
*/
const hid_cus_ls_config1_desc_t hid_cus_ls_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(hid_cus_ls_config1_desc_t),
		.num_interfaces = 1,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},

	// Interface 0 alternate setting 0 descriptor
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 0,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_HID_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_HID_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_HID_INTERFACE_PROTOCOL_NONE,
		.string_index = 0
	},

	// HID descriptor
	.hid_0_0_0 = {
		.length = sizeof(tru_usb_hid_desc_t),
		.desc_type = TRU_USB_HID_DESC_TYPE_HID,
		.release_num = 0x0101,  // HID class specification release (BCD format)
		.country_code = 0x00,
		.num_descriptors = 1,  // Number of HID class descriptors
		.report_desc_type = TRU_USB_HID_DESC_TYPE_REPORT,  // First HID class descriptor type
		.report_desc_len = sizeof(hid_cus_report_desc_1_0_0)  // Size of first HID class descriptor
	},

	// Endpoint descriptor. HID requires the IN EP1 to be specified. HID only supports interrupt flow and control flow on EP0
	.ep_data_in_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = HID_CUS_IN_REPORT_EPNUM,
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

	// Endpoint descriptor. HID OUT EP1 is optional but this sample will use it. HID only supports interrupt flow on EP1 and control flow on EP0
	.ep_data_out_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = HID_CUS_OUT_REPORT_EPNUM,
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
const tru_usb_config_desc_set_t hid_cus_ls_config_descs[] = {
	{ .desc = (uint8_t *)&hid_cus_ls_config1_desc, .size = sizeof(hid_cus_ls_config1_desc) }
};

// Total number of configurations for low speed mode
#define HID_CUS_LS_NUM_OF_CONFIGS (sizeof(hid_cus_ls_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =============================================================================================
// HID class interface extensions array of all configurations, interfaces and alternate settings
// =============================================================================================

// Array of all HID interface extensions for low speed mode.  Each entry starts with the Configuration number, Interface number, Alternate setting number
const tru_usb_hid_interface_ext_t hid_cus_ls_interface_exts[] = {
	{
		.ext_hdr = {
			.config_num = 1,
			.interface_num = 0,
			.alt_setting_num = 0
		},
		.hid_desc = (tru_usb_hid_desc_t *)&hid_cus_ls_config1_desc.hid_0_0_0,
		.report_desc_info = { .desc = (uint8_t *)hid_cus_report_desc_1_0_0, .size = sizeof(hid_cus_report_desc_1_0_0) },
		.physical_desc_info_set = { .items = NULL, .num_elements = 0 },
		.reports_info_set = &hid_cus_reports_info_set_1_0_0
	}
};

// =================
// Device descriptor
// =================

// Device descriptor for low speed mode
const tru_usb_dev_desc_t hid_cus_ls_dev_desc = {
	sizeof(tru_usb_dev_desc_t),
	TRU_USB_DESC_TYPE_DEVICE,
	HID_CUS_USB_VER,                      // USB specification version number (BCD format)
	TRU_USB_DEVICE_CLASS_NULL,
	TRU_USB_DEVICE_SUBCLASS_NULL,
	TRU_USB_DEVICE_PROTOCOL_NULL,
	8,                                 // EP0 max packet size
	HID_CUS_DEF_VID,                      // Vendor ID
	HID_CUS_DEF_PID,                      // Product ID
	HID_CUS_DEF_VER,                      // Device release number
	1,                                 // Index of manufacturer string
	2,                                 // Index of product string
	3,                                 // Index of serial string
	HID_CUS_LS_NUM_OF_CONFIGS             // Number of configurations
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
	tru_usb_hid_desc_t       hid_0_0_0;
	tru_usb_ep_desc_t        ep_data_in_0_0_0;
	tru_usb_ep_desc_t        ep_data_out_0_0_0;
}hid_cus_fs_config1_desc_t;

/*
	HID configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 HID descriptor per interface,
				0 or more endpoint descriptor(s) per interface

	Note:
		HID class descriptors are not included (i.e. report, physical or vendor) inside the configuration set of descriptors,
		instead they are stored separately.

		HID only supports Interrupt flow on EP1 and Control flow on EP0.
		IN EP1 is required and must be declared - this is used by the device to transmit Report data to the host.
		OUT EP1 is optional, if not declared then Reports are transmitted to a device through the Control OUT EP0 using Set_Report(Output) requests.
*/
const hid_cus_fs_config1_desc_t hid_cus_fs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(hid_cus_fs_config1_desc_t),
		.num_interfaces = 1,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},

	// Interface 0 alternate setting 0 descriptor
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 0,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_HID_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_HID_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_HID_INTERFACE_PROTOCOL_NONE,
		.string_index = 0
	},

	// HID descriptor
	.hid_0_0_0 = {
		.length = sizeof(tru_usb_hid_desc_t),
		.desc_type = TRU_USB_HID_DESC_TYPE_HID,
		.release_num = 0x0101,  // HID class specification release (BCD format)
		.country_code = 0x00,
		.num_descriptors = 1,  // Number of HID class descriptors
		.report_desc_type = TRU_USB_HID_DESC_TYPE_REPORT,  // First HID class descriptor type
		.report_desc_len = sizeof(hid_cus_report_desc_1_0_0)  // Size of first HID class descriptor
	},

	// Note on HID endpoints: HID only supports interrupt flow on EP1 (IN or OUT) and control flow on EP0 (OUT)

	// Endpoint descriptor. HID requires IN EP1
	.ep_data_in_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = HID_CUS_IN_REPORT_EPNUM,
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

	// Endpoint descriptor. HID OUT EP1 is optional but we implement it for this demo sample
	.ep_data_out_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = HID_CUS_OUT_REPORT_EPNUM,
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
			.bits.mps = TRU_USB_EP_FS_INTERRUPT_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 1  // Host polling interval
	}
};

// Array of all configuration descriptor sets (pointers and sizes) for full speed mode
const tru_usb_config_desc_set_t hid_cus_fs_config_descs[] = {
	{ .desc = (uint8_t *)&hid_cus_fs_config1_desc, .size = sizeof(hid_cus_fs_config1_desc) }
};

// Total number of configurations for full speed mode
#define HID_CUS_FS_NUM_OF_CONFIGS (sizeof(hid_cus_fs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =============================================================================================
// HID class interface extensions array of all configurations, interfaces and alternate settings
// =============================================================================================

// Array of all HID interface extensions for full speed mode.  Each entry starts with the Configuration number, Interface number, Alternate setting number
tru_usb_hid_interface_ext_t hid_cus_fs_interface_exts[] = {
	{
		.ext_hdr = {
			.config_num = 1,
			.interface_num = 0,
			.alt_setting_num = 0
		},
		.hid_desc = (tru_usb_hid_desc_t *)&hid_cus_fs_config1_desc.hid_0_0_0,
		.report_desc_info = { .desc = (uint8_t *)hid_cus_report_desc_1_0_0, .size = sizeof(hid_cus_report_desc_1_0_0) },
		.physical_desc_info_set = { .items = NULL, .num_elements = 0 },
		.reports_info_set = &hid_cus_reports_info_set_1_0_0
	}
};

// =================
// Device descriptor
// =================

// Device descriptor for full speed mode
const tru_usb_dev_desc_t hid_cus_fs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = HID_CUS_USB_VER,  // USB specification version number (BCD format)
	.dev_class = TRU_USB_DEVICE_CLASS_NULL,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = 64,  // EP0 max packet size
	.vid = HID_CUS_DEF_VID,
	.pid = HID_CUS_DEF_PID,
	.product_ver = HID_CUS_DEF_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = HID_CUS_FS_NUM_OF_CONFIGS
};

#if HID_CUS_HS_DESC_ENABLE == 1

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
	tru_usb_hid_desc_t       hid_0_0_0;
	tru_usb_ep_desc_t        ep_data_in_0_0_0;
	tru_usb_ep_desc_t        ep_data_out_0_0_0;
}hid_cus_hs_config1_desc_t;

/*
	HID configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			1 or more interface descriptor(s),
				1 HID descriptor per interface,
				0 or more endpoint descriptor(s) per interface

	Note:
		HID class descriptors are not included (i.e. report, physical or vendor) inside the configuration set of descriptors,
		instead they should be stored as a separate set using a class specific extension.

		HID only supports Interrupt flow on EP1 and Control flow on EP0.
		IN EP1 is required and must be declared - this is used by the device to transmit Report data to the host.
		OUT EP1 is optional, if not declared then Reports are transmitted to a device through the Control OUT EP0 using Set_Report(Output) requests.
*/
const hid_cus_hs_config1_desc_t hid_cus_hs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(hid_cus_hs_config1_desc_t),
		.num_interfaces = 1,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},

	// Interface 0 alternate setting 0 descriptor
	.interface_0_0_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 0,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_HID_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_HID_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_HID_INTERFACE_PROTOCOL_NONE,
		.string_index = 0
	},

	// HID descriptor
	.hid_0_0_0 = {
		.length = sizeof(tru_usb_hid_desc_t),
		.desc_type = TRU_USB_HID_DESC_TYPE_HID,
		.release_num = 0x0101,  // HID class specification release (BCD format)
		.country_code = 0x00,
		.num_descriptors = 1,  // Number of HID class descriptors
		.report_desc_type = TRU_USB_HID_DESC_TYPE_REPORT,  // First HID class descriptor type
		.report_desc_len = sizeof(hid_cus_report_desc_1_0_0)  // Size of first HID class descriptor
	},

	// Endpoint descriptor. HID requires the IN EP1 to be specified. HID only supports interrupt flow and control flow on EP0
	.ep_data_in_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = HID_CUS_IN_REPORT_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_INTERRUPT,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = TRU_USB_EP_HS_INTERRUPT_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 1  // Host polling interval
	},

	// Endpoint descriptor. HID OUT EP1 is optional but this sample will use it. HID only supports interrupt flow on EP1 and control flow on EP0
	.ep_data_out_0_0_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = HID_CUS_OUT_REPORT_EPNUM,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_INTERRUPT,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = TRU_USB_EP_HS_INTERRUPT_MAX_MPS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = 1  // Host polling interval
	}
};

// Array of all configuration descriptor sets (pointers and sizes) for high speed mode
const tru_usb_config_desc_set_t hid_cus_hs_config_descs[] = {
	{ .desc = (uint8_t *)&hid_cus_hs_config1_desc, .size = sizeof(hid_cus_hs_config1_desc) }
};

// Total number of configurations for high speed mode
#define HID_CUS_HS_NUM_OF_CONFIGS (sizeof(hid_cus_hs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =============================================================================================
// HID class interface extensions array of all configurations, interfaces and alternate settings
// =============================================================================================

// Array of all HID interface extensions for high speed mode.  Each entry starts with the Configuration number, Interface number, Alternate setting number
const tru_usb_hid_interface_ext_t hid_cus_hs_interface_exts[] = {
	{
		.ext_hdr = {
			.config_num = 1,
			.interface_num = 0,
			.alt_setting_num = 0
		},
		.hid_desc = (tru_usb_hid_desc_t *)&hid_cus_hs_config1_desc.hid_0_0_0,
		.report_desc_info = { .desc = (uint8_t *)hid_cus_report_desc_1_0_0, .size = sizeof(hid_cus_report_desc_1_0_0) },
		.physical_desc_info_set = { .items = NULL, .num_elements = 0 },
		.reports_info_set = &hid_cus_reports_info_set_1_0_0
	}
};

// =================
// Device descriptor
// =================

// Device descriptor for high high speed mode
const tru_usb_dev_desc_t hid_cus_hs_dev_desc = {
	.length = sizeof(hid_cus_hs_dev_desc),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = HID_CUS_USB_VER,  // USB specification version number (BCD format)
	.dev_class = TRU_USB_DEVICE_CLASS_NULL,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = HID_CUS_DEF_VID,
	.pid = HID_CUS_DEF_PID,
	.product_ver = HID_CUS_DEF_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = HID_CUS_HS_NUM_OF_CONFIGS
};

// Device qualifier descriptor for full speed mode (describes other speed, i.e. high speed mode)
const tru_usb_dev_qual_desc_t hid_cus_fs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = HID_CUS_USB_VER,  // USB release number
	.dev_class = TRU_USB_DEVICE_CLASS_NULL,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = HID_CUS_HS_NUM_OF_CONFIGS,
	.reserved = 0
};

// Device qualifier descriptor for high speed mode (describes other speed, i.e. full speed mode)
const tru_usb_dev_qual_desc_t hid_cus_hs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = HID_CUS_USB_VER,  // USB release number
	.dev_class = TRU_USB_DEVICE_CLASS_NULL,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = HID_CUS_FS_NUM_OF_CONFIGS,
	.reserved = 0
};

#endif

// ==================
// String descriptors
// ==================

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t lang_id[2];
}hid_cus_string_lang_ids_t;

// Supported language IDs string descriptor
const hid_cus_string_lang_ids_t hid_cus_lang_string_desc = {
	.length = sizeof(hid_cus_lang_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	// List of language IDs
	.lang_id = {
		TRU_USB_LANG_ID_ENGLISH_US,
		TRU_USB_LANG_ID_ENGLISH_UK
	}
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}hid_cus_string_manuf_t;

// Manufacturer string descriptor
const hid_cus_string_manuf_t hid_cus_manuf_string_desc = {
	.length = sizeof(hid_cus_manuf_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u' }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[9];
}hid_cus_string_product_t;

// Product string descriptor
const hid_cus_string_product_t hid_cus_prod_string_desc = {
	.length = sizeof(hid_cus_prod_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', 'H', 'I', 'D', 'C', 'u', 's' }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}hid_cus_string_serial_t;

// Serial number string descriptor
const hid_cus_string_serial_t hid_cus_ser_string_desc = {
	.length = sizeof(hid_cus_ser_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { '1', '2', '3' }
};

// An array of all the indexes & language IDs mapped to string descriptor pointers
// Note: this is made up and not in the USB specification but it is needed in practice
const tru_usb_string_desc_info_t hid_cus_string_descs[] = {
	{ .index = 0, .lang_id = TRU_USB_LANG_ID_NONE,       .desc = (void *)&hid_cus_lang_string_desc },
	{ .index = 1, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&hid_cus_manuf_string_desc },
	{ .index = 2, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&hid_cus_prod_string_desc },
	{ .index = 3, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&hid_cus_ser_string_desc },
	{ .index = 1, .lang_id = TRU_USB_LANG_ID_ENGLISH_UK, .desc = (void *)&hid_cus_manuf_string_desc },
	{ .index = 2, .lang_id = TRU_USB_LANG_ID_ENGLISH_UK, .desc = (void *)&hid_cus_prod_string_desc },
	{ .index = 3, .lang_id = TRU_USB_LANG_ID_ENGLISH_UK, .desc = (void *)&hid_cus_ser_string_desc }
};

// ===========================================================================
// Final HID peripheral device descriptors (pointers to all structures above)
// ===========================================================================

// Common
tru_usb_pd_info_t hid_cus_base_pd_info = {
#if HID_CUS_HS_DESC_ENABLE == 1
	.hs_dev_desc = (tru_usb_dev_desc_t *)&hid_cus_hs_dev_desc,
#else
	.hs_dev_desc = NULL,
#endif
	.fs_dev_desc = (tru_usb_dev_desc_t *)&hid_cus_fs_dev_desc,
	.ls_dev_desc = (tru_usb_dev_desc_t *)&hid_cus_ls_dev_desc,

#if HID_CUS_HS_DESC_ENABLE == 1
	.hs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&hid_cus_hs_dev_qual_desc,
	.fs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&hid_cus_fs_dev_qual_desc,
#else
	.hs_dev_qual_desc = NULL,
	.fs_dev_qual_desc = NULL,
#endif

#if HID_CUS_HS_DESC_ENABLE == 1
	.hs_config_descs = (tru_usb_config_desc_set_t *)hid_cus_hs_config_descs, .hs_config_descs_num_entries = sizeof(hid_cus_hs_config_descs) / sizeof(tru_usb_config_desc_set_t),
#else
	.hs_config_descs = NULL, .hs_config_descs_num_entries = 0,
#endif
	.fs_config_descs = (tru_usb_config_desc_set_t *)hid_cus_fs_config_descs, .fs_config_descs_num_entries = sizeof(hid_cus_fs_config_descs) / sizeof(tru_usb_config_desc_set_t),
	.ls_config_descs = (tru_usb_config_desc_set_t *)hid_cus_ls_config_descs, .ls_config_descs_num_entries = sizeof(hid_cus_ls_config_descs) / sizeof(tru_usb_config_desc_set_t),

	.string_descs = (tru_usb_string_desc_info_t *)hid_cus_string_descs, .string_descs_num_entries = sizeof(hid_cus_string_descs) / sizeof(tru_usb_string_desc_info_t)
};

// Common + class
tru_usb_hid_pd_info_t hid_cus_pd_info = {
	.pd = &hid_cus_base_pd_info,

#if HID_CUS_HS_DESC_ENABLE == 1
	.hs_hid_interface_exts = (tru_usb_hid_interface_ext_t *)hid_cus_hs_interface_exts, .hs_hid_interface_exts_num_entries = sizeof(hid_cus_hs_interface_exts) / sizeof(tru_usb_hid_interface_ext_t),
#else
	.hs_hid_interface_exts = NULL, .hs_hid_interface_exts_num_entries = 0,
#endif
	.fs_hid_interface_exts = (tru_usb_hid_interface_ext_t *)hid_cus_fs_interface_exts, .fs_hid_interface_exts_num_entries = sizeof(hid_cus_fs_interface_exts) / sizeof(tru_usb_hid_interface_ext_t),
	.ls_hid_interface_exts = (tru_usb_hid_interface_ext_t *)hid_cus_ls_interface_exts, .ls_hid_interface_exts_num_entries = sizeof(hid_cus_ls_interface_exts) / sizeof(tru_usb_hid_interface_ext_t),
};

tru_usb_hid_pd_info_t *get_hid_cus_pd_info(void){
	return (tru_usb_hid_pd_info_t *)&hid_cus_pd_info;
}

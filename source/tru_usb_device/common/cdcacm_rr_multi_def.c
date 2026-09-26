#include "cdcacm_rr_multi_def.h"
#include "usb/dclass/tru_usb_iad_def.h"

// ==============================================
// Class specific interface extension descriptors
// ==============================================

// ============================================
// CDC-ACM class interface extension structures
// ============================================

// Line coding for each interface
// Line control for each interface
// Encapsulated buffer for each interface
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	tru_usb_cdc_linecoding_t cdcacm_rr_multi_linecoding_1_0_0 = {
		.dte_rate = CDCACM_RR_MULTI_VCP1_DEFAULT_BIT_RATE,
		.char_format = CDCACM_RR_MULTI_VCP1_DEFAULT_CHAR_FORMAT,
		.parity_type = CDCACM_RR_MULTI_VCP1_DEFAULT_PARITY_TYPE,
		.data_bits = CDCACM_RR_MULTI_VCP1_DEFAULT_DATA_BITS
	};

	tru_usb_cdc_linecontrol_t cdcacm_rr_multi_linecontrol_1_0_0 = { .val= 0 };

	tru_usb_cdc_encap_t cdcacm_rr_multi_encap_1_0_0 = {
		.encap_cmd = NULL,
		.encap_cmd_buf_size = 0,
		.encap_resp = NULL,
		.encap_resp_buf_size = 0
	};

	tru_usb_cdc_uartstate_t cdcacm_rr_multi_uartstate_1_0_0 = { .val = 0 };
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	tru_usb_cdc_linecoding_t cdcacm_rr_multi_linecoding_1_2_0 = {
		.dte_rate = CDCACM_RR_MULTI_VCP1_DEFAULT_BIT_RATE,
		.char_format = CDCACM_RR_MULTI_VCP1_DEFAULT_CHAR_FORMAT,
		.parity_type = CDCACM_RR_MULTI_VCP1_DEFAULT_PARITY_TYPE,
		.data_bits = CDCACM_RR_MULTI_VCP1_DEFAULT_DATA_BITS
	};

	tru_usb_cdc_linecontrol_t cdcacm_rr_multi_linecontrol_1_2_0 = { .val= 0 };

	tru_usb_cdc_encap_t cdcacm_rr_multi_encap_1_2_0 = {
		.encap_cmd = NULL,
		.encap_cmd_buf_size = 0,
		.encap_resp = NULL,
		.encap_resp_buf_size = 0
	};

	tru_usb_cdc_uartstate_t cdcacm_rr_multi_uartstate_1_2_0 = { .val = 0 };
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	tru_usb_cdc_linecoding_t cdcacm_rr_multi_linecoding_1_4_0 = {
		.dte_rate = CDCACM_RR_MULTI_VCP1_DEFAULT_BIT_RATE,
		.char_format = CDCACM_RR_MULTI_VCP1_DEFAULT_CHAR_FORMAT,
		.parity_type = CDCACM_RR_MULTI_VCP1_DEFAULT_PARITY_TYPE,
		.data_bits = CDCACM_RR_MULTI_VCP1_DEFAULT_DATA_BITS
	};

	tru_usb_cdc_linecontrol_t cdcacm_rr_multi_linecontrol_1_4_0 = { .val= 0 };

	tru_usb_cdc_encap_t cdcacm_rr_multi_encap_1_4_0 = {
		.encap_cmd = NULL,
		.encap_cmd_buf_size = 0,
		.encap_resp = NULL,
		.encap_resp_buf_size = 0
	};

	tru_usb_cdc_uartstate_t cdcacm_rr_multi_uartstate_1_4_0 = { .val = 0 };
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	tru_usb_cdc_linecoding_t cdcacm_rr_multi_linecoding_1_6_0 = {
		.dte_rate = CDCACM_RR_MULTI_VCP1_DEFAULT_BIT_RATE,
		.char_format = CDCACM_RR_MULTI_VCP1_DEFAULT_CHAR_FORMAT,
		.parity_type = CDCACM_RR_MULTI_VCP1_DEFAULT_PARITY_TYPE,
		.data_bits = CDCACM_RR_MULTI_VCP1_DEFAULT_DATA_BITS
	};

	tru_usb_cdc_linecontrol_t cdcacm_rr_multi_linecontrol_1_6_0 = { .val= 0 };

	tru_usb_cdc_encap_t cdcacm_rr_multi_encap_1_6_0 = {
		.encap_cmd = NULL,
		.encap_cmd_buf_size = 0,
		.encap_resp = NULL,
		.encap_resp_buf_size = 0
	};

	tru_usb_cdc_uartstate_t cdcacm_rr_multi_uartstate_1_6_0 = { .val = 0 };
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	tru_usb_cdc_linecoding_t cdcacm_rr_multi_linecoding_1_8_0 = {
		.dte_rate = CDCACM_RR_MULTI_VCP1_DEFAULT_BIT_RATE,
		.char_format = CDCACM_RR_MULTI_VCP1_DEFAULT_CHAR_FORMAT,
		.parity_type = CDCACM_RR_MULTI_VCP1_DEFAULT_PARITY_TYPE,
		.data_bits = CDCACM_RR_MULTI_VCP1_DEFAULT_DATA_BITS
	};

	tru_usb_cdc_linecontrol_t cdcacm_rr_multi_linecontrol_1_8_0 = { .val= 0 };

	tru_usb_cdc_encap_t cdcacm_rr_multi_encap_1_8_0 = {
		.encap_cmd = NULL,
		.encap_cmd_buf_size = 0,
		.encap_resp = NULL,
		.encap_resp_buf_size = 0
	};

	tru_usb_cdc_uartstate_t cdcacm_rr_multi_uartstate_1_8_0 = { .val = 0 };
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	tru_usb_cdc_linecoding_t cdcacm_rr_multi_linecoding_1_10_0 = {
		.dte_rate = CDCACM_RR_MULTI_VCP1_DEFAULT_BIT_RATE,
		.char_format = CDCACM_RR_MULTI_VCP1_DEFAULT_CHAR_FORMAT,
		.parity_type = CDCACM_RR_MULTI_VCP1_DEFAULT_PARITY_TYPE,
		.data_bits = CDCACM_RR_MULTI_VCP1_DEFAULT_DATA_BITS
	};

	tru_usb_cdc_linecontrol_t cdcacm_rr_multi_linecontrol_1_10_0 = { .val= 0 };

	tru_usb_cdc_encap_t cdcacm_rr_multi_encap_1_10_0 = {
		.encap_cmd = NULL,
		.encap_cmd_buf_size = 0,
		.encap_resp = NULL,
		.encap_resp_buf_size = 0
	};

	tru_usb_cdc_uartstate_t cdcacm_rr_multi_uartstate_1_10_0 = { .val = 0 };
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	tru_usb_cdc_linecoding_t cdcacm_rr_multi_linecoding_1_12_0 = {
		.dte_rate = CDCACM_RR_MULTI_VCP1_DEFAULT_BIT_RATE,
		.char_format = CDCACM_RR_MULTI_VCP1_DEFAULT_CHAR_FORMAT,
		.parity_type = CDCACM_RR_MULTI_VCP1_DEFAULT_PARITY_TYPE,
		.data_bits = CDCACM_RR_MULTI_VCP1_DEFAULT_DATA_BITS
	};

	tru_usb_cdc_linecontrol_t cdcacm_rr_multi_linecontrol_1_12_0 = { .val= 0 };

	tru_usb_cdc_encap_t cdcacm_rr_multi_encap_1_12_0 = {
		.encap_cmd = NULL,
		.encap_cmd_buf_size = 0,
		.encap_resp = NULL,
		.encap_resp_buf_size = 0
	};

	tru_usb_cdc_uartstate_t cdcacm_rr_multi_uartstate_1_12_0 = { .val = 0 };
#endif

// =================================================================================================
// CDC-ACM class interface extensions array of all configurations, interfaces and alternate settings
// =================================================================================================

// Array of all CDC-ACM interface extensions.  Each entry starts with the Configuration number, Interface number, Alternate setting number
const tru_usb_cdc_interface_ext_t cdcacm_rr_multi_interface_exts[] = {
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	{ .ext_hdr = { .config_num = 1, .interface_num = 0, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_0_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_0_0, .encap = &cdcacm_rr_multi_encap_1_0_0, .uartstate = &cdcacm_rr_multi_uartstate_1_0_0 },
	{ .ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_0_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_0_0, .encap = &cdcacm_rr_multi_encap_1_0_0, .uartstate = &cdcacm_rr_multi_uartstate_1_0_0 },
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	{ .ext_hdr = { .config_num = 1, .interface_num = 2, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_2_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_2_0, .encap = &cdcacm_rr_multi_encap_1_2_0, .uartstate = &cdcacm_rr_multi_uartstate_1_2_0 },
	{ .ext_hdr = { .config_num = 1, .interface_num = 3, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_2_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_2_0, .encap = &cdcacm_rr_multi_encap_1_2_0, .uartstate = &cdcacm_rr_multi_uartstate_1_2_0 },
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	{ .ext_hdr = { .config_num = 1, .interface_num = 4, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_4_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_4_0, .encap = &cdcacm_rr_multi_encap_1_4_0, .uartstate = &cdcacm_rr_multi_uartstate_1_4_0 },
	{ .ext_hdr = { .config_num = 1, .interface_num = 5, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_4_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_4_0, .encap = &cdcacm_rr_multi_encap_1_4_0, .uartstate = &cdcacm_rr_multi_uartstate_1_4_0 },
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	{ .ext_hdr = { .config_num = 1, .interface_num = 6, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_6_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_6_0, .encap = &cdcacm_rr_multi_encap_1_6_0, .uartstate = &cdcacm_rr_multi_uartstate_1_6_0 },
	{ .ext_hdr = { .config_num = 1, .interface_num = 7, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_6_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_6_0, .encap = &cdcacm_rr_multi_encap_1_6_0, .uartstate = &cdcacm_rr_multi_uartstate_1_6_0 },
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	{ .ext_hdr = { .config_num = 1, .interface_num = 8, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_8_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_8_0, .encap = &cdcacm_rr_multi_encap_1_8_0, .uartstate = &cdcacm_rr_multi_uartstate_1_8_0 },
	{ .ext_hdr = { .config_num = 1, .interface_num = 9, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_8_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_8_0, .encap = &cdcacm_rr_multi_encap_1_8_0, .uartstate = &cdcacm_rr_multi_uartstate_1_8_0 },
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	{ .ext_hdr = { .config_num = 1, .interface_num = 10, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_10_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_10_0, .encap = &cdcacm_rr_multi_encap_1_10_0, .uartstate = &cdcacm_rr_multi_uartstate_1_10_0 },
	{ .ext_hdr = { .config_num = 1, .interface_num = 11, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_10_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_10_0, .encap = &cdcacm_rr_multi_encap_1_10_0, .uartstate = &cdcacm_rr_multi_uartstate_1_10_0 },
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	{ .ext_hdr = { .config_num = 1, .interface_num = 12, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_12_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_12_0, .encap = &cdcacm_rr_multi_encap_1_12_0, .uartstate = &cdcacm_rr_multi_uartstate_1_12_0 },
	{ .ext_hdr = { .config_num = 1, .interface_num = 13, .alt_setting_num = 0 }, .linecoding = &cdcacm_rr_multi_linecoding_1_12_0, .linecontrol = &cdcacm_rr_multi_linecontrol_1_12_0, .encap = &cdcacm_rr_multi_encap_1_12_0, .uartstate = &cdcacm_rr_multi_uartstate_1_12_0 },
#endif
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
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	tru_usb_iad_desc_t                      iad_vcp1;
	tru_usb_interface_desc_t                interface_func_vcp1;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp1;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp1;
	tru_usb_cdc_func_desc_union_t           func_union_vcp1;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp1;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp1;
	tru_usb_interface_desc_t                interface_data_vcp1;
	tru_usb_ep_desc_t                       ep_data_in_vcp1;
	tru_usb_ep_desc_t                       ep_data_out_vcp1;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	tru_usb_iad_desc_t                      iad_vcp2;
	tru_usb_interface_desc_t                interface_func_vcp2;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp2;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp2;
	tru_usb_cdc_func_desc_union_t           func_union_vcp2;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp2;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp2;
	tru_usb_interface_desc_t                interface_data_vcp2;
	tru_usb_ep_desc_t                       ep_data_in_vcp2;
	tru_usb_ep_desc_t                       ep_data_out_vcp2;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	tru_usb_iad_desc_t                      iad_vcp3;
	tru_usb_interface_desc_t                interface_func_vcp3;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp3;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp3;
	tru_usb_cdc_func_desc_union_t           func_union_vcp3;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp3;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp3;
	tru_usb_interface_desc_t                interface_data_vcp3;
	tru_usb_ep_desc_t                       ep_data_in_vcp3;
	tru_usb_ep_desc_t                       ep_data_out_vcp3;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	tru_usb_iad_desc_t                      iad_vcp4;
	tru_usb_interface_desc_t                interface_func_vcp4;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp4;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp4;
	tru_usb_cdc_func_desc_union_t           func_union_vcp4;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp4;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp4;
	tru_usb_interface_desc_t                interface_data_vcp4;
	tru_usb_ep_desc_t                       ep_data_in_vcp4;
	tru_usb_ep_desc_t                       ep_data_out_vcp4;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	tru_usb_iad_desc_t                      iad_vcp5;
	tru_usb_interface_desc_t                interface_func_vcp5;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp5;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp5;
	tru_usb_cdc_func_desc_union_t           func_union_vcp5;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp5;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp5;
	tru_usb_interface_desc_t                interface_data_vcp5;
	tru_usb_ep_desc_t                       ep_data_in_vcp5;
	tru_usb_ep_desc_t                       ep_data_out_vcp5;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	tru_usb_iad_desc_t                      iad_vcp6;
	tru_usb_interface_desc_t                interface_func_vcp6;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp6;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp6;
	tru_usb_cdc_func_desc_union_t           func_union_vcp6;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp6;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp6;
	tru_usb_interface_desc_t                interface_data_vcp6;
	tru_usb_ep_desc_t                       ep_data_in_vcp6;
	tru_usb_ep_desc_t                       ep_data_out_vcp6;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	tru_usb_iad_desc_t                      iad_vcp7;
	tru_usb_interface_desc_t                interface_func_vcp7;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp7;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp7;
	tru_usb_cdc_func_desc_union_t           func_union_vcp7;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp7;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp7;
	tru_usb_interface_desc_t                interface_data_vcp7;
	tru_usb_ep_desc_t                       ep_data_in_vcp7;
	tru_usb_ep_desc_t                       ep_data_out_vcp7;
#endif
}cdcacm_rr_multi_ls_config1_desc_t;

/*
	Dual CDC configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			0 or more interface association descriptor(s),
				1 or more interface descriptor(s),
					1 CDC descriptor per interface,
					0 or more endpoint descriptor(s) per interface

	Note:
		CDC class descriptors are not included (i.e. report, physical or vendor) inside the configuration set of descriptors,
		instead they should be stored as a separate set using a class specific extension.
*/
const cdcacm_rr_multi_ls_config1_desc_t cdcacm_rr_multi_ls_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(cdcacm_rr_multi_ls_config1_desc_t),
		.num_interfaces = 2 * CDCACM_RR_MULTI_NUM_PORTS,  // Number of interfaces (counting only alternate setting == 0) in this configuration
		.config_num = 1,
		.string_index = 0,  // Index of configuration string (0 = no string)
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	// IAD descriptor
	.iad_vcp1 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp1 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_NTF_EPNUM,
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
	.interface_data_vcp1 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_TXD_EPNUM,
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
	.ep_data_out_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	// IAD descriptor
	.iad_vcp2 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp2 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_NTF_EPNUM,
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
	.interface_data_vcp2 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_TXD_EPNUM,
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
	.ep_data_out_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	// IAD descriptor
	.iad_vcp3 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp3 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_NTF_EPNUM,
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
	.interface_data_vcp3 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_TXD_EPNUM,
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
	.ep_data_out_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	// IAD descriptor
	.iad_vcp4 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp4 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_NTF_EPNUM,
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
	.interface_data_vcp4 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_TXD_EPNUM,
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
	.ep_data_out_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	// IAD descriptor
	.iad_vcp5 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp5 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_NTF_EPNUM,
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
	.interface_data_vcp5 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_TXD_EPNUM,
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
	.ep_data_out_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	// IAD descriptor
	.iad_vcp6 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp6 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_NTF_EPNUM,
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
	.interface_data_vcp6 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_TXD_EPNUM,
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
	.ep_data_out_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	// IAD descriptor
	.iad_vcp7 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp7 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_NTF_EPNUM,
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
	.interface_data_vcp7 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_TXD_EPNUM,
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
	.ep_data_out_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_RXD_EPNUM,
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
#endif
};

// Array of all configuration descriptor sets (pointers and sizes) for low speed mode
const tru_usb_config_desc_set_t cdcacm_rr_multi_ls_config_descs[] = {
	{ .desc = (uint8_t *)&cdcacm_rr_multi_ls_config1_desc, .size = sizeof(cdcacm_rr_multi_ls_config1_desc) }
};

// Total number of configurations for low speed mode
#define CDCACM_RR_MULTI_LS_NUM_OF_CONFIGS (sizeof(cdcacm_rr_multi_ls_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for low speed mode
const tru_usb_dev_desc_t cdcacm_rr_multi_ls_dev_desc = {
	.desc_type = sizeof(tru_usb_dev_desc_t),
	.length = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = CDCACM_RR_MULTI_USB_VER,  // USB specification version number (BCD format)
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = TRU_USB_EP_LS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = CDCACM_RR_MULTI_VID,
	.pid = CDCACM_RR_MULTI_PID,
	.product_ver = CDCACM_RR_MULTI_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = CDCACM_RR_MULTI_LS_NUM_OF_CONFIGS
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
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	tru_usb_iad_desc_t                      iad_vcp1;
	tru_usb_interface_desc_t                interface_func_vcp1;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp1;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp1;
	tru_usb_cdc_func_desc_union_t           func_union_vcp1;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp1;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp1;
	tru_usb_interface_desc_t                interface_data_vcp1;
	tru_usb_ep_desc_t                       ep_data_in_vcp1;
	tru_usb_ep_desc_t                       ep_data_out_vcp1;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	tru_usb_iad_desc_t                      iad_vcp2;
	tru_usb_interface_desc_t                interface_func_vcp2;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp2;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp2;
	tru_usb_cdc_func_desc_union_t           func_union_vcp2;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp2;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp2;
	tru_usb_interface_desc_t                interface_data_vcp2;
	tru_usb_ep_desc_t                       ep_data_in_vcp2;
	tru_usb_ep_desc_t                       ep_data_out_vcp2;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	tru_usb_iad_desc_t                      iad_vcp3;
	tru_usb_interface_desc_t                interface_func_vcp3;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp3;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp3;
	tru_usb_cdc_func_desc_union_t           func_union_vcp3;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp3;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp3;
	tru_usb_interface_desc_t                interface_data_vcp3;
	tru_usb_ep_desc_t                       ep_data_in_vcp3;
	tru_usb_ep_desc_t                       ep_data_out_vcp3;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	tru_usb_iad_desc_t                      iad_vcp4;
	tru_usb_interface_desc_t                interface_func_vcp4;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp4;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp4;
	tru_usb_cdc_func_desc_union_t           func_union_vcp4;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp4;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp4;
	tru_usb_interface_desc_t                interface_data_vcp4;
	tru_usb_ep_desc_t                       ep_data_in_vcp4;
	tru_usb_ep_desc_t                       ep_data_out_vcp4;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	tru_usb_iad_desc_t                      iad_vcp5;
	tru_usb_interface_desc_t                interface_func_vcp5;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp5;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp5;
	tru_usb_cdc_func_desc_union_t           func_union_vcp5;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp5;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp5;
	tru_usb_interface_desc_t                interface_data_vcp5;
	tru_usb_ep_desc_t                       ep_data_in_vcp5;
	tru_usb_ep_desc_t                       ep_data_out_vcp5;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	tru_usb_iad_desc_t                      iad_vcp6;
	tru_usb_interface_desc_t                interface_func_vcp6;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp6;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp6;
	tru_usb_cdc_func_desc_union_t           func_union_vcp6;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp6;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp6;
	tru_usb_interface_desc_t                interface_data_vcp6;
	tru_usb_ep_desc_t                       ep_data_in_vcp6;
	tru_usb_ep_desc_t                       ep_data_out_vcp6;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	tru_usb_iad_desc_t                      iad_vcp7;
	tru_usb_interface_desc_t                interface_func_vcp7;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp7;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp7;
	tru_usb_cdc_func_desc_union_t           func_union_vcp7;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp7;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp7;
	tru_usb_interface_desc_t                interface_data_vcp7;
	tru_usb_ep_desc_t                       ep_data_in_vcp7;
	tru_usb_ep_desc_t                       ep_data_out_vcp7;
#endif
}cdcacm_rr_multi_fs_config1_desc_t;

/*
	Dual CDC configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			0 or more interface association descriptor(s),
				1 or more interface descriptor(s),
					1 CDC descriptor per interface,
					0 or more endpoint descriptor(s) per interface

	Note:
		CDC class descriptors are not included (i.e. report, physical or vendor) inside the configuration set of descriptors,
		instead they should be stored as a separate set using a class specific extension.
*/
const cdcacm_rr_multi_fs_config1_desc_t cdcacm_rr_multi_fs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(cdcacm_rr_multi_fs_config1_desc_t),
		.num_interfaces = 2 * CDCACM_RR_MULTI_NUM_PORTS,
		.config_num = 1,
		.string_index = 0,  // Index of configuration string (0 = no string)
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	// IAD descriptor
	.iad_vcp1 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp1 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},
	
	// Union functional descriptor
	.func_union_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM  // Interface number of the subordinate
	},
	
	// Call Management functional descriptor
	.func_call_man_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_NTF_EPNUM,
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
	.interface_data_vcp1 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_TXD_EPNUM,
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
	.ep_data_out_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	// IAD descriptor
	.iad_vcp2 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp2 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_NTF_EPNUM,
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
	.interface_data_vcp2 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_TXD_EPNUM,
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
	.ep_data_out_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	// IAD descriptor
	.iad_vcp3 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp3 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_NTF_EPNUM,
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
	.interface_data_vcp3 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_TXD_EPNUM,
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
	.ep_data_out_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	// IAD descriptor
	.iad_vcp4 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp4 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_NTF_EPNUM,
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
	.interface_data_vcp4 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_TXD_EPNUM,
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
	.ep_data_out_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	// IAD descriptor
	.iad_vcp5 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp5 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_NTF_EPNUM,
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
	.interface_data_vcp5 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_TXD_EPNUM,
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
	.ep_data_out_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	// IAD descriptor
	.iad_vcp6 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp6 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_NTF_EPNUM,
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
	.interface_data_vcp6 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_TXD_EPNUM,
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
	.ep_data_out_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	// IAD descriptor
	.iad_vcp7 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp7 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0100,  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,
		.interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_NTF_EPNUM,
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
	.interface_data_vcp7 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_TXD_EPNUM,
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
	.ep_data_out_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_RXD_EPNUM,
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
#endif
};

// Array of all configuration descriptor sets (pointers and sizes) for full speed mode
const tru_usb_config_desc_set_t cdcacm_rr_multi_fs_config_descs[] = {
	{ .desc = (uint8_t *)&cdcacm_rr_multi_fs_config1_desc, .size = sizeof(cdcacm_rr_multi_fs_config1_desc) }
};

// Total number of configurations for full speed mode
#define CDCACM_RR_MULTI_FS_NUM_OF_CONFIGS (sizeof(cdcacm_rr_multi_fs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for full speed mode
const tru_usb_dev_desc_t cdcacm_rr_multi_fs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = CDCACM_RR_MULTI_USB_VER,  // USB specification version number (BCD format)
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = 64,  // EP0 max packet size
	.vid = CDCACM_RR_MULTI_VID,
	.pid = CDCACM_RR_MULTI_PID,
	.product_ver = CDCACM_RR_MULTI_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = CDCACM_RR_MULTI_FS_NUM_OF_CONFIGS
};

#if CDCACM_RR_MULTI_HS_DESC_ENABLE == 1

// ===========================
// High speed mode descriptors
// ===========================

// =========================
// Configuration descriptors
// =========================

// Configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t                   config_0;
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	tru_usb_iad_desc_t                      iad_vcp1;
	tru_usb_interface_desc_t                interface_func_vcp1;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp1;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp1;
	tru_usb_cdc_func_desc_union_t           func_union_vcp1;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp1;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp1;
	tru_usb_interface_desc_t                interface_data_vcp1;
	tru_usb_ep_desc_t                       ep_data_in_vcp1;
	tru_usb_ep_desc_t                       ep_data_out_vcp1;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	tru_usb_iad_desc_t                      iad_vcp2;
	tru_usb_interface_desc_t                interface_func_vcp2;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp2;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp2;
	tru_usb_cdc_func_desc_union_t           func_union_vcp2;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp2;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp2;
	tru_usb_interface_desc_t                interface_data_vcp2;
	tru_usb_ep_desc_t                       ep_data_in_vcp2;
	tru_usb_ep_desc_t                       ep_data_out_vcp2;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	tru_usb_iad_desc_t                      iad_vcp3;
	tru_usb_interface_desc_t                interface_func_vcp3;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp3;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp3;
	tru_usb_cdc_func_desc_union_t           func_union_vcp3;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp3;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp3;
	tru_usb_interface_desc_t                interface_data_vcp3;
	tru_usb_ep_desc_t                       ep_data_in_vcp3;
	tru_usb_ep_desc_t                       ep_data_out_vcp3;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	tru_usb_iad_desc_t                      iad_vcp4;
	tru_usb_interface_desc_t                interface_func_vcp4;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp4;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp4;
	tru_usb_cdc_func_desc_union_t           func_union_vcp4;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp4;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp4;
	tru_usb_interface_desc_t                interface_data_vcp4;
	tru_usb_ep_desc_t                       ep_data_in_vcp4;
	tru_usb_ep_desc_t                       ep_data_out_vcp4;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	tru_usb_iad_desc_t                      iad_vcp5;
	tru_usb_interface_desc_t                interface_func_vcp5;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp5;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp5;
	tru_usb_cdc_func_desc_union_t           func_union_vcp5;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp5;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp5;
	tru_usb_interface_desc_t                interface_data_vcp5;
	tru_usb_ep_desc_t                       ep_data_in_vcp5;
	tru_usb_ep_desc_t                       ep_data_out_vcp5;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	tru_usb_iad_desc_t                      iad_vcp6;
	tru_usb_interface_desc_t                interface_func_vcp6;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp6;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp6;
	tru_usb_cdc_func_desc_union_t           func_union_vcp6;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp6;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp6;
	tru_usb_interface_desc_t                interface_data_vcp6;
	tru_usb_ep_desc_t                       ep_data_in_vcp6;
	tru_usb_ep_desc_t                       ep_data_out_vcp6;
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	tru_usb_iad_desc_t                      iad_vcp7;
	tru_usb_interface_desc_t                interface_func_vcp7;
	tru_usb_cdc_func_desc_hdr_t             func_hdr_vcp7;
	tru_usb_cdc_func_desc_acm_t             func_acm_vcp7;
	tru_usb_cdc_func_desc_union_t           func_union_vcp7;
	tru_usb_cdc_func_desc_call_management_t func_call_man_vcp7;
	tru_usb_ep_desc_t                       ep_comm_msg_vcp7;
	tru_usb_interface_desc_t                interface_data_vcp7;
	tru_usb_ep_desc_t                       ep_data_in_vcp7;
	tru_usb_ep_desc_t                       ep_data_out_vcp7;
#endif
}cdcacm_rr_multi_hs_config1_desc_t;

/*
	Dual CDC configuration 1 set of descriptors.
	It contains descriptors for a single configuration, i.e. the following:
		1 configuration descriptor,
			0 or more interface association descriptor(s),
				1 or more interface descriptor(s),
					1 CDC descriptor per interface,
					0 or more endpoint descriptor(s) per interface
*/
const cdcacm_rr_multi_hs_config1_desc_t cdcacm_rr_multi_hs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(cdcacm_rr_multi_hs_config1_desc_t),
		.num_interfaces = 2 * CDCACM_RR_MULTI_NUM_PORTS,
		.config_num = 1,
		.string_index = 0,  // Index of configuration string (0 = no string)
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED  // Maximum power consumption from the bus expressed in 2x mA units, e.g. 250 = 500 mA
	},
#if CDCACM_RR_MULTI_NUM_PORTS >= 1
	// IAD descriptor
	.iad_vcp1 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp1 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0110  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP1_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp1 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,  // Capabilities
		.interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_NTF_EPNUM,
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
	.interface_data_vcp1 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP1_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_TXD_EPNUM,
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
	.ep_data_out_vcp1 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP1_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 2
	// IAD descriptor
	.iad_vcp2 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp2 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0110  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP2_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp2 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,  // Capabilities
		.interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_NTF_EPNUM,
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
	.interface_data_vcp2 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP2_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_TXD_EPNUM,
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
	.ep_data_out_vcp2 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP2_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 3
	// IAD descriptor
	.iad_vcp3 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp3 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0110  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP3_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp3 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,  // Capabilities
		.interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_NTF_EPNUM,
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
	.interface_data_vcp3 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP3_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_TXD_EPNUM,
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
	.ep_data_out_vcp3 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP3_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 4
	// IAD descriptor
	.iad_vcp4 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp4 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0110  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP4_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp4 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,  // Capabilities
		.interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_NTF_EPNUM,
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
	.interface_data_vcp4 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP4_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_TXD_EPNUM,
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
	.ep_data_out_vcp4 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP4_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 5
	// IAD descriptor
	.iad_vcp5 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp5 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0110  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP5_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp5 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,  // Capabilities
		.interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_NTF_EPNUM,
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
	.interface_data_vcp5 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP5_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_TXD_EPNUM,
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
	.ep_data_out_vcp5 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP5_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 6
	// IAD descriptor
	.iad_vcp6 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp6 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0110  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP6_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp6 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,  // Capabilities
		.interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_NTF_EPNUM,
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
	.interface_data_vcp6 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP6_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_TXD_EPNUM,
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
	.ep_data_out_vcp6 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP6_RXD_EPNUM,
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
#endif
#if CDCACM_RR_MULTI_NUM_PORTS >= 7
	// IAD descriptor
	.iad_vcp7 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,
		.interface_count = 2,
		.function_class = TRU_USB_CDC_INTERFACE_CLASS,
		.function_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.function_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.function = 0
	},

	// Interface descriptor for the Communications Interface
	.interface_func_vcp7 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 1,
		.interface_class = TRU_USB_CDC_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_INTERFACE_SUBCLASS_ACM,
		.interface_protocol = TRU_USB_CDC_INTERFACE_PROTOCOL_AT_V250,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Header functional descriptor
	.func_hdr_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_hdr_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_HDR,
		.release_num = 0x0110  // CDC specification release number (BCD format)
	},

	// ACM functional descriptor
	.func_acm_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_acm_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_ACM,
		.capabilites = TRU_USB_CDC_FUNC_ACM_CAP_SUPPORT_LINE_CONTROL
	},

	// Union functional descriptor
	.func_union_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_union_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_UNION,
		.ctrl_interface_num = CDCACM_RR_MULTI_VCP7_NTF_ITFNUM,  // Interface number of the control
		.sub_interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM  // Interface number of the subordinate
	},

	// Call Management functional descriptor
	.func_call_man_vcp7 = {
		.length = sizeof(tru_usb_cdc_func_desc_call_management_t),
		.desc_type = TRU_USB_CDC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_CDC_DESC_SUBTYPE_FUNC_CALL_MANAGEMENT,
		.capabilites = TRU_USB_CDC_FUNC_CM_CAP_NONE,  // Capabilities
		.interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM  // Interface number of the data
	},

	// Endpoint descriptor for Communications Messages - in this case it is for Management Element Notifications
	.ep_comm_msg_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_NTF_EPNUM,
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
	.interface_data_vcp7 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = CDCACM_RR_MULTI_VCP7_DAT_ITFNUM,
		.alt_setting_num = 0,
		.num_endpoints = 2,
		.interface_class = TRU_USB_CDC_DATA_INTERFACE_CLASS,
		.interface_subclass = TRU_USB_CDC_DATA_INTERFACE_SUBCLASS_UNDEFINED,
		.interface_protocol = TRU_USB_CDC_DATA_INTERFACE_CLASS_PROTOCOL_UNDEFINED,
		.string_index = 0  // Index of interface string (0 = no string)
	},

	// Endpoint descriptor for Data Messages (device to host)
	.ep_data_in_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_TXD_EPNUM,
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
	.ep_data_out_vcp7 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = CDCACM_RR_MULTI_VCP7_RXD_EPNUM,
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
#endif
};

// Array of all configuration descriptor sets (pointers and sizes) for high speed mode
const tru_usb_config_desc_set_t cdcacm_rr_multi_hs_config_descs[] = {
	{ .desc = (uint8_t *)&cdcacm_rr_multi_hs_config1_desc, .size = sizeof(cdcacm_rr_multi_hs_config1_desc) }
};

// Total number of configurations for high speed mode
#define CDCACM_RR_MULTI_HS_NUM_OF_CONFIGS (sizeof(cdcacm_rr_multi_hs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for high speed mode
const tru_usb_dev_desc_t cdcacm_rr_multi_hs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = CDCACM_RR_MULTI_USB_VER,  // USB specification version number (BCD format)
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = CDCACM_RR_MULTI_VID,
	.pid = CDCACM_RR_MULTI_PID,
	.product_ver = CDCACM_RR_MULTI_VER,  // Device release number
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = CDCACM_RR_MULTI_HS_NUM_OF_CONFIGS
};

// Device qualifier descriptor for full speed mode (describes other speed, i.e. high speed mode)
const tru_usb_dev_qual_desc_t cdcacm_rr_multi_fs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = CDCACM_RR_MULTI_USB_VER,  // USB release number
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = CDCACM_RR_MULTI_HS_NUM_OF_CONFIGS,
	.reserved = 0
};

// Device qualifier descriptor for high speed mode (describes other speed, i.e. full speed mode)
const tru_usb_dev_qual_desc_t cdcacm_rr_multi_hs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = CDCACM_RR_MULTI_USB_VER,  // USB release number
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = CDCACM_RR_MULTI_FS_NUM_OF_CONFIGS,
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
}cdcacm_rr_multi_string_lang_ids_t;

// Supported language IDs string descriptor
const cdcacm_rr_multi_string_lang_ids_t cdcacm_rr_multi_lang_string_desc = {
	.length = sizeof(cdcacm_rr_multi_lang_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.lang_id = { TRU_USB_LANG_ID_ENGLISH_US }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}cdcacm_rr_multi_string_manuf_t;

// Manufacturer string descriptor
const cdcacm_rr_multi_string_manuf_t cdcacm_rr_multi_manuf_string_desc = {
	.length = sizeof(cdcacm_rr_multi_manuf_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[17];
}cdcacm_rr_multi_string_product_t;

// Product string descriptor
const cdcacm_rr_multi_string_product_t cdcacm_rr_multi_prod_string_desc = {
	.length = sizeof(cdcacm_rr_multi_prod_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', 'C', 'D', 'C', 'A', 'C', 'M', 'B', 'l', 'k', 'M', 'u', 'l', 't', 'i' }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}cdcacm_rr_multi_string_serial_t;

// Serial number string descriptor
const cdcacm_rr_multi_string_serial_t cdcacm_rr_multi_ser_string_desc = {
	.length = sizeof(cdcacm_rr_multi_ser_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { '1', '2', '3' }
};

// An array of all the indexes & language IDs mapped to string descriptor pointers
// Note: this is not described in the USB specification but it is needed in practice
const tru_usb_string_desc_info_t cdcacm_rr_multi_string_descs[] = {
	{ .index = 0, .lang_id = TRU_USB_LANG_ID_NONE,       .desc = (void *)&cdcacm_rr_multi_lang_string_desc },
	{ .index = 1, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&cdcacm_rr_multi_manuf_string_desc },
	{ .index = 2, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&cdcacm_rr_multi_prod_string_desc },
	{ .index = 3, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&cdcacm_rr_multi_ser_string_desc }
};

// ===============================================================================
// Final dual CDC peripheral device descriptors (pointers to all structures above)
// ===============================================================================

// Common
tru_usb_pd_info_t cdcacm_rr_multi_base_pd_info = {
#if CDCACM_RR_MULTI_HS_DESC_ENABLE == 1
	.hs_dev_desc = (tru_usb_dev_desc_t *)&cdcacm_rr_multi_hs_dev_desc,
#else
	.hs_dev_desc = NULL,
#endif
	.fs_dev_desc = (tru_usb_dev_desc_t *)&cdcacm_rr_multi_fs_dev_desc,
	.ls_dev_desc = (tru_usb_dev_desc_t *)&cdcacm_rr_multi_ls_dev_desc,

#if CDCACM_RR_MULTI_HS_DESC_ENABLE == 1
	.hs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&cdcacm_rr_multi_hs_dev_qual_desc,
	.fs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&cdcacm_rr_multi_fs_dev_qual_desc,
#else
	.hs_dev_qual_desc = NULL,
	.fs_dev_qual_desc = NULL,
#endif

#if CDCACM_RR_MULTI_HS_DESC_ENABLE == 1
	.hs_config_descs = (tru_usb_config_desc_set_t *)cdcacm_rr_multi_hs_config_descs, .hs_config_descs_num_entries = sizeof(cdcacm_rr_multi_hs_config_descs) / sizeof(tru_usb_config_desc_set_t),
#else
	.hs_config_descs = NULL, .hs_config_descs_num_entries = 0,
#endif
	.fs_config_descs = (tru_usb_config_desc_set_t *)cdcacm_rr_multi_fs_config_descs, .fs_config_descs_num_entries = sizeof(cdcacm_rr_multi_fs_config_descs) / sizeof(tru_usb_config_desc_set_t),
	.ls_config_descs = (tru_usb_config_desc_set_t *)cdcacm_rr_multi_ls_config_descs, .ls_config_descs_num_entries = sizeof(cdcacm_rr_multi_ls_config_descs) / sizeof(tru_usb_config_desc_set_t),

	.string_descs = (tru_usb_string_desc_info_t *)cdcacm_rr_multi_string_descs, .string_descs_num_entries = sizeof(cdcacm_rr_multi_string_descs) / sizeof(tru_usb_string_desc_info_t)
};

// Common + class
tru_usb_cdc_pd_info_t cdcacm_rr_multi_pd_info = {
	.pd = &cdcacm_rr_multi_base_pd_info,

#if CDCACM_RR_MULTI_HS_DESC_ENABLE == 1
	.hs_cdc_interface_exts = (tru_usb_cdc_interface_ext_t *)cdcacm_rr_multi_interface_exts, .hs_cdc_interface_exts_num_entries = sizeof(cdcacm_rr_multi_interface_exts) / sizeof(tru_usb_cdc_interface_ext_t),
#else
	.hs_cdc_interface_exts = NULL, .hs_cdc_interface_exts_num_entries = 0,
#endif
	.fs_cdc_interface_exts = (tru_usb_cdc_interface_ext_t *)cdcacm_rr_multi_interface_exts, .fs_cdc_interface_exts_num_entries = sizeof(cdcacm_rr_multi_interface_exts) / sizeof(tru_usb_cdc_interface_ext_t),
	.ls_cdc_interface_exts = (tru_usb_cdc_interface_ext_t *)cdcacm_rr_multi_interface_exts, .ls_cdc_interface_exts_num_entries = sizeof(cdcacm_rr_multi_interface_exts) / sizeof(tru_usb_cdc_interface_ext_t),
};

tru_usb_cdc_pd_info_t *get_cdcacm_rr_multi_pd_info(void){
	return (tru_usb_cdc_pd_info_t *)&cdcacm_rr_multi_pd_info;
}

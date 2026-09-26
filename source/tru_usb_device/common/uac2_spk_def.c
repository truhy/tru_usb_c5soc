#include "uac2_spk_def.h"
#include "usb/dclass/tru_usb_iad_def.h"
#include "tru_iom.h"

// ==============================================
// Class specific interface extension descriptors
// ==============================================

// ==============================================================
// UAC 2.0 class interface extension structures for Audio Control
// ==============================================================

tru_usb_uac2_related_itf_t uac2_spk_audiocontrol_itfs_1_0_0[] = {
	{ .itf_num = UAC2_SPK_AUDCTL_ITF_NUM }
};
tru_usb_uac2_related_itf_t uac2_spk_audiostream_itfs_1_0_0[] = {
	{ .itf_num = UAC2_SPK_AUDOUT_ITF_NUM }
};

// Clock source sampling frequencies
uint32_t uac2_spk_clk_frq_cur_1_0_0[] = {
	44100,  // Default
};
uac2_spk_clk_frq_range_t uac2_spk_clk_frq_range_1_0_0 = {
	.num_subranges = UAC2_SPK_AUDOUT_NUM_SMP_FRQ,
	.range = UAC2_SPK_AUDOUT_SMP_FRQ_RANGE
};
tru_usb_uac2_clk_frq_t uac2_spk_clk_frq_1_0_0[] = {
	{ .entity_id = UAC2_SPK_CLK_SRC_UNIT_ID, .channel_num = 0, .cur = &uac2_spk_clk_frq_cur_1_0_0[0], .range = &uac2_spk_clk_frq_range_1_0_0 },
};

// Clock selector current pin
uint8_t uac2_spk_clk_sel_cur_1_0_0[] = {
	0x01,
};
tru_usb_uac2_clk_sel_t uac2_spk_clk_sel_1_0_0[] = {
	{ .entity_id = UAC2_SPK_CLK_SEL_UNIT_ID, .channel_num = 0, .cur = &uac2_spk_clk_sel_cur_1_0_0[0] },
};

#if UAC2_SPK_COPYPROTECT_CONTROL != TRU_USB_UAC2_CONTROL_NA
	uint8_t uac2_spk_copyprotect_cur_1_0_0[] = {
		0x00,
		0x00,
	};
	tru_usb_uac2_copyprotect_t uac2_spk_copyprotects_1_0_0[] = {
		{ .entity_id = UAC2_SPK_ITE_UNIT_ID, .cur = &uac2_spk_copyprotect_cur_1_0_0[0] },
		{ .entity_id = UAC2_SPK_OTE_UNIT_ID, .cur = &uac2_spk_copyprotect_cur_1_0_0[1] },
	};
#endif

#if UAC2_SPK_MUTE_CONTROL != TRU_USB_UAC2_CONTROL_NA
	// Array of all available Mute Controls in a unit.  Index is the channel number
	uint8_t uac2_spk_mute_cur_1_0_0[] = {
		0x00,
		0x00,
		0x00,
	};
	tru_usb_uac2_mute_t uac2_spk_mutes_1_0_0[] = {
		{ .entity_id = UAC2_SPK_FE_UNIT_ID, .channel_num = 0, .cur = &uac2_spk_mute_cur_1_0_0[0] },
		{ .entity_id = UAC2_SPK_FE_UNIT_ID, .channel_num = 1, .cur = &uac2_spk_mute_cur_1_0_0[1] },
		{ .entity_id = UAC2_SPK_FE_UNIT_ID, .channel_num = 2, .cur = &uac2_spk_mute_cur_1_0_0[2] },
	};
#endif

#if UAC2_SPK_VOLUME_CONTROL != TRU_USB_UAC2_CONTROL_NA
	uint16_t uac2_spk_volume_cur_1_0_0[] = {
		0x0000,
		0x0000,
		0x0000,
	};
	uint16_t uac2_spk_volume_min_1_0_0[] = {
		0x8000,
		0x8000,
		0x8000,
	};
	uint16_t uac2_spk_volume_max_1_0_0[] = {
		0x7fff,
		0x7fff,
		0x7fff,
	};
	uint16_t uac2_spk_volume_res_1_0_0[] = {
		0x0001,
		0x0001,
		0x0001,
	};
	tru_usb_uac2_volume_t volumes_1_0_0[] = {
		{ .entity_id = UAC2_SPK_FE_UNIT_ID, .channel_num = 0, .cur = &uac2_spk_volume_cur_1_0_0[0], .min = &uac2_spk_volume_min_1_0_0[0], .max = &uac2_spk_volume_max_1_0_0[0], .res = &uac2_spk_volume_res_1_0_0[0] },
		{ .entity_id = UAC2_SPK_FE_UNIT_ID, .channel_num = 1, .cur = &uac2_spk_volume_cur_1_0_0[1], .min = &uac2_spk_volume_min_1_0_0[1], .max = &uac2_spk_volume_max_1_0_0[1], .res = &uac2_spk_volume_res_1_0_0[1] },
		{ .entity_id = UAC2_SPK_FE_UNIT_ID, .channel_num = 2, .cur = &uac2_spk_volume_cur_1_0_0[2], .min = &uac2_spk_volume_min_1_0_0[2], .max = &uac2_spk_volume_max_1_0_0[2], .res = &uac2_spk_volume_res_1_0_0[2] },
	};
#endif

// =================================================================================================
// UAC 2.0 class interface extensions array of all configurations, interfaces and alternate settings
// =================================================================================================

// Note, for convenience we treat the alternate setting number as a separate interface, but the USB specification considers the alternate
// settings as a single interface, so also sharing the same user settings.  We can apply the sharing of user settings by simply making them
// point to the same structure(s).

// Each entry starts with the Configuration number, Interface number, Alternate setting number
const tru_usb_uac2_interface_ext_t uac2_spk_interface_exts[] = {
	// Audio Control class interface extensions
	{
		.ext_hdr = { .config_num = 1, .interface_num = 0, .alt_setting_num = 0 },
		.is_audio_control = true,
		.related_itfs = uac2_spk_audiostream_itfs_1_0_0, .num_related_itfs = sizeof(uac2_spk_audiostream_itfs_1_0_0) / sizeof(tru_usb_uac2_related_itf_t),
		.clk_frqs = uac2_spk_clk_frq_1_0_0, .num_clk_frqs = sizeof(uac2_spk_clk_frq_1_0_0) / sizeof(tru_usb_uac2_clk_frq_t),
		.clk_sels = uac2_spk_clk_sel_1_0_0, .num_clk_sels = sizeof(uac2_spk_clk_sel_1_0_0) / sizeof(tru_usb_uac2_clk_sel_t),
		#if UAC2_SPK_COPYPROTECT_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.copyprotects = uac2_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac2_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac2_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC2_SPK_MUTE_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.mutes = uac2_spk_mutes_1_0_0, .num_mutes = sizeof(uac2_spk_mutes_1_0_0) / sizeof(tru_usb_uac2_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC2_SPK_VOLUME_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.volumes = volumes_1_0_0, .num_volumes = sizeof(volumes_1_0_0) / sizeof(tru_usb_uac2_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = 0, .subslot_size = 0, .bit_resolution = 0 },
	},

	// Audio Streaming class interface extensions for zero bandwidth
	{
		.ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 0 },
		.is_audio_control = false,
		.related_itfs = uac2_spk_audiocontrol_itfs_1_0_0, .num_related_itfs = sizeof(uac2_spk_audiocontrol_itfs_1_0_0) / sizeof(tru_usb_uac2_related_itf_t),
		.clk_frqs = uac2_spk_clk_frq_1_0_0, .num_clk_frqs = sizeof(uac2_spk_clk_frq_1_0_0) / sizeof(tru_usb_uac2_clk_frq_t),
		.clk_sels = uac2_spk_clk_sel_1_0_0, .num_clk_sels = sizeof(uac2_spk_clk_sel_1_0_0) / sizeof(tru_usb_uac2_clk_sel_t),
		#if UAC2_SPK_COPYPROTECT_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.copyprotects = uac2_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac2_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac2_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC2_SPK_MUTE_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.mutes = uac2_spk_mutes_1_0_0, .num_mutes = sizeof(uac2_spk_mutes_1_0_0) / sizeof(tru_usb_uac2_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC2_SPK_VOLUME_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.volumes = volumes_1_0_0, .num_volumes = sizeof(volumes_1_0_0) / sizeof(tru_usb_uac2_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = 0, .subslot_size = 0, .bit_resolution = 0 },
	},

	// Audio Streaming class interface extensions for 16bit
	{
		.ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 1 },
		.is_audio_control = false,
		.related_itfs = uac2_spk_audiocontrol_itfs_1_0_0, .num_related_itfs = sizeof(uac2_spk_audiocontrol_itfs_1_0_0) / sizeof(tru_usb_uac2_related_itf_t),
		.clk_frqs = uac2_spk_clk_frq_1_0_0, .num_clk_frqs = sizeof(uac2_spk_clk_frq_1_0_0) / sizeof(tru_usb_uac2_clk_frq_t),
		.clk_sels = uac2_spk_clk_sel_1_0_0, .num_clk_sels = sizeof(uac2_spk_clk_sel_1_0_0) / sizeof(tru_usb_uac2_clk_sel_t),
		#if UAC2_SPK_COPYPROTECT_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.copyprotects = uac2_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac2_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac2_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC2_SPK_MUTE_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.mutes = uac2_spk_mutes_1_0_0, .num_mutes = sizeof(uac2_spk_mutes_1_0_0) / sizeof(tru_usb_uac2_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC2_SPK_VOLUME_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.volumes = volumes_1_0_0, .num_volumes = sizeof(volumes_1_0_0) / sizeof(tru_usb_uac2_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = UAC2_SPK_SMP_NUM_CH_16B, .subslot_size = UAC2_SPK_SMP_RES_16B / 8, .bit_resolution = UAC2_SPK_SMP_RES_16B },
	},

	// Audio Streaming class interface extensions for 24bit
	{
		.ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 2 },
		.is_audio_control = false,
		.related_itfs = uac2_spk_audiocontrol_itfs_1_0_0, .num_related_itfs = sizeof(uac2_spk_audiocontrol_itfs_1_0_0) / sizeof(tru_usb_uac2_related_itf_t),
		.clk_frqs = uac2_spk_clk_frq_1_0_0, .num_clk_frqs = sizeof(uac2_spk_clk_frq_1_0_0) / sizeof(tru_usb_uac2_clk_frq_t),
		.clk_sels = uac2_spk_clk_sel_1_0_0, .num_clk_sels = sizeof(uac2_spk_clk_sel_1_0_0) / sizeof(tru_usb_uac2_clk_sel_t),
		#if UAC2_SPK_COPYPROTECT_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.copyprotects = uac2_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac2_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac2_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC2_SPK_MUTE_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.mutes = uac2_spk_mutes_1_0_0, .num_mutes = sizeof(uac2_spk_mutes_1_0_0) / sizeof(tru_usb_uac2_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC2_SPK_VOLUME_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.volumes = volumes_1_0_0, .num_volumes = sizeof(volumes_1_0_0) / sizeof(tru_usb_uac2_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = UAC2_SPK_SMP_NUM_CH_24B, .subslot_size = UAC2_SPK_SMP_RES_24B / 8, .bit_resolution = UAC2_SPK_SMP_RES_24B },
	},

	// Audio Streaming class interface extensions for 32bit
	{
		.ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 3 },
		.is_audio_control = false,
		.related_itfs = uac2_spk_audiocontrol_itfs_1_0_0, .num_related_itfs = sizeof(uac2_spk_audiocontrol_itfs_1_0_0) / sizeof(tru_usb_uac2_related_itf_t),
		.clk_frqs = uac2_spk_clk_frq_1_0_0, .num_clk_frqs = sizeof(uac2_spk_clk_frq_1_0_0) / sizeof(tru_usb_uac2_clk_frq_t),
		.clk_sels = uac2_spk_clk_sel_1_0_0, .num_clk_sels = sizeof(uac2_spk_clk_sel_1_0_0) / sizeof(tru_usb_uac2_clk_sel_t),
		#if UAC2_SPK_COPYPROTECT_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.copyprotects = uac2_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac2_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac2_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC2_SPK_MUTE_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.mutes = uac2_spk_mutes_1_0_0, .num_mutes = sizeof(uac2_spk_mutes_1_0_0) / sizeof(tru_usb_uac2_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC2_SPK_VOLUME_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.volumes = volumes_1_0_0, .num_volumes = sizeof(volumes_1_0_0) / sizeof(tru_usb_uac2_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = UAC2_SPK_SMP_NUM_CH_32B, .subslot_size = UAC2_SPK_SMP_RES_32B / 8, .bit_resolution = UAC2_SPK_SMP_RES_32B },
	},
};

// ============================================
// UAC 2.0 class endpoint extensions structures
// ============================================

#if UAC2_SPK_PITCH_CONTROL != TRU_USB_UAC2_CONTROL_NA
	tru_usb_uac2_pitch_t uac2_spk_pitch_1 = {
		.cur = 0
	};
#endif

// ============================================================================
// UAC 2.0 class endpoint extensions array for the currently selected interface
// ============================================================================

tru_usb_uac2_ep_ext_t uac2_spk_ep_exts[] = {
	{
		.ep_addr = UAC2_SPK_AUDOUT_EPADR,
		#if UAC2_SPK_PITCH_CONTROL != TRU_USB_UAC2_CONTROL_NA
			.pitch = &uac2_spk_pitch_1,
		#else
			.pitch = NULL,
		#endif
	},
};

// ==========================
// Low speed mode descriptors
// ==========================

// Low speed does not support Isochronous Transfer type, therefore this speed is unsupported by this class

// ===========================
// Full speed mode descriptors
// ===========================

// =========================
// Configuration descriptors
// =========================

// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t clock_id;
	uint8_t num_in_pins;
	uint8_t c_source_id[1];
	tru_usb_uac2_clk_sel_controls_t controls;
	uint8_t clock_sel;
}uac2_spk_fs_config1_clock_sel_desc_t;

// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t unit_id;
	uint8_t source_id;
	tru_usb_uac2_fu_controls_t ma_controls[UAC2_SPK_AUDOUT_NUM_CH + 1];
	uint8_t feature;
}uac2_spk_fs_config1_fu_desc_t;

// UAC configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t                    config_0;
	tru_usb_iad_desc_t                       iad_0;
	tru_usb_interface_desc_t                 ac_interface_0;
	tru_usb_uac2_ac_itf_hdr_desc_t           ac_interface_header_0;
	tru_usb_uac2_clock_source_desc_t         ac_clock_source1_0;
	uac2_spk_fs_config1_clock_sel_desc_t     ac_clock_sel1_0;
	tru_usb_uac2_input_terminal_desc_t       ac_input_terminal1_0;
	uac2_spk_fs_config1_fu_desc_t            ac_feature_unit1_0;
	tru_usb_uac2_output_terminal_desc_t      ac_output_terminal1_0;
	tru_usb_interface_desc_t                 as_interface_silence_0;
#if UAC2_SPK_SMP_RES_16B_ENABLE
	tru_usb_interface_desc_t                 as_interface_16b_0;
	tru_usb_uac2_as_cls_itf_desc_t           as_cls_interface_16b_0;
	tru_usb_uac2_af_type1_desc_t             af_type_16b_0;
	tru_usb_ep_desc_t                        as_std_data_ep_16b_0;
	tru_usb_uac2_as_cls_iso_ep_desc_t        as_cls_data_ep_16b_0;
	#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_ep_desc_t                        as_std_fb_ep_16b_0;
	#endif
#endif
#if UAC2_SPK_SMP_RES_24B_ENABLE
	tru_usb_interface_desc_t                 as_interface_24b_0;
	tru_usb_uac2_as_cls_itf_desc_t           as_cls_interface_24b_0;
	tru_usb_uac2_af_type1_desc_t             af_type_24b_0;
	tru_usb_ep_desc_t                        as_std_data_ep_24b_0;
	tru_usb_uac2_as_cls_iso_ep_desc_t        as_cls_data_ep_24b_0;
	#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_ep_desc_t                        as_std_fb_ep_24b_0;
	#endif
#endif
#if UAC2_SPK_SMP_RES_32B_ENABLE
	tru_usb_interface_desc_t                 as_interface_32b_0;
	tru_usb_uac2_as_cls_itf_desc_t           as_cls_interface_32b_0;
	tru_usb_uac2_af_type1_desc_t             af_type_32b_0;
	tru_usb_ep_desc_t                        as_std_data_ep_32b_0;
	tru_usb_uac2_as_cls_iso_ep_desc_t        as_cls_data_ep_32b_0;
	#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_ep_desc_t                        as_std_fb_ep_32b_0;
	#endif
#endif
}uac2_spk_fs_config1_desc_t;

// UAC configuration 1
const uac2_spk_fs_config1_desc_t uac2_spk_fs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(uac2_spk_fs_config1_desc_t),
		.num_interfaces = 2,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED
	},

	// IAD descriptor
	.iad_0 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = 0,
		.interface_count = 2,
		.function_class = TRU_USB_UAC2_ITF_CLASS,
		.function_subclass = TRU_USB_UAC2_ITF_SUBCLASS_UNDEFINED,
		.function_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.function = 0
	},

	// Interface descriptor for the Audio Control Interface
	.ac_interface_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC2_SPK_AUDCTL_ITF_NUM,
		.alt_setting_num = 0,
		.num_endpoints = 0,
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOCONTROL,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},

	// Class-Specific AC (AudioControl) Interface Header Descriptor
	.ac_interface_header_0 = {
		.length = sizeof(tru_usb_uac2_ac_itf_hdr_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_HEADER,
		.adc = 0x0200,
		.category = TRU_USB_UAC2_FUNC_CAT_DESKTOP_SPEAKER,
		.total_length =
			sizeof(tru_usb_uac2_ac_itf_hdr_desc_t) +
			sizeof(tru_usb_uac2_clock_source_desc_t) +
			sizeof(uac2_spk_fs_config1_clock_sel_desc_t) +
			sizeof(tru_usb_uac2_input_terminal_desc_t) +
			sizeof(uac2_spk_fs_config1_fu_desc_t) +
			sizeof(tru_usb_uac2_output_terminal_desc_t),
		.controls = {
			.bits.latency = TRU_USB_UAC2_CONTROL_NA,
			.bits.res2_7 = 0
		}
	},

	// Clock Source Descriptor
	.ac_clock_source1_0 = {
		.length = sizeof(tru_usb_uac2_clock_source_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_CLOCK_SOURCE,
		.clock_id = UAC2_SPK_CLK_SRC_UNIT_ID,
		.attributes = {
			.bits.clock_type = TRU_USB_UAC2_CLOCK_SOURCE_ATR_INT_PROG,
			.bits.sync_to_sof = 0,
			.bits.res3_7 = 0
		},
		.controls = {
			.bits.clock_freq = TRU_USB_UAC2_CONTROL_RW,
			.bits.clock_validity = TRU_USB_UAC2_CONTROL_NA,
			.bits.res4_7 = 0
		},
		.assoc_terminal = 0,
		.clock_source = 0
	},

	// Clock Selector Descriptor
	.ac_clock_sel1_0 = {
		.length = sizeof(uac2_spk_fs_config1_clock_sel_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_CLOCK_SELECTOR,
		.clock_id = UAC2_SPK_CLK_SEL_UNIT_ID,
		.num_in_pins = 1,
		.c_source_id = { UAC2_SPK_CLK_SRC_UNIT_ID },
		.controls = {
			.bits.clock_sel = TRU_USB_UAC2_CONTROL_RW,
			.bits.res2_7 = 0
		},
		.clock_sel = 0
	},

	// Input Terminal Descriptor
	.ac_input_terminal1_0 = {
		.length = sizeof(tru_usb_uac2_input_terminal_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_INPUT_TERMINAL,
		.terminal_id = UAC2_SPK_ITE_UNIT_ID,
		.terminal_type = TRU_USB_UAC2_TERMT_USB_STREAMING,
		.assoc_terminal = 0,
		.c_source_id = UAC2_SPK_CLK_SEL_UNIT_ID,
		//.c_source_id = UAC2_SPK_CLK_SRC_UNIT_ID,
		.num_channels = UAC2_SPK_AUDOUT_NUM_CH,
		.channel_config = TRU_USB_UAC2_CHCFG_FL | TRU_USB_UAC2_CHCFG_FR,
		.channel_names = 0,
		.controls = {
			.bits.copy_protect = UAC2_SPK_COPYPROTECT_CONTROL,
			.bits.connector = TRU_USB_UAC2_CONTROL_NA,
			.bits.overload = TRU_USB_UAC2_CONTROL_NA,
			.bits.cluster = TRU_USB_UAC2_CONTROL_NA,
			.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
			.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
			.bits.res12_15 = TRU_USB_UAC2_CONTROL_NA
		},
		.terminal = 0
	},
	
	// Feature Unit Descriptor
	.ac_feature_unit1_0 = {
		.length = sizeof(uac2_spk_fs_config1_fu_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_FEATURE_UNIT,
		.unit_id = UAC2_SPK_FE_UNIT_ID,
		.source_id = UAC2_SPK_ITE_UNIT_ID,
		.ma_controls = {
			{
				.bits.mute = UAC2_SPK_MUTE_CONTROL,
				.bits.volume = UAC2_SPK_VOLUME_CONTROL,
				.bits.bass = TRU_USB_UAC2_CONTROL_NA,
				.bits.mid = TRU_USB_UAC2_CONTROL_NA,
				.bits.treble = TRU_USB_UAC2_CONTROL_NA,
				.bits.equalizer = TRU_USB_UAC2_CONTROL_NA,
				.bits.agc = TRU_USB_UAC2_CONTROL_NA,
				.bits.delay = TRU_USB_UAC2_CONTROL_NA,
				.bits.bass_boost = TRU_USB_UAC2_CONTROL_NA,
				.bits.loudness = TRU_USB_UAC2_CONTROL_NA,
				.bits.input_gain = TRU_USB_UAC2_CONTROL_NA,
				.bits.input_gain_pad = TRU_USB_UAC2_CONTROL_NA,
				.bits.phase_inverter = TRU_USB_UAC2_CONTROL_NA,
				.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
				.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
				.bits.res30_31 = TRU_USB_UAC2_CONTROL_NA,
			},
			{
				.bits.mute = UAC2_SPK_MUTE_CONTROL,
				.bits.volume = UAC2_SPK_VOLUME_CONTROL,
				.bits.bass = TRU_USB_UAC2_CONTROL_NA,
				.bits.mid = TRU_USB_UAC2_CONTROL_NA,
				.bits.treble = TRU_USB_UAC2_CONTROL_NA,
				.bits.equalizer = TRU_USB_UAC2_CONTROL_NA,
				.bits.agc = TRU_USB_UAC2_CONTROL_NA,
				.bits.delay = TRU_USB_UAC2_CONTROL_NA,
				.bits.bass_boost = TRU_USB_UAC2_CONTROL_NA,
				.bits.loudness = TRU_USB_UAC2_CONTROL_NA,
				.bits.input_gain = TRU_USB_UAC2_CONTROL_NA,
				.bits.input_gain_pad = TRU_USB_UAC2_CONTROL_NA,
				.bits.phase_inverter = TRU_USB_UAC2_CONTROL_NA,
				.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
				.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
				.bits.res30_31 = TRU_USB_UAC2_CONTROL_NA,
			},
			{
				.bits.mute = UAC2_SPK_MUTE_CONTROL,
				.bits.volume = UAC2_SPK_VOLUME_CONTROL,
				.bits.bass = TRU_USB_UAC2_CONTROL_NA,
				.bits.mid = TRU_USB_UAC2_CONTROL_NA,
				.bits.treble = TRU_USB_UAC2_CONTROL_NA,
				.bits.equalizer = TRU_USB_UAC2_CONTROL_NA,
				.bits.agc = TRU_USB_UAC2_CONTROL_NA,
				.bits.delay = TRU_USB_UAC2_CONTROL_NA,
				.bits.bass_boost = TRU_USB_UAC2_CONTROL_NA,
				.bits.loudness = TRU_USB_UAC2_CONTROL_NA,
				.bits.input_gain = TRU_USB_UAC2_CONTROL_NA,
				.bits.input_gain_pad = TRU_USB_UAC2_CONTROL_NA,
				.bits.phase_inverter = TRU_USB_UAC2_CONTROL_NA,
				.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
				.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
				.bits.res30_31 = TRU_USB_UAC2_CONTROL_NA,
			},
		},
		.feature = 0
	},
	
	// Output Terminal Descriptor
	.ac_output_terminal1_0 = {
		.length = sizeof(tru_usb_uac2_output_terminal_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_OUTPUT_TERMINAL,
		.terminal_id = UAC2_SPK_OTE_UNIT_ID,
		.terminal_type = TRU_USB_UAC2_TERMT_OUTPUT_SPEAKER,
		.assoc_terminal = 0,
		.source_id = UAC2_SPK_FE_UNIT_ID,
		.c_source_id = UAC2_SPK_CLK_SEL_UNIT_ID,
		//.c_source_id = UAC2_SPK_CLK_SRC_UNIT_ID,
		.controls = {
			.bits.copy_protect = UAC2_SPK_COPYPROTECT_CONTROL,
			.bits.connector = TRU_USB_UAC2_CONTROL_NA,
			.bits.overload = TRU_USB_UAC2_CONTROL_NA,
			.bits.cluster = TRU_USB_UAC2_CONTROL_NA,
			.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
			.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
			.bits.res12_15 = TRU_USB_UAC2_CONTROL_NA
		},
		.terminal = 0
	},
	
	// Interface descriptor - default zero bandwidth for when audio is not used, e.g. in the stop state
	.as_interface_silence_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 1,
		.alt_setting_num = 0,
		.num_endpoints = 0,
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},

#if UAC2_SPK_SMP_RES_16B_ENABLE
	// Interface descriptor - for 16-bit audio stream
	.as_interface_16b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC2_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC2_SPK_ALT_NUM_16B,
		#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_16b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC2_SPK_ITE_UNIT_ID,
		.controls = {
			.bits.active_alt_setting = TRU_USB_UAC2_CONTROL_R,
			.bits.valid_alt_settings = TRU_USB_UAC2_CONTROL_R,
			.bits.res4_7 = 0
		},
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.formats = TRU_USB_UAC2_AF_TYPE1_PCM,
		.num_channels = UAC2_SPK_SMP_NUM_CH_16B,
		.channel_config = TRU_USB_UAC2_CHCFG_FL | TRU_USB_UAC2_CHCFG_FR,
		.channel_names = 0
	},

	// Type I Format Type Descriptor
	.af_type_16b_0 = {
		.length = sizeof(tru_usb_uac2_af_type1_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.subslot = UAC2_SPK_SMP_FRAME_16B,
		.bit_resolution = UAC2_SPK_SMP_RES_16B
	},

	// Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_16b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC2_SPK_AUDOUT_EPSYC_FS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_EPMPS_FS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_EPINT_FS
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_16b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.res0_6 = 0,
			.bits.max_packets_only = 0
		},
		.controls = {
			.bits.pitch = UAC2_SPK_PITCH_CONTROL,
			.bits.data_overrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.data_underrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.res6_7 = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_16b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_FB_EPMPS_FS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_FB_EPINT_FS
	},
#endif
#endif


#if UAC2_SPK_SMP_RES_24B_ENABLE
	// Interface descriptor - for 24-bit audio stream
	.as_interface_24b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC2_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC2_SPK_ALT_NUM_24B,
		#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_24b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC2_SPK_ITE_UNIT_ID,
		.controls = {
			.bits.active_alt_setting = TRU_USB_UAC2_CONTROL_R,
			.bits.valid_alt_settings = TRU_USB_UAC2_CONTROL_R,
			.bits.res4_7 = 0
		},
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.formats = TRU_USB_UAC2_AF_TYPE1_PCM,
		.num_channels = UAC2_SPK_SMP_NUM_CH_24B,
		.channel_config = TRU_USB_UAC2_CHCFG_FL | TRU_USB_UAC2_CHCFG_FR,
		.channel_names = 0
	},

	// Type I Format Type Descriptor
	.af_type_24b_0 = {
		.length = sizeof(tru_usb_uac2_af_type1_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.subslot = UAC2_SPK_SMP_FRAME_24B,
		.bit_resolution = UAC2_SPK_SMP_RES_24B
	},

	// Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_24b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC2_SPK_AUDOUT_EPSYC_FS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_EPMPS_FS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_EPINT_FS
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_24b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.res0_6 = 0,
			.bits.max_packets_only = 0
		},
		.controls = {
			.bits.pitch = UAC2_SPK_PITCH_CONTROL,
			.bits.data_overrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.data_underrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.res6_7 = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_24b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_FB_EPMPS_FS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_FB_EPINT_FS
	},
#endif
#endif

#if UAC2_SPK_SMP_RES_32B_ENABLE
	// Interface descriptor - for 32-bit audio stream
	.as_interface_32b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC2_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC2_SPK_ALT_NUM_32B,
		#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_32b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC2_SPK_ITE_UNIT_ID,
		.controls = {
			.bits.active_alt_setting = TRU_USB_UAC2_CONTROL_R,
			.bits.valid_alt_settings = TRU_USB_UAC2_CONTROL_R,
			.bits.res4_7 = 0
		},
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.formats = TRU_USB_UAC2_AF_TYPE1_PCM,
		.num_channels = UAC2_SPK_SMP_NUM_CH_32B,
		.channel_config = TRU_USB_UAC2_CHCFG_FL | TRU_USB_UAC2_CHCFG_FR,
		.channel_names = 0
	},

	// Type I Format Type Descriptor
	.af_type_32b_0 = {
		.length = sizeof(tru_usb_uac2_af_type1_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.subslot = UAC2_SPK_SMP_FRAME_32B,
		.bit_resolution = UAC2_SPK_SMP_RES_32B
	},

	// Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_32b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC2_SPK_AUDOUT_EPSYC_FS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_EPMPS_FS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_EPINT_FS
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_32b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.res0_6 = 0,
			.bits.max_packets_only = 0
		},
		.controls = {
			.bits.pitch = UAC2_SPK_PITCH_CONTROL,
			.bits.data_overrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.data_underrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.res6_7 = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC2_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_32b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_FB_EPMPS_FS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_FB_EPINT_FS
	},
#endif
#endif
};

// Array of all configuration descriptor sets (pointers and sizes) for full speed mode
const tru_usb_config_desc_set_t uac2_spk_fs_config_descs[] = {
	{ .desc = (uint8_t *)&uac2_spk_fs_config1_desc, .size = sizeof(uac2_spk_fs_config1_desc) }
};

// Total number of configurations for full speed mode
#define UAC2_SPK_FS_NUM_OF_CONFIGS (sizeof(uac2_spk_fs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for full speed mode
const tru_usb_dev_desc_t uac2_spk_fs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = UAC2_SPK_USB_VER,
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,
	.vid = UAC2_SPK_VID,
	.pid = UAC2_SPK_PID,
	.product_ver = UAC2_SPK_VER,
	.manufacturer = 1,
	.product = 2,
	.serial = 3,
	.num_configs = UAC2_SPK_FS_NUM_OF_CONFIGS
};

#if UAC2_SPK_HS_DESC_ENABLE == 1

// ===========================
// High speed mode descriptors
// ===========================

// =========================
// Configuration descriptors
// =========================

// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t clock_id;
	uint8_t num_in_pins;
	uint8_t c_source_id[1];
	tru_usb_uac2_clk_sel_controls_t controls;
	uint8_t clock_sel;
}uac2_spk_hs_config1_clock_sel_desc_t;

// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t unit_id;
	uint8_t source_id;
	tru_usb_uac2_fu_controls_t ma_controls[UAC2_SPK_AUDOUT_NUM_CH + 1];
	uint8_t feature;
}uac2_spk_hs_config1_fu_desc_t;

// UAC configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t                    config_0;
	tru_usb_iad_desc_t                       iad_0;
	tru_usb_interface_desc_t                 ac_interface_0;
	tru_usb_uac2_ac_itf_hdr_desc_t           ac_interface_header_0;
	tru_usb_uac2_clock_source_desc_t         ac_clock_source1_0;
	uac2_spk_hs_config1_clock_sel_desc_t     ac_clock_sel1_0;
	tru_usb_uac2_input_terminal_desc_t       ac_input_terminal1_0;
	uac2_spk_hs_config1_fu_desc_t            ac_feature_unit1_0;
	tru_usb_uac2_output_terminal_desc_t      ac_output_terminal1_0;
	tru_usb_interface_desc_t                 as_interface_silence_0;
#if UAC2_SPK_SMP_RES_16B_ENABLE
	tru_usb_interface_desc_t                 as_interface_16b_0;
	tru_usb_uac2_as_cls_itf_desc_t           as_cls_interface_16b_0;
	tru_usb_uac2_af_type1_desc_t             af_type_16b_0;
	tru_usb_ep_desc_t                        as_std_data_ep_16b_0;
	tru_usb_uac2_as_cls_iso_ep_desc_t        as_cls_data_ep_16b_0;
	#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_ep_desc_t                        as_std_fb_ep_16b_0;
	#endif
#endif
#if UAC2_SPK_SMP_RES_24B_ENABLE
	tru_usb_interface_desc_t                 as_interface_24b_0;
	tru_usb_uac2_as_cls_itf_desc_t           as_cls_interface_24b_0;
	tru_usb_uac2_af_type1_desc_t             af_type_24b_0;
	tru_usb_ep_desc_t                        as_std_data_ep_24b_0;
	tru_usb_uac2_as_cls_iso_ep_desc_t        as_cls_data_ep_24b_0;
	#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_ep_desc_t                        as_std_fb_ep_24b_0;
	#endif
#endif
#if UAC2_SPK_SMP_RES_32B_ENABLE
	tru_usb_interface_desc_t                 as_interface_32b_0;
	tru_usb_uac2_as_cls_itf_desc_t           as_cls_interface_32b_0;
	tru_usb_uac2_af_type1_desc_t             af_type_32b_0;
	tru_usb_ep_desc_t                        as_std_data_ep_32b_0;
	tru_usb_uac2_as_cls_iso_ep_desc_t        as_cls_data_ep_32b_0;
	#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_ep_desc_t                        as_std_fb_ep_32b_0;
	#endif
#endif
}uac2_spk_hs_config1_desc_t;

// UAC configuration 1
const uac2_spk_hs_config1_desc_t uac2_spk_hs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(uac2_spk_hs_config1_desc_t),
		.num_interfaces = 2,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED
	},

	// IAD descriptor
	.iad_0 = {
		.length = sizeof(tru_usb_iad_desc_t),
		.desc_type = TRU_USB_IAD_DESC_TYPE,
		.first_interface = 0,
		.interface_count = 2,
		.function_class = TRU_USB_UAC2_ITF_CLASS,
		.function_subclass = TRU_USB_UAC2_ITF_SUBCLASS_UNDEFINED,
		.function_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.function = 0
	},

	// Interface descriptor for the Audio Control Interface
	.ac_interface_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC2_SPK_AUDCTL_ITF_NUM,
		.alt_setting_num = 0,
		.num_endpoints = 0,
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOCONTROL,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},

	// Class-Specific AC (AudioControl) Interface Header Descriptor
	.ac_interface_header_0 = {
		.length = sizeof(tru_usb_uac2_ac_itf_hdr_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_HEADER,
		.adc = 0x0200,
		.category = TRU_USB_UAC2_FUNC_CAT_DESKTOP_SPEAKER,
		.total_length =
			sizeof(tru_usb_uac2_ac_itf_hdr_desc_t) +
			sizeof(tru_usb_uac2_clock_source_desc_t) +
			sizeof(uac2_spk_hs_config1_clock_sel_desc_t) +
			sizeof(tru_usb_uac2_input_terminal_desc_t) +
			sizeof(uac2_spk_hs_config1_fu_desc_t) +
			sizeof(tru_usb_uac2_output_terminal_desc_t),
		.controls = {
			.bits.latency = TRU_USB_UAC2_CONTROL_NA,
			.bits.res2_7 = 0
		}
	},

	// Clock Source Descriptor
	.ac_clock_source1_0 = {
		.length = sizeof(tru_usb_uac2_clock_source_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_CLOCK_SOURCE,
		.clock_id = UAC2_SPK_CLK_SRC_UNIT_ID,
		.attributes = {
			.bits.clock_type = TRU_USB_UAC2_CLOCK_SOURCE_ATR_INT_PROG,
			.bits.sync_to_sof = 0,
			.bits.res3_7 = 0
		},
		.controls = {
			.bits.clock_freq = TRU_USB_UAC2_CONTROL_RW,
			.bits.clock_validity = TRU_USB_UAC2_CONTROL_NA,
			.bits.res4_7 = 0
		},
		.assoc_terminal = 0,
		.clock_source = 0
	},

	// Clock Selector Descriptor
	.ac_clock_sel1_0 = {
		.length = sizeof(uac2_spk_hs_config1_clock_sel_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_CLOCK_SELECTOR,
		.clock_id = UAC2_SPK_CLK_SEL_UNIT_ID,
		.num_in_pins = 1,
		.c_source_id = { UAC2_SPK_CLK_SRC_UNIT_ID },
		.controls = {
			.bits.clock_sel = TRU_USB_UAC2_CONTROL_RW,
			.bits.res2_7 = 0
		},
		.clock_sel = 0
	},

	// Input Terminal Descriptor
	.ac_input_terminal1_0 = {
		.length = sizeof(tru_usb_uac2_input_terminal_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_INPUT_TERMINAL,
		.terminal_id = UAC2_SPK_ITE_UNIT_ID,
		.terminal_type = TRU_USB_UAC2_TERMT_USB_STREAMING,
		.assoc_terminal = 0,
		.c_source_id = UAC2_SPK_CLK_SEL_UNIT_ID,
		.num_channels = UAC2_SPK_AUDOUT_NUM_CH,
		.channel_config = TRU_USB_UAC2_CHCFG_FL | TRU_USB_UAC2_CHCFG_FR,
		.channel_names = 0,
		.controls = {
			.bits.copy_protect = UAC2_SPK_COPYPROTECT_CONTROL,
			.bits.connector = TRU_USB_UAC2_CONTROL_NA,
			.bits.overload = TRU_USB_UAC2_CONTROL_NA,
			.bits.cluster = TRU_USB_UAC2_CONTROL_NA,
			.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
			.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
			.bits.res12_15 = TRU_USB_UAC2_CONTROL_NA
		},
		.terminal = 0
	},
	
	// Feature Unit Descriptor
	.ac_feature_unit1_0 = {
		.length = sizeof(uac2_spk_hs_config1_fu_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_FEATURE_UNIT,
		.unit_id = UAC2_SPK_FE_UNIT_ID,
		.source_id = UAC2_SPK_ITE_UNIT_ID,
		.ma_controls = {
				{
					.bits.mute = UAC2_SPK_MUTE_CONTROL,
					.bits.volume = UAC2_SPK_VOLUME_CONTROL,
					.bits.bass = TRU_USB_UAC2_CONTROL_NA,
					.bits.mid = TRU_USB_UAC2_CONTROL_NA,
					.bits.treble = TRU_USB_UAC2_CONTROL_NA,
					.bits.equalizer = TRU_USB_UAC2_CONTROL_NA,
					.bits.agc = TRU_USB_UAC2_CONTROL_NA,
					.bits.delay = TRU_USB_UAC2_CONTROL_NA,
					.bits.bass_boost = TRU_USB_UAC2_CONTROL_NA,
					.bits.loudness = TRU_USB_UAC2_CONTROL_NA,
					.bits.input_gain = TRU_USB_UAC2_CONTROL_NA,
					.bits.input_gain_pad = TRU_USB_UAC2_CONTROL_NA,
					.bits.phase_inverter = TRU_USB_UAC2_CONTROL_NA,
					.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
					.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
					.bits.res30_31 = TRU_USB_UAC2_CONTROL_NA,
				},
				{
					.bits.mute = UAC2_SPK_MUTE_CONTROL,
					.bits.volume = UAC2_SPK_VOLUME_CONTROL,
					.bits.bass = TRU_USB_UAC2_CONTROL_NA,
					.bits.mid = TRU_USB_UAC2_CONTROL_NA,
					.bits.treble = TRU_USB_UAC2_CONTROL_NA,
					.bits.equalizer = TRU_USB_UAC2_CONTROL_NA,
					.bits.agc = TRU_USB_UAC2_CONTROL_NA,
					.bits.delay = TRU_USB_UAC2_CONTROL_NA,
					.bits.bass_boost = TRU_USB_UAC2_CONTROL_NA,
					.bits.loudness = TRU_USB_UAC2_CONTROL_NA,
					.bits.input_gain = TRU_USB_UAC2_CONTROL_NA,
					.bits.input_gain_pad = TRU_USB_UAC2_CONTROL_NA,
					.bits.phase_inverter = TRU_USB_UAC2_CONTROL_NA,
					.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
					.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
					.bits.res30_31 = TRU_USB_UAC2_CONTROL_NA,
				},
				{
					.bits.mute = UAC2_SPK_MUTE_CONTROL,
					.bits.volume = UAC2_SPK_VOLUME_CONTROL,
					.bits.bass = TRU_USB_UAC2_CONTROL_NA,
					.bits.mid = TRU_USB_UAC2_CONTROL_NA,
					.bits.treble = TRU_USB_UAC2_CONTROL_NA,
					.bits.equalizer = TRU_USB_UAC2_CONTROL_NA,
					.bits.agc = TRU_USB_UAC2_CONTROL_NA,
					.bits.delay = TRU_USB_UAC2_CONTROL_NA,
					.bits.bass_boost = TRU_USB_UAC2_CONTROL_NA,
					.bits.loudness = TRU_USB_UAC2_CONTROL_NA,
					.bits.input_gain = TRU_USB_UAC2_CONTROL_NA,
					.bits.input_gain_pad = TRU_USB_UAC2_CONTROL_NA,
					.bits.phase_inverter = TRU_USB_UAC2_CONTROL_NA,
					.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
					.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
					.bits.res30_31 = TRU_USB_UAC2_CONTROL_NA,
				},
		},
		.feature = 0
	},
	
	// Output Terminal Descriptor
	.ac_output_terminal1_0 = {
		.length = sizeof(tru_usb_uac2_output_terminal_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AC_ITF_DESC_SUBTYPE_OUTPUT_TERMINAL,
		.terminal_id = UAC2_SPK_OTE_UNIT_ID,
		.terminal_type = TRU_USB_UAC2_TERMT_OUTPUT_SPEAKER,
		.assoc_terminal = 0,
		.source_id = UAC2_SPK_FE_UNIT_ID,
		.c_source_id = UAC2_SPK_CLK_SEL_UNIT_ID,
		.controls = {
			.bits.copy_protect = UAC2_SPK_COPYPROTECT_CONTROL,
			.bits.connector = TRU_USB_UAC2_CONTROL_NA,
			.bits.overload = TRU_USB_UAC2_CONTROL_NA,
			.bits.cluster = TRU_USB_UAC2_CONTROL_NA,
			.bits.underflow = TRU_USB_UAC2_CONTROL_NA,
			.bits.overflow = TRU_USB_UAC2_CONTROL_NA,
			.bits.res12_15 = TRU_USB_UAC2_CONTROL_NA
		},
		.terminal = 0
	},
	
	// Interface descriptor - default zero bandwidth for stop state
	.as_interface_silence_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 1,
		.alt_setting_num = 0,
		.num_endpoints = 0,
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},
	
#if UAC2_SPK_SMP_RES_16B_ENABLE
	// Interface descriptor - for 16-bit audio stream
	.as_interface_16b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC2_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC2_SPK_ALT_NUM_16B,
		#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},
	
	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_16b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC2_SPK_ITE_UNIT_ID,
		.controls = {
			.bits.active_alt_setting = TRU_USB_UAC2_CONTROL_R,
			.bits.valid_alt_settings = TRU_USB_UAC2_CONTROL_R,
			.bits.res4_7 = 0
		},
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.formats = TRU_USB_UAC2_AF_TYPE1_PCM,
		.num_channels = UAC2_SPK_SMP_NUM_CH_16B,
		.channel_config = TRU_USB_UAC2_CHCFG_FL | TRU_USB_UAC2_CHCFG_FR,
		.channel_names = 0
	},

	// Type I Format Type Descriptor
	.af_type_16b_0 = {
		.length = sizeof(tru_usb_uac2_af_type1_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.subslot = UAC2_SPK_SMP_FRAME_16B,
		.bit_resolution = UAC2_SPK_SMP_RES_16B
	},

	// Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_16b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC2_SPK_AUDOUT_EPSYC_HS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_EPMPS_HS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_EPINT_HS
	},
	
	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_16b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.res0_6 = 0,
			.bits.max_packets_only = 0
		},
		.controls = {
			.bits.pitch = UAC2_SPK_PITCH_CONTROL,
			.bits.data_overrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.data_underrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.res6_7 = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},


#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_16b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_FB_EPMPS_HS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_FB_EPINT_HS
	},
#endif
#endif

#if UAC2_SPK_SMP_RES_24B_ENABLE
	// Interface descriptor - for 24-bit audio stream
	.as_interface_24b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC2_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC2_SPK_ALT_NUM_24B,
		#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_24b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC2_SPK_ITE_UNIT_ID,
		.controls = {
			.bits.active_alt_setting = TRU_USB_UAC2_CONTROL_R,
			.bits.valid_alt_settings = TRU_USB_UAC2_CONTROL_R,
			.bits.res4_7 = 0
		},
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.formats = TRU_USB_UAC2_AF_TYPE1_PCM,
		.num_channels = UAC2_SPK_SMP_NUM_CH_24B,
		.channel_config = TRU_USB_UAC2_CHCFG_FL | TRU_USB_UAC2_CHCFG_FR,
		.channel_names = 0
	},

	// Type I Format Type Descriptor
	.af_type_24b_0 = {
		.length = sizeof(tru_usb_uac2_af_type1_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.subslot = UAC2_SPK_SMP_FRAME_24B,
		.bit_resolution = UAC2_SPK_SMP_RES_24B
	},

	// Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_24b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC2_SPK_AUDOUT_EPSYC_HS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_EPMPS_HS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_EPINT_HS
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_24b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.res0_6 = 0,
			.bits.max_packets_only = 0
		},
		.controls = {
			.bits.pitch = UAC2_SPK_PITCH_CONTROL,
			.bits.data_overrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.data_underrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.res6_7 = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_24b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_FB_EPMPS_HS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_FB_EPINT_HS
	},
#endif
#endif

#if UAC2_SPK_SMP_RES_32B_ENABLE
	// Interface descriptor - for 32-bit audio stream
	.as_interface_32b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC2_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC2_SPK_ALT_NUM_32B,
		#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC2_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC2_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC2_ITF_IP_VERSION_02_00,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_32b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC2_SPK_ITE_UNIT_ID,
		.controls = {
			.bits.active_alt_setting = TRU_USB_UAC2_CONTROL_R,
			.bits.valid_alt_settings = TRU_USB_UAC2_CONTROL_R,
			.bits.res4_7 = 0
		},
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.formats = TRU_USB_UAC2_AF_TYPE1_PCM,
		.num_channels = UAC2_SPK_SMP_NUM_CH_32B,
		.channel_config = TRU_USB_UAC2_CHCFG_FL | TRU_USB_UAC2_CHCFG_FR,
		.channel_names = 0
	},

	// Type I Format Type Descriptor
	.af_type_32b_0 = {
		.length = sizeof(tru_usb_uac2_af_type1_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC2_AF_TYPE1,
		.subslot = UAC2_SPK_SMP_FRAME_32B,
		.bit_resolution = UAC2_SPK_SMP_RES_32B
	},

	// Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_32b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC2_SPK_AUDOUT_EPSYC_HS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_EPMPS_HS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_EPINT_HS
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_32b_0 = {
		.length = sizeof(tru_usb_uac2_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC2_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC2_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.res0_6 = 0,
			.bits.max_packets_only = 0
		},
		.controls = {
			.bits.pitch = UAC2_SPK_PITCH_CONTROL,
			.bits.data_overrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.data_underrun = TRU_USB_UAC2_CONTROL_NA,
			.bits.res6_7 = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC2_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_32b_0 = {
		.length = sizeof(tru_usb_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC2_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0
		},
		.mps = {
			.bits.mps = UAC2_SPK_AUDOUT_FB_EPMPS_HS,
			.bits.add_trans = TRU_USB_EP_PERIODIC_ADD_TRANS_NONE,
			.bits.res13_15 = 0
		},
		.interval = UAC2_SPK_AUDOUT_FB_EPINT_HS
	},
#endif
#endif
};

// Array of all configuration descriptor sets (pointers and sizes) for high speed mode
const tru_usb_config_desc_set_t uac2_spk_hs_config_descs[] = {
	{ .desc = (uint8_t *)&uac2_spk_hs_config1_desc, .size = sizeof(uac2_spk_hs_config1_desc) }
};

// Total number of configurations for high speed mode
#define UAC2_SPK_HS_NUM_OF_CONFIGS (sizeof(uac2_spk_hs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for high speed mode
const tru_usb_dev_desc_t uac2_spk_hs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = UAC2_SPK_USB_VER,
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,
	.vid = UAC2_SPK_VID,
	.pid = UAC2_SPK_PID,
	.product_ver = UAC2_SPK_VER,
	.manufacturer = 1,
	.product = 2,
	.serial = 3,
	.num_configs = UAC2_SPK_HS_NUM_OF_CONFIGS
};

// Device qualifier descriptor for full speed mode (describes other speed, i.e. high speed mode)
const tru_usb_dev_qual_desc_t uac2_spk_fs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = UAC2_SPK_USB_VER,
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,
	.num_configs = UAC2_SPK_HS_NUM_OF_CONFIGS,
	.reserved = 0
};

// Device qualifier descriptor for high speed mode (describes other speed, i.e. full speed mode)
const tru_usb_dev_qual_desc_t uac2_spk_hs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = UAC2_SPK_USB_VER,
	.dev_class = TRU_USB_DEVICE_CLASS_MISC,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_MULTI,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_IAD,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,
	.num_configs = UAC2_SPK_FS_NUM_OF_CONFIGS,
	.reserved = 0
};

#endif

// ==================
// String descriptors
// ==================

// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t lang_id[1];
}uac2_spk_string_lang_ids_t;

// Supported language IDs string descriptor
const uac2_spk_string_lang_ids_t uac2_spk_lang_string_desc = {
	.length = sizeof(uac2_spk_lang_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.lang_id = { TRU_USB_LANG_ID_ENGLISH_US }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}uac2_spk_string_manuf_t;

// Manufacturer string descriptor
const uac2_spk_string_manuf_t uac2_spk_manuf_string_desc = {
	.length = sizeof(uac2_spk_manuf_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[10];
}uac2_spk_string_product_t;

// Product string descriptor
const uac2_spk_string_product_t uac2_spk_prod_string_desc = {
	.length = sizeof(uac2_spk_prod_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', 'U', 'A', 'C', '2', 'S', 'p', 'k' }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}uac2_spk_string_serial_t;

// Serial number string descriptor
const uac2_spk_string_serial_t uac2_spk_ser_string_desc = {
	.length = sizeof(uac2_spk_ser_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { '1', '2', '3' }
};

// An array of all the indexes & language IDs mapped to string descriptor pointers
// Note: this is made up and not in the USB specification but it is needed in practice
const tru_usb_string_desc_info_t uac2_spk_string_descs[] = {
	{ .index = 0, .lang_id = TRU_USB_LANG_ID_NONE,       .desc = (void *)&uac2_spk_lang_string_desc },
	{ .index = 1, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&uac2_spk_manuf_string_desc },
	{ .index = 2, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&uac2_spk_prod_string_desc },
	{ .index = 3, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&uac2_spk_ser_string_desc }
};

// ==========================================================================
// Final peripheral device descriptors (pointers to all structures above)
// ==========================================================================

// Common
tru_usb_pd_info_t uac2_spk_base_pd_info = {
#if UAC2_SPK_HS_DESC_ENABLE == 1
	.hs_dev_desc = (tru_usb_dev_desc_t *)&uac2_spk_hs_dev_desc,
#else
	.hs_dev_desc = NULL,
#endif
	.fs_dev_desc = (tru_usb_dev_desc_t *)&uac2_spk_fs_dev_desc,
	.ls_dev_desc = NULL,

#if UAC2_SPK_HS_DESC_ENABLE == 1
	.hs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&uac2_spk_hs_dev_qual_desc,
	.fs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&uac2_spk_fs_dev_qual_desc,
#else
	.hs_dev_qual_desc = NULL,
	.fs_dev_qual_desc = NULL,
#endif

#if UAC2_SPK_HS_DESC_ENABLE == 1
	.hs_config_descs = (tru_usb_config_desc_set_t *)uac2_spk_hs_config_descs, .hs_config_descs_num_entries = sizeof(uac2_spk_hs_config_descs) / sizeof(tru_usb_config_desc_set_t),
#else
	.hs_config_descs = NULL, .hs_config_descs_num_entries = 0,
#endif
	.fs_config_descs = (tru_usb_config_desc_set_t *)uac2_spk_fs_config_descs, .fs_config_descs_num_entries = sizeof(uac2_spk_fs_config_descs) / sizeof(tru_usb_config_desc_set_t),
	.ls_config_descs = NULL, .ls_config_descs_num_entries = 0,

	.string_descs = (tru_usb_string_desc_info_t *)uac2_spk_string_descs, .string_descs_num_entries = sizeof(uac2_spk_string_descs) / sizeof(tru_usb_string_desc_info_t)
};

// Common + class
tru_usb_uac2_pd_info_t uac2_spk_uac2_pd_info = {
	.pd = &uac2_spk_base_pd_info,

#if UAC2_SPK_HS_DESC_ENABLE == 1
	.hs_uac2_interface_exts = (tru_usb_uac2_interface_ext_t *)uac2_spk_interface_exts, .hs_uac2_interface_exts_num_entries = sizeof(uac2_spk_interface_exts) / sizeof(tru_usb_uac2_interface_ext_t),
#else
	.hs_uac2_interface_exts = NULL, .hs_uac2_interface_exts_num_entries = 0,
#endif
	.fs_uac2_interface_exts = (tru_usb_uac2_interface_ext_t *)uac2_spk_interface_exts, .fs_uac2_interface_exts_num_entries = sizeof(uac2_spk_interface_exts) / sizeof(tru_usb_uac2_interface_ext_t),
	.ls_uac2_interface_exts = NULL, .ls_uac2_interface_exts_num_entries = 0,

#if UAC2_SPK_HS_DESC_ENABLE == 1
	.hs_uac2_ep_exts = (tru_usb_uac2_ep_ext_t *)uac2_spk_ep_exts, .hs_uac2_ep_exts_num_entries = sizeof(uac2_spk_ep_exts) / sizeof(tru_usb_uac2_ep_ext_t),
#else
	.hs_uac2_ep_exts = NULL, .hs_uac2_ep_exts_num_entries = 0,
#endif
	.fs_uac2_ep_exts = (tru_usb_uac2_ep_ext_t *)uac2_spk_ep_exts, .fs_uac2_ep_exts_num_entries = sizeof(uac2_spk_ep_exts) / sizeof(tru_usb_uac2_ep_ext_t),
	.ls_uac2_ep_exts = (tru_usb_uac2_ep_ext_t *)uac2_spk_ep_exts, .ls_uac2_ep_exts_num_entries = sizeof(uac2_spk_ep_exts) / sizeof(tru_usb_uac2_ep_ext_t),
};

tru_usb_uac2_pd_info_t *get_uac2_spk_pd_info(void){
	return (tru_usb_uac2_pd_info_t *)&uac2_spk_uac2_pd_info;
}

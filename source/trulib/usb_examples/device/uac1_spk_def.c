#include "uac1_spk_def.h"
#include "tru_iom.h"

// ==============================================
// Class specific interface extension descriptors
// ==============================================

// ==============================================================
// UAC 1.0 class interface extension structures for Audio Control
// ==============================================================

tru_usb_uac_related_itf_t uac1_spk_audiocontrol_itfs_1_0_0[] = {
	{ .itf_num = UAC1_SPK_AUDCTL_ITF_NUM }
};
tru_usb_uac_related_itf_t uac1_spk_audiostream_itfs_1_0_0[] = {
	{ .itf_num = UAC1_SPK_AUDOUT_ITF_NUM }
};

#if UAC1_SPK_COPYPROTECT_CONTROL == 1
	uint8_t uac1_spk_copyprotect_cur_1_0_0[] = {
		0x00,
		0x00,
	};
	tru_usb_uac_copyprotect_t uac1_spk_copyprotects_1_0_0[] = {
		{ .entity_id = UAC1_SPK_ITE_UNIT_ID, .cur = &uac1_spk_copyprotect_cur_1_0_0[0] },
		{ .entity_id = UAC1_SPK_OTE_UNIT_ID, .cur = &uac1_spk_copyprotect_cur_1_0_0[1] },
	};
#endif

#if UAC1_SPK_MUTE_CONTROL == 1
	// Array of all available Mute Controls
	uint8_t uac1_spk_mute_cur_1_0_0[] = {
		0x00,
		0x00,
		0x00,
	};
	tru_usb_uac_mute_t uac1_spk_mutes_1_0_0[] = {
		{ .entity_id = UAC1_SPK_FE_UNIT_ID, .channel_num = 0xff, .cur = &uac1_spk_mute_cur_1_0_0[0] },
		{ .entity_id = UAC1_SPK_FE_UNIT_ID, .channel_num = 0, .cur = &uac1_spk_mute_cur_1_0_0[0] },
		{ .entity_id = UAC1_SPK_FE_UNIT_ID, .channel_num = 1, .cur = &uac1_spk_mute_cur_1_0_0[1] },
		{ .entity_id = UAC1_SPK_FE_UNIT_ID, .channel_num = 2, .cur = &uac1_spk_mute_cur_1_0_0[2] },
	};
#endif

#if UAC1_SPK_VOLUME_CONTROL == 1
	uint16_t uac1_spk_volume_cur_1_0_0[] = {
		0x0000,
		0x0000,
		0x0000,
	};
	uint16_t uac1_spk_volume_min_1_0_0[] = {
		0x8000,
		0x8000,
		0x8000,
	};
	uint16_t uac1_spk_volume_max_1_0_0[] = {
		0x7fff,
		0x7fff,
		0x7fff,
	};
	uint16_t uac1_spk_volume_res_1_0_0[] = {
		0x0001,
		0x0001,
		0x0001,
	};
	tru_usb_uac_volume_t uac1_spk_volumes_1_0_0[] = {
		{ .entity_id = UAC1_SPK_FE_UNIT_ID, .channel_num = 0xff, .cur = &uac1_spk_volume_cur_1_0_0[0], .min = &uac1_spk_volume_min_1_0_0[0], .max = &uac1_spk_volume_max_1_0_0[0], .res = &uac1_spk_volume_res_1_0_0[0] },
		{ .entity_id = UAC1_SPK_FE_UNIT_ID, .channel_num = 0, .cur = &uac1_spk_volume_cur_1_0_0[0], .min = &uac1_spk_volume_min_1_0_0[0], .max = &uac1_spk_volume_max_1_0_0[0], .res = &uac1_spk_volume_res_1_0_0[0] },
		{ .entity_id = UAC1_SPK_FE_UNIT_ID, .channel_num = 1, .cur = &uac1_spk_volume_cur_1_0_0[1], .min = &uac1_spk_volume_min_1_0_0[1], .max = &uac1_spk_volume_max_1_0_0[1], .res = &uac1_spk_volume_res_1_0_0[1] },
		{ .entity_id = UAC1_SPK_FE_UNIT_ID, .channel_num = 2, .cur = &uac1_spk_volume_cur_1_0_0[2], .min = &uac1_spk_volume_min_1_0_0[2], .max = &uac1_spk_volume_max_1_0_0[2], .res = &uac1_spk_volume_res_1_0_0[2] },
	};
#endif

// =================================================================================================
// UAC 1.0 class interface extensions array of all configurations, interfaces and alternate settings
// =================================================================================================

// Note, for convenience we treat the alternate setting number as a separate interface, but the USB specification considers the alternate
// settings as a single interface, so also sharing the same user settings.  We can apply the sharing of user settings by simply making them
// point to the same structure(s).

// Each entry starts with the Configuration number, Interface number, Alternate setting number
const tru_usb_uac_interface_ext_t uac1_spk_interface_exts[] = {
	// Audio Control class interface extensions
	{
		.ext_hdr = { .config_num = 1, .interface_num = 0, .alt_setting_num = 0 },
		.is_audio_control = true,
		.related_itfs = uac1_spk_audiostream_itfs_1_0_0, .num_related_itfs = sizeof(uac1_spk_audiostream_itfs_1_0_0) / sizeof(tru_usb_uac_related_itf_t),
		#if UAC1_SPK_COPYPROTECT_CONTROL == 1
			.copyprotects = uac1_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac1_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC1_SPK_MUTE_CONTROL == 1
			.mutes = uac1_spk_mutes_1_0_0, .num_mutes = sizeof(uac1_spk_mutes_1_0_0) / sizeof(tru_usb_uac_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC1_SPK_VOLUME_CONTROL == 1
			.volumes = uac1_spk_volumes_1_0_0, .num_volumes = sizeof(uac1_spk_volumes_1_0_0) / sizeof(tru_usb_uac_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = 0, .subframe_size = 0, .bit_resolution = 0 },
	},

	// Audio Streaming class interface extensions for zero bandwidth
	{
		.ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 0 },
		.is_audio_control = false,
		.related_itfs = uac1_spk_audiocontrol_itfs_1_0_0, .num_related_itfs = sizeof(uac1_spk_audiocontrol_itfs_1_0_0) / sizeof(tru_usb_uac_related_itf_t),
		#if UAC1_SPK_COPYPROTECT_CONTROL == 1
			.copyprotects = uac1_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac1_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC1_SPK_MUTE_CONTROL == 1
			.mutes = uac1_spk_mutes_1_0_0, .num_mutes = sizeof(uac1_spk_mutes_1_0_0) / sizeof(tru_usb_uac_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC1_SPK_VOLUME_CONTROL == 1
			.volumes = uac1_spk_volumes_1_0_0, .num_volumes = sizeof(uac1_spk_volumes_1_0_0) / sizeof(tru_usb_uac_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = 0, .subframe_size = 0, .bit_resolution = 0 },
	},

	// Audio Streaming class interface extensions for 16bit
	{
		.ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 1 },
		.is_audio_control = false,
		.related_itfs = uac1_spk_audiocontrol_itfs_1_0_0, .num_related_itfs = sizeof(uac1_spk_audiocontrol_itfs_1_0_0) / sizeof(tru_usb_uac_related_itf_t),
		#if UAC1_SPK_COPYPROTECT_CONTROL == 1
			.copyprotects = uac1_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac1_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC1_SPK_MUTE_CONTROL == 1
			.mutes = uac1_spk_mutes_1_0_0, .num_mutes = sizeof(uac1_spk_mutes_1_0_0) / sizeof(tru_usb_uac_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC1_SPK_VOLUME_CONTROL == 1
			.volumes = uac1_spk_volumes_1_0_0, .num_volumes = sizeof(uac1_spk_volumes_1_0_0) / sizeof(tru_usb_uac_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = UAC1_SPK_SMP_NUM_CH_16B, .subframe_size = UAC1_SPK_SMP_RES_16B / 8, .bit_resolution = UAC1_SPK_SMP_RES_16B },
	},

	// Audio Streaming class interface extensions for 24bit
	{
		.ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 2 },
		.is_audio_control = false,
		.related_itfs = uac1_spk_audiocontrol_itfs_1_0_0, .num_related_itfs = sizeof(uac1_spk_audiocontrol_itfs_1_0_0) / sizeof(tru_usb_uac_related_itf_t),
		#if UAC1_SPK_COPYPROTECT_CONTROL == 1
			.copyprotects = uac1_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac1_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC1_SPK_MUTE_CONTROL == 1
			.mutes = uac1_spk_mutes_1_0_0, .num_mutes = sizeof(uac1_spk_mutes_1_0_0) / sizeof(tru_usb_uac_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC1_SPK_VOLUME_CONTROL == 1
			.volumes = uac1_spk_volumes_1_0_0, .num_volumes = sizeof(uac1_spk_volumes_1_0_0) / sizeof(tru_usb_uac_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = UAC1_SPK_SMP_NUM_CH_24B, .subframe_size = UAC1_SPK_SMP_RES_24B / 8, .bit_resolution = UAC1_SPK_SMP_RES_24B },
	},

	// Audio Streaming class interface extensions for 32bit
	{
		.ext_hdr = { .config_num = 1, .interface_num = 1, .alt_setting_num = 3 },
		.is_audio_control = false,
		.related_itfs = uac1_spk_audiocontrol_itfs_1_0_0, .num_related_itfs = sizeof(uac1_spk_audiocontrol_itfs_1_0_0) / sizeof(tru_usb_uac_related_itf_t),
		#if UAC1_SPK_COPYPROTECT_CONTROL == 1
			.copyprotects = uac1_spk_copyprotects_1_0_0, .num_copyprotects = sizeof(uac1_spk_copyprotects_1_0_0) / sizeof(tru_usb_uac_copyprotect_t),
		#else
			.copyprotects = NULL, .num_copyprotects = 0,
		#endif
		#if UAC1_SPK_MUTE_CONTROL == 1
			.mutes = uac1_spk_mutes_1_0_0, .num_mutes = sizeof(uac1_spk_mutes_1_0_0) / sizeof(tru_usb_uac_mute_t),
		#else
			.mutes = NULL, .num_mutes = 0,
		#endif
		#if UAC1_SPK_VOLUME_CONTROL == 1
			.volumes = uac1_spk_volumes_1_0_0, .num_volumes = sizeof(uac1_spk_volumes_1_0_0) / sizeof(tru_usb_uac_volume_t),
		#else
			.volumes = NULL, .num_volumes = 0,
		#endif
		.af = { .num_channels = UAC1_SPK_SMP_NUM_CH_32B, .subframe_size = UAC1_SPK_SMP_RES_32B / 8, .bit_resolution = UAC1_SPK_SMP_RES_32B },
	},
};

// ============================================
// UAC 1.0 class endpoint extensions structures
// ============================================

#if UAC1_SPK_SMP_FRQ_CONTROL == 1
	tru_usb_uac_samp_freq_t uac1_spk_samp_freq_1 = {
		.cur = { B0(UAC1_SPK_SMP_FRQ_16B_1), B1(UAC1_SPK_SMP_FRQ_16B_1), B2(UAC1_SPK_SMP_FRQ_16B_1) },
		.min = { 0, 0, 0 },
		.max = { B0(UAC1_SPK_MAX_SMP_FRQ), B1(UAC1_SPK_MAX_SMP_FRQ), B2(UAC1_SPK_MAX_SMP_FRQ) },
		.res = { 1, 0, 0 },
	};
#endif

#if UAC1_SPK_PITCH_CONTROL == 1
	tru_usb_uac_pitch_t uac1_spk_pitch_1 = {
		.cur = 0
	};
#endif

// ============================================================================
// UAC 1.0 class endpoint extensions array for the currently selected interface
// ============================================================================

tru_usb_uac_ep_ext_t uac1_spk_ep_exts[] = {
	{
		.ep_addr = UAC1_SPK_AUDOUT_EPADR,
		#if UAC1_SPK_SMP_FRQ_CONTROL == 1
			.samp_freq = &uac1_spk_samp_freq_1,
		#else
			.samp_freq = NULL,
		#endif
		#if UAC1_SPK_PITCH_CONTROL == 1
			.pitch = &uac1_spk_pitch_1,
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
	uint16_t release_num;
	uint16_t total_length;
	uint8_t in_collection;
	uint8_t interface_num[1];
}uac1_spk_fs_config1_ac_itf_hdr_desc_t;

// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t unit_id;
	uint8_t source_id;
	uint8_t control_size;
	tru_usb_uac_fu_controls_uint16_t controls[UAC1_SPK_AUDOUT_NUM_CH + 1];
	uint8_t feature;
}uac1_spk_fs_config1_fu_desc_t;

#if UAC1_SPK_SMP_RES_16B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_16B > 0
// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t format_type;
	uint8_t num_channels;
	uint8_t subframe_size;
	uint8_t bit_resolution;
	uint8_t samp_freq_type;
	uint8_t samp_frequencies[3*UAC1_SPK_NUM_SMP_FRQ_16B];
}uac1_spk_fs_config1_af_type1_desc_16b_t;
#endif

#if UAC1_SPK_SMP_RES_24B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_24B > 0
// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t format_type;
	uint8_t num_channels;
	uint8_t subframe_size;
	uint8_t bit_resolution;
	uint8_t samp_freq_type;
	uint8_t samp_frequencies[3*UAC1_SPK_NUM_SMP_FRQ_24B];
}uac1_spk_fs_config1_af_type1_desc_24b_t;
#endif

#if UAC1_SPK_SMP_RES_32B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_32B > 0
// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t format_type;
	uint8_t num_channels;
	uint8_t subframe_size;
	uint8_t bit_resolution;
	uint8_t samp_freq_type;
	uint8_t samp_frequencies[3*UAC1_SPK_NUM_SMP_FRQ_32B];
}uac1_spk_fs_config1_af_type1_desc_32b_t;
#endif

// UAC configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t                       config_0;
	tru_usb_interface_desc_t                    ac_interface_0;
	uac1_spk_fs_config1_ac_itf_hdr_desc_t       ac_interface_header_0;
	tru_usb_uac_input_terminal_desc_t           ac_input_terminal1_0;
	uac1_spk_fs_config1_fu_desc_t               ac_feature_unit1_0;
	tru_usb_uac_output_terminal_desc_t          ac_output_terminal1_0;
	tru_usb_interface_desc_t                    as_interface_silence_0;
#if UAC1_SPK_SMP_RES_16B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_16B > 0
	tru_usb_interface_desc_t                    as_interface_16b_0;
	tru_usb_uac_as_cls_itf_desc_t               as_cls_interface_16b_0;
	uac1_spk_fs_config1_af_type1_desc_16b_t     af_type_16b_0;
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_data_ep_16b_0;
	tru_usb_uac_as_cls_iso_ep_desc_t            as_cls_data_ep_16b_0;
	#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_fb_ep_16b_0;
	#endif
#endif
#if UAC1_SPK_SMP_RES_24B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_24B > 0
	tru_usb_interface_desc_t                    as_interface_24b_0;
	tru_usb_uac_as_cls_itf_desc_t               as_cls_interface_24b_0;
	uac1_spk_fs_config1_af_type1_desc_24b_t     af_type_24b_0;
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_data_ep_24b_0;
	tru_usb_uac_as_cls_iso_ep_desc_t            as_cls_data_ep_24b_0;
	#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_fb_ep_24b_0;
	#endif
#endif
#if UAC1_SPK_SMP_RES_32B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_32B > 0
	tru_usb_interface_desc_t                    as_interface_32b_0;
	tru_usb_uac_as_cls_itf_desc_t               as_cls_interface_32b_0;
	uac1_spk_fs_config1_af_type1_desc_32b_t     af_type_32b_0;
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_data_ep_32b_0;
	tru_usb_uac_as_cls_iso_ep_desc_t            as_cls_data_ep_32b_0;
	#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_fb_ep_32b_0;
	#endif
#endif
}uac1_spk_fs_config1_desc_t;

// UAC configuration 1
const uac1_spk_fs_config1_desc_t uac1_spk_fs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(uac1_spk_fs_config1_desc_t),
		.num_interfaces = 2,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED
	},

	// Interface descriptor for the Audio Control Interface
	.ac_interface_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC1_SPK_AUDCTL_ITF_NUM,
		.alt_setting_num = 0,
		.num_endpoints = 0,
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOCONTROL,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},

	// Class-Specific AC (AudioControl) Interface Header Descriptor
	.ac_interface_header_0 = {
		.length = sizeof(uac1_spk_fs_config1_ac_itf_hdr_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AC_ITF_DESC_SUBTYPE_HEADER,
		.release_num = 0x0100,
		.total_length =
			sizeof(uac1_spk_fs_config1_ac_itf_hdr_desc_t) +
			sizeof(tru_usb_uac_input_terminal_desc_t) +
			sizeof(uac1_spk_fs_config1_fu_desc_t) +
			sizeof(tru_usb_uac_output_terminal_desc_t),
		.in_collection = UAC1_SPK_AUDOUT_NUM_ITF,
		.interface_num = { UAC1_SPK_AUDOUT_ITF_NUM }
	},

	// Input Terminal Descriptor
	.ac_input_terminal1_0 = {
		.length = sizeof(tru_usb_uac_input_terminal_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AC_ITF_DESC_SUBTYPE_INPUT_TERMINAL,
		.terminal_id = UAC1_SPK_ITE_UNIT_ID,
		.terminal_type = TRU_USB_UAC_TERMT_USB_STREAMING,
		.assoc_terminal = 0,
		.num_channels = UAC1_SPK_AUDOUT_NUM_CH,
		.channel_config = TRU_USB_UAC_CHCFG_L | TRU_USB_UAC_CHCFG_R,
		.channel_names = 0,
		.terminal = 0
	},
	
	// Feature Unit Descriptor
	.ac_feature_unit1_0 = {
		.length = sizeof(uac1_spk_fs_config1_fu_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AC_ITF_DESC_SUBTYPE_FEATURE_UNIT,
		.unit_id = UAC1_SPK_FE_UNIT_ID,
		.source_id = UAC1_SPK_ITE_UNIT_ID,
		.control_size = 2,
		.controls = {
			{
				.bits.mute = UAC1_SPK_MUTE_CONTROL,
				.bits.volume = UAC1_SPK_VOLUME_CONTROL,
				.bits.bass = 0,
				.bits.mid = 0,
				.bits.treble = 0,
				.bits.equalizer = 0,
				.bits.agc = 0,
				.bits.delay = 0,
				.bits.bass_boost = 0,
				.bits.loudness = 0,
				.bits.res10_15 = 0
			},
			{
				.bits.mute = UAC1_SPK_MUTE_CONTROL,
				.bits.volume = UAC1_SPK_VOLUME_CONTROL,
				.bits.bass = 0,
				.bits.mid = 0,
				.bits.treble = 0,
				.bits.equalizer = 0,
				.bits.agc = 0,
				.bits.delay = 0,
				.bits.bass_boost = 0,
				.bits.loudness = 0,
				.bits.res10_15 = 0
			},
			{
				.bits.mute = UAC1_SPK_MUTE_CONTROL,
				.bits.volume = UAC1_SPK_VOLUME_CONTROL,
				.bits.bass = 0,
				.bits.mid = 0,
				.bits.treble = 0,
				.bits.equalizer = 0,
				.bits.agc = 0,
				.bits.delay = 0,
				.bits.bass_boost = 0,
				.bits.loudness = 0,
				.bits.res10_15 = 0
			},
		},
		.feature = 0x00
	},
	
	// Output Terminal Descriptor
	.ac_output_terminal1_0 = {
		.length = sizeof(tru_usb_uac_output_terminal_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AC_ITF_DESC_SUBTYPE_OUTPUT_TERMINAL,
		.terminal_id = UAC1_SPK_OTE_UNIT_ID,
		.terminal_type = TRU_USB_UAC_TERMT_OUTPUT_SPEAKER,
		.assoc_terminal = 0,
		.source_id = UAC1_SPK_FE_UNIT_ID,
		.terminal = 0
	},
	
	// Interface descriptor - default zero bandwidth for when audio is not used, e.g. in the stop state
	.as_interface_silence_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 1,
		.alt_setting_num = 0,
		.num_endpoints = 0,
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},
	
#if UAC1_SPK_SMP_RES_16B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_16B > 0
	// Interface descriptor - for 16-bit audio stream
	.as_interface_16b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC1_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC1_SPK_ALT_NUM_16B,
		#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},
	
	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_16b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC1_SPK_AUDOUT_ITF_NUM,
		.delay = 1,
		.format_tag = TRU_USB_UAC_AF_TYPE1_PCM
	},

	// Type I Format Type Descriptor
	.af_type_16b_0 = {
		.length = sizeof(uac1_spk_fs_config1_af_type1_desc_16b_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC_AF_TYPE1,
		.num_channels = UAC1_SPK_SMP_NUM_CH_16B,
		.subframe_size = UAC1_SPK_SMP_RES_16B / 8,
		.bit_resolution = UAC1_SPK_SMP_RES_16B,
		.samp_freq_type = UAC1_SPK_NUM_SMP_FRQ_16B,
		.samp_frequencies = {
			#if UAC1_SPK_SMP_FRQ_16B_1 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_1), B1(UAC1_SPK_SMP_FRQ_16B_1), B2(UAC1_SPK_SMP_FRQ_16B_1),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_2 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_2), B1(UAC1_SPK_SMP_FRQ_16B_2), B2(UAC1_SPK_SMP_FRQ_16B_2),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_3 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_3), B1(UAC1_SPK_SMP_FRQ_16B_3), B2(UAC1_SPK_SMP_FRQ_16B_3),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_4 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_4), B1(UAC1_SPK_SMP_FRQ_16B_4), B2(UAC1_SPK_SMP_FRQ_16B_4),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_5 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_5), B1(UAC1_SPK_SMP_FRQ_16B_5), B2(UAC1_SPK_SMP_FRQ_16B_5),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_6 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_6), B1(UAC1_SPK_SMP_FRQ_16B_6), B2(UAC1_SPK_SMP_FRQ_16B_6),
			#endif
		}
	},
	
	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_16b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC1_SPK_AUDOUT_EPSYC_FS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_EPMPS_FS,
		.interval = UAC1_SPK_AUDOUT_EPINT_FS,
		.refresh = UAC1_SPK_AUDOUT_EPREF_FS,
		#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.sync_address = UAC1_SPK_AUDOUT_FB_EPADR,
		#else
			.sync_address = 0,
		#endif
	},
	
	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_16b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.sampling_freq = UAC1_SPK_SMP_FRQ_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Sampling Frequency Control Request
			.bits.pitch = UAC1_SPK_PITCH_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Pitch Control Request
			.bits.res2_6 = 0,
			.bits.max_packets_only = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_16b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_FB_EPMPS_FS,
		.interval = UAC1_SPK_AUDOUT_FB_EPINT_FS,
		.refresh = UAC1_SPK_AUDOUT_FB_EPREF_FS,
		.sync_address = 0
	},
#endif
#endif

#if UAC1_SPK_SMP_RES_24B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_24B > 0
	// Interface descriptor - for 24-bit audio stream
	.as_interface_24b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC1_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC1_SPK_ALT_NUM_24B,
		#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_24b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC1_SPK_AUDOUT_ITF_NUM,
		.delay = 1,
		.format_tag = TRU_USB_UAC_AF_TYPE1_PCM
	},

	// Type I Format Type Descriptor
	.af_type_24b_0 = {
		.length = sizeof(uac1_spk_fs_config1_af_type1_desc_24b_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC_AF_TYPE1,
		.num_channels = UAC1_SPK_SMP_NUM_CH_24B,
		.subframe_size = UAC1_SPK_SMP_RES_24B / 8,
		.bit_resolution = UAC1_SPK_SMP_RES_24B,
		.samp_freq_type = UAC1_SPK_NUM_SMP_FRQ_24B,
		.samp_frequencies = {
			#if UAC1_SPK_SMP_FRQ_24B_1 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_1), B1(UAC1_SPK_SMP_FRQ_24B_1), B2(UAC1_SPK_SMP_FRQ_24B_1),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_2 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_2), B1(UAC1_SPK_SMP_FRQ_24B_2), B2(UAC1_SPK_SMP_FRQ_24B_2),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_3 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_3), B1(UAC1_SPK_SMP_FRQ_24B_3), B2(UAC1_SPK_SMP_FRQ_24B_3),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_4 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_4), B1(UAC1_SPK_SMP_FRQ_24B_4), B2(UAC1_SPK_SMP_FRQ_24B_4),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_5 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_5), B1(UAC1_SPK_SMP_FRQ_24B_5), B2(UAC1_SPK_SMP_FRQ_24B_5),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_6 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_6), B1(UAC1_SPK_SMP_FRQ_24B_6), B2(UAC1_SPK_SMP_FRQ_24B_6),
			#endif
		}
	},

	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_24b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC1_SPK_AUDOUT_EPSYC_FS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_EPMPS_FS,
		.interval = UAC1_SPK_AUDOUT_EPINT_FS,
		.refresh = UAC1_SPK_AUDOUT_EPREF_FS,
		#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.sync_address = UAC1_SPK_AUDOUT_FB_EPADR,
		#else
			.sync_address = 0,
		#endif
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_24b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.sampling_freq = UAC1_SPK_SMP_FRQ_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Sampling Frequency Control Request
			.bits.pitch = UAC1_SPK_PITCH_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Pitch Control Request
			.bits.res2_6 = 0,
			.bits.max_packets_only = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_24b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_FB_EPMPS_FS,
		.interval = UAC1_SPK_AUDOUT_FB_EPINT_FS,
		.refresh = UAC1_SPK_AUDOUT_FB_EPREF_FS,
		.sync_address = 0
	},
#endif
#endif

#if UAC1_SPK_SMP_RES_32B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_32B > 0
	// Interface descriptor - for 32-bit audio stream
	.as_interface_32b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC1_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC1_SPK_ALT_NUM_32B,
		#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_32b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC1_SPK_AUDOUT_ITF_NUM,
		.delay = 1,
		.format_tag = TRU_USB_UAC_AF_TYPE1_PCM
	},

	// Type I Format Type Descriptor
	.af_type_32b_0 = {
		.length = sizeof(uac1_spk_fs_config1_af_type1_desc_32b_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC_AF_TYPE1,
		.num_channels = UAC1_SPK_SMP_NUM_CH_32B,
		.subframe_size = UAC1_SPK_SMP_RES_32B / 8,
		.bit_resolution = UAC1_SPK_SMP_RES_32B,
		.samp_freq_type = UAC1_SPK_NUM_SMP_FRQ_32B,
		.samp_frequencies = {
			#if UAC1_SPK_SMP_FRQ_32B_1 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_1), B1(UAC1_SPK_SMP_FRQ_32B_1), B2(UAC1_SPK_SMP_FRQ_32B_1),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_2 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_2), B1(UAC1_SPK_SMP_FRQ_32B_2), B2(UAC1_SPK_SMP_FRQ_32B_2),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_3 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_3), B1(UAC1_SPK_SMP_FRQ_32B_3), B2(UAC1_SPK_SMP_FRQ_32B_3),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_4 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_4), B1(UAC1_SPK_SMP_FRQ_32B_4), B2(UAC1_SPK_SMP_FRQ_32B_4),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_5 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_5), B1(UAC1_SPK_SMP_FRQ_32B_5), B2(UAC1_SPK_SMP_FRQ_32B_5),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_6 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_6), B1(UAC1_SPK_SMP_FRQ_32B_6), B2(UAC1_SPK_SMP_FRQ_32B_6),
			#endif
		}
	},

	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_32b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC1_SPK_AUDOUT_EPSYC_FS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_EPMPS_FS,
		.interval = UAC1_SPK_AUDOUT_EPINT_FS,
		.refresh = UAC1_SPK_AUDOUT_EPREF_FS,
		#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.sync_address = UAC1_SPK_AUDOUT_FB_EPADR,
		#else
			.sync_address = 0,
		#endif
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_32b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.sampling_freq = UAC1_SPK_SMP_FRQ_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Sampling Frequency Control Request
			.bits.pitch = UAC1_SPK_PITCH_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Pitch Control Request
			.bits.res2_6 = 0,
			.bits.max_packets_only = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC1_SPK_AUDOUT_EPSYC_FS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_32b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_FB_EPMPS_FS,
		.interval = UAC1_SPK_AUDOUT_FB_EPINT_FS,
		.refresh = UAC1_SPK_AUDOUT_FB_EPREF_FS,
		.sync_address = 0
	},
#endif
#endif
};

// Array of all configuration descriptor sets (pointers and sizes) for full speed mode
const tru_usb_config_desc_set_t uac1_spk_fs_config_descs[] = {
	{ .desc = (uint8_t *)&uac1_spk_fs_config1_desc, .size = sizeof(uac1_spk_fs_config1_desc) }
};

// Total number of configurations for full speed mode
#define UAC1_SPK_FS_NUM_OF_CONFIGS (sizeof(uac1_spk_fs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for full speed mode
const tru_usb_dev_desc_t uac1_spk_fs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = UAC1_SPK_USB_VER,
	.dev_class = TRU_USB_DEVICE_CLASS_NULL,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = UAC1_SPK_VID,
	.pid = UAC1_SPK_PID,
	.product_ver = UAC1_SPK_VER,
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = UAC1_SPK_FS_NUM_OF_CONFIGS
};

#if UAC1_SPK_HS_DESC_ENABLE == 1

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
	uint16_t release_num;
	uint16_t total_length;
	uint8_t in_collection;
	uint8_t interface_num[1];
}uac1_spk_hs_config1_ac_itf_hdr_desc_t;

// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t unit_id;
	uint8_t source_id;
	uint8_t control_size;
	tru_usb_uac_fu_controls_uint16_t controls[UAC1_SPK_AUDOUT_NUM_CH + 1];
	uint8_t feature;
}uac1_spk_hs_config1_fu_desc_t;

#if UAC1_SPK_SMP_RES_16B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_16B > 0
// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t format_type;
	uint8_t num_channels;
	uint8_t subframe_size;
	uint8_t bit_resolution;
	uint8_t samp_freq_type;
	uint8_t samp_frequencies[3*UAC1_SPK_NUM_SMP_FRQ_16B];
}uac1_spk_hs_config1_af_type1_desc_16b_t;
#endif

#if UAC1_SPK_SMP_RES_24B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_24B > 0
// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t format_type;
	uint8_t num_channels;
	uint8_t subframe_size;
	uint8_t bit_resolution;
	uint8_t samp_freq_type;
	uint8_t samp_frequencies[3*UAC1_SPK_NUM_SMP_FRQ_24B];
}uac1_spk_hs_config1_af_type1_desc_24b_t;
#endif

#if UAC1_SPK_SMP_RES_32B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_32B > 0
// This is a variable size type so we need to create it specifically for this instance
typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint8_t desc_subtype;
	uint8_t format_type;
	uint8_t num_channels;
	uint8_t subframe_size;
	uint8_t bit_resolution;
	uint8_t samp_freq_type;
	uint8_t samp_frequencies[3*UAC1_SPK_NUM_SMP_FRQ_32B];
}uac1_spk_hs_config1_af_type1_desc_32b_t;
#endif

// UAC configuration 1
typedef struct __attribute__((packed)){
	tru_usb_config_desc_t                       config_0;
	tru_usb_interface_desc_t                    ac_interface_0;
	uac1_spk_hs_config1_ac_itf_hdr_desc_t       ac_interface_header_0;
	tru_usb_uac_input_terminal_desc_t           ac_input_terminal1_0;
	uac1_spk_hs_config1_fu_desc_t               ac_feature_unit1_0;
	tru_usb_uac_output_terminal_desc_t          ac_output_terminal1_0;
	tru_usb_interface_desc_t                    as_interface_silence_0;
#if UAC1_SPK_SMP_RES_16B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_16B > 0
	tru_usb_interface_desc_t                    as_interface_16b_0;
	tru_usb_uac_as_cls_itf_desc_t               as_cls_interface_16b_0;
	uac1_spk_hs_config1_af_type1_desc_16b_t     af_type_16b_0;
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_data_ep_16b_0;
	tru_usb_uac_as_cls_iso_ep_desc_t            as_cls_data_ep_16b_0;
	#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_fb_ep_16b_0;
	#endif
#endif
#if UAC1_SPK_SMP_RES_24B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_24B > 0
	tru_usb_interface_desc_t                    as_interface_24b_0;
	tru_usb_uac_as_cls_itf_desc_t               as_cls_interface_24b_0;
	uac1_spk_hs_config1_af_type1_desc_24b_t     af_type_24b_0;
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_data_ep_24b_0;
	tru_usb_uac_as_cls_iso_ep_desc_t            as_cls_data_ep_24b_0;
	#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_fb_ep_24b_0;
	#endif
#endif
#if UAC1_SPK_SMP_RES_32B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_32B > 0
	tru_usb_interface_desc_t                    as_interface_32b_0;
	tru_usb_uac_as_cls_itf_desc_t               as_cls_interface_32b_0;
	uac1_spk_hs_config1_af_type1_desc_32b_t     af_type_32b_0;
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_data_ep_32b_0;
	tru_usb_uac_as_cls_iso_ep_desc_t            as_cls_data_ep_32b_0;
	#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	tru_usb_uac_as_std_iso_ep_desc_t            as_std_fb_ep_32b_0;
	#endif
#endif
}uac1_spk_hs_config1_desc_t;

// UAC configuration 1
const uac1_spk_hs_config1_desc_t uac1_spk_hs_config1_desc = {
	// Configuration descriptor
	.config_0 = {
		.length = sizeof(tru_usb_config_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_CONFIG,
		.total_length = sizeof(uac1_spk_hs_config1_desc_t),
		.num_interfaces = 2,
		.config_num = 1,
		.string_index = 0,
		.attributes =
			TRU_USB_CONFIG_DESC_ATTRIB_RES_D7 |
			TRU_USB_CONFIG_DESC_ATTRIB_SELF_POWERED |
			TRU_USB_CONFIG_DESC_ATTRIB_REMOTE_WAKEUP,
		.max_power = TRU_USB_CONFIG_DESC_MAXPOWER_SELF_POWERED
	},

	// Interface descriptor for the Audio Control Interface
	.ac_interface_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC1_SPK_AUDCTL_ITF_NUM,
		.alt_setting_num = 0,
		.num_endpoints = 0,
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOCONTROL,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},

	// Class-Specific AC (AudioControl) Interface Header Descriptor
	.ac_interface_header_0 = {
		.length = sizeof(uac1_spk_hs_config1_ac_itf_hdr_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AC_ITF_DESC_SUBTYPE_HEADER,
		.release_num = 0x0100,
		.total_length =
			sizeof(uac1_spk_hs_config1_ac_itf_hdr_desc_t) +
			sizeof(tru_usb_uac_input_terminal_desc_t) +
			sizeof(uac1_spk_hs_config1_fu_desc_t) +
			sizeof(tru_usb_uac_output_terminal_desc_t),
		.in_collection = UAC1_SPK_AUDOUT_NUM_ITF,
		.interface_num = { UAC1_SPK_AUDOUT_ITF_NUM }
	},

	// Input Terminal Descriptor
	.ac_input_terminal1_0 = {
		.length = sizeof(tru_usb_uac_input_terminal_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AC_ITF_DESC_SUBTYPE_INPUT_TERMINAL,
		.terminal_id = UAC1_SPK_ITE_UNIT_ID,
		.terminal_type = TRU_USB_UAC_TERMT_USB_STREAMING,
		.assoc_terminal = 0,
		.num_channels = UAC1_SPK_AUDOUT_NUM_CH,
		.channel_config = TRU_USB_UAC_CHCFG_L | TRU_USB_UAC_CHCFG_R,
		.channel_names = 0,
		.terminal = 0
	},
	
	// Feature Unit Descriptor
	.ac_feature_unit1_0 = {
		.length = sizeof(uac1_spk_hs_config1_fu_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AC_ITF_DESC_SUBTYPE_FEATURE_UNIT,
		.unit_id = UAC1_SPK_FE_UNIT_ID,
		.source_id = UAC1_SPK_ITE_UNIT_ID,
		.control_size = 2,
		.controls = {
			{
				.bits.mute = UAC1_SPK_MUTE_CONTROL,
				.bits.volume = UAC1_SPK_VOLUME_CONTROL,
				.bits.bass = 0,
				.bits.mid = 0,
				.bits.treble = 0,
				.bits.equalizer = 0,
				.bits.agc = 0,
				.bits.delay = 0,
				.bits.bass_boost = 0,
				.bits.loudness = 0,
				.bits.res10_15 = 0
			},
			{
				.bits.mute = UAC1_SPK_MUTE_CONTROL,
				.bits.volume = UAC1_SPK_VOLUME_CONTROL,
				.bits.bass = 0,
				.bits.mid = 0,
				.bits.treble = 0,
				.bits.equalizer = 0,
				.bits.agc = 0,
				.bits.delay = 0,
				.bits.bass_boost = 0,
				.bits.loudness = 0,
				.bits.res10_15 = 0
			},
			{
				.bits.mute = UAC1_SPK_MUTE_CONTROL,
				.bits.volume = UAC1_SPK_VOLUME_CONTROL,
				.bits.bass = 0,
				.bits.mid = 0,
				.bits.treble = 0,
				.bits.equalizer = 0,
				.bits.agc = 0,
				.bits.delay = 0,
				.bits.bass_boost = 0,
				.bits.loudness = 0,
				.bits.res10_15 = 0
			},
		},
		.feature = 0x00
	},
	
	// Output Terminal Descriptor
	.ac_output_terminal1_0 = {
		.length = sizeof(tru_usb_uac_output_terminal_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AC_ITF_DESC_SUBTYPE_OUTPUT_TERMINAL,
		.terminal_id = UAC1_SPK_OTE_UNIT_ID,
		.terminal_type = TRU_USB_UAC_TERMT_OUTPUT_SPEAKER,
		.assoc_terminal = 0,
		.source_id = UAC1_SPK_FE_UNIT_ID,
		.terminal = 0
	},
	
	// Interface descriptor - default zero bandwidth for stop state
	.as_interface_silence_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = 1,
		.alt_setting_num = 0,
		.num_endpoints = 0,
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},
	
#if UAC1_SPK_SMP_RES_16B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_16B > 0
	// Interface descriptor - for 16-bit audio stream
	.as_interface_16b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC1_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC1_SPK_ALT_NUM_16B,
		#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},
	
	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_16b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC1_SPK_AUDOUT_ITF_NUM,
		.delay = 1,
		.format_tag = TRU_USB_UAC_AF_TYPE1_PCM
	},

	// Type I Format Type Descriptor
	.af_type_16b_0 = {
		.length = sizeof(uac1_spk_hs_config1_af_type1_desc_16b_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC_AF_TYPE1,
		.num_channels = UAC1_SPK_SMP_NUM_CH_16B,
		.subframe_size = UAC1_SPK_SMP_RES_16B / 8,
		.bit_resolution = UAC1_SPK_SMP_RES_16B,
		.samp_freq_type = UAC1_SPK_NUM_SMP_FRQ_16B,
		.samp_frequencies = {
			#if UAC1_SPK_SMP_FRQ_16B_1 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_1), B1(UAC1_SPK_SMP_FRQ_16B_1), B2(UAC1_SPK_SMP_FRQ_16B_1),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_2 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_2), B1(UAC1_SPK_SMP_FRQ_16B_2), B2(UAC1_SPK_SMP_FRQ_16B_2),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_3 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_3), B1(UAC1_SPK_SMP_FRQ_16B_3), B2(UAC1_SPK_SMP_FRQ_16B_3),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_4 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_4), B1(UAC1_SPK_SMP_FRQ_16B_4), B2(UAC1_SPK_SMP_FRQ_16B_4),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_5 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_5), B1(UAC1_SPK_SMP_FRQ_16B_5), B2(UAC1_SPK_SMP_FRQ_16B_5),
			#endif
			#if UAC1_SPK_SMP_FRQ_16B_6 > 0
				B0(UAC1_SPK_SMP_FRQ_16B_6), B1(UAC1_SPK_SMP_FRQ_16B_6), B2(UAC1_SPK_SMP_FRQ_16B_6),
			#endif
		}
	},

	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_16b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC1_SPK_AUDOUT_EPSYC_HS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_EPMPS_HS,
		.interval = UAC1_SPK_AUDOUT_EPINT_HS,
		.refresh = UAC1_SPK_AUDOUT_EPREF_HS,
		#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.sync_address = UAC1_SPK_AUDOUT_FB_EPADR,
		#else
			.sync_address = 0,
		#endif
	},
	
	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_16b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.sampling_freq = UAC1_SPK_SMP_FRQ_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Sampling Frequency Control Request
			.bits.pitch = UAC1_SPK_PITCH_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Pitch Control Request
			.bits.res2_6 = 0,
			.bits.max_packets_only = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},


#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_16b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_FB_EPMPS_HS,
		.interval = UAC1_SPK_AUDOUT_FB_EPINT_HS,
		.refresh = UAC1_SPK_AUDOUT_FB_EPREF_HS,
		.sync_address = 0
	},
#endif
#endif

#if UAC1_SPK_SMP_RES_24B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_24B > 0
	// Interface descriptor - for 24-bit audio stream
	.as_interface_24b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC1_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC1_SPK_ALT_NUM_24B,
		#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_24b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC1_SPK_AUDOUT_ITF_NUM,
		.delay = 1,
		.format_tag = TRU_USB_UAC_AF_TYPE1_PCM
	},

	// Type I Format Type Descriptor
	.af_type_24b_0 = {
		.length = sizeof(uac1_spk_hs_config1_af_type1_desc_24b_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC_AF_TYPE1,
		.num_channels = UAC1_SPK_SMP_NUM_CH_24B,
		.subframe_size = UAC1_SPK_SMP_RES_24B / 8,
		.bit_resolution = UAC1_SPK_SMP_RES_24B,
		.samp_freq_type = UAC1_SPK_NUM_SMP_FRQ_24B,
		.samp_frequencies = {
			#if UAC1_SPK_SMP_FRQ_24B_1 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_1), B1(UAC1_SPK_SMP_FRQ_24B_1), B2(UAC1_SPK_SMP_FRQ_24B_1),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_2 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_2), B1(UAC1_SPK_SMP_FRQ_24B_2), B2(UAC1_SPK_SMP_FRQ_24B_2),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_3 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_3), B1(UAC1_SPK_SMP_FRQ_24B_3), B2(UAC1_SPK_SMP_FRQ_24B_3),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_4 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_4), B1(UAC1_SPK_SMP_FRQ_24B_4), B2(UAC1_SPK_SMP_FRQ_24B_4),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_5 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_5), B1(UAC1_SPK_SMP_FRQ_24B_5), B2(UAC1_SPK_SMP_FRQ_24B_5),
			#endif
			#if UAC1_SPK_SMP_FRQ_24B_6 > 0
				B0(UAC1_SPK_SMP_FRQ_24B_6), B1(UAC1_SPK_SMP_FRQ_24B_6), B2(UAC1_SPK_SMP_FRQ_24B_6),
			#endif
		}
	},

	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_24b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC1_SPK_AUDOUT_EPSYC_HS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_EPMPS_HS,
		.interval = UAC1_SPK_AUDOUT_EPINT_HS,
		.refresh = UAC1_SPK_AUDOUT_EPREF_HS,
		#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.sync_address = UAC1_SPK_AUDOUT_FB_EPADR,
		#else
			.sync_address = 0,
		#endif
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_24b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.sampling_freq = UAC1_SPK_SMP_FRQ_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Sampling Frequency Control Request
			.bits.pitch = UAC1_SPK_PITCH_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Pitch Control Request
			.bits.res2_6 = 0,
			.bits.max_packets_only = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_24b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_FB_EPMPS_HS,
		.interval = UAC1_SPK_AUDOUT_FB_EPINT_HS,
		.refresh = UAC1_SPK_AUDOUT_FB_EPREF_HS,
		.sync_address = 0
	},
#endif
#endif

#if UAC1_SPK_SMP_RES_32B_ENABLE && UAC1_SPK_NUM_SMP_FRQ_32B > 0
	// Interface descriptor - for 32-bit audio stream
	.as_interface_32b_0 = {
		.length = sizeof(tru_usb_interface_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_INTERFACE,
		.interface_num = UAC1_SPK_AUDOUT_ITF_NUM,
		.alt_setting_num = UAC1_SPK_ALT_NUM_32B,
		#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.num_endpoints = 2,
		#else
			.num_endpoints = 1,
		#endif
		.interface_class = TRU_USB_UAC_ITF_CLASS,
		.interface_subclass = TRU_USB_UAC_ITF_SUBCLASS_AUDIOSTREAMING,
		.interface_protocol = TRU_USB_UAC_ITF_PROTOCOL_UNDEFINED,
		.string_index = 0
	},

	// Class-Specific AS (AudioStreaming) Interface Descriptor
	.as_cls_interface_32b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_itf_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.terminal_link = UAC1_SPK_AUDOUT_ITF_NUM,
		.delay = 1,
		.format_tag = TRU_USB_UAC_AF_TYPE1_PCM
	},

	// Type I Format Type Descriptor
	.af_type_32b_0 = {
		.length = sizeof(uac1_spk_hs_config1_af_type1_desc_32b_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_INTERFACE,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_FORMAT_TYPE,
		.format_type = TRU_USB_UAC_AF_TYPE1,
		.num_channels = UAC1_SPK_SMP_NUM_CH_32B,
		.subframe_size = UAC1_SPK_SMP_RES_32B / 8,
		.bit_resolution = UAC1_SPK_SMP_RES_32B,
		.samp_freq_type = UAC1_SPK_NUM_SMP_FRQ_32B,
		.samp_frequencies = {
			#if UAC1_SPK_SMP_FRQ_32B_1 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_1), B1(UAC1_SPK_SMP_FRQ_32B_1), B2(UAC1_SPK_SMP_FRQ_32B_1),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_2 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_2), B1(UAC1_SPK_SMP_FRQ_32B_2), B2(UAC1_SPK_SMP_FRQ_32B_2),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_3 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_3), B1(UAC1_SPK_SMP_FRQ_32B_3), B2(UAC1_SPK_SMP_FRQ_32B_3),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_4 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_4), B1(UAC1_SPK_SMP_FRQ_32B_4), B2(UAC1_SPK_SMP_FRQ_32B_4),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_5 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_5), B1(UAC1_SPK_SMP_FRQ_32B_5), B2(UAC1_SPK_SMP_FRQ_32B_5),
			#endif
			#if UAC1_SPK_SMP_FRQ_32B_6 > 0
				B0(UAC1_SPK_SMP_FRQ_32B_6), B1(UAC1_SPK_SMP_FRQ_32B_6), B2(UAC1_SPK_SMP_FRQ_32B_6),
			#endif
		}
	},

	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_std_data_ep_32b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_OUT
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = UAC1_SPK_AUDOUT_EPSYC_HS,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_DATA,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_EPMPS_HS,
		.interval= UAC1_SPK_AUDOUT_EPINT_HS,
		.refresh = UAC1_SPK_AUDOUT_EPREF_HS,
		#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
			.sync_address = UAC1_SPK_AUDOUT_FB_EPADR,
		#else
			.sync_address = 0,
		#endif
	},

	// Class-Specific AS (AudioStreaming) Isochronous Audio Data Endpoint Descriptor
	.as_cls_data_ep_32b_0 = {
		.length = sizeof(tru_usb_uac_as_cls_iso_ep_desc_t),
		.desc_type = TRU_USB_UAC_DESC_TYPE_ENDPOINT,
		.desc_subtype = TRU_USB_UAC_AS_ITF_DESC_SUBTYPE_GENERAL,
		.attributes = {
			.bits.sampling_freq = UAC1_SPK_SMP_FRQ_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Sampling Frequency Control Request
			.bits.pitch = UAC1_SPK_PITCH_CONTROL,  // 1 = Enable host to use the Set/Get Endpoint Pitch Control Request
			.bits.res2_6 = 0,
			.bits.max_packets_only = 0
		},
		.lock_delay_units = 0,
		.lock_delay = 0
	},

#if UAC1_SPK_AUDOUT_EPSYC_HS == TRU_USB_EP_ISO_SYNC_TYPE_ASYNC
	// UAC1 specific Standard AS (AudioStreaming) Isochronous Audio Synch (Feedback) Endpoint Descriptor
	.as_std_fb_ep_32b_0 = {
		.length = sizeof(tru_usb_uac_as_std_iso_ep_desc_t),
		.desc_type = TRU_USB_DESC_TYPE_ENDPOINT,
		.address = {
			.bits.ep_num = UAC1_SPK_AUDOUT_FB_EPADR & 0xf,
			.bits.res4_6 = 0,
			.bits.dir = TRU_USB_EP_DIR_IN
		},
		.attributes = {
			.bits.transfer_type = TRU_USB_EP_TRANSFER_TYPE_ISOCHRONOUS,
			.bits.sync_type = TRU_USB_EP_ISO_SYNC_TYPE_NONE,
			.bits.usage_type = TRU_USB_EP_USAGE_TYPE_FEEDBACK,
			.bits.res6_7 = 0,
		},
		.mps = UAC1_SPK_AUDOUT_FB_EPMPS_HS,
		.interval = UAC1_SPK_AUDOUT_FB_EPINT_HS,
		.refresh = UAC1_SPK_AUDOUT_FB_EPREF_HS,
		.sync_address = 0
	},
#endif
#endif
};

// Array of all configuration descriptor sets (pointers and sizes) for high speed mode
const tru_usb_config_desc_set_t uac1_spk_hs_config_descs[] = {
	{ .desc = (uint8_t *)&uac1_spk_hs_config1_desc, .size = sizeof(uac1_spk_hs_config1_desc) }
};

// Total number of configurations for high speed mode
#define UAC1_SPK_HS_NUM_OF_CONFIGS (sizeof(uac1_spk_hs_config_descs) / sizeof(tru_usb_config_desc_set_t))

// =================
// Device descriptor
// =================

// Device descriptor for high speed mode
const tru_usb_dev_desc_t uac1_spk_hs_dev_desc = {
	.length = sizeof(tru_usb_dev_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE,
	.usb_ver = UAC1_SPK_USB_VER,
	.dev_class = TRU_USB_DEVICE_CLASS_NULL,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.vid = UAC1_SPK_VID,
	.pid = UAC1_SPK_PID,
	.product_ver = UAC1_SPK_VER,
	.manufacturer = 1,  // Index of manufacturer string
	.product = 2,  // Index of product string
	.serial = 3,  // Index of serial string
	.num_configs = UAC1_SPK_HS_NUM_OF_CONFIGS
};

// Device qualifier descriptor for full speed mode (describes other speed, i.e. high speed mode)
const tru_usb_dev_qual_desc_t uac1_spk_fs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = UAC1_SPK_USB_VER,
	.dev_class = TRU_USB_DEVICE_CLASS_NULL,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_HS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = UAC1_SPK_HS_NUM_OF_CONFIGS,
	.reserved = 0
};

// Device qualifier descriptor for high speed mode (describes other speed, i.e. full speed mode)
const tru_usb_dev_qual_desc_t uac1_spk_hs_dev_qual_desc = {
	.length = sizeof(tru_usb_dev_qual_desc_t),
	.desc_type = TRU_USB_DESC_TYPE_DEVICE_QUAL,
	.usb_ver = UAC1_SPK_USB_VER,
	.dev_class = TRU_USB_DEVICE_CLASS_NULL,
	.dev_subclass = TRU_USB_DEVICE_SUBCLASS_NULL,
	.dev_protocol = TRU_USB_DEVICE_PROTOCOL_NULL,
	.mps = TRU_USB_EP_FS_CONTROL_MAX_MPS,  // EP0 max packet size
	.num_configs = UAC1_SPK_FS_NUM_OF_CONFIGS,
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
}uac1_spk_string_lang_ids_t;

// Supported language IDs string descriptor
const uac1_spk_string_lang_ids_t uac1_spk_lang_string_desc = {
	.length = sizeof(uac1_spk_lang_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.lang_id = { TRU_USB_LANG_ID_ENGLISH_US }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}uac1_spk_string_manuf_t;

// Manufacturer string descriptor
const uac1_spk_string_manuf_t uac1_spk_manuf_string_desc = {
	.length = sizeof(uac1_spk_manuf_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[10];
}uac1_spk_string_product_t;

// Product string descriptor
const uac1_spk_string_product_t uac1_spk_prod_string_desc = {
	.length = sizeof(uac1_spk_prod_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { 'T', 'r', 'u', 'U', 'A', 'C', '1', 'S', 'p', 'k' }
};

typedef struct __attribute__((packed)){
	uint8_t length;
	uint8_t desc_type;
	uint16_t string[3];
}uac1_spk_string_serial_t;

// Serial number string descriptor
const uac1_spk_string_serial_t uac1_spk_ser_string_desc = {
	.length = sizeof(uac1_spk_ser_string_desc),
	.desc_type = TRU_USB_DESC_TYPE_STRING,
	.string = { '1', '2', '3' }
};

// An array of all the indexes & language IDs mapped to string descriptor pointers
// Note: this is made up and not in the USB specification but it is needed in practice
const tru_usb_string_desc_info_t uac1_spk_string_descs[] = {
	{ .index = 0, .lang_id = TRU_USB_LANG_ID_NONE,       .desc = (void *)&uac1_spk_lang_string_desc },
	{ .index = 1, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&uac1_spk_manuf_string_desc },
	{ .index = 2, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&uac1_spk_prod_string_desc },
	{ .index = 3, .lang_id = TRU_USB_LANG_ID_ENGLISH_US, .desc = (void *)&uac1_spk_ser_string_desc }
};

// ==========================================================================
// Final peripheral device descriptors (pointers to all structures above)
// ==========================================================================

// Common
tru_usb_pd_info_t uac1_spk_base_pd_info = {
#if UAC1_SPK_HS_DESC_ENABLE == 1
	.hs_dev_desc = (tru_usb_dev_desc_t *)&uac1_spk_hs_dev_desc,
#else
	.hs_dev_desc = NULL,
#endif
	.fs_dev_desc = (tru_usb_dev_desc_t *)&uac1_spk_fs_dev_desc,
	.ls_dev_desc = NULL,

#if UAC1_SPK_HS_DESC_ENABLE == 1
	.hs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&uac1_spk_hs_dev_qual_desc,
	.fs_dev_qual_desc = (tru_usb_dev_qual_desc_t *)&uac1_spk_fs_dev_qual_desc,
#else
	.hs_dev_qual_desc = NULL,
	.fs_dev_qual_desc = NULL,
#endif

#if UAC1_SPK_HS_DESC_ENABLE == 1
	.hs_config_descs = (tru_usb_config_desc_set_t *)uac1_spk_hs_config_descs, .hs_config_descs_num_entries = sizeof(uac1_spk_hs_config_descs) / sizeof(tru_usb_config_desc_set_t),
#else
	.hs_config_descs = NULL, .hs_config_descs_num_entries = 0,
#endif
	.fs_config_descs = (tru_usb_config_desc_set_t *)uac1_spk_fs_config_descs, .fs_config_descs_num_entries = sizeof(uac1_spk_fs_config_descs) / sizeof(tru_usb_config_desc_set_t),
	.ls_config_descs = NULL, .ls_config_descs_num_entries = 0,

	.string_descs = (tru_usb_string_desc_info_t *)uac1_spk_string_descs, .string_descs_num_entries = sizeof(uac1_spk_string_descs) / sizeof(tru_usb_string_desc_info_t)
};

// Common + class
tru_usb_uac_pd_info_t uac1_spk_uac_pd_info = {
	.pd = &uac1_spk_base_pd_info,

#if UAC1_SPK_HS_DESC_ENABLE == 1
	.hs_uac_interface_exts = (tru_usb_uac_interface_ext_t *)uac1_spk_interface_exts, .hs_uac_interface_exts_num_entries = sizeof(uac1_spk_interface_exts) / sizeof(tru_usb_uac_interface_ext_t),
#else
	.hs_uac_interface_exts = NULL, .hs_uac_interface_exts_num_entries = 0,
#endif
	.fs_uac_interface_exts = (tru_usb_uac_interface_ext_t *)uac1_spk_interface_exts, .fs_uac_interface_exts_num_entries = sizeof(uac1_spk_interface_exts) / sizeof(tru_usb_uac_interface_ext_t),
	.ls_uac_interface_exts = NULL, .ls_uac_interface_exts_num_entries = 0,

#if UAC1_SPK_HS_DESC_ENABLE == 1
	.hs_uac_ep_exts = (tru_usb_uac_ep_ext_t *)uac1_spk_ep_exts, .hs_uac_ep_exts_num_entries = sizeof(uac1_spk_ep_exts) / sizeof(tru_usb_uac_ep_ext_t),
#else
	.hs_uac_ep_exts = NULL, .hs_uac_ep_exts_num_entries = 0,
#endif
	.fs_uac_ep_exts = (tru_usb_uac_ep_ext_t *)uac1_spk_ep_exts, .fs_uac_ep_exts_num_entries = sizeof(uac1_spk_ep_exts) / sizeof(tru_usb_uac_ep_ext_t),
	.ls_uac_ep_exts = (tru_usb_uac_ep_ext_t *)uac1_spk_ep_exts, .ls_uac_ep_exts_num_entries = sizeof(uac1_spk_ep_exts) / sizeof(tru_usb_uac_ep_ext_t),
};

tru_usb_uac_pd_info_t *get_uac1_spk_pd_info(void){
	return (tru_usb_uac_pd_info_t *)&uac1_spk_uac_pd_info;
}

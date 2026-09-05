#include "hid_gamepad1_c5soc.h"

#if defined(TRU_CFG_CHIPSET) && TRU_CFG_CHIPSET == TRU_OPT_CHIPSET_C5SOC

// Trulib includes
#include "tru_config.h"
#include "c5soc/tru_clkmgr_c5soc.h"
#include "c5soc/tru_i2c_c5soc.h"
#include "c5soc/tru_adxl345.h"

static tru_usb_pc_t pc;
static tru_usb_hid_t hid;
static tru_adxl345_accel_t accel;
static uint32_t tru_adxl345_res;

static void setup_adxl345(void){
	uint8_t buffer[1];

	accel.sample_count = 0;

	// Get the L4 Slave Peripheral clock frequency
	accel.l4_sp_clock_freq_hz = get_l4_sp_clk(TRU_HPS_INPUT_CLK_HZ).fout;
	//printf("L4_SP_CLK = %u Hz\n", accel.l4_sp_clock_freq_hz);

	// Initialise
	tru_adxl345_i2c_init(accel.l4_sp_clock_freq_hz, TRU_ADXL345_I2C_SPEED_KHZ, TRU_HPS_I2C_CON_ADDR_7BIT, TRU_ADXL345_I2C_DEV_ADDR);

	// Read ADXL345 device ID from the ADXL345
	//tru_adxl345_i2c_read(buffer, 1, TRU_ADXL345_DEVID_ADDR);

	tru_adxl345_i2c_stop_flush_fifo();

	// Set calibration offsets
	buffer[0] = OPT_ADXL345_OFSX;
	tru_adxl345_i2c_write(buffer, 1, TRU_ADXL345_OFSX_ADDR);
	buffer[0] = OPT_ADXL345_OFSY;
	tru_adxl345_i2c_write(buffer, 1, TRU_ADXL345_OFSY_ADDR);
	buffer[0] = OPT_ADXL345_OFSZ;
	tru_adxl345_i2c_write(buffer, 1, TRU_ADXL345_OFSZ_ADDR);

	// Set ADXL345 output rate
	TRU_ADXL345_BW_RATE_PTR(buffer)->val = 0;
	TRU_ADXL345_BW_RATE_PTR(buffer)->bits.rate = OPT_ADXL345_RATE;
	tru_adxl345_i2c_write(buffer, 1, TRU_ADXL345_BW_RATE_ADDR);

	// Set ADXL345 data options
	TRU_ADXL345_DATA_FORMAT_PTR(buffer)->val = 0;
	TRU_ADXL345_DATA_FORMAT_PTR(buffer)->bits.range = OPT_ADXL345_RANGE;
	TRU_ADXL345_DATA_FORMAT_PTR(buffer)->bits.fullres = OPT_ADXL345_FULLRES;
	TRU_ADXL345_DATA_FORMAT_PTR(buffer)->bits.intinvert = 1;
	tru_adxl345_i2c_write(buffer, 1, TRU_ADXL345_DATA_FORMAT_ADDR);

	// Set ADXL345 FIFO mode off
	TRU_ADXL345_FIFO_CTL_PTR(buffer)->val = 0;
	TRU_ADXL345_FIFO_CTL_PTR(buffer)->bits.fifomode = TRU_ADXL345_FIFOMODE_BYPASS;
	TRU_ADXL345_FIFO_CTL_PTR(buffer)->bits.samples = 16;
	tru_adxl345_i2c_write(buffer, 1, TRU_ADXL345_FIFO_CTL_ADDR);

	// Set ADXL345 to start measuring
	TRU_ADXL345_POWER_CTL_PTR(buffer)->val = 0;
	TRU_ADXL345_POWER_CTL_PTR(buffer)->bits.measure = 1;
	tru_adxl345_i2c_write(buffer, 1, TRU_ADXL345_POWER_CTL_ADDR);
}

void hid_gamepad1_init_app(void){
	setup_adxl345();
	tru_adxl345_res = tru_adxl345_determine_res(OPT_ADXL345_RANGE, OPT_ADXL345_FULLRES);

	tru_dwc2_phy_t phy = {
		.speed = TRU_DWC2_PHYSPEED_HS,
		.iftype = TRU_DWC2_PHYIFTYPE_INTERNAL,
		.rate = TRU_DWC2_PHYRATE_SDR,
		.width = TRU_DWC2_PHYWIDTH_8BIT
	};

	hid_gamepad1_init(
		&pc,
		&hid,
		TRU_USB_U1_BASE,
		phy,
		TRU_DWC2_DCFG_DEVSPD_USBHS20,
		true,
		false,
		HID_GAMEPAD1_DMA_MODE_CHOICE
	);

	tru_usb_pc_start(&pc);
}

void hid_gamepad1_deinit_app(void){
	hid_gamepad1_deinit(&hid);
}

static void update_adxl345_sample(void){
	tru_adxl345_int_source_t int_source;

	tru_adxl345_i2c_read(&int_source.val, 1, TRU_ADXL345_INT_SOURCE_ADDR);  // Read interrupt source flags
	if(int_source.bits.dataready == 1){
		tru_adxl345_i2c_read_bm(&accel.sample, 6, TRU_ADXL345_DATAX0_ADDR);  // Read out samples
	}
}

// Override weak function
void hid_gamepad1_update_controller(tru_hid_gamepad1_input_report_t *report){
	update_adxl345_sample();

	int16_t x;
	int16_t y;
	int16_t z;

	report->buttons.val = 0;

#if HID_GAMEPAD1_POS_RES
	// Convert sample resolution to HID resolution
	if(HID_GAMEPAD1_POS_RES > tru_adxl345_res){
		uint32_t shift = HID_GAMEPAD1_POS_RES - tru_adxl345_res + 1;  // multiplier
		x = (accel.sample.x > 0) ? accel.sample.x << shift : (accel.sample.x + 1) << shift - 1;
		y = (accel.sample.y > 0) ? accel.sample.y << shift : (accel.sample.y + 1) << shift - 1;
		z = (accel.sample.z > 0) ? accel.sample.z << shift : (accel.sample.z + 1) << shift - 1;
	}else if(HID_GAMEPAD1_POS_RES < tru_adxl345_res){
		uint32_t shift = tru_adxl345_res - HID_GAMEPAD1_POS_RES + 1;  // divider
		x = (accel.sample.x > 0) ? accel.sample.x >> shift : accel.sample.x >> shift;
		y = (accel.sample.y > 0) ? accel.sample.y >> shift : accel.sample.y >> shift;
		z = (accel.sample.z > 0) ? accel.sample.z >> shift : accel.sample.z >> shift;
	}

	report->x = x;
	report->y = y;
	report->z = z;
#endif

#if HID_GAMEPAD1_ROT_RES
	// Convert sample resolution to HID resolution
	if(HID_GAMEPAD1_ROT_RES > tru_adxl345_res){
		uint32_t shift = HID_GAMEPAD1_ROT_RES - tru_adxl345_res + 1;  // multiplier
		x = (accel.sample.x > 0) ? accel.sample.x << shift : (accel.sample.x + 1) << shift - 1;
		y = (accel.sample.y > 0) ? accel.sample.y << shift : (accel.sample.y + 1) << shift - 1;
		z = (accel.sample.z > 0) ? accel.sample.z << shift : (accel.sample.z + 1) << shift - 1;
	}else if(HID_GAMEPAD1_ROT_RES < tru_adxl345_res){
		uint32_t shift = tru_adxl345_res - HID_GAMEPAD1_ROT_RES + 1;  // divider
		x = (accel.sample.x > 0) ? accel.sample.x >> shift : accel.sample.x >> shift;
		y = (accel.sample.y > 0) ? accel.sample.y >> shift : accel.sample.y >> shift;
		z = (accel.sample.z > 0) ? accel.sample.z >> shift : accel.sample.z >> shift;
	}

	report->rx = x;
	report->ry = y;
	report->rz = z;
#endif
}

#endif

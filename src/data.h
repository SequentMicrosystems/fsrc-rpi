#ifndef DATA_H
#define DATA_H

#define CARD_NAME "Flagstaff-Research"
#define PROGRAM_NAME "fsrc"
#define VERSION "1.0.0"

#define SLAVE_OWN_ADDRESS_BASE 0x0c

#define U5_IN_CH_NO 12
#define ANALOG_VAL_SIZE 2
#define RTD_CH_NO 3
#define RTD_TEMP_VAL_SIZE 4
#define RTD_RES_VAL_SIZE 4
#define U10_OUT_CH_NO 2
#define PUMP_CH_NO 4
#define PUMP_VAL_SIZE 2
#define PUMP_VAL_MIN 0
#define PUMP_VAL_MAX 100
#define FET_CH_NO 8
#define DIGI_CH_NO 4
#define DIGI_CNT_SIZE 4
#define OWB_CH_NO 14
#define OWB_TEMP_VAL_SIZE 2
#define OWB_ROM_SIZE 8

#define MIN_CH_NO 1

#define CALIBRATION_KEY 0xaa
#define RESET_CALIBRATION_KEY	0x55
#define WDT_RESET_SIGNATURE     0xca
#define WDT_RESET_COUNT_SIGNATURE    0xbe

#define VOLT_TO_MILIVOLT 1000
#define MILIAMPER_TO_MICROAMPER 1000

enum CALIB_STATUS {
	CAL_IN_PROGRESS = 0,
	CAL_DONE,
	CAL_ERR,
};
enum CALIB_ID {
	CAL_NOTHING = 0,
	CAL_U10_OUT,
	CAL_U5_IN = CAL_U10_OUT + U10_OUT_CH_NO,
	CAL_RTD = CAL_U5_IN + U5_IN_CH_NO,
};

enum I2C_MEM {
	I2C_MEM_FETS = 0,
	I2C_MEM_FET_SET,
	I2C_MEM_FET_CLR,
	I2C_MEM_DIGI,

	I2C_MEM_U10_OUT,
	I2C_MEM_PUMP = I2C_MEM_U10_OUT + U10_OUT_CH_NO * ANALOG_VAL_SIZE,

	I2C_MEM_U5_IN = I2C_MEM_PUMP + PUMP_CH_NO * PUMP_VAL_SIZE,
	I2C_MEM_RTD_TEMP = I2C_MEM_U5_IN + U5_IN_CH_NO * ANALOG_VAL_SIZE,
	I2C_MEM_RTD_RES = I2C_MEM_RTD_TEMP + RTD_CH_NO * RTD_TEMP_VAL_SIZE,

	I2C_MEM_CALIB_VALUE = I2C_MEM_RTD_RES + RTD_CH_NO * RTD_RES_VAL_SIZE,
	I2C_MEM_CALIB_CHANNEL = I2C_MEM_CALIB_VALUE + 4,
	I2C_MEM_CALIB_KEY,
	I2C_MEM_CALIB_STATUS,
	I2C_MODBUS_SETINGS,
	I2C_NBS1,
	I2C_MBS2,
	I2C_MBS3,
	I2C_MODBUS_ID_OFFSET,
	I2C_RTC_YEAR,
	I2C_RTC_MONTH,
	I2C_RTC_DAY,
	I2C_RTC_HOUR,
	I2C_RTC_MINUTE,
	I2C_RTC_SECOND,
	I2C_RTC_SET_YEAR,
	I2C_RTC_SET_MONTH,
	I2C_RTC_SET_DAY,
	I2C_RTC_SET_HOUR,
	I2C_RTC_SET_MINUTE,
	I2C_RTC_SET_SECOND,
	I2C_RTC_CMD,
	I2C_MEM_WDT_RESET,
	I2C_MEM_WDT_INTERVAL_SET,
	I2C_MEM_WDT_INTERVAL_GET = I2C_MEM_WDT_INTERVAL_SET + 2,
	I2C_MEM_WDT_INIT_INTERVAL_SET = I2C_MEM_WDT_INTERVAL_GET + 2,
	I2C_MEM_WDT_INIT_INTERVAL_GET = I2C_MEM_WDT_INIT_INTERVAL_SET + 2,
	I2C_MEM_WDT_RESET_COUNT = I2C_MEM_WDT_INIT_INTERVAL_GET + 2,
	I2C_MEM_WDT_CLEAR_RESET_COUNT = I2C_MEM_WDT_RESET_COUNT + 2,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_SET,
	I2C_MEM_WDT_POWER_OFF_INTERVAL_GET = I2C_MEM_WDT_POWER_OFF_INTERVAL_SET + 4,
	I2C_MEM_DIGI_RISING = I2C_MEM_WDT_POWER_OFF_INTERVAL_GET + 4,
	I2C_MEM_DIGI_FALLING,
	I2C_MEM_DIGI_COUNT_RST,
	I2C_MEM_DIGI_COUNT,

	I2C_MEM_OWB_DEV = I2C_MEM_DIGI_COUNT + DIGI_CH_NO * DIGI_CNT_SIZE,
	I2C_MEM_OWB_TEMP_ALL,
	I2C_MEM_OWB_ROM_CODE_IDX = I2C_MEM_OWB_TEMP_ALL + OWB_TEMP_VAL_SIZE,
	I2C_MEM_OWB_ROM_CODE,
	I2C_MEM_OWB_START_SEARCH = I2C_MEM_OWB_ROM_CODE + OWB_ROM_SIZE,
	I2C_MEM_OWB_TEMP,

	I2C_MEM_CPU_RESET = 0xaa,
  I2C_MEM_PUMP_PWM_PRESCALER, //2 bytes
	I2C_MEM_REVISION_MAJOR = 253,
	I2C_MEM_REVISION_MINOR,
	SLAVE_BUFF_SIZE = 255
};

#define OK 0
#define ERR -1
#define ARG_CNT_ERR -2
#define ARG_RANGE_ERR -3
#define IO_ERR -4

#define STR_(x) #x
#define STR(x) STR_(x)
#define MASK_1 1
#define MASK_2 3
#define MASK_3 7
#define MASK_4 15
#define MASK_5 31
#define MASK_6 63
#define MASK_7 127
#define MASK_(x) MASK_##x
#define MASK(x) MASK_(x)

typedef enum {
	OFF,
	ON,
	STATE_COUNT,
} State;

#endif /* DATA_H */

// vi:fdm=marker

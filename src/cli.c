#include "analog.h"
#include "analog/u10out.h"
#include "analog/u5in.h"
#include "calib.h"
#include "cli.h"
#include "comm.h"
#include "data.h"
#include "digi.h"
#include "fet.h"
#include "help.h"
#include "owb.h"
#include "pump.h"
#include "rs485.h"
#include "rtc.h"
#include "rtd.h"
#include "wdt.h"

const CliCmdType *gCmdArray[] = {
	&CMD_HELP,
	&CMD_VERSION,
	&CMD_GET_CARD_INFO,
	&CMD_RTD_TEMP_READ,
	&CMD_RTD_RES_READ,
	&CMD_RTD_RES_CALIB,
	&CMD_OWB_READ,
	&CMD_OWB_ID_READ,
	&CMD_OWB_SNS_CNT_READ,
	&CMD_OWB_SCAN,
	&CMD_DIGI_READ,
	&CMD_DIGI_EDGE_WRITE,
	&CMD_DIGI_EDGE_READ,
	&CMD_DIGI_CNT_READ,
	&CMD_DIGI_CNT_RESET,
	&CMD_CAL_STATUS,
	&CMD_FET_READ,
	&CMD_FET_WRITE,
	&CMD_RTC_GET,
	&CMD_RTC_SET,
	&CMD_PUMP_READ,
	&CMD_PUMP_WRITE,
  &CMD_PUMP_PRESCALER_WRITE,
	&CMD_WDT_RELOAD,
	&CMD_WDT_SET_PERIOD,
	&CMD_WDT_GET_PERIOD,
	&CMD_WDT_SET_INIT_PERIOD,
	&CMD_WDT_GET_INIT_PERIOD,
	&CMD_WDT_SET_OFF_PERIOD,
	&CMD_WDT_GET_OFF_PERIOD,
	&CMD_WDT_GET_RESET_COUNT,
	&CMD_WDT_CLR_RESET_COUNT,
	&CMD_U5_IN_READ,
	&CMD_U5_IN_CAL,
	&CMD_U10_OUT_READ,
	&CMD_U10_OUT_CAL,
	&CMD_U10_OUT_WRITE,
	&CMD_CFG485_READ,
	&CMD_CFG485_WRITE,
	0
};

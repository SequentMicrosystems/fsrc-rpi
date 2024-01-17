#include "../analog.h"
#include "u5in.h"

bool badU5InCh(int ch) {
	if(!(MIN_CH_NO <= ch && ch <= U5_IN_CH_NO)) {
		printf("0-10V input channel out of range![%d..%d]\n", MIN_CH_NO, U5_IN_CH_NO);
		return true;
	}
	return false;
}

const CliCmdType CMD_U5_IN_READ = {/*{{{*/
	"uinrd",
	2,
	&doU5InRead,
	"  uinrd            Read 0-5V input voltage value(V)\n",
	"  Usage:           "PROGRAM_NAME" <id> uinrd <channel>\n",
	"  Example:         "PROGRAM_NAME" 0 uinrd 2 #Read voltage on 0-5V input channel #2 on board #0\n",
};
int doU5InRead(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int id = atoi(argv[1]);
	int dev = doBoardInit(id);
	if(dev < 0) {
		return ERR;
	}
	int ch = atoi(argv[3]);
	if(badU5InCh(ch)) {
		return ARG_RANGE_ERR;
	}
	float val = 0;
	if(OK != val16Get(dev, I2C_MEM_U5_IN, ch, VOLT_TO_MILIVOLT, &val)) {
		return ERR;
	}
	printf("%0.3f\n", val);
	return OK;
}/*}}}*/

const CliCmdType CMD_U5_IN_CAL = {/*{{{*/
	"uincal",
	2,
	&doU5InCal,
	"  uincal           Calibrate 0-5 input channel, the calibration must be done in 2 points\n",
	"  Usage 1:         "PROGRAM_NAME" <id> uincal <channel> <value(V)>\n"
	"  Usage 2:         "PROGRAM_NAME" <id> uincal <channel> reset\n",
	"  Example:         "PROGRAM_NAME" 0 uincal 1 0.5; Calibrate the 0-5V input channel #1 on board #0 at 0.5V\n"
};
int doU5InCal(int argc, char *argv[]) {
	if(argc != 5) {
		return ARG_CNT_ERR;
	}
	int ch = atoi(argv[3]);
	if(badU5InCh(ch)) {
		return ARG_RANGE_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if(dev < 0) {
		return ERR;
	}
	if(strcasecmp(argv[4], "reset") == 0) {
		if(OK != calibReset(dev, CAL_U5_IN + (ch - 1))) {
			return ERR;
		}
		return OK;
	}
	float value = atof(argv[4]);
	if(OK != calibSet(dev, CAL_U5_IN + (ch - 1), value)) {
		return ERR;
	}
	return OK;
}/*}}}*/

// vi: fdm=marker

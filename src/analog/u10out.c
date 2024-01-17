#include "../analog.h"
#include "u10out.h"

bool badU10OutCh(int ch) {
	if(!(MIN_CH_NO <= ch && ch <= U10_OUT_CH_NO)) {
		printf("0-10V output channel out of range![%d..%d]\n", MIN_CH_NO, U10_OUT_CH_NO);
		return true;
	}
	return false;
}

const CliCmdType CMD_U10_OUT_READ = {/*{{{*/
	"uoutrd",
	2,
	&doU10OutRead,
	"  uoutrd           Read 0-10V output voltage value(V)\n",
	"  Usage:           "PROGRAM_NAME" <id> uoutrd <channel>\n",
	"  Example:         "PROGRAM_NAME" 0 uoutrd 2 #Read voltage on 0-10V output channel #2 on board #0\n",
};
int doU10OutRead(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int id = atoi(argv[1]);
	int dev = doBoardInit(id);
	if(dev < 0) {
		return ERR;
	}
	int ch = atoi(argv[3]);
	if(badU10OutCh(ch)) {
		return ARG_RANGE_ERR;
	}
	float val = 0;
	if(OK != val16Get(dev, I2C_MEM_U10_OUT, ch, VOLT_TO_MILIVOLT, &val)) {
		return ERR;
	}
	printf("%0.3f\n", val);
	return OK;
}/*}}}*/
const CliCmdType CMD_U10_OUT_WRITE = {/*{{{*/
	"uoutwr",
	2,
	&doU10OutWrite,
	"  uoutwr           Write 0-10V output voltage value(V)\n",
	"  Usage:           "PROGRAM_NAME" <id> uoutwr <channel> <value(V)>\n",
	"  Example:         "PROGRAM_NAME" 0 uoutwr 2 2.5 #Write 2.5V to 0-10V output channel #2 on board #0\n",
};
int doU10OutWrite(int argc, char *argv[]) {
	if(argc != 5) {
		return ARG_CNT_ERR;
	}
	int id = atoi(argv[1]);
	int dev = doBoardInit(id);
	if(dev < 0) {
		return ERR;
	}
	int ch = atoi(argv[3]);
	if(badU10OutCh(ch)) {
		return ARG_RANGE_ERR;
	}
	float val = atof(argv[4]);
	if(!(0 <= val && val <= 10)) {
		printf("Invalid voltage value, must be 0..10\n");
		return ARG_RANGE_ERR;
	}
	if(OK != val16Set(dev, I2C_MEM_U10_OUT, ch, VOLT_TO_MILIVOLT, val)) {
		return ERR;
	}
	return OK;
}/*}}}*/

const CliCmdType CMD_U10_OUT_CAL = {/*{{{*/
	"uoutcal",
	2,
	&doU10OutCal,
	"  uoutcal          Calibrate 0-10V output channel, the calibration must be done in 2 points at min 5V apart\n",
	"  Usage 1:         "PROGRAM_NAME" <id> uoutcal <channel> <value(V)>\n"
	"  Usage 2:         "PROGRAM_NAME" <id> uoutcal <channel> reset\n",
	"  Example:         "PROGRAM_NAME" 0 uoutcal 1 0.5; Calibrate the 0-10V output channel #1 on board #0 at 0.5V\n"
};
int doU10OutCal(int argc, char *argv[]) {
	if(argc != 5) {
		return ARG_CNT_ERR;
	}
	int ch = atoi(argv[3]);
	if(badU10OutCh(ch)) {
		return ARG_RANGE_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if(dev < 0) {
		return ERR;
	}
	if(strcasecmp(argv[4], "reset") == 0) {
		if(OK != calibReset(dev, CAL_U10_OUT + (ch - 1))) {
			return ERR;
		}
		return OK;
	}
	float value = atof(argv[4]);
	if(OK != calibSet(dev, CAL_U10_OUT + (ch - 1), value)) {
		return ERR;
	}
	return OK;
}/*}}}*/

// vi: fdm=marker

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "comm.h"
#include "data.h"
#include "digi.h"

// TODO: Add ranges in all error messages

bool badDigiCh(uint8_t ch) {
	if(!(MIN_CH_NO <= ch && ch <= DIGI_CH_NO)) {
		printf("Digital channel number value out of range![%d..%d]\n", MIN_CH_NO, DIGI_CH_NO);
		return true;
	}
	return false;
}
bool badDigiEncCh(uint8_t ch) {
	if(!(MIN_CH_NO <= ch && ch <= DIGI_CH_NO / 2)) {
		printf("Digital encoded channel number value out of range![%d..%d]\n", MIN_CH_NO, DIGI_CH_NO / 2);
		return true;
	}
	return false;
}

int digiChGet(int dev, uint8_t ch, State *state) {
	if(NULL == state) {
		return ERR;
	}
	if(badDigiCh(ch)) {
		printf("Invalid digi ch nr!\n");
		return ERR;
	}
	uint8_t buf[1];
	if(OK != i2cMem8Read(dev, I2C_MEM_DIGI, buf, 1)) {
		return ERR;
	}
	if(buf[0] & (1 << (ch - 1))) {
		*state = ON;
	}
	else {
		*state = OFF;
	}
	return OK;
}

int digiGet(int dev, int *val) {
	uint8_t buff[1];
	if(NULL == val) {
		return ERR;
	}
	if(OK != i2cMem8Read(dev, I2C_MEM_DIGI, buff, 1)) {
		return ERR;
	}
	*val = buff[0];
	return OK;
}

int digiEdgeGet(int dev, uint8_t ch, uint8_t *val) {
	if(NULL == val) {
		return ERR;
	}
	if(badDigiCh(ch)) {
		printf("Invalid digi ch nr!\n");
		return ERR;
	}
	uint8_t buf[2];
	if(OK != i2cMem8Read(dev, I2C_MEM_DIGI_RISING, buf, 2)) {
		return ERR;
	}
	uint8_t rising = buf[0];
	uint8_t falling = buf[1];
	*val = 0;
	if(rising & (1 << (ch - 1))) {
		*val |= 1<<0;
	}
	if(falling & (1 << (ch - 1))) {
		*val |= 1<<1;
	}
	return OK;
}

int digiEdgeSet(int dev, uint8_t ch, uint8_t val) {
	if(badDigiCh(ch)) {
		return ERR;
	}
	uint8_t buf[2];
	if(OK != i2cMem8Read(dev, I2C_MEM_DIGI_RISING, buf, 2)) {
		return ERR;
	}
	uint8_t rising = buf[0];
	uint8_t falling = buf[1];
	uint32_t mask = 1 << (ch - 1);
	if(val & 1<<0) { //check rising
		rising |= mask;
	}
	else {
		rising &= ~mask;
	}
	if(val & 1<<1) { //check falling
		falling |= mask;
	}
	else {
		falling &= ~mask;
	}
	buf[0] = rising;
	buf[1] = falling;
	if(OK != i2cMem8Write(dev, I2C_MEM_DIGI_RISING, buf, 2)) {
		return ERR;
	}
	return OK;
}

int digiCountGet(int dev, uint8_t ch, uint32_t *val) {
	if(badDigiCh(ch)) {
		return ERR;
	}
	if(NULL == val) {
		return ERR;
	}
	uint8_t buf[4];
	if(OK != i2cMem8Read(dev, I2C_MEM_DIGI_COUNT + DIGI_CNT_SIZE * (ch - 1), buf, DIGI_CNT_SIZE)) {
		return ERR;
	}
	memcpy(val, buf, 4);
	return OK;
}

int digiCountReset(int dev, uint8_t ch) {
	if(badDigiCh(ch)) {
		return ERR;
	}
	if(OK != i2cMem8Write(dev, I2C_MEM_DIGI_COUNT_RST, &ch, 1)) {
		return ERR;
	}
	return OK;
}

const CliCmdType CMD_DIGI_READ = {
        "optrd",
        2,
        &doDigiRead,
        "  optrd            Read digicoupled inputs status\n",
        "  Usage:           "PROGRAM_NAME" <id> optrd <channel>\n"
        "  Usage:           "PROGRAM_NAME" <id> optrd\n",
        "  Example:         "PROGRAM_NAME" 0 optrd 2; Read Status of Digital input ch #2 on Board #0\n"
};
int doDigiRead(int argc, char *argv[]) {
	int dev = doBoardInit(atoi(argv[1]));
	if(dev < 0) {
		return ERR;
	}
	if(argc == 4) {
		int channel = atoi(argv[3]);
		if(badDigiCh(channel)) {
			return ARG_RANGE_ERR;
		}
		State state = STATE_COUNT;
		if(OK != digiChGet(dev, channel, &state)) {
			printf("Fail to read!\n");
			return ERR;
		}
		if(state != OFF) {
			printf("1\n");
		}
		else {
			printf("0\n");
		}
	}
	else if(argc == 3) {
		int val;
		if(OK != digiGet(dev, &val)) {
			printf("Fail to read!\n");
			return ERR;
		}
		printf("%d\n", val);
	}
	else {
		return ARG_CNT_ERR;
	}
	return OK;
}

const CliCmdType CMD_DIGI_EDGE_READ = {
        "optedgerd",
        2,
        &doDigiEdgeRead,
        "  optedgerd        Read digicoupled counting edges 0 - none; 1 - rising; 2 - falling; 3 - both\n",
        "  Usage:           "PROGRAM_NAME" <id> optedgerd <channel>\n",
        "  Example:         "PROGRAM_NAME" 0 optedgerd 2; Read counting edges of digicoupled channel #2 on Board #0\n"
};
int doDigiEdgeRead(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if(dev < 0) {
		return ERR;
	}
	uint8_t channel = (uint8_t)atoi(argv[3]);
	if(badDigiCh(channel)) {
		return ARG_RANGE_ERR;
	}
	uint8_t val;
	if(OK != digiEdgeGet(dev, channel, &val)) {
		printf("Fail to read!\n");
		return ERR;
	}
	printf("%d\n", val);
	return OK;
}

const CliCmdType CMD_DIGI_EDGE_WRITE = {
        "optedgewr",
        2,
        &doDigiEdgeWrite,
        "  optedgewr        Set digicoupled channel counting edges  0- count disable;\n"
	"                   1-count rising edges; 2 - count falling edges; 3 - count both edges\n",
        "  Usage:           "PROGRAM_NAME" <id> optedgewr <channel> <edges> \n",
        "  Example:         "PROGRAM_NAME" 0 optedgewr 2 1; Set Digital channel #2 on Board #0 to count rising edges\n"
};
int doDigiEdgeWrite(int argc, char *argv[]) {
	if( (argc != 5)) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if(dev <= 0) {
		return ERR;
	}
	int channel = atoi(argv[3]);
	if(badDigiCh(channel)) {
		return ARG_RANGE_ERR;
	}
	uint8_t state = 0;
	if(strcasecmp(argv[4], "none") == 0) {
		state = 0;
	}
	else if(strcasecmp(argv[4], "up") == 0
		|| strcasecmp(argv[4], "rising") == 0) {
		state = 1;
	}
	else if(strcasecmp(argv[4], "down") == 0
		|| strcasecmp(argv[4], "falling") == 0) {
		state = 2;
	}
	else if(strcasecmp(argv[4], "both") == 0) {
		state = 3;
	}
	else {
		state = (uint8_t)atoi(argv[4]);
		// TODO: FIXME: bug: atoi returns 0 even if argv[4] is not a number
		if(!(state <= 3)) {
			printf("Invalid edge counting type [0..3]!\n");
			return ARG_RANGE_ERR;
		}
	}
	if(OK != digiEdgeSet(dev, channel, state)) {
		printf("Fail to write digicoupled ch edge counting \n");
		return ERR;
	}
	return OK;
}


const CliCmdType CMD_DIGI_CNT_READ = {
        "optcntrd",
        2,
        &doDigiCntRead,
        "  optcntrd         Read digicoupled inputs edges count for one channel\n",
        "  Usage:           "PROGRAM_NAME" <id> optcntrd <channel>\n",
        "  Example:         "PROGRAM_NAME" 0 optcntrd 2; Read contor of digi input #2 on Board #0\n"
};
int doDigiCntRead(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if(dev <= 0) {
		return ERR;
	}
	uint8_t channel = 0;
	channel = atoi(argv[3]);
	if(badDigiCh(channel)) {
		printf("Digital ch number value out of range!\n");
		return ARG_RANGE_ERR;
	}
	uint32_t val = 0;
	if(OK != digiCountGet(dev, channel, &val)) {
		printf("Fail to read!\n");
		return ERR;
	}
	printf("%u\n", val);
	return OK;
}

const CliCmdType CMD_DIGI_CNT_RESET = {
        "optcntrst",
        2,
        &doDigiCntReset,
        "  optcntrst        Reset digicoupled inputs edges count for one channel\n",
        "  Usage:           "PROGRAM_NAME" <id> optcntrst <channel>\n",
        "  Example:         "PROGRAM_NAME" 0 optcntrst 2; Reset contor of digi input #2 on Board #0\n"
};
int doDigiCntReset(int argc, char *argv[]) {
	if(argc != 4) {
		return ARG_CNT_ERR;
	}
	int dev = doBoardInit(atoi(argv[1]));
	if(dev < 0) {
		return ERR;
	}
	uint8_t channel = 0;
	channel = atoi(argv[3]);
	if(badDigiCh(channel)) {
		printf("Digital ch number value out of range!\n");
		return ARG_RANGE_ERR;
	}
	if(OK != digiCountReset(dev, channel)) {
		printf("Fail to reset!\n");
		return ERR;
	}
	return OK;
}

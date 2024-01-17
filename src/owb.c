#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comm.h"
#include "data.h"
#include "owb.h"

const CliCmdType CMD_OWB_READ = {
	"owbtrd",
	2,
	&doOwbGet,
	"  owbtrd           Display the temperature readed from a one wire bus connected sensor\n",
	"  Usage:           "PROGRAM_NAME" <stack> owbtrd <sensor (1.."STR(OWB_CH_NO)">\n",
	"  Example:         "PROGRAM_NAME" 0 owbtrd 1 Display the temperature of the sensor #1\n"
};
int doOwbGet(int argc, char *argv[])
{
	int dev = -1;
	uint8_t buff[5];
	int resp = 0;
	int channel = 0;
	float temp = 0;
	if (argc != 4) {
		return ARG_CNT_ERR;
	}
	channel = atoi(argv[3]);
	if (channel < 1 || channel > OWB_CH_NO) {
		return ERR;
	}
	dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0) {
		return ERR;
	}
	if (OK != i2cMem8Read(dev, I2C_MEM_OWB_DEV, buff, 1)) {
		printf("Fail to read one wire bus info!\n");
		return ERR;
	}
	if(channel > buff[0]) {
		printf("Invalid channel number, only %d sensors connected!\n", buff[0]);
		return ERR;
	}
	if (OK != i2cMem8Read(dev, I2C_MEM_OWB_TEMP + (channel - 1) * OWB_TEMP_VAL_SIZE , buff, OWB_TEMP_VAL_SIZE)) {
		printf("Fail to read one wire bus info!\n");
		return ERR;
	}
	memcpy(&resp, buff, 2);
	temp = (float)resp / 100;
	printf("%0.2f C\n", temp);
	return OK;
}

const CliCmdType CMD_OWB_ID_READ = {
	"owbidrd",
	2,
	&doOwbIdGet,
        "  owbidrd          Display the 64bits ROM ID of the one wire bus connected sensor\n",
        "  Usage:           "PROGRAM_NAME" <stack> owbidrd <sensor (1.."STR(OWB_CH_NO)")>\n",
        "  Example:         "PROGRAM_NAME" 0 owbidrd 1 Display the ROM ID of the sensor #1\n"
};
int doOwbIdGet(int argc, char *argv[]) {
	int dev = -1;
	uint8_t buff[8];
	int channel = 0;
	uint64_t romID = 0;
	if (argc != 4) {
		return ARG_CNT_ERR;
	}
	channel = atoi(argv[3]);
	if (channel < 1 || channel > OWB_CH_NO) {
		return ERR;
	}
	dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0) {
		return ERR;
	}
	buff[0] = 0xff & (channel - 1);
	if (OK != i2cMem8Write(dev, I2C_MEM_OWB_ROM_CODE_IDX, buff, 1)) {
		printf("Fail to read one wire bus info!\n");
		return ERR;
	}
	if (OK != i2cMem8Read(dev, I2C_MEM_OWB_DEV, buff, 1)) {
		printf("Fail to read one wire bus info!\n");
		return ERR;
	}
	if (channel > buff[0]) {
		printf("Invalid channel number, only %d sensors connected!\n", buff[0]);
		return ERR;
	}
	if (OK != i2cMem8Read(dev, I2C_MEM_OWB_ROM_CODE , buff, 8)) {
		printf("Fail to read one wire bus info!\n");
		return ERR;
	}
	memcpy(&romID, buff, 8);
	printf("0x%llx\n", (long long unsigned int)romID);
	return OK;
}

const CliCmdType CMD_OWB_SNS_CNT_READ = {
	"owbcntrd",
	2,
	&doOwbSensCountRead,
        "  owbcntrd         Display the number of One Wire Bus connected sensors\n",
        "  Usage:           "PROGRAM_NAME" <stack> owbcntrd\n",
        "  Example:         "PROGRAM_NAME" 0 owbcntrd  Display the number of sensors connected\n"
};

int doOwbSensCountRead(int argc, char *argv[]) {
	int dev = -1;
	uint8_t buff[2];
	if (argc != 3) {
		return ARG_CNT_ERR;
	}
	dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0) {
		return ERR;
	}
	if (OK != i2cMem8Read(dev, I2C_MEM_OWB_DEV, buff, 1)) {
		printf("Fail to read!\n");
		return ERR;
	}

	printf("%d\n", buff[0]);
	return OK;
}

const CliCmdType CMD_OWB_SCAN = {
	"owbscan",
	2,
	&doOwbScan,
        "  owbscan          Start One Wire Bus scaning procedure\n",
        "  Usage:           "PROGRAM_NAME" <stack> owbscan\n",
        "  Example:         "PROGRAM_NAME" 0 owbscan  Start One Wire Bus scaning procedure\n"
};
int doOwbScan(int argc, char *argv[]) {
	int dev = -1;
	uint8_t buff[2];
	if (argc != 3) {
		return ARG_CNT_ERR;
	}
	dev = doBoardInit(atoi(argv[1]));
	if (dev <= 0) {
		return ERR;
	}
	buff[0] = 0xaa;
	if (OK != i2cMem8Write(dev, I2C_MEM_OWB_START_SEARCH, buff, 1)) {
		printf("Fail to write!\n");
		return ERR;
	}
	printf("OK\n");
	return OK;
}

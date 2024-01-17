#include <stdio.h>
#include <stdlib.h>

#include "comm.h"
#include "data.h"
#include "fet.h"

const CliCmdType CMD_FET_READ = {
	"fetrd",
        2,
        &doFetRead,
        "  fetrd            Read fet state\n",
        "  Usage 1:         "PROGRAM_NAME" <id> fetrd <channel[1.."STR(FET_CH_NO)"]>\n"
        "  Usage 2:         "PROGRAM_NAME" <id> fetrd\n",
        "  Example:         "PROGRAM_NAME" 0 fetrd 2  Get the state of fet #2 on board #0\n"
};
int doFetRead(int argc, char *argv[]) {
        if(!(argc == 3 || argc == 4)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if(dev < 0) {
                return ERR;
        }
        if(argc == 3) {
		uint8_t buf[1];
                if(OK != i2cMem8Read(dev, I2C_MEM_FETS, buf, 1)) {
                        printf("Fail to read!\n");
                        return ERR;
                }
		for(int rel = 1; rel <= FET_CH_NO; ++rel) {
			if(buf[0] & (1 << (rel - 1))) {
				printf("1 ");
			} else {
				printf("0 ");
			}
		}
		printf("\n");
        }
        else if(argc == 4) {
		uint8_t buf[1];
		if(OK != i2cMem8Read(dev, I2C_MEM_FETS, buf, 1)) {
			printf("Fail to write!\n");
			return ERR;
		}
		int rel = atoi(argv[3]);
                if(!(1 <= rel && rel <= FET_CH_NO)) {
			printf("Led number out of range");
                        return ARG_RANGE_ERR;
                }
		if(buf[0] & (1 << (rel - 1))) {
			printf("1\n"); /* rel ON */
		} else {
			printf("0\n");
		}
        }
        return OK;
} 

const CliCmdType CMD_FET_WRITE = {
	"fetwr",
        2,
        &doFetWrite,
        "  fetwr            Change fet state\n",
        "  Usage 1:         "PROGRAM_NAME" <id> fetwr <channel[1.."STR(FET_CH_NO)"]> <state(0/1)>\n"
        "  Usage 2:         "PROGRAM_NAME" <id> fetwr <mask[0.."STR(MASK(FET_CH_NO))"]>\n",
        "  Example:         "PROGRAM_NAME" 0 fetwr 2 1  Set the state of fet #2 to ON\n"
};
int doFetWrite(int argc, char *argv[]) {
        if(!(argc == 4 || argc == 5)) {
                return ARG_CNT_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if(dev < 0) {
                return ERR;
        }
        if(argc == 4) {
                int state = 0;
                state = atoi(argv[3]);
                if(!(0 <= state && state <= (1 << FET_CH_NO) - 1)) {
                        return ARG_RANGE_ERR;
                }
                uint8_t buf[1];
                buf[0] = 0xff & state;
                if(OK != i2cMem8Write(dev, I2C_MEM_FETS, buf, 1)) {
                        printf("Fail to write!\n");
                        return ERR;
                }
        }
        else if(argc == 5) {
                int state = 0;
                int rel = atoi(argv[3]);
                if(!(1 <= rel && rel <= FET_CH_NO)) {
			printf("Led number out of range");
                        return ARG_RANGE_ERR;
                }
                state = atoi(argv[4]);
                uint8_t buf[1];
                buf[0] = 0xff & rel;
                if(state > 0) {
                        if(OK != i2cMem8Write(dev, I2C_MEM_FET_SET, buf, 1)) {
                                printf("Fail to write!\n");
                                return ERR;
                        }
                }
                else {
                        if(OK != i2cMem8Write(dev, I2C_MEM_FET_CLR, buf, 1)) {
                                printf("Fail to write!\n");
                                return ERR;
                        }
                }
        }
        return OK;
} 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "comm.h"
#include "data.h"
#include "pump.h"

const CliCmdType CMD_PUMP_READ = {
        "pumprd",
        2,
        &doPumpRead,
        "  pumprd           Display the pump value in %\n",
        "  Usage:           "PROGRAM_NAME" <id> pumprd <ch [1.."STR(PUMP_CH_NO)"]>\n",
        "  Example:         "PROGRAM_NAME" 0 pumprd 1  Display the pump 1 value on board #0 \n"
};
int doPumpRead(int argc, char *argv[]) {
        (void)argv;
        if (argc != 4) {
                return ARG_CNT_ERR;
        }
        int ch = atoi(argv[3]);
        if (!(1 <= ch && ch <= PUMP_CH_NO)) {
                return ARG_RANGE_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if (dev < 0) {
                return ERR;
        }
        uint8_t buf[2];
        if (OK != i2cMem8Read(dev, I2C_MEM_PUMP + PUMP_VAL_SIZE * (ch - 1), buf, PUMP_VAL_SIZE)) {
		printf("Fail to read!\n");
		return ERR;
        }
        int16_t val;
        memcpy(&val, buf, 2);
        printf("%.1f\n", (float)val / 10);
        return OK;
}

const CliCmdType CMD_PUMP_WRITE = {
        "pumpwr",
        2,
        &doPumpWrite,
        "  pumpwr           Set the pump value ["STR(PUMP_VAL_MIN)".."STR(PUMP_VAL_MAX)"]\n",
        "  Usage:           "PROGRAM_NAME" <id> pumpwr <ch (1.."STR(PUMP_CH_NO)"> <value(%)>\n",
        "  Example:         "PROGRAM_NAME" 0 pumpwr 1 25.2  Set the pump 1 value to 25.2% on board #0  \n"
};
int doPumpWrite(int argc, char *argv[]) {
        if (argc != 5) {
                return ARG_CNT_ERR;
        }
        int ch = atoi(argv[3]);
        if (!(1 <= ch && ch <= PUMP_CH_NO)) {
		printf("Pump channel out of range[1.."STR(PUMP_CH_NO)"]");
                return ARG_RANGE_ERR;
        }
        float val = atof(argv[4]);
        if (!(PUMP_VAL_MIN <= val && val <= PUMP_VAL_MAX)) {
		printf("Pump value out of range["STR(PUMP_VAL_MIN)".."STR(PUMP_VAL_MAX)"]!");
                return ARG_RANGE_ERR;
        }
        int dev = doBoardInit(atoi(argv[1]));
        if (dev <= 0) {
                return ERR;
        }
        int16_t aux = round(val * 10);
        uint8_t buf[2];
        memcpy(buf, &aux, 2);
        if (OK != i2cMem8Write(dev, I2C_MEM_PUMP + PUMP_VAL_SIZE * (ch - 1), buf, PUMP_VAL_SIZE)) {
                printf("Fail to write!\n");
                return ERR;
        }
        return OK;
}


const CliCmdType CMD_PUMP_PRESCALER_WRITE = {
        "fdivwr",
        2,
        &doPrescWrite,
        "  fdivwr           Set the pump PWM frequency divider [0..65535], PWM freq = 64kHz/(divider + 1)\n",
        "  Usage:           "PROGRAM_NAME" <id> fdivwr <value [0..65535]>\n",
        "  Example:         "PROGRAM_NAME" 0 fdivwr 3  Set the pump pwm frequency to 16kHz \n"
};
int doPrescWrite(int argc, char *argv[]) {
        if (argc != 4) {
                return ARG_CNT_ERR;
        }
        int div = atoi(argv[3]);

        int dev = doBoardInit(atoi(argv[1]));
        if (dev <= 0) {
                return ERR;
        }
        uint16_t aux = (uint16_t)div;
        uint8_t buf[2];
        memcpy(buf, &aux, 2);
        if (OK != i2cMem8Write(dev, I2C_MEM_PUMP_PWM_PRESCALER, buf, 2)) {
                printf("Fail to write!\n");
                return ERR;
        }
        return OK;
}


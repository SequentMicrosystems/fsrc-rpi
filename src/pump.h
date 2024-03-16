#include "cli.h"

extern const CliCmdType CMD_PUMP_READ;
extern const CliCmdType CMD_PUMP_WRITE;
extern const CliCmdType CMD_PUMP_PRESCALER_WRITE ;

int doPumpRead(int argc, char *argv[]);
int doPumpWrite(int argc, char *argv[]);
int doPrescWrite(int argc, char *argv[]);

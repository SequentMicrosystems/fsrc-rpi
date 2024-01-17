#include "cli.h"

extern const CliCmdType CMD_OWB_READ;
extern const CliCmdType CMD_OWB_ID_READ;
extern const CliCmdType CMD_OWB_SNS_CNT_READ;
extern const CliCmdType CMD_OWB_SCAN;

int doOwbGet(int argc, char *argv[]);
int doOwbIdGet(int argc, char *argv[]);
int doOwbSensCountRead(int argc, char *argv[]);
int doOwbScan(int argc, char *argv[]);

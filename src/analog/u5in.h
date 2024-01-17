#ifndef U5IN_H_
#define U5IN_H_

#include "../cli.h"

extern const CliCmdType CMD_U5_IN_READ;

extern const CliCmdType CMD_U5_IN_CAL;


int doU5InRead(int argc, char *argv[]);

int doU5InCal(int argc, char *argv[]);

#endif /* U5IN_H_ */

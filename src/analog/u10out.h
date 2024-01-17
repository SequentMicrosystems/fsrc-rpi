#ifndef U10OUT_H_
#define U10OUT_H_

#include "../cli.h"

extern const CliCmdType CMD_U10_OUT_READ;
extern const CliCmdType CMD_U10_OUT_CAL;

extern const CliCmdType CMD_U10_OUT_WRITE;


int doU10OutRead(int argc, char *argv[]);
int doU10OutWrite(int argc, char *argv[]);

int doU10OutCal(int argc, char *argv[]);

#endif /* U10OUT_H_ */

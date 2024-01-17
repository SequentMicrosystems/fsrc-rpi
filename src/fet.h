#ifndef FET_H
#define FET_H

#include "cli.h"

extern const CliCmdType CMD_FET_READ;
extern const CliCmdType CMD_FET_WRITE;

int doFetRead(int argc, char *argv[]);
int doFetWrite(int argc, char *argv[]);

#endif /* FET_H */

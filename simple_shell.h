#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

/* header files */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

void execute_command(char *command, int *status);

#endif /* SIMPLE_SHELL_H */

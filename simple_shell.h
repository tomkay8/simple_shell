#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Function to execute a command */
int execute_command(const char *command);

/* Other function prototypes can be added here */

#endif

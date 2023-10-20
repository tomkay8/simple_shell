#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

int execute_command(char *command) {
    pid_t pid; /* Declare pid_t at the beginning*/

    /* Create an array to hold the command and arguments */
    char *args[2];
    args[0] = command;
    args[1] = NULL;

    /* Create a child process */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* This code is executed by the child process */
        /* Use execve to execute the command */
        if (execve(command, args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        /* This code is executed by the parent process */
        int status;
        wait(&status);

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return -1; /* Execution failed */
        }
    }

    return 0; /* This line indicates success */
}


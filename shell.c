#include "shell.h"

int execute_command(char *command)
{
    pid_t pid;
    char *args[2];

    args[0] = command;
    args[1] = NULL;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        if (execve(command, args, NULL) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        wait(&status);
        if (WIFEXITED(status))
        {
            return WEXITSTATUS(status);
        }
        else
        {
            return -1;
        }
    }
    return 0;
}


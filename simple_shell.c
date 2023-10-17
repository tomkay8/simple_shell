#include "simple_shell.h"

int main()
{
    char command[MAX_COMMAND_LENGTH];
    int status;

    while (1)
    {
        /* Display the prompt */
        printf("$ ");
        fflush(stdout);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            /* Check for end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        if (command[strlen(command) - 1] == '\n')
        {
            /* Remove the trailing newline character */
            command[strlen(command) - 1] = '\0';
        }

        execute_command(command, &status); /* Call the function with status variable */
    }

    return 0;
}

void execute_command(char *command, int *status)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed"); /* Print an error message for fork failure */
        exit(1);
    }
    else if (pid == 0)
    {
        char *args[] = {command, NULL}; /* Array of pointers */
        execve(command, args, NULL);    /* Try to execute the command */
        perror("Command not found");    /* Print an error message if the command is not found */
        exit(1);
    }
    else
    {
        wait(status); /* Wait for the child process to finish */
    }
}

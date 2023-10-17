#include "simple_shell.h"

int main()
{
    char command[MAX_COMMAND_LENGTH];
    int status;

    while (1)
    {
        /* Display the prompt */
        write(1, "$ ", 2);

        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
        {
            /* Check for end of file (Ctrl+D) */
            write(1, "\n", 1);
            break;
        }

        if (command[strlen(command) - 1] == '\n')
        {
            /* Remove the trailing newline character */
            command[strlen(command) - 1] = '\0';
        }

        execute_command(command, &status); /* Call the function with the status variable */
    }

    return 0;
}

void execute_command(char *command, int *status)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        char *error_msg = "Fork failed\n";
        write(2, error_msg, strlen(error_msg)); /* Print an error message for fork failure */
        _exit(1);
    }
    else if (pid == 0)
    {
        char *args[MAX_ARGUMENTS + 2]; /* Array of pointers with space for arguments and two NULL pointers */
        int i = 0;
        char *token = strtok(command, " ");

        while (token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        if (execve(args[0], args, NULL) == -1)
        {
            char *error_msg = "Command not found\n";
            write(2, error_msg, strlen(error_msg)); /* Print an error message if the command is not found */
            _exit(1);
        }
    }
    else
    {
        wait(status); /* Wait for the child process to finish */
    }
}

#include "shell.h"

int main(void)
{
    char *error, *buffer = NULL;
    size_t bufsize = 0;
    ssize_t nread;

    while (1)
    {
        char prompt[] = "$ "; /* Display the prompt */

        write(STDOUT_FILENO, prompt, 2);
        nread = getline(&buffer, &bufsize, stdin);
        if (nread == -1)
        {
            if (feof(stdin))
            {
                char newline = '\n';

                write(STDOUT_FILENO, &newline, 1);
                break;
            }
            error = "getline error\n"; /* Assign value here */
            write(STDOUT_FILENO, error, 14);
            exit(EXIT_FAILURE);
        }
        /* Remove the newline character */
        if (buffer[nread - 1] == '\n')
        {
            buffer[nread - 1] = '\0';
        }
        if (isatty(STDIN_FILENO))
        {
            /* Execute the command */
            if (execute_command(buffer) == -1)
            {
                error = "Command not found\n"; /* Assign value here */
                write(STDOUT_FILENO, error, 18);
            }
        }
    }
    free(buffer);
    return (0);
}


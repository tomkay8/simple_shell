#include "simple_shell.h"

int main(void)
{
    char *input = NULL;
    size_t len = 0;

    while (1)
    {
        ssize_t read_size;
        pid_t child_pid;

        write(STDOUT_FILENO, "$ ", 2); /* Display the prompt */

        read_size = getline(&input, &len, stdin);

        if (read_size == -1)
        {
            if (feof(stdin))
            {
                /* Handle the end of file condition (Ctrl+D) */
                write(STDOUT_FILENO, "\n", 1);
                break;
            }
            write(STDERR_FILENO, "Error reading input\n", 20); /* Handle other errors */
            continue;
        }

        /* Remove the trailing newline character */
        if (input[read_size - 1] == '\n')
            input[read_size - 1] = '\0';

        /* Execute the command using execve */
        child_pid = fork();
        if (child_pid == -1)
        {
            write(STDERR_FILENO, "Fork failed\n", 12); /* Handle fork error */
            free(input);
            exit(1);
        }
        if (child_pid == 0)
        {
            char *args[2];
	    args[0]  = input;
	    args[1] =  NULL;
            execve(input, args, NULL);
            write(STDERR_FILENO, "No such file or directory\n", 18);
            free(input);
            exit(1);
        }
        else
        {
            int status;
            wait(&status); /* Wait for the child process to finish */
        }
    }

    free(input);
    return 0;
}

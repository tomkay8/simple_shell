#include "simple_shell.h"

/**
 * main - Entry point for the simple shell program
 *
 * Return: Always return 0
 */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	int status;

	while (1)
	{
		/* Display the prompt */
		write(STDOUT_FILENO, "$ ", 2);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			/* Check for end of file (Ctrl+D) */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (command[strlen(command) - 1] == '\n')
		{
			/* Remove the trailing newline character */
			command[strlen(command) - 1] = '\0';
		}

		execute_command(command, &status); /* Call the function */
	}

	return (0);
}

/**
 * execute_command - Execute a shell command
 * @command: The command to execute
 * @status: A pointer to the status variable
 *
 * This function forks child process and attempts to execute the given command.
 * If it successful, the child process is replaced with the executed command.
 *
 * Return: 0
 */
void execute_command(char *command, int *status)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (pid == 0)
	{
		char *args[2];

		args[0] = command;
		args[1] = NULL;

		execve(args[0], args, NULL); /* Try to execute the command */
		perror("Command not found");
		exit(1);
	}
	else
	{
		wait(status); /* Wait for the child process to finish */
	}
}

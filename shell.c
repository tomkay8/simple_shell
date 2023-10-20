#include "shell.h"
/**
 * execute_command - Execute a command in the child process.
 *
 * This function takes a command as input, craetes a child process, uses
 * execv to execute the command in the child process.
 *
 * @command: The command to be executed.
 *
 * Return: 0 if successful, -1 if fails.
 */
int execute_command(char *command)
{
	pid_t pid; /* Declare pid_t at the beginning*/
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	/* Create a child process */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		/* This code is executed by the child process */
		/* Use execve to execute the command */
		if (execve(command, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* This code is executed by the parent process */
		int status;

		wait(&status);

		if (WIFEXITED(status))
		{
			return (WEXITSTATUS(status));
		}
		else
		{
			return (-1); /* Execution failed */
		}
	}
	return (0); /* This line indicates success */
}

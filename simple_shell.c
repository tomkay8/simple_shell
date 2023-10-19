#include "simple_shell.h"

int main(void)
{
	char *input = NULL;
	size_t len = 0;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9); // Display the prompt

		ssize_t read_size;
		pid_t child_pid;

		read_size = getline(&input, &len, stdin);

		if (read_size == -1)
		{
			if (feof(stdin))
			{
				// Handle the end of file condition (Ctrl+D)
				write(STDOUT_FILENO, "\n", 1);
				break;
			}
			write(STDERR_FILENO, "Error reading input\n", 20); // Handle other errors
			continue;
		}

		// Remove the trailing newline character
		if (input[read_size - 1] == '\n')
			input[read_size - 1] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			free(input);
			break;
		}

		// Execute the command using execve
		child_pid = fork();
		if (child_pid == -1)
		{
			write(STDERR_FILENO, "Fork failed\n", 12); // Handle fork error
			free(input);
			exit(1);
		}
		if (child_pid == 0)
		{
			char *args[] = {input, NULL};
			execve(input, args, NULL);
			write(STDERR_FILENO, "Command not found\n", 18); // Handle execution errors
			free(input);
			exit(1);
		}
		else
		{
			int status;
			wait(&status); // Wait for the child process to finish
		}
	}

	free(input);
	return 0;
}

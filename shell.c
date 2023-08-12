#include "shell.h"

/**
 * main - Entry point
 * @argc: Number of arguments
 * @argv: Arguments
 * @env: Environment
 *
 * Return: 0 on success, 1 on failure
 */
int main(void)
{
	bool running = true;
	char input[1024];
	int status = 0;

	while (running)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#shell_dial_sb3$", 16);
		else
			running = false;
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			break;
		}
		pid_t child_pid;
		child_pid = fork();

		if (child_pid == -1)
		{
			perror("error");
			exit(1);
		}
		else if (child_pid == 0)
		{
			if (strlen(input) > 0)
			{
				if (execlp(input, input, NULL) == -1)
				{
					perror("error");
					exit(1);
				}
			}
			exit(0);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}
	return (0);
}

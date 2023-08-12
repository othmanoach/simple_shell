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
	while (running)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#shell_dial_sb3$", 16);
		else
			running = false;
		fgets(input, sizeof(input), stdin)
		if (input == NULL)
		{
			break;
		}
		if (input[0] == '\n')
			continue;
		if (_strcmp(input, "exit\n") == 0)
		{
			running = false;
			continue;
		}
	}
	return (0);
}

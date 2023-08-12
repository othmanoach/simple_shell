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

	while (running)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#shell_dial_sb3$", 16);
		else
			running = false;
	}
	return (0);
}

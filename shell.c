#include "shell.h"

int shell_helper(char *input);

/**
 * main - function that executes the shell
 *
 * Return: Always 0.
 */
int main(void)
{
	bool running = true;
	char input[MAX_INPUT_LENGTH];

	while (running)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#shell_dial_sb3$ ", 17);
		else
			running = false;

		if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
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
		shell_helper(input);
	}
	return (0);
}
/**
 * shell_helper - function that executes the shell
 * @input: input from the user
 *
 * Return: Always 0.
 */
int shell_helper(char *input)
{
	char *args[MAX_INPUT_LENGTH];
	char *token = strtok(input, " ");
	int i = 0;
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	if (execvp(args[0], args) == -1)
	{
		perror("execvp");
	}
	return (0);
}

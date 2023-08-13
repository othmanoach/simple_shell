#include "shell.h"
int handleBuiltIn(char **tokens, char *buffer)
{
	if (_strcmp(tokens[0], "exit") == 0)
		return exitFunction(tokens, buffer);
	else if (_strcmp(tokens[0], "env") == 0)
		return envFunction();
	else
		return -1;
}

int envFunction(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		_puts(environ[i]);

	return 0;
}

int exitFunction(char **tokens, char *buffer)
{
	int i = 0;
	int exitStatus = 0;

	while (tokens[i])
		i++;
	if (i == 1)
	{
		freeArguments(tokens);
		free(buffer);
		exit(0);
	}
	if (_atoi(tokens[1]) == -1)
	{
		fprintf(stderr, "./shell_dial_sbe3: 1: exit: %s\n", tokens[1]);
		return 2;
	}
	exitStatus = atoi(tokens[1]);
	freeArguments(tokens);
	free(buffer);
	exit(exitStatus);
}

int _atoi(char *nptr)
{
	int i = 0, n = 0;

	if (nptr[i] == '+')
		i++;

	while (nptr[i])
	{
		if (nptr[i] < '0' || nptr[i] > '9')
			return -1;

		n = (n * 10) + (nptr[i] - '0');
		i++;
	}

	return n;
}

void freeArguments(char **arguments)
{
	int i = 0;

	while (arguments[i])
	{
		free(arguments[i]);
		i++;
	}
}

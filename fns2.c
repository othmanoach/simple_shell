#include "shell.h"

/**
 * _changeDirectory - Changes the current working directory.
 * @data: A pointer to a struct of data.
 */
void _changeDirectory(appData_t *data)
{
	char currentDirectory[500];

	getcwd(currentDirectory, 500);

	if (data == NULL)
	{
		return;
	}

	if (!data->arguments[1] ||
		_strcmp(data->arguments[1], "~") == 0 ||
		_strcmp(data->arguments[1], "~/") == 0)
		{
		_changeToHomeDirectory(data, currentDirectory);
	}
	else if (_strcmp(data->arguments[1], "-") == 0)
	{
		_changeToPreviousDirectory(data, currentDirectory);
	}
	else
	{
		_changeToAnyDirectory(data, currentDirectory);
	}
}

/**
 * _changeToAnyDirectory - Changes the current working directory to any.
 * @data: A pointer to a struct of data.
 * @currentDirectory: The current working directory.
 */
void _changeToAnyDirectory(appData_t *data, char *currentDirectory)
{
	char *newDirectory = data->arguments[1];

	if (access(newDirectory, R_OK | W_OK) == 0)
	{
		chdir(newDirectory);

		_setenv(data->env, "OLDPWD", currentDirectory, 1);
	} else
	{
		perror(newDirectory);
	}
}

/**
 * _changeToHomeDirectory - Changes the current working directory to home.
 * @data: A pointer to a struct of data.
 * @currentDirectory: The current working directory.
 */
void _changeToHomeDirectory(appData_t *data, char *currentDirectory)
{
	environment_t *newDirectoryEnv = _getenv(data->env, "HOME");

	if (newDirectoryEnv == NULL)
	{
		perror("HOME environment variable not set");
		return;
	}

	if (access(newDirectoryEnv->value, R_OK | W_OK) == 0)
	{
		chdir(newDirectoryEnv->value);

		_setenv(data->env, "OLDPWD", currentDirectory, 1);
	} else
	{
		perror(newDirectoryEnv->value);
	}
}

/**
 * _changeToPreviousDirectory - Changes the current working 
 * directory to previous.
 * @data: A pointer to a struct of data.
 * @currentDirectory: The current working directory.
 */
void _changeToPreviousDirectory(appData_t *data, char *currentDirectory)
{
	environment_t *previousDirectoryEnv = _getenv(data->env, "OLDPWD");

	if (previousDirectoryEnv == NULL)
	{
		perror("OLDPWD environment variable not set");
		return;
	}

	if (access(previousDirectoryEnv->value, R_OK | W_OK) == 0)
	{
		chdir(previousDirectoryEnv->value);

		_setenv(data->env, "OLDPWD", currentDirectory, 1);
	} else
	{
		perror(previousDirectoryEnv->value);
	}
}

/**
 * _checkEndCharacter - Checks if the last character of a string is '\0'.
 * @inputString: The string to be checked.
 * Return: If the last character is '\0' - 1.
 * Otherwise - 0.
 */
int _checkEndCharacter(char *inputString)
{
	int currentIndex = 0;

	if (inputString == NULL)
	{
		return (0);
	}

	while (!inputString[currentIndex])
	{
		currentIndex++;
	}

	return (inputString[currentIndex] == '\0');
}

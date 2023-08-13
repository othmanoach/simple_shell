#include "shell.h"
int executeCommand(char **arguments, char *buffer)
{
	pid_t processID;
	char *commandPath = NULL;
	int exitCode = handleBuiltIn(arguments, buffer);

	if (exitCode == -1)
	{
		commandPath = getCommandPath(arguments[0]);
		if (!commandPath)
		{
			_puts("Not found");
			return 2;
		}
		processID = fork();
		if (processID == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (processID == 0)
		{
			if (execve(commandPath, arguments, environ) == -1)
			{
				perror("execve");
				freeArguments(arguments);
				free(buffer);
				exit(2);
			}
		}
		else
		{
			waitpid(processID, &exitCode, 0);
			if (exitCode != 0)
				exitCode = 2;
		}
		if (_strcmp(commandPath, arguments[0]) != 0)
			free(commandPath);
	}
	return exitCode;
}

char *getEnvVariable(char *name)
{
	int i = 0;
	ssize_t len = _strlen(name);

	for (; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return &environ[i][len + 1];
	}
	return (NULL);
}

char *getCommandPath(char *command)
{
	char *path, *pathCopy, *pathToken, *filePath;
	int commandLength, directoryLength;
	struct stat buffer;

	path = getEnvVariable("PATH");
	if (path)
	{
		pathCopy = _strdup(path);
		commandLength = _strlen(command);
		pathToken = strtok(pathCopy, ":");

		while (pathToken)
		{
			directoryLength = _strlen(pathToken);
			filePath = malloc(commandLength + directoryLength + 2);
			_strcpy(filePath, pathToken);
			_strcat(filePath, "/");
			_strcat(filePath, command);
			_strcat(filePath, "\0");
			if (stat(filePath, &buffer) == 0)
			{
				free(pathCopy);
				return filePath;
			}
			else
			{
				free(filePath);
				pathToken = strtok(NULL, ":");
			}
		}
		free(pathCopy);
		if (stat(command, &buffer) == 0)
		{
			return command;
		}
		return (NULL);
	}

	return (NULL);
}

void splitInput(char *inputBuffer, char **tokenArray)
{
	size_t tokenLength;
	const char *delimiter = " \t\n";
	char *token = NULL;
	int count = 0;
	char *inputCopy = NULL;

	inputCopy = _strdup(inputBuffer);
	token = strtok(inputCopy, delimiter);
	for (count = 0; token; count++)
	{
		tokenLength = _strlen(token);
		tokenArray[count] = malloc(sizeof(char *) * tokenLength);
		_strncpy(tokenArray[count], token, tokenLength + 1);
		token = strtok(NULL, delimiter);
	}
	free(inputCopy);
}

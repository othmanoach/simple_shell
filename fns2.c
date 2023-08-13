#include "shell.h"

/**
 * executeCommand - executes a command
 * @arguments: array of arguments
 * @buffer: buffer that holds the user input
 * Return: 0 if successful, 1 if not
 */
int executeCommand(char **arguments, char *buffer)
{
	pid_t processID;
	char *commandPath = NULL;
	int exitCode = handleBuiltIn(arguments, buffer);
	int i = 0;

	if (exitCode == -1)
	{
		commandPath = getCommandPath(arguments[0]);
		if (!commandPath)
		{
			_puts("Not found");
			return (2);
		}
		processID = fork();
		if (processID == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (processID == 0)
		{
			int out_fd = dup(STDOUT_FILENO);
			close(STDOUT_FILENO);
			if (dup2(out_fd, STDOUT_FILENO) == -1)
			{perror("dup2");
			exit(EXIT_FAILURE);}

			if (execve(commandPath, arguments, environ) == -1)
			{perror("execve");
				freeArguments(arguments);
				free(buffer);
				exit(2);}
		}
		else{int status;
			while (i < 3) {waitpid(processID, &status, 0);
				if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
					exitCode = 2;
				i++;}}
		if (_strcmp(commandPath, arguments[0]) != 0)
			free(commandPath);
	}
	return exitCode;
}

/**
 * getEnvVariable - gets an environment variable
 * @name: name of the environment variable
 * Return: pointer to the environment variable
 */
char *getEnvVariable(char *name)
{
	int i = 0;
	ssize_t len = _strlen(name);

	for (; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
	}
	return (NULL);
}

/**
 * getCommandPath - gets the path of a command
 * @command: command to get the path of
 * Return: pointer to the path
 */
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
				return (filePath);
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
			return (command);
		}
		return (NULL);
	}

	return (NULL);
}

/**
 * splitInput - splits the input into tokens
 * @inputBuffer: buffer that holds the user input
 * @tokenArray: array of tokens
 */
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


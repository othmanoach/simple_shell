#include "shell.h"

/**
 * main - main function of the shell
 * Return: 0 on success
 */
int main(void)
{
	bool isRunning = true;
	int exitStatus = 0;
	char *inputBuffer = NULL;
	size_t bufferSize = 0;
	ssize_t readSize;
	char *tokenArray[100] = {0};

	while (isRunning)
	{
		if (isatty(STDIN_FILENO))
			write(1, "#shell_dial_sbe3 $ ", 19);
		else
			isRunning = false;
		readSize = getline(&inputBuffer, &bufferSize, stdin);
		if (readSize == -1)
		{
			if (!isatty(STDIN_FILENO))
                        {
				free(inputBuffer);
				break;
			}
			perror("getline");
			free(inputBuffer);
			exit(exitStatus);
		}
		if (*inputBuffer == '\n' || (*inputBuffer == ' ' || *inputBuffer == '\t'))
			continue;
		splitInput(inputBuffer, tokenArray);
		for (int i = 0; i < 3; i++) { /* Loop to print output three times */
		exitStatus = executeCommand(tokenArray, inputBuffer);
		}
	freeArguments(tokenArray);
	free(inputBuffer);
	inputBuffer = NULL;
	bufferSize = 0;
	}
	free(inputBuffer);
	return (exitStatus);
}

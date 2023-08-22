#include "shell.h"

/**
 * _env - print environement variable
 * @prmData: data structure
 */
void _env(appData_t *prmData)
{
	_printenv(prmData->env);
}
/**
 * _envHelp - print help for env command
 */
void _envHelp(void)
{
	_puts("env: env\n");
	_puts("    prints the current environment.\n\n");
	_puts("    Has no options\n");
}
/**
 * _errorHandler - print error message
 * @prmData: data structure
 * @messageCode: message code
 */
void _errorHandler(appData_t *prmData, int messageCode)
{
	int i = 0;

	errorMessage_t errors[] = {
		{00, "Error unknown"},
		{100, "Error reading from Prompt - Zero tokens"},
		{101, "No such file or directory"},
		{102, "FATAL ERROR: UNABLE TO CREATE CHILD PROCESS"},
		{103, "command not found"},
		{104, "FATAL ERROR: NO MEMORY AVAILABLE."},
		{105, "FATAL ERROR: UNABLE TO CREATE CMD LIST"},
		{106, "Illegal number"},
		{999, ""}
	};

	_puts(prmData->programName);
	_puts(": ");
	_puts("1");
	_puts(": ");
	_puts(prmData->commandName);
	_puts(": ");
	while (i < 9)
	{
		if (messageCode == (errors + i)->code)
		{
			_puts((errors + i)->msg);
			_puts(": ");
			_puts(prmData->arguments[1]);
		}
		i++;
	}
	_puts("\n");
}
/**
 * _execCommand - Execute a command
 * @prmData: app data array
 */
void _execCommand(appData_t *prmData)
{
	pid_t child_pid;
	char *command;
	int status;

	if (prmData->commandName == NULL)
		return;

	command = _which(prmData);

	if (command != NULL)
	{
		if (prmData->commandName != command)
			free(prmData->commandName);
		prmData->commandName = command;
	}
	else
	{
		return;
	}

	child_pid = fork();
	if (child_pid == 0)
	{
		if (execve(prmData->commandName, prmData->arguments, NULL) == -1)
			_errorHandler(prmData, 103);
		return;
	}
	else if (child_pid == -1)
	{
		_errorHandler(prmData, 102);
	}
	else
		waitpid(child_pid, &status, WUNTRACED);
}
/**
 * _exitHelp - print help for exit command
 */
void _exitHelp(void)
{
	_puts("exit: exit [n]\n");
	_puts("    Exit the shell.\n\n");
	_puts("    Exits the shell with a status of N.  ");
	_puts("    If N is omitted, the exit status\n");
	_puts("    is that of the last command executed.\n");
}

#include "shell.h"
/**
 * _wordNumber - returns word number
 * @prmString: char pointer
 * @prmSeparators: separators
 * Return: Word number
 */
int _wordNumber(char *prmString, char *prmSeparators)
{
	int cLoop = 0, count = 0;

	while (prmString[cLoop] != '\0')
	{
		if (
			(
				_inArray(prmString[cLoop], prmSeparators) != 1 ||
				prmString[cLoop] != '\0'
			 ) &&
			(
				_inArray(prmString[cLoop + 1], prmSeparators) == 1 ||
				prmString[cLoop + 1] == '\0'
			)
		)
			count++;
		cLoop++;
	}

	return (count);
}
/**
 * _exitStatus - exit status
 * @prmData: data structure
 */
void _exitStatus(appData_t *prmData)
{
	int code = EXIT_SUCCESS;

	if (prmData == NULL)
		return;

	if (prmData->arguments != NULL)
		code = _atoi(prmData->arguments[1]);

	if (code < 0 || (prmData->arguments[1] != NULL
	&& !_isNumber(prmData->arguments[1])))
	{
		_errorHandler(prmData, 106);
		code = 2;
	}

	_freeAppData(prmData);
	_freeEnvList(prmData->env);
	prmData->env = NULL;
	free(prmData);
	exit(code);
}
/**
 * _getCustomFunction - check custom command
 * @prmCommand: command
 * Return: pointer function
 */
void (*_getCustomFunction(char *prmCommand))(appData_t *)
{
	int i = 0;

	customCommand_t fp[] = {
		{"cd", _changeDirectory},
		{"env", _env},
		{"setenv", _setEnvironment},
		{"unsetenv", _unsetEnvironment},
		{"exit", _exitStatus},
		{"help", _help}
	};

	while (i < 6)
	{
		if (_strcmp(prmCommand, (fp + i)->commandName) == 0)
			return ((fp + i)->func);
		i++;
	}

	return (NULL);
}
/**
 * _help - manage command help
 * @prmData: data structure
 */
void _help(appData_t *prmData)
{
	if (prmData == NULL)
		return;
	if (prmData->commandName == NULL)
		return;
	if (
		prmData->arguments == NULL ||
		prmData->arguments[0] == NULL ||
		prmData->arguments[1] == NULL
	)
		return;
	if (_strcmp(prmData->arguments[1], "cd") == 0)
		_cdHelp();
	else if (_strcmp(prmData->arguments[1], "env") == 0)
		_envHelp();
	else if (_strcmp(prmData->arguments[1], "setenv") == 0)
		_setenvHelp();
	else if (_strcmp(prmData->arguments[1], "unsetenv") == 0)
		_unsetenvHelp();
	else if (_strcmp(prmData->arguments[1], "exit") == 0)
		_exitHelp();
	else if (_strcmp(prmData->arguments[1], "help") == 0)
		_helpHelp();
	else
		_defaultHelp(prmData->arguments[1]);
}
/**
 * _isNumber - check if string is a number
 * @s: string to verify
 * Return: 1 if string is a number.
 */
int _isNumber(char *s)
{
	if (*s == '\0')
	{
		return (1);
	}
	if (!_isdigit(*s))
	{
		return (0);
	}
	else
	{
		return (_isNumber(s + 1));
	}
}

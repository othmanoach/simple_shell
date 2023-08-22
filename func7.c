#include "shell.h"

/**
 * _helpHelp - print help for help command
 */
void _helpHelp(void)
{
	_puts("help: help [-dms] [pattern ...]\n");
	_puts("    Display information about builtin commands.\n\n");
	_puts("    Displays brief summaries of builtin commands.  If PATTERN is\n");
	_puts("    specified, gives detailed help on all commands ");
	_puts("    matching PATTERN,\n");
	_puts("    otherwise the list of help topics is printed.\n\n");
	_puts("    Options:\n");
	_puts("      -d        output short description for each topic\n");
	_puts("      -m        display usage in pseudo-manpage format\n");
	_puts("      -s        output only a short usage synopsis for each topic m");
	_puts("atching\n        PATTERN\n\n");
	_puts("    Arguments:\n");
	_puts("      PATTERN   Pattern specifying a help topic\n\n");
	_puts("    Exit Status:\n");
	_puts("    Returns success unless PATTERN is not found or an invalid ");
	_puts("    option is given.\n");
}
/**
 * _inArray - Search a character in an array
 * @prmChar: character to search
 * @prmArray: character array where to search
 * Return: true if success
 */
int _inArray(char prmChar, char *prmArray)
{
	int cLoop;

	if (prmArray == NULL)
		return (0);

	for (cLoop = 0; prmArray[cLoop] != '\0'; cLoop++)
		if (prmArray[cLoop] == prmChar)
			return (1);

	return (0);
}
/**
 * _initData - init data structure
 * @prmArgv: pointer to pointer to
 * Return: data structure
 */
appData_t *_initData(char **prmArgv)
{
	appData_t *appData;

	appData = malloc(sizeof(appData_t) * 1);

	if (appData == NULL)
		return (NULL);

	appData->arguments = NULL;
	appData->buffer = NULL;
	appData->commandName = NULL;
	appData->commandList = NULL;
	appData->history = NULL;
	appData->env = NULL;
	appData->programName = (prmArgv[0] != NULL) ? prmArgv[0] : NULL;
	_initEnvData(appData);

	return (appData);
}
/**
 * _initEnvData - init environment linked list
 * @prmData: data structre
 */
void _initEnvData(appData_t *prmData)
{
	int cLoop = 0;
	environment_t *new;

	if (prmData == NULL)
		return;

	while (environ[cLoop] != NULL)
	{
		new = _addEnvNodeEnd(&prmData->env, environ[cLoop]);

		if (new == NULL)
		{
			free(prmData->env);
			prmData->env = NULL;
			return;
		}

		cLoop++;
	}
}
/**
 * _isdigit - test if a character is a number
 * @prmChar: char
 * Return: return 1 if true
 */
int _isdigit(char prmChar)
{
	return (prmChar >= '0' && prmChar <= '9');
}

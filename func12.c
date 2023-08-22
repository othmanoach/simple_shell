#include "shell.h"

/**
 * _strtow - splits a string into word
 * @prmString: the char pointer
 * @prmSeparators: separators
 * @prmEscapeSeparators: the escaping separators
 * Return: word array
 */
char **_strtow(char *prmString, char *prmSeparators, char *prmEscapeSeparators)
{
	int cLoop = 0, cLoop1 = 0, wordSize = 0, word_number = 0, size = 0;
	char *word = NULL, **words = NULL, character;

	if (prmString == NULL)
		return (NULL);

	size = _strlen(prmString);
	word_number = _wordNumber(prmString, prmSeparators);

	if (prmString == NULL || !prmString || word_number == 0)
		return (NULL);

	words = _calloc(sizeof(char *), (word_number + 1));

	if (words == NULL)
		return (NULL);

	for (cLoop = 0; cLoop <= size && cLoop1 < word_number; cLoop++)
	{
		character = prmString[cLoop];
		if (_checkEscapeSeparators(character, prmEscapeSeparators))
			break;
		if (!_checkSeparators(character, prmSeparators))
			wordSize++;
		else
			if (wordSize > 0)
			{
				word = _getword(prmString, cLoop - wordSize, wordSize);
				_addWord(word, &cLoop1, words);
				wordSize = 0;
			}
	}
	words[cLoop1] = NULL;

	return (words);
}
/**
 * _unsetenv - unset environment variable
 * @prmData: data structure
 * @prmName: environment name
 */
void _unsetenv(appData_t *prmData, char *prmName)
{
	_deleteEnvNode(prmData->env, prmName);
}
/**
 * _unsetenvHelp - print help for unsetenv command
 */
void _unsetenvHelp(void)
{
	_puts("unsetenv: unsetenv [VARIABLE]\n");
	_puts("    Initializes a new environment variable, or ");
	_puts("    modifies an existing one.\n\n");
	_puts("    VARIABLE must not have the character '='.\n");
	_puts("    If no arguments are given, setenv prints the current ");
	_puts("    environment.\n");
}
/**
 * _unsetEnvironment - unset environment variable
 * @prmData: data's structure
 */
void _unsetEnvironment(appData_t *prmData)
{
	if (prmData == NULL)
		return;

	if (prmData->arguments == NULL)
		return;

	if (prmData->arguments[1] == NULL)
		return;

	_unsetenv(prmData, prmData->arguments[1]);
}
/**
 * _which - return absolute path of a command
 * @prmData: app data structure
 * Return: absolute path
 */
char *_which(appData_t *prmData)
{
	char **pathList, *absolutePath;
	struct stat st;
	int cLoop = 0;

	if (
		prmData->commandName[0] == '.' &&
		prmData->commandName[1] == '/' &&
		stat(prmData->commandName, &st) == 0
	)
		return (prmData->commandName);

	pathList = _parsingPathEnvironment(prmData);

	if (pathList == NULL)
		return (NULL);

	while (pathList[cLoop] != NULL)
	{
		absolutePath = _generateAbsolutePath(pathList[cLoop], prmData->commandName);

		if (stat(absolutePath, &st) == 0)
		{
			_freeCharDoublePointer(pathList);
			return (absolutePath);
		}
		free(absolutePath);
		cLoop++;
	}
	_freeCharDoublePointer(pathList);

	if (stat(prmData->commandName, &st) == 0)
	{
		return (prmData->commandName);
	}
	else
		_errorHandler(prmData, 101);

	return (NULL);
}

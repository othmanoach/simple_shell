#include "shell.h"

/**
 * _changeToHomeDirectory - changing to home directory
 * @prmData: data structure
 * @prmCurrentDirectory: current directory path
 */
void _changeToHomeDirectory(appData_t *prmData, char *prmCurrentDirectory)
{
	environment_t *newDirectory;

	newDirectory = _getenv(prmData->env, "HOME");

	if (access(newDirectory->value, R_OK | W_OK) == 0)
	{
		chdir(newDirectory->value);
		_setenv(prmData->env, "OLDPWD", prmCurrentDirectory, 1);
	}
	else
	{
		perror(newDirectory->value);
	}
}
/**
 * _changeToPreviousDirectory - change to previous directory
 * @prmData: data structure
 * @prmCurrentDirectory: current directory path
 */
void _changeToPreviousDirectory(appData_t *prmData, char *prmCurrentDirectory)
{
	environment_t *newDirectory;

	newDirectory = _getenv(prmData->env, "OLDPWD");

	if (access(newDirectory->value, R_OK | W_OK) == 0)
	{
		chdir(newDirectory->value);
		_setenv(prmData->env, "OLDPWD", prmCurrentDirectory, 1);
	}
	else
	{
		perror(newDirectory->value);
	}
}
/**
 * _checkEndCharacter - check if a string have an end of file character
 * @prmString: string
 * Return: 0 if failed, 1 if success
 */
int _checkEndCharacter(char *prmString)
{
	int cLoop = 0;

	if (prmString == NULL)
		return (0);

	while (!prmString[cLoop])
		cLoop++;

	return (prmString[cLoop] == '\0');
}
/**
 * _checkEscapeSeparators - check if character corresponds
 *     to one of escape separators
 * @prmChar: character to compare
 * @prmEscapeSeparators: list a separators
 *
 * Return: 0 if failed, 1 if success
 */
int _checkEscapeSeparators(char prmChar, char *prmEscapeSeparators)
{
	if (prmEscapeSeparators == NULL)
		return (0);

	return (_inArray(prmChar, prmEscapeSeparators));
}
/**
 * _checkSeparators - check if a character correspond
 * to one of separators or EOF character
 * @prmChar: character to compare
 * @prmSeparators: list of separators:
 * Return: 0 if failed, 1 if success
 */
int _checkSeparators(char prmChar, char *prmSeparators)
{
	if (prmSeparators == NULL)
		return (0);

	return (
		_inArray(prmChar, prmSeparators) == 1 ||
		prmChar == '\0'
	);
}

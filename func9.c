#include "shell.h"

/**
 * _parsingPathEnvironment - split environment variable
 * @prmData: data structure
 * Return: string array
 */
char **_parsingPathEnvironment(appData_t *prmData)
{
	char **paths;
	environment_t *pathEnvNode;

	pathEnvNode = _getenv(prmData->env, "PATH");
	paths = _strtow(pathEnvNode->value, PATH_SEPARATOR, NULL);

	return (paths);
}
/**
 * _printenv - print environment variables
 * @prmEnviron: environment variable list
 */
void _printenv(environment_t *prmEnviron)
{
	if (prmEnviron == NULL)
		return;

	_puts(prmEnviron->name);
	_puts("=");
	if (prmEnviron->value != NULL)
		_puts(prmEnviron->value);
	_puts("\n");
	_printenv(prmEnviron->next);
}
/**
 * _prompt - display prompt
 */
void _prompt(void)
{
	_puts(PROMPT);
}
/**
 * _putchar - writes the character c to stdout
 * @prmChar: The character to print
 * Return: number of printed char
 */
int _putchar(char prmChar)
{
	return (write(STDIN_FILENO, &prmChar, 1));
}
/**
 * _puts - write all char from string to stdout
 * @prmStr: string to print
 * Return: number of printed char
 */

int _puts(char *prmStr)
{
	int i = 0, sum = 0;

	while (prmStr[i])
	{
		sum += _putchar(prmStr[i]);
		i++;
	}
	return (sum);
}
/**
 * _realloc - reallocates a memory block using malloc and free
 * @prmPtr: source pointer
 * @prmOldSize: in pointer size
 * @prmNewSize: out pointer size
 * Return: reallocated pointer
 */
void *_realloc(void *prmPtr, unsigned int prmOldSize, unsigned int prmNewSize)
{
	void *s = prmPtr;

	if (prmPtr == NULL)
		return (malloc(prmNewSize));
	if (prmNewSize == prmOldSize)
		return (prmPtr);
	if (prmNewSize == 0)
	{
		free(prmPtr);
		return (NULL);
	}

	s = malloc(prmNewSize);

	if (s == NULL)
		return (NULL);

	s = _memcpy(s, prmPtr, prmOldSize);
	free(prmPtr);

	return (s);
}
/**
 * _setenv - set environment value
 * @prmEnviron: environment linked list
 * @prmName: environment name
 * @prmValue: environment value
 * @prmOverwrite: overwrite
 */
void _setenv(
	environment_t *prmEnviron,
	char *prmName,
	char *prmValue,
	int prmOverwrite
) {
	environment_t *envNode;
	char *tmp;

	if (prmName == NULL || prmValue == NULL)
		return;

	envNode = _getenv(prmEnviron, prmName);

	if (envNode == NULL)
	{
		tmp = _generateEnvGlobal(prmName, prmValue);
		_addEnvNodeEnd(&prmEnviron, tmp);
		free(tmp);
	}
	else if (prmOverwrite == 1)
	{
		free(envNode->value);
		envNode->value = _strdup(prmValue);
	}
}
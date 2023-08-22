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

#include "shell.h"

/**
 * _setenvHelp - print help for setenv command
 */
void _setenvHelp(void)
{
	_puts("setenv: setenv [VARIABLE] [VALUE]\n");
	_puts("    Initializes a new environment variable, ");
	_puts("    or modifies an existing one.\n\n");
	_puts("    VARIABLE must not have the character '='.\n");
	_puts("    If no arguments are given, setenv prints ");
	_puts("    the current environment.\n");
}
/**
 * _setEnvironment - set environment variable
 * @prmData: data's structure
 */
void _setEnvironment(appData_t *prmData)
{
	if (prmData == NULL)
		return;

	if (prmData->arguments == NULL)
		return;

	if (prmData->arguments[1] == NULL || prmData->arguments[2] == NULL)
		return;

	_setenv(prmData->env, prmData->arguments[1], prmData->arguments[2], 1);
}
/**
 * _strcat - concatenates two string
 * @prmDest: char pointer
 * @prmSrc: char pointer
 * Return: string
 */
char *_strcat(char *prmDest, char *prmSrc)
{
	int length, d_size, s_size;

	d_size = _strlen(prmDest);
	s_size = _strlen(prmSrc);

	for (length = 0; length < s_size; length++)
	{
		prmDest[d_size + length] = prmSrc[length];
	}

	return (prmDest);
}
/**
 * _strcmp - compares two strings
 * @prmString1: char pointer
 * @prmString2: char pointer
 * Return: difference between ascii number
 */
int _strcmp(char *prmString1, char *prmString2)
{
	int length;

	for (length = 0; prmString1[length] != '\0'; length++)
	{
		if (prmString1[length] - prmString2[length] != 0)
			return (prmString1[length] - prmString2[length]);
	}

	return (0);
}
/**
 * _strconcat - concatenates two strings.
 * @prmString1: char pointer to concatenate
 * @prmString2: char pointer to concatenate
 * Return: char pointer concatenated
 */
char *_strconcat(char *prmString1, char *prmString2)
{
	char *s;
	int cLoop1, cLoop2, size;

	if (prmString1 == NULL)
		prmString1 = "\0";

	if (prmString2 == NULL)
		prmString2 = "\0";

	size = _strlen(prmString1) + _strlen(prmString2);
	s = malloc(sizeof(char) * (size + 1));

	if (s == NULL)
		return (NULL);

	for (cLoop1 = 0; prmString1[cLoop1]; cLoop1++)
		s[cLoop1] = prmString1[cLoop1];

	for (cLoop2 = 0; prmString2[cLoop2]; cLoop1++, cLoop2++)
		s[cLoop1] = prmString2[cLoop2];

	s[cLoop1] = '\0';

	return (s);
}
/**
 * _strcpy - copies the string pointed to by src, including the terminating
 *       null byte (\0),to the buffer pointed to by dest
 * @prmDest: char pointer
 * @prmSrc: char pointer
 * Return: char*
 */
char *_strcpy(char *prmDest, char *prmSrc)
{
	int cLoop, size = _strlen(prmSrc);

	for (cLoop = 0; cLoop < size; cLoop++)
	{
		prmDest[cLoop] = prmSrc[cLoop];
	}

	prmDest[size] = '\0';

	return (prmDest);
}
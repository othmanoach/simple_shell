#include "shell.h"

/**s
 * _strcspn - get the length of a prefix substring.s
 * @prmString: the string to searchs
 * @prmDeny: characters to denys
 * Return: a pointer to the first occurrence of the character cs
 *         in the string s, or NULL if the character is not founds
 */
unsigned int _strcspn(char *prmString, char *prmDeny)s
{
	unsigned int sLoop, dLoop;

	for (dLoop = 0; prmDeny[dLoop] != '\0'; dLoop++)s
	{
		for (sLoop = 0; prmDeny[dLoop] != prmString[sLoop]; sLoop++)
			if ('\0' == prmString[sLoop])
				return (sLoop);
	}

	return (sLoop);
}
/**
 * _strdup - a pointer to a newly allocated space in memory,
 *           which contains a copy of the string given as a parameter.
 * @prmString: char pointer to copy
 * Return: a new char pointer
 */
char *_strdup(char *prmString)
{
	char *string;
	int cLoop;

	if (prmString == NULL)
		return (NULL);

	string = malloc(sizeof(char) * (_strlen(prmString) + 1));

	if (string == NULL)
		return (NULL);

	for (cLoop = 0; cLoop < _strlen(prmString) + 1; cLoop++)
		string[cLoop] = prmString[cLoop];

	return (string);
}
/**
 * _strlen - return string length
 * @prmStr: string
 * Return: string length
 */
int _strlen(char *prmStr)
{
	if (prmStr == NULL || *prmStr == '\0')
		return (0);
	return (_strlen(prmStr + 1) + 1);
}
/**
 * _strncpy - copies a string
 * @prmDest: char pointer
 * @prmSrc: char pointer
 * @prmLimit: number of character
 * Return: string
 */
char *_strncpy(char *prmDest, char *prmSrc, int prmLimit)
{
	int length, size_s;

	size_s = _strlen(prmSrc);

	for (length = 0; length < prmLimit; length++)
	{
		prmDest[length] = (length <= size_s) ? prmSrc[length] : '\0';
	}

	return (prmDest);
}
/**
 * _strstr - locates a substring.
 * @prmHaystack: string where to search
 * @prmNeedle: string to search
 * @prmBegin: force to start at begin if true
 * Return: the address to first location
 */
char *_strstr(char *prmHaystack, char *prmNeedle, int prmBegin)
{
	int haystackLoop = 0, needleLoop = 0, size = _strlen(prmNeedle);

	if (prmNeedle[0] == '\0')
	{
		return (prmHaystack);
	}

	for (
		haystackLoop = 0, needleLoop = 0;
		(haystackLoop + needleLoop) < _strlen(prmHaystack);
		needleLoop++
	)
	{
		if (prmNeedle[needleLoop] != prmHaystack[haystackLoop + needleLoop])
		{
			if (prmBegin == 0)
			{
				haystackLoop += needleLoop;
				needleLoop = 0;
			}
			else
				return (NULL);
		}

		if (needleLoop == size - 1)
		{
			return (&prmHaystack[haystackLoop]);
		}
	}

	return (NULL);
}

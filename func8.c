#include "shell.h"

/**
 * _itoa - Convert an int to a string
 * @prmNumber: int to convert
 * Return: converted string
 */

char *_itoa(int prmNumber)
{
	char *s;
	int cLoop;
	long number;

	number = prmNumber;
	cLoop = _nbrLen(number);
	s = malloc(sizeof(char) * cLoop + 1);

	if (s == NULL)
	{
		return (NULL);
	}

	s[cLoop] = '\0';

	if (number == 0)
	{
		s = "0";
	}
	else if (number < 0)
	{
		s[0] = '-';
		number *= -1;
	}

	while (number)
	{
		s[--cLoop] = number % 10 + 48;
		number /= 10;
	}

	return (s);
}
/**
 * _listEnvLen - length of a linked list
 * @prmHead: first node
 * Return: length
 */
int _listEnvLen(environment_t *prmHead)
{
	if (prmHead == NULL)
		return (0);
	if (prmHead->next == NULL)
		return (1);
	else
		return (_listEnvLen(prmHead->next) + 1);
}
/**
 * _memcpy - copies n bytes from memory area src to memory area dest
 * @prmDest: pointer to memory area
 * @prmSrc: pointer to src memory area
 * @prmLimit: number ot bytes to fill
 * Return: pointer to dest
 */
char *_memcpy(char *prmDest, char *prmSrc, unsigned int prmLimit)
{
	unsigned int cLoop;

	for (cLoop = 0; cLoop < prmLimit; cLoop++)
	{
		prmDest[cLoop] = prmSrc[cLoop];
	}

	return (prmDest);
}
/**
 * _memset - fills the first n bytes of the memory area
 *      pointed to by s with the constant byte b
 * @prmString: pointer to memory area
 * @prmCharacter: constant
 * @prmLimit: number ot bytes to fill
 * Return: write n bytes of value b
 */
char *_memset(char *prmString, char prmCharacter, unsigned int prmLimit)
{
	unsigned int cLoop;

	for (cLoop = 0; cLoop < prmLimit; cLoop++)
	{
		prmString[cLoop] = prmCharacter;
	}

	return (prmString);
}
/**
 * _nbrLen - length of a number
 * @prmNumber: number
 * Return: length of the number
 */

int _nbrLen(int prmNumber)
{
	int cLoop = 0, number;

	if (prmNumber == 0)
		return (1);

	number = prmNumber;

	if (number < 0)
	{
		number *= -1;
		cLoop++;	/* for the sign char */
	}

	while (number)
	{
		number /= 10;
		cLoop++;
	}

	return (cLoop);
}
#include "shell.h"
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

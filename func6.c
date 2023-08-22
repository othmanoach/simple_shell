#include "shell.h"

/**
 * _getenv - get environment variable
 * @prmEnviron: first node
 * @prmName: environment variable name
 * Return: environment variable node
 */
environment_t *_getenv(environment_t *prmEnviron, char *prmName)
{
	if (prmEnviron == NULL)
		return (NULL);

	if (_strcmp(prmEnviron->name, prmName) == 0)
		return (prmEnviron);

	return (_getenv(prmEnviron->next, prmName));
}
/**
 * _getEnvIndex - return index of an environment variable
 * @prmHead: first node
 * @prmName: name
 * Return: index
 */
int _getEnvIndex(environment_t *prmHead, char *prmName)
{
	if (prmHead == NULL || _strcmp(prmHead->name, prmName) == 0)
		return (0);
	else
		return (_getEnvIndex(prmHead->next, prmName) + 1);
}
/**
 * _getenvname - return environment name
 * @prmVariable: environment name
 * Return: environment name
 */
char *_getenvname(char *prmVariable)
{
	char **tmp, *name;

	tmp = _strtow(prmVariable, ENV_SEPARATOR, NULL);

	if (tmp == NULL)
		return (NULL);

	name = _strdup(tmp[0]);
	_freeCharDoublePointer(tmp);
	tmp = NULL;

	return (name);
}
/**
 * _getLastEnvNode - get last node
 * @prmHeadNode: first node
 * Return: last element
 */
environment_t *_getLastEnvNode(environment_t *prmHeadNode)
{
	environment_t *head, *next;

	head = prmHeadNode;

	if (head == NULL)
		return (NULL);

	next = head->next;

	if (next == NULL)
		return (head);
	else
		return (_getLastEnvNode(next));
}
/**
 * _getword - returns word
 * @prmGlobal: char pointer
 * @prmOffset: start of the word
 * @prmSize: length of the word
 * Return: Word number
 */
char *_getword(char *prmGlobal, int prmOffset, int prmSize)
{
	char *word;
	int cLoop;

	word = malloc(sizeof(char) * prmSize + 1);

	if (word == NULL)
		return (NULL);

	for (cLoop = 0; cLoop < (prmSize); cLoop++)
		word[cLoop] = prmGlobal[prmOffset + cLoop];

	word[cLoop] = '\0';

	return (word);
}

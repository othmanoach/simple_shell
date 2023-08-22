#include "shell.h"

/**
 * _cleanString - erase begin spaces and ending spaces from string
 * @prmString: string to clean
 * Return: clean string
 */
char *_cleanString(char *prmString)
{
	int cLoopStart = 0, cLoopEnd = 0, size = 0;
	char *string;

	if (prmString == NULL)
		return (NULL);

	size = _strlen(prmString);

	while (_inArray(prmString[cLoopStart], " ") == 1)
		cLoopStart++;

	cLoopEnd = size - 1;
	while (_inArray(prmString[cLoopEnd], " ") == 1)
		cLoopEnd--;
	cLoopEnd = size - 1 - cLoopEnd;

	string = _calloc(sizeof(char), size - cLoopStart - cLoopEnd + 1);
	_strncpy(string, (prmString + cLoopStart), size - cLoopStart - cLoopEnd);
	string[size - cLoopStart - cLoopEnd] = '\0';

	prmString = _realloc(
		prmString,
		size,
		sizeof(char) * (size - cLoopStart - cLoopEnd + 1)
	);
	_strcpy(prmString, string);
	prmString[size - cLoopStart - cLoopEnd] = '\0';
	free(string);
	return (prmString);
}
/**
 * _createEnvNode - create a new node
 * @prmGlobal: global environment value
 * Return: new element
 */
environment_t *_createEnvNode(char *prmGlobal)
{
	environment_t *new;

	if (prmGlobal == NULL)
		return (NULL);

	new = malloc(sizeof(environment_t));
	if (new == NULL)
		return (NULL);

	new->name = _getenvname(prmGlobal);
	new->value = _getenvvalue(prmGlobal);
	new->global = _strdup(prmGlobal);
	new->next = NULL;

	return (new);
}
/**
 * _ctrlC - control c managment
 * @prmSignal: signal value
 */
void _ctrlC(int prmSignal __attribute__((unused)))
{
	_puts("\n");
	_prompt();
}
/**
 * _defaultHelp - print help when any command found
 * @prmCommand: command name
 */
void _defaultHelp(char *prmCommand)
{
	_puts("bash: help: Aucune rubrique d'aide ne correspond à \"");
	_puts(prmCommand);
	_puts("\". Essayez \"help help\", \"man -k ");
	_puts(prmCommand);
	_puts("\" ou \"info ");
	_puts(prmCommand);
	_puts("\".\n");
}
/**
 * _deleteEnvNode - delete an environment variable
 * @prmHead: first node
 * @prmName: name
 * Return: error code
 */
int _deleteEnvNode(environment_t *prmHead, char *prmName)
{
	environment_t *beforeNode, *afterNode, *currentNode, *firstNode;
	unsigned int length, currentIndex;

	firstNode = prmHead;
	currentIndex = _getEnvIndex(prmHead, prmName);

	if (firstNode == NULL)
		return (-1);

	length = _listEnvLen(firstNode);

	if (length == 0 || currentIndex > (unsigned int) length - 1)
		return (-1);

	if (currentIndex == 0)
	{
		prmHead = prmHead->next;
		free(firstNode);
		return (1);
	}

	beforeNode = _getEnvNodeAtIndex(firstNode, currentIndex - 1);
	if (currentIndex == length - 1)
		afterNode = NULL;
	else
		afterNode = _getEnvNodeAtIndex(firstNode, currentIndex + 1);

	currentNode = _getEnvNodeAtIndex(firstNode, currentIndex);
	beforeNode->next = afterNode;
	free(currentNode->name);
	currentNode->name = NULL;
	free(currentNode->value);
	currentNode->value = NULL;
	free(currentNode->global);
	currentNode->global = NULL;
	free(currentNode);
	currentNode = NULL;

	return (1);
}

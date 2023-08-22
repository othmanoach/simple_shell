#include "shell.h"

/**
 * _freeAppData - free all pointer of the appllication
 * @prmData: data structure
 */
void _freeAppData(appData_t *prmData)
{
	if (prmData == NULL)
		return;

	if (prmData->arguments != NULL)
		_freeCharDoublePointer(prmData->arguments);
	prmData->arguments = NULL;
	if (prmData->buffer != NULL)
		free(prmData->buffer);
	prmData->buffer = NULL;
	if (prmData->commandName != NULL)
		free(prmData->commandName);
	prmData->commandName = NULL;
	if (prmData->commandList != NULL)
		_freeCharDoublePointer(prmData->commandList);
	prmData->commandList = NULL;
	if (prmData->history != NULL)
		_freeCharDoublePointer(prmData->history);
	prmData->history = NULL;

}
/**
 * _freeCharDoublePointer - free memory of a double pointer
 * @prmPtr: double pointer
 */
void _freeCharDoublePointer(char **prmPtr)
{
	int cLoop = 0;

	if (prmPtr == NULL)
		return;

	while (prmPtr[cLoop] != NULL)
	{
		free(prmPtr[cLoop]);
		prmPtr[cLoop] = NULL;
		cLoop++;
	}
	free(prmPtr);
}
/**
 * _freeEnvList - free a struct linked list
 * @prmHeadNode: first element
 * Return: frees a list_t list
 */
void _freeEnvList(environment_t *prmHeadNode)
{
	if (prmHeadNode == NULL)
		return;
	_freeEnvList(prmHeadNode->next);
	free(prmHeadNode->name);
	prmHeadNode->name = NULL;
	free(prmHeadNode->value);
	prmHeadNode->value = NULL;
	free(prmHeadNode->global);
	prmHeadNode->global = NULL;
	free(prmHeadNode);
}
/**
 * _generateAbsolutePath - Generate an absolute path from environment variable
 * @prmPath: path environment variable
 * @prmCommandName: command name
 * Return: absolute path
 */
char *_generateAbsolutePath(char *prmPath, char *prmCommandName)
{
	char *tmp, *path, *absolutePath, lastCharacter;
	int pathValueSize;

	path = _strdup(prmPath);
	pathValueSize = _strlen(path);
	lastCharacter = path[pathValueSize - 1];

	if (lastCharacter != '/')
	{
		tmp = path;
		path = _strconcat(tmp, "/");
		free(tmp);
	}

	tmp = "";
	tmp = _strconcat(tmp, path);
	absolutePath = _strconcat(tmp, prmCommandName);
	free(tmp);
	free(path);

	return (absolutePath);
}
/**
 * _generateEnvGlobal - generate a global environment variable
 *   from name and value
 * @prmName: environment name
 * @prmValue: environment value
 * Return: global environment variable
 */
char *_generateEnvGlobal(char *prmName, char *prmValue)
{
	char *tmp, *global;

	global = "";
	global = _strconcat(global, prmName);
	tmp = _strconcat(global, "=");
	free(global);
	global = _strconcat(tmp, prmValue);
	free(tmp);

	return (global);
}

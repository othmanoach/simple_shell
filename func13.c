#include "shell.h"

/**
 * _getenvvalue - return environment value
 * @prmVariable: environment name
 * Return: environment value
 */
char *_getenvvalue(char *prmVariable)
{
	char **tmp, *name;

	tmp = _strtow(prmVariable, ENV_SEPARATOR, NULL);

	if (tmp == NULL)
		return (NULL);

	name = _strdup(tmp[1]);
	_freeCharDoublePointer(tmp);
	tmp = NULL;

	return (name);
}

/**
 * _getline - Return command line type by user
 * @prmData: data structure
 * Return: buffer
 */
void _getline(appData_t *prmData)
{
	char c = '\0';
	int i = 0, rd, bufferSize = BUFFER_SIZE;

	prmData->buffer = _calloc(sizeof(char), BUFFER_SIZE);

	while (c != '\n' && c != EOF)
	{
		rd = read(STDIN_FILENO, &c, 1);

		if (rd == 0)
		{
			_putchar('\n');
			if (prmData->env != NULL)
				_freeEnvList(prmData->env);
			prmData->env = NULL;
			_freeAppData(prmData);
			free(prmData);
			exit(EXIT_SUCCESS);
		}

		if (i >= bufferSize - 1)
		{
			prmData->buffer = _realloc(
				prmData->buffer,
				bufferSize,
				sizeof(char) * (i + 2)
			);
			bufferSize = i + 2;
		}
		prmData->buffer[i] = c;
		i++;
	}
	prmData->buffer[i] = '\0';
}

/**
 * _getEnvNodeAtIndex - the nth node of a listint_t linked list
 * @prmHead: first element
 * @prmIndex: element's number
 *
 * Return: a node
 */
environment_t *_getEnvNodeAtIndex(
	environment_t *prmHead,
	unsigned int prmIndex
) {
	unsigned int cLoop = 0;

	while (prmHead != NULL)
	{
		if (prmIndex == cLoop)
			return (prmHead);
		prmHead = prmHead->next;
		cLoop++;
	}

	return (NULL);
}


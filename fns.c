#include "shell.h"

/**
 * _addEnvNodeEnd - Adds a new node at the end of a linked list.
 * @head: A pointer to the head of the linked list.
 * @globalValue: The value to be added to the new node.
 * Return: If an error occurs - NULL.
 * Otherwise - a pointer to the new node.
 */
environment_t *_addEnvNodeEnd(environment_t **head, char *globalValue)
{
	environment_t *newNode, *lastNode;


	if (head == NULL)
	{
		return (NULL);
	}


	newNode = _createEnvNode(globalValue);
	if (newNode == NULL)
	{
		return (NULL);
	}


	if (*head == NULL)
	{
		*head = newNode;
	} else
	{

		lastNode = _getLastEnvNode(*head);


		if (lastNode == NULL)
		{
			free(newNode);
			return (NULL);
		}


		lastNode->next = newNode;
	}


	return (newNode);
}

/**
 * _addWordToCharArray - Adds a word to a char array.
 * @word: The word to be added.
 * @currentIndex: The current index of the char array.
 * @stringArray: The char array to add the word to.
 */
void _addWordToCharArray(char *word, int *currentIndex, char **stringArray)
{
	char *cleanedWord = _cleanString(word);

	stringArray[*currentIndex] = _strdup(cleanedWord);

	free(cleanedWord);
	(*currentIndex)++;
}

/**
 * customAtoi - Converts a string to an integer.
 * @inputString: The string to be converted.
 * Return: The converted integer.
 */
int customAtoi(char *inputString)
{
	char sign = 1, currentCharacter;
	int stringLength = _strlen(inputString), currentIndex;
	unsigned int resultNumber = 0;

	for (currentIndex = 0; currentIndex < stringLength; currentIndex++)
	{
		currentCharacter = inputString[currentIndex];

		if (_isdigit(currentCharacter))
		{
			resultNumber *= 10;
			resultNumber += currentCharacter - '0';
		}
		else if (currentCharacter == '-')
		{
			sign = -sign;
		}
		else if (resultNumber > 0)
		{
			break;
		}
	}
	return (sign * resultNumber);
}

/**
 * _customCalloc - Allocates memory for an array.
 * @numElements: The number of elements to allocate memory for.
 * @elementSize: The size of each element.
 * Return: If an error occurs - NULL.
 * Otherwise - a pointer to the allocated memory.
 */
void *_customCalloc(unsigned int numElements, unsigned int elementSize)
{
	void *allocatedMemory;

	if (numElements == 0 || elementSize == 0)
	{
		return (NULL);
	}

	allocatedMemory = malloc(numElements * elementSize);

	if (allocatedMemory == NULL)
	{
		return (NULL);
	}

	allocatedMemory =
	_customMemset(allocatedMemory, 0, numElements * elementSize);

	return (allocatedMemory);
}

/**
 * _printCdHelp - Prints the help page for the cd builtin.
 */
void _printCdHelp(void)
{
	_puts("cd: cd [-L|[-P [-e]] [-@]] [dir]\n    Change the shell working dir");
	_puts("ectory.\n\n    Change the current directory to DIR.  The default DIR");
	_puts(" is the value of the\n    HOME shell variable.\n    The variable CDP");
	_puts("ATH defines the search path for the directory containing\n    DIR.  ");
	_puts("Alternative directory names in CDPATH are separated by a ");
	_puts("colon (:).\n    A null directory name is the same as the current dir");
	_puts("ectory.  If DIR begins\n    with a slash (/), then CDPATH is not use");
	_puts("d.\n\n    If the directory is not found, and the shell option `cdabl");
	_puts("e_vars' is set,\n    the word is assumed to be  a variable name.  If");
	_puts(" that variable has a value,\n    its value is used for DIR.\n\n    O");
	_puts("ptions:\n        -L      force symbolic links to be followed: resolv");
	_puts("e symbolic links in\n        DIR after processing instances of `..'");
	_puts("\n        -P      use the physical directory structure without foll");
	_puts("owing symbolic\n        links: resolve symbolic links in DIR before");
	_puts(" processing instances\n        of `..'\n        -e      if the -P o");
	_puts("ption is supplied, and the current working directory\n        canno");
	_puts("t be determined successfully, exit with a non-zero status\n        ");
	_puts("-@  on systems that support it, present a file with extended attrib");
	_puts("utes\n            as a directory containing the file attributes\n\n");
	_puts("    The default is to follow symbolic links, as if `-L' were specif");
	_puts("ied.\n");
	_puts("    `..' is processed by removing the immediately previous pathname");
	_puts(" component\n    back to a slash or the beginning of DIR.\n\n");
	_puts("    Exit Status:\n");
	_puts("    Returns 0 if the directory is changed, and if $PWD is set succe");
	_puts("ssfully when\n    -P is used; non-zero otherwise.\n");
}

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define ENV_SEPARATOR "="
#define ESCAPE_SEPARATOR "#"
#define PATH_SEPARATOR ":"
#define COMMAND_SEPARATOR ";\n"
#define SEPARATORS " \n"
#define PROMPT "$ "

extern char **environ;

/**
 * struct environment_s - environment variable
 *
 * @name: environment name
 * @value: environment value
 * @next: points to the next node
 * @global: pointer to usr/bin PATH
 */
typedef struct environment_s
{
	char *name;   /* ex: PATH */
	char *value;  /* ex: /bin:/usr/bin */
	char *global; /* PATH=/bin:/usr/bin */
	struct environment_s *next;
} environment_t;

/**
 * struct appData_s - data variable
 *
 * @arguments: argument's array
 * @buffer: buffer
 * @commandName: command name
 * @commandList: command list
 * @history: array history
 * @programName: program name
 * @env: pointer to env variable
 */
typedef struct appData_s
{
	char **arguments;
	char *buffer;
	char *commandName;
	char **commandList;
	char **history;
	char *programName;
	environment_t *env;
} appData_t;

/**
 * struct errorMessage_s - An structure for each error message
 *
 * @code: error code
 * @msg: pointer to error message
 *
 */
typedef struct errorMessage_s
{
	int code;
	char *msg;
} errorMessage_t;

/**
 * struct customCommand_s - struct conversion to function
 *
 * @commandName: flag string
 * @func: pointer to func
 */
typedef struct customCommand_s
{
	char *commandName;
	void (*func)(appData_t *);
} customCommand_t;

environment_t *_addEnvNodeEnd(
	environment_t **prmHeadNode,
	char *prmGlobal
);

void _changeDirectory(appData_t *data);
void _changeToAnyDirectory(appData_t *data, char *currentDirectory);
void _changeToHomeDirectory(appData_t *data, char *currentDirectory);
void _changeToPreviousDirectory(appData_t *data, char *currentDirectory);
int _checkEndCharacter(char *inputString);
environment_t *_addEnvNodeEnd(environment_t **head, char *globalValue);
void _addWordToCharArray(char *word, int *currentIndex, char **stringArray);
int customAtoi(char *inputString);
void *_customCalloc(unsigned int numElements, unsigned int elementSize);
void _printCdHelp(void);

#endif
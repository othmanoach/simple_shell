#ifndef SHELL_H
#define SHELL_H
/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <ctype.h>

/* Global variables */

extern char **env;

/* ------------String functions--------------------- */


/* calculates the length of a string */
int _strlen(char *str);

/* concatenate two strings */
char *_strcat(char *dest, char *src);

/* print functions */
void _puts(char *str);
int _putchar(char c);


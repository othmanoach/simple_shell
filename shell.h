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

extern char **environ;

/* String functions */
int _strlen(char *s);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
char *_strtok(char *str, char *delim);
int _strncmp(char *s1, char *s2, size_t n);
char *_strncpy(char *dest, char *src, size_t n);

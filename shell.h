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
#define MAX_INPUT_LENGTH 1024
extern char **env;

/* ------------String functions--------------------- */
/* Function prototype */
int shell_helper(char *input);

/* Define _puts function */
void _puts(char *str) {
    /* Implementation of _puts */
}

/* Define _strcmp function */
int _strcmp(char *s1, char *s2) {
    /* Implementation of _strcmp */
}

/* Define env variable */
char **env;

/* calculates the length of a string */
int _strlen(char *str); 

/* concatenate two strings */
char *_strcat(char *dest, char *src);

/* compare two strings */
int _strcmp(char *s1, char *s2);

/* compare two strings */
int _strncmp(const char *s1, const char *s2, size_t n);

/* copies a string */
char *_strcpy(char *dest, char *src);

/* copies a string */
char *_strncpy(char *dest, char *src, int n);

/* returns a pointer to a new string which is a duplicate of the string str */
char *_strdup(char *str);

/* write a character to stdout */
int _putchar(char c);

/* write a string to stdout */
void _puts(char *str);


/* --------------String functions------------------- */







/* --------------Memory functions------------------- */

/* copies a memory area */
char *_memcpy(char *dest, char *src, unsigned int n); 

/* --------------Memory functions------------------- */

#endif /* SHELL_H */

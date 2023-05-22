#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

extern char **environ;

char *_getenv(const char *name);
int _strncmp(char *s1, char *s2, size_t n);
size_t _strlen(const char *s);
char *searchfile(char **argv, char *path);

#endif /*MAIN_H*/

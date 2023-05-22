#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFF 10

extern char **environ;

char *_getenv(const char *name);
int _strncmp(const char *s1, const char *s2, size_t n);
size_t _strlen(const char *s);
char *searchfile(char **argv, char *path);
int _setenv(const char *name, const char *value, int overwrite);
char **split_args(char **tokens, char **argv, int k);
int exe_command(char **argv, char *original_path, int *status);
int handle_args(char **tokens, char *original_path, int *status);
int get_token(char *lineptr, char *original_path, int *status);
int prompt(char *original_path, int *status);
char *new_env_var(const char *name, const char *value);
int _setenv(const char *name, const char *value, int overwrite);
int handle_cd(char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);

#endif /*MAIN_H*/

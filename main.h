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

int _strncmp(const char *s1, const char *s2, size_t n);
char *_strtok(char *str, const char *delim);
char *_strdup(const char *s);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
size_t _strlen(const char *s);
char *searchfile(char **argv, char *path);
char *_getenv(char **my_env, const char *name);
int _setenv(char **my_env, const char *name, const char *value, int overwrite);
int check_env(char **my_env, char *new_env, int overwrite, const char *name);
int _unsetenv(char **my_env, const char *name);
char **split_args(char **tokens, char **argv, int k);
int exe_command(char **argv, char *original_path, int *status);
int handle_args(char **my_env, char **and_arr, char *original_path, int *status, int *option);
int get_token(char **my_env, char *lineptr, char *original_path, int *status);
int handle_and(char **my_env, char **tokens, char *original_path, int *status);
int handle_or(char **my_env, char **tokens, char *original_path, int *status, int *option);
int prompt(char **my_env, char *original_path, int *status);
int handle_cd(char **my_env, char **argv);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif /*MAIN_H*/

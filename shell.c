#include "main.h"

/**
 * main - Shell program
 * @ac: argument counter
 * @av: argument variable
 * @env: environment variables
 *
 * Return: 0 (on success)
 */
int main(int ac, char **av, char **env)
{
	int i = 0, status;
	char *lineptr = NULL, *pmt = "# ", *argv[] = {"", NULL};
	char *token;
	size_t n = 0;
	ssize_t gline;
	pid_t cpid;
	struct stat st;

	while (gline != EOF)
	{
		write(1, pmt, 2);
		gline = getline(&lineptr, &n, stdin);

		if (gline == -1)
			exit(1);
		if (gline == 1)/*Check if nothing was typed i.e press only enter key */
			continue;

		if (lineptr[gline - 1] == '\n')
		{
			lineptr[gline - 1] = '\0';
		}

		i = 0;

		token = strtok(lineptr, " ");

		while (token)
		{
			argv[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;
		if (argv[0] == NULL)
		{
			continue;
		}

		if (searchfile(argv, env) == 1)
			cpid = fork(); /*start a child process*/
		else
			continue;
		/*
		if (stat(argv[0], &st) == 0)
		{
			printf("Found\n");
			cpid = fork(); *start a child process*
		}
		else
		{
			printf("NOT FOUND\n");
			continue;
		}
		*/

		printf("I got printed? hmmm\n");
		if (cpid == -1)
			perror("Error:");

		if (cpid == 0)
		{
			argv[0] = lineptr; /*assign the command read by getline*/

			if (execve(argv[0], argv, env) == -1)
			{
				perror("Error");
				exit(1);
			}
		}
		else
			wait(&status);/*wait for child process to end*/
	}
	free(lineptr);
	return (0);
}

int searchfile(char *av[], char **env)
{
	struct stat stbuf;
	char *path = getenv("PATH"), *path_dir = NULL, *buff = NULL;
	int i;

	/*printf("PATH\n----\n%s\n", path);*/
	path_dir = strtok(path, ":");

	i = 1;
	while(path_dir)
	{
		while (av[i])
		{
			buff = malloc(strlen(path_dir) + strlen(av[i]) + 2);
			if (buff == NULL)
				return (1);
			strcpy(buff, path_dir);
			strcat(buff, "/");
			strcat(buff, av[i]);

			if (stat(buff, &stbuf) == 0)
			{
				printf("FOUND\n");
				return (1);
			}
			else
			{
				printf("%s: NOT FOUND\n", buff);
				return (-1);
			}
		}

		//printf("%s\n", path_dir);
		path_dir = strtok(NULL, ":");
	}
	return (-1);
}

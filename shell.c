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
	int i = 0, status, create = 0;
	char *lineptr = NULL, *command = NULL, *pmt = "# ", *argv[] = {"", NULL};
	char *token, *original_path = getenv("PATH"), *path = NULL;
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

		printf("Just before check [%d]\n", getpid());

		path = strdup(original_path); //create a copy of the original path
		if (command = searchfile(argv, path))
		{
			printf("FOUND");
			cpid = fork(); /*start a child process*/
		}
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

		if (cpid == -1)
			perror("CPID Error:");

		printf("I [%d] got printed? hmmm\n", getpid());

		if (cpid == 0)
		{
			argv[0] = command; /*assign the command read by getline*/

			if (execve(argv[0], argv, env) == -1)
			{
				perror("EXECVE Error");
				exit(1);
			}
		}
		else
		{
			wait(&status);/*wait for child process to end*/
			printf("Wait status: %d\n", status);
		}
	}
	free(lineptr);
	return (0);
}

char *searchfile(char **av, char *path)
{
	struct stat stbuf;
	/*char *path = getenv("PATH");*/
	char *path_dir = NULL, *buff = NULL;
	int i;

	printf("PATH\n----\n%s\n", path);
	path_dir = strtok(path, ":");

	/*i = 1;*/
	printf("First token %s\n", path_dir);
	while(path_dir)
	{
		i = 0;
		//printf("Just before the loop av[%d]: %s\n", i, av[i]);
		printf("av[%d]: %s\n", i, av[i]);
		buff = malloc(strlen(path_dir) + strlen(av[i]) + 2);
		if (buff == NULL)
			return (NULL);
		strcpy(buff, path_dir);
		strcat(buff, "/");
		strcat(buff, av[i]);

		printf("buff before search: %s\n", buff);
		if (stat(buff, &stbuf) == 0)
		{
			printf("FOUND IN SEARCH\n");
			return (buff);
		}

		//printf("%s\n", path_dir);
		path_dir = strtok(NULL, ":");
	}
	printf("%s: NOT FOUND\n", buff);
	free(buff);
	return (NULL);
}

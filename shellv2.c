#include "main.h"

char **split_args(char **tokens, char **argv, int k);
int exe_command(char **argv, char *original_path, char **env, int *status);
int handle_args(char **tokens, char *original_path, char **env, int *status);
int get_token(char *lineptr, char *original_path, char **env, int *status);
int prompt(char *original_path, char **env, int *status);

int prompt(char *original_path, char **env, int *status)
{
	ssize_t gline;
	size_t n = 0;
	char *lineptr = NULL, *pmt = "# ";

	write(1, pmt, 2);
	gline = getline(&lineptr, &n, stdin);

	if (gline == -1)
		return (-1);
	if (gline == 1)/*Check if nothing was typed i.e press only enter key */
		return (1);

	if (gline == EOF)
		return (7);
	if (lineptr[gline - 1] == '\n')
		lineptr[gline - 1] = '\0';

	if (get_token(lineptr, original_path, env, status) == 99)
		return (-1);
	return (1);
}


int get_token(char *lineptr, char *original_path, char **env, int *status)
{
	char *token1 = NULL, *tokens[50];
	int i;

	i = 0;
	token1 = strtok(lineptr, ";");
	while (token1)
	{
		tokens[i] = token1;
		token1 = strtok(NULL, ";");
		i++;
	}
	tokens[i] = NULL;

	return (handle_args(tokens, original_path, env, status));
}

int handle_args(char **tokens, char *original_path, char **env, int *status)
{
	char *dir = NULL, prev[100] = "", prev_dir[100] = "";
	char *argv[100] = {"", NULL};
	int k;

	k = 0;
	while (tokens[k])
	{
		split_args(tokens, argv, k);

		if (strcmp(argv[0], "exit") == 0)
		{
			if (argv[1])
				*status = (atoi(argv[1]));
			return (99);
		}

		dir = NULL;

		if (strcmp(argv[0], "cd") == 0)
		{
			if (argv[1])
				dir = argv[1];
			if (!dir)
				dir = "/home";
			if (strcmp(dir, "-") == 0)
			{
				if (strlen(prev) != 0)
				{
					if (getcwd(prev_dir, sizeof(prev_dir)) == NULL)
						perror("Error");
					if (chdir(prev) != 0)
					{
						perror("Error");
						break;
					}
					strcpy(prev, prev_dir);
				}
				else
				{
					/**
					 * Don't use printf
					 *
					 */
					printf("cd: OLDPWD not set\n");
					break;
				}

			}
			else
			{
				if (getcwd(prev_dir, sizeof(prev_dir)) == NULL)
					perror("Error");
				if (chdir(dir) != 0)
				{
					perror("Error");
					break;
				}
				strcpy(prev, prev_dir);
			}
			break;
		}
		exe_command(argv, original_path, env, status);
		if (*status == -1)
			break;
		k++;
	}
	return (*status);
}

int exe_command(char **argv, char *original_path, char **env, int *status)
{
	char *path = NULL, *command = NULL;
	pid_t cpid;

	path = strdup(original_path); /*create a copy of the original path*/
	command = searchfile(argv, path);
	if (command)
	{
		cpid = fork(); /*start a child process*/
	}
	else
	{
		/**
		 * Handle Error massage
		 *
		 *
		 *while(argv[0][z++]);
		 */
		write(2, argv[0], strlen(argv[0]));
		write(2, "\n", 1);
		return (-1);
	}
	if (cpid == -1)
		perror("CPID Error:");
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
		wait(status);/*wait for child process to end*/
		printf("Wait status: %d\n", *status >> 8);
		return (*status);
	}
	return (0);
}

char **split_args(char **tokens, char **argv, int k)
{
	char *token;
	int i;

	i = 0;
	token = strtok(tokens[k], " ");

	while (token)
	{
		argv[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	argv[i] = NULL;

	return (argv);
}

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
	int i = 0, status, a = 1;
	char *original_path = getenv("PATH");

	while (a)
	{
		i = prompt(original_path, env, &status);
		if (i == 1)
			continue;
		else if (i == 7)
			a = 0;
		else
			exit(status);
	}
	printf("Done\n");
	return (0);
}

char *searchfile(char **av, char *path)
{
	struct stat stbuf;
	/*char *path = getenv("PATH");*/
	char *path_dir = NULL, *buff = NULL;
	int i;

	path_dir = strtok(path, ":");

	while (path_dir)
	{
		i = 0;
		if (av[i][0] != '/' && av[i][0] != '.')
		{
			buff = malloc(strlen(path_dir) + strlen(av[i]) + 2);
			if (buff == NULL)
				return (NULL);
			strcpy(buff, path_dir);
			strcat(buff, "/");
			strcat(buff, av[i]);
		}
		else
		{
			buff = malloc(strlen(av[i]));
			if (buff == NULL)
				return (NULL);
			strcpy(buff, av[i]);
		}

		if (stat(buff, &stbuf) == 0)
		{
			return (buff);
		}

		path_dir = strtok(NULL, ":");
	}
	free(buff);
	return (NULL);
}

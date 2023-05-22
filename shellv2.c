#include "main.h"

char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
char **split_args(char **tokens, char **argv, int k);
int exe_command(char **argv, char *original_path, int *status);
int handle_args(char **tokens, char *original_path, int *status);
int get_token(char *lineptr, char *original_path, int *status);
int prompt(char *original_path, int *status);
char *new_env_var(const char *name, const char *value);
char *env_copy(void);
int _setenv(const char *name, const char *value, int overwrite);
int handle_cd(char **argv);

int handle_cd(char **argv)
{
	char *dir = NULL, prev[100] = "", prev_dir[100] = "";

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
				return (9);
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
			return (9);
		}

	}
	else
	{
		if (getcwd(prev_dir, sizeof(prev_dir)) == NULL)
			perror("Error");
		if (chdir(dir) != 0)
		{
			perror("Error");
			return (9);
		}
		strcpy(prev, prev_dir);
	}
	return (9);
}

int _setenv(const char *name, const char *value, int overwrite)
{
	printf("%s\n%s\n%d\n", name, value, overwrite);

	return (0);
}

char *env_copy(void)
{
	int j = 0, size = 0;
	char **my_env = NULL;

	/*get the number of environment*/
	while (environ[size++]);

	/* */
	my_env = malloc(sizeof(char *) * (size + 1));
	if (!my_env)
		return (NULL);

	while (environ[j])
	{
		my_env[j] = malloc(strlen(environ[j]) + 1);
		if (!my_env[j])
		{
			while (j)
				free(my_env[--j]);
			free(my_env);
			return (NULL);
		}
		strcpy(my_env[j], environ[j]);
		j++;
	}
	return (NULL);
}

char *new_env_var(const char *name, const char *value)
{
	char *new_env = NULL;

	new_env = malloc(strlen(name) + strlen(value) + 2);
	if (!new_env)
		return (NULL);
	strcpy(new_env, name);
	strcat(new_env, "=");
	strcat(new_env, value);

	return (new_env);
}

int prompt(char *original_path, int *status)
{
	ssize_t gline;
	size_t n = 0;
	char *lineptr = NULL, *pmt = "# ";

	write(1, pmt, 2);
	gline = getline(&lineptr, &n, stdin);

	if (gline == -1)
	{
		free(lineptr);
		if (gline == EOF)
			return (7);
		else
			return (-1);
	}
	if (gline == 1)/*Check if nothing was typed i.e press only enter key */
	{
		free(lineptr);
		return (1);
	}

	if (lineptr[gline - 1] == '\n')
		lineptr[gline - 1] = '\0';

	if (get_token(lineptr, original_path, status) == 99)
	{
		free(lineptr);
		return (-1);
	}

	free(lineptr);
	return (1);
}


int get_token(char *lineptr, char *original_path, int *status)
{
	char *token1 = NULL, *tokens[50];
	int i= 0;
	token1 = strtok(lineptr, ";");
	while (token1)
	{
		tokens[i] = token1;
		token1 = strtok(NULL, ";");
		i++;
	}
	tokens[i] = NULL;

	return (handle_args(tokens, original_path, status));
}

int handle_args(char **tokens, char *original_path, int *status)
{
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


		if (strcmp(argv[0], "cd") == 0)
		{
			if (handle_cd(argv) == 9)
				break;
		}
		exe_command(argv, original_path, status);
		if (*status == -1)
			break;
		k++;
	}
	return (*status);
}

int exe_command(char **argv, char *original_path, int *status)
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
		if (execve(argv[0], argv, environ) == -1)
		{
			perror("EXECVE Error");
			exit(1);
		}
	}
	else
	{
		wait(status);/*wait for child process to end*/
		free(command);
		free(path);
		printf("Wait status: %d\n", *status >> 8);
		return (*status);
	}
	free(path);
	free(command);
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

		free(buff);
		path_dir = strtok(NULL, ":");
	}
	return (NULL);
}

size_t _strlen(const char *s)
{
	size_t i = 0;

	while (*s != '\0')
		i++, s++;
	return (i);
}

int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i = 0, s1Len = _strlen(s1), s2Len = _strlen(s2);

	while (i < s1Len && i < s2Len && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (0);
}

char *_getenv(const char *name)
{
	int i = 0, j = 0, k = 0;
	char *token, **my_env = NULL, **env = environ, *temp = NULL;

	while (environ[k])
	{
		if (_strncmp(environ[k], name, _strlen(name)) == 0 && environ[k][_strlen(name)] == '=')
		{
			//printf("%s\n", environ[k] + strlen(name) + 1);
			return (environ[k] + _strlen(name) + 1);
		}
		k++;
	}
	return (NULL);
}

/**
 * main - Shell program
 * @ac: argument counter
 * @av: argument variable
 * @env: environment variables
 *
 * Return: 0 (on success)
 */
int main(void)
{
	int i = 0, status, a = 1;
	char *original_path = _getenv("PATH");

	while (a)
	{
		i = prompt(original_path, &status);
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

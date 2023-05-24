#include "main.h"

/**
 * _strdup - make a copy of a string constant
 * @s: a string
 *
 * Return: pointer to string copy
 */
char *_strdup(const char *s)
{
	int i = 0;
	char *temp = NULL;

	while (s[i])
		i++;

	temp = malloc(sizeof(char) * (i + 1));

	if (temp == NULL)
		return (NULL);

	i = 0;
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	} temp[i] = '\0';

	return (temp);
}

/**
 * _strcat - Concatenate two strings
 * @dest: Destinantion string
 * @src: string to be append to dest
 *
 * Return: the pointer to concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;
	char *temp = dest;

	while (temp[i] != '\0')
	{
		i++;
	}

	while (src[j] != '\0')
	{
		temp[i] = src[j];
		i++;
		j++;
	}

	temp[i] = '\0';

	return (dest);
}

/**
 * _strcpy - make a copy of a string
 * @dest: where the copy should be stored
 * @src: string to be copied
 *
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';

	return (dest);
}

int handle_cd(char **my_env, char **argv)
{
	char *dir = NULL, prev[100] = "", prev_dir[100] = "";

	if (argv[1])
		dir = argv[1];
	if (!dir)
		dir = "/home";
	if (_strcmp(dir, "-") == 0)
	{
		_strcpy(prev, _getenv(my_env, "OLDPWD"));
		if (_strlen(prev) != 0)
		{
			if (getcwd(prev_dir, sizeof(prev_dir)) == NULL)
				perror("Error");
			if (chdir(prev) != 0)
			{
				perror("Error");
				return (9);
			}
			_strcpy(prev, prev_dir);
			if (_setenv(my_env, "OLDPWD", prev, 1) == 0)
				printf("Success\n");
		}
		else
		{
			/**
			 * Don't use printf
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
		_strcpy(prev, prev_dir);
		if (_setenv(my_env, "OLDPWD", prev, 1) == 0)
			printf("Success\n");
	}

	return (9);
}

int prompt(char **my_env, char *original_path, int *status)
{
	ssize_t gline;
	size_t n = 0;
	char *lineptr = NULL;

	gline = _getline(&lineptr, &n, stdin);

	if (gline == -1)
	{
		free(lineptr);
		return (-1);
	}
	else if (gline == 0)
	{
		free(lineptr);
		return (7);
	}
	if (gline == 1)/*Check if nothing was typed i.e press only enter key */
	{
		free(lineptr);
		return (1);
	}

	if (lineptr[gline - 1] == '\n')
		lineptr[gline - 1] = '\0';

	if (get_token(my_env, lineptr, original_path, status) == 99)
	{
		free(lineptr);
		return (-1);
	}

	free(lineptr);
	return (1);
}

/**
 * _strtok - A function that slipts a string based off it's delimeter
 * into tokens, subsequence call to the function is needed to
 * get the other tokens. see (man strtok) for more details
 *
 * @str: the string to slipt
 * @delim: the delimeter(s) to use
 *
 * Return: token
 */
char *_strtok(char *str, const char *delim)
{
	static char *position;
	int i = 0, j = 0, len = 0, check = 0, temp = 0;

	if (str != NULL)
		position = str;
	else
		str = position;
	len = _strlen(delim);

	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		j = 0;
		while (j < len)
		{
			if (str[i] == delim[j])
			{
				str[i] = '\0';
				check++;
				break;
			}
			j++;
		}
		i++;
		if (check > 0 && ++temp > check)
		{
			position = &str[i - 1];
			return (str);
		}
	}
	if (!str[i])
	{
		position = NULL;
		return (str);
	}
	return (NULL);
}

int get_token(char **my_env, char *lineptr, char *original_path, int *status)
{
	char *token1 = NULL, *tokens[50];
	int i = 0;

	token1 = _strtok(lineptr, ";");
	while (token1)
	{
		tokens[i] = token1;
		token1 = _strtok(NULL, ";");
		i++;
	}
	tokens[i] = NULL;

	return (handle_args(my_env, tokens, original_path, status));
}

int handle_args(char **my_env, char **tokens, char *original_path, int *status)
{
	char *argv[100] = {"", NULL};
	int k;

	k = 0;
	while (tokens[k])
	{
		split_args(tokens, argv, k);

		if (_strcmp(argv[0], "exit") == 0)
		{
			if (argv[1])
				*status = (atoi(argv[1]));
			return (99);
		}


		if (_strcmp(argv[0], "cd") == 0)
		{
			if (handle_cd(my_env, argv) == 9)
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
		cpid = fork(); /*start a child process*/
	else
	{
		/**
		 * Handle Error massage
		 */
		write(2, argv[0], _strlen(argv[0]));
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
			buff = malloc(_strlen(path_dir) + _strlen(av[i]) + 2);
			if (buff == NULL)
				return (NULL);
			_strcpy(buff, path_dir);
			strcat(buff, "/");
			strcat(buff, av[i]);
		}
		else
		{
			buff = malloc(_strlen(av[i]));
			if (buff == NULL)
				return (NULL);
			_strcpy(buff, av[i]);
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

/**
 * _strncmp - Compare (n)bytes of two strings
 * @s1: first string
 * @s2: second string
 * @n: bytes to be compared
 *
 * Return: the integer difference
 */
int _strncmp(const char *s1, const char *s2, size_t n)
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

/**
 * _strcmp - Compare two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: the integer difference
 */
int _strcmp(const char *s1, const char *s2)
{
	int i = 0;
	int s1Len = _strlen(s1);
	int s2Len = _strlen(s2);

	while (i < s1Len && i < s2Len)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (s1[i] - s2[i]);
}

char *_getenv(char **my_env, const char *name)
{
	int k = 0;

	while (my_env[k])
	{
		if (_strncmp(my_env[k], name, _strlen(name)) == 0)
		{
			if (my_env[k][_strlen(name)] == '=')
				return (my_env[k] + _strlen(name) + 1);
		}
		k++;
	}
	return (NULL);
}

/**
 * _getline - my getline function
 * @lineptr - pointer to pointer where what is read
 * should be stored or NULL
 * @n: byte size or 0
 * @stream: where input should be read from
 *
 * Return: bytes read
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int fd = fileno(stream);
	ssize_t rd, red = 0;

	*lineptr = malloc((sizeof(char) * BUFF));
	if (*lineptr == NULL)
		return (-1);

	while ((rd = read(fd, *lineptr + red, BUFF)) > 0)
	{
		*n = *n + BUFF;
		*lineptr = _realloc(*lineptr, *n, (*n + BUFF));
		if (*lineptr == NULL)
		{
			free(*lineptr);
			return (-1);
		}
		red = red + rd;
		if ((*lineptr)[red - 1] == '\n')
			break;
	}
	if (rd < 0)
	{
		free(*lineptr);
		return (-1);
	}
	(*lineptr)[red] = '\0';
	return (red);
}

/**
 * _realloc - reallocates a momeory block using malloc and free
 * @ptr: pointer to old block of memory
 * @old_size: size of the old block of memory
 * @new_size: size of the new block of memory
 *
 * Return: pointer to memory block or NULL
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new = NULL;

	if (ptr != NULL)
	{
		if (new_size == old_size)
			return (ptr);
		if (new_size == 0)
		{
			free(ptr);
			return (NULL);
		}
		else if (new_size > old_size)
		{
			new = malloc(new_size);
			if (new != NULL)
			{
				memcpy(new, ptr, old_size);
				free(ptr);
				return (new);
			}
		}
	}
	ptr = malloc(new_size);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}


int _setenv(char **my_env, const char *name, const char *value, int overwrite)
{
	int i = 0, j = 0;
	char *new_env = NULL;

	new_env = malloc(_strlen(name) + _strlen(value) + 2);
	if (!new_env)
		return (1);

	while (name[i])
	{
		new_env[i] = name[i];
		i++;
	}
	new_env[i++] = '=';
	while (value[j])
	{
		new_env[i] = value[j];
		i++, j++;
	}

	if (check_env(my_env, new_env, overwrite, name) == 1)
	{
		free(new_env);
		return (1);
	}
	return (0);
}

int check_env(char **my_env, char *new_env, int overwrite, const char *name)
{
	int k = 0;
	char *temp = NULL;

	/*search for "name", replace it's value if overwrite != 0*/
	while (my_env[k])
	{
		if (_strncmp(my_env[k], name, _strlen(name)) == 0)
		{
			if (my_env[k][_strlen(name)] == '=')
			{
				if (overwrite != 0)
				{
					temp = my_env[k];
					my_env[k] = new_env;
					free(temp);
				}
				else
					return (1);
				break;
			}
		}
		k++;
	}
	if (my_env[k] == NULL)
	{
		my_env[k++] = new_env;
		my_env[k] = NULL;
	}
	return (0);
}

int _unsetenv(char **my_env, const char *name)
{
	int k = 0, l, check = 0;

	/*search for "name", replace it's value if overwrite != 0*/
	while (my_env[k])
	{
		if (_strncmp(my_env[k], name, _strlen(name)) == 0)
		{
			if (my_env[k][_strlen(name)] == '=')
			{
				check = 1;
				free(my_env[k]);
				break;
			}
		}
		k++;
	}

	if (check == 1)
	{
		l = k + 1;

		while (my_env[l])
		{
			my_env[k] = my_env[l];
			k++, l++;
		}
		my_env[k] = NULL;

		return (0);
	}
	return (-1);
}

/**
 * main - Shell program
 * @ac: argument counter
 * @av: argument variable
 * @env: environment variable
 *
 * Return: 0 (on success)
 */
int main(int ac __attribute__((unused)), char **av __attribute__((unused)), char **env)
{
	int i = 0, status = 0, a = 1, j = 0;
	char *original_path, *pmt = "# ";

	char *my_env[100];

	while (env[j])
	{
		my_env[j] = malloc(_strlen(env[j]) * sizeof(char) + 1);
		if (my_env[j] == NULL)
			return (-1);
		_strcpy(my_env[j], env[j]);
		j++;
	}
	my_env[j] = NULL;

	original_path = _getenv(my_env, "PATH");

	_setenv(my_env, "OLDPWD", "", 1);
	while (a)
	{
		/*Is this fine????*/
		if (isatty(STDIN_FILENO))
			write(1, pmt, 2);
		i = prompt(my_env, original_path, &status);
		if (i == 1)
			continue;
		else if (i == 7)
			a = 0;
		else
			a = 0;
	}
	printf("Done\n");

	j = 0;
	while (my_env[j])
		free(my_env[j++]);
	return (status);
}

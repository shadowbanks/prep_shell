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
	int i = 0, status, create = 0, k = 0;
	char *lineptr = NULL, *command = NULL, *pmt = "# ", *argv[] = {"", NULL}, *tokens[50];
	char *token, *original_path = getenv("PATH"), *path = NULL, *token1 = NULL;
	size_t n = 0, z = 0;
	ssize_t gline;
	pid_t cpid;
	struct stat st;
	int result;
	char prev_dir[100] = "", pwd[100] = "";
	char *dir = NULL, prev[100] = "";

//	while (gline != EOF)
	while (1)
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
/*
		if (strcmp(lineptr, "cd") == 0)
		{
			if (chdir("/home") != 0)
			{
				perror("chdir");
			}
			else
				printf("Current directory\n");
			continue;
		}
*/
		i = 0;
		token1 = strtok(lineptr, ";");
		while (token1)
		{
			tokens[i] = token1;
			token1 = strtok(NULL, ";");
			//printf("TEST token1[%d]: %s\n", i, tokens[i]);
			i++;
		}
		tokens[i] = NULL;
		//printf("TEST: %s\n", token1);

		k = 0;
		while (tokens[k])
		{
			i = 0;
			token = strtok(tokens[k], " ");

			while (token)
			{
				argv[i] = token;
				token = strtok(NULL, " ");
				//printf("TEST argv: %s\n", argv[i]);
				i++;
			}
			argv[i] = NULL;
			if (argv[0] == NULL)
			{
				continue;
			}

			//printf("Just before check [%d]\n", getpid());

			if (strcmp(argv[0], "exit") == 0)
			{
				if (argv[1])
					return (atoi(argv[1]));
				return (0);
			}

			dir = NULL;

			if (strcmp(argv[0], "cd") == 0)
			{
				//printf("I'm here\n");
				if (argv[1])
				{
					//printf("Here???\n");
					dir = argv[1];
				}
				if (!dir)
				{
					//printf("In here\n");
					dir = "/home";
				}
				//printf("Checking\n");
				if (strcmp(dir, "-") == 0)
				{
					//printf("This is -\n");
					if (strlen(prev) != 0)
					{
						//printf("Check prev: %s\n", prev);
						if (getcwd(prev_dir, sizeof(prev_dir)) == NULL)
							perror("Error");
						//printf("PWD: %s\n", prev_dir);
						//result = chdir(prev);
						//printf("%s", prev_dir);
						if (chdir(prev) != 0)
						{
							perror("Error");
							break;
						}
						strcpy(prev, prev_dir);
					}
					else
					{
						//printf("cd: OLDPWD not set\n");
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
					//else
						//printf("changed %s\n", dir);
				}
				break;
			}

			path = strdup(original_path); //create a copy of the original path
			if (command = searchfile(argv, path))
			{
				//printf("FOUND: %s\n", command);
				cpid = fork(); /*start a child process*/
			}
			else
			{
				//Handle Error massage
				//while(argv[0][z++]);
				write(2, argv[0], strlen(argv[0]));
				//write(2, "command not found" 17);
				write(2, "\n", 1);
				//printf("ma: command not found%ld\n", z);
				break;
			}

			if (cpid == -1)
				perror("CPID Error:");

			//printf("I [%d] got printed? hmmm\n", getpid());

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
				printf("Wait status: %d\n", status>>8);
			}
			k++;
			//printf("NEXT token1: %s\n", tokens[k]);
		}
	}
	//printf("\nbefore END\n");
	free(lineptr);
	//printf("\nEND\n");
	return (0);
}

char *searchfile(char **av, char *path)
{
	struct stat stbuf;
	/*char *path = getenv("PATH");*/
	char *path_dir = NULL, *buff = NULL;
	int i;

	//printf("PATH\n----\n%s\n", path);
	path_dir = strtok(path, ":");

	/*i = 1;*/
	//printf("First token %s\n", path_dir);
	while(path_dir)
	{
		i = 0;
		//printf("Just before the loop av[%d]: %s\n", i, av[i]);
		//printf("av[%d]: %s\n", i, av[i]);
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

		//printf("buff before search: %s\n", buff);
		if (stat(buff, &stbuf) == 0)
		{
			//printf("FOUND IN SEARCH\n");
			return (buff);
		}

		//printf("%s\n", path_dir);
		path_dir = strtok(NULL, ":");
	}
	//printf("%s: NOT FOUND\n", buff);
	free(buff);
	return (NULL);
}

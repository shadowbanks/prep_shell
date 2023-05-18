#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int ac, char **av, char **env)
{
	int i, status;
	char *lineptr = NULL, *pmt = "# ", *argv[100], *token;
	size_t n = 0;
	ssize_t gline = 0;
	pid_t cpid;

	if (ac > 1)


	while (gline != EOF)
	{
		write(1, pmt, 2);
		gline = getline(&lineptr, &n, stdin);
		if (gline == -1)
			break;
		if (gline == 1)
			continue;
		cpid = fork();
		if (cpid == -1)
			perror("Error:");
		if (cpid == 0)
		{
			if (lineptr[gline - 1] == '\n')
				lineptr[gline - 1] = '\0';

			i = 0;
			token = strtok(lineptr, " ");
			//printf("token %s\n", token);
			while (token)
			{
				//printf("inner token %s\n", token);
				argv[i++] = token;
				token = strtok(NULL, " ");
			}
			argv[i] = NULL;

			/*printf("current pid: %d\n", getpid());*/
			/*printf("%s\n", *argv);*/
			if (execve(argv[0], argv, env) == -1)
			{
				perror(av[0]);
				exit(1);
			}
		}
		else
		{
			wait(&status);
			/*printf("I should be: %d pid\n", getpid());*/
			/*printf("i = %d\n", i++);*/
		}

	}
	free(lineptr);
	return (0);
}

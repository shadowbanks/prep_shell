#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(int ac, char **av, char **env)
{
	int i = 0, status;
	char *lineptr = NULL, *pmt = "# ", *argv[] = {"", NULL};
	size_t n = 0;
	ssize_t gline;
	pid_t cpid;

	while (gline != EOF)
	{
		write(1, pmt, 2);
		gline = getline(&lineptr, &n, stdin);
		if (gline == -1)
			break;
		cpid = fork();
		if (cpid == -1)
			perror("Error:");
		if (cpid == 0)
		{
			if (lineptr[gline-1] == '\n')
				lineptr[gline-1] = '\0';

			argv[0] = lineptr;
			printf("current pid: %d\n", getpid());
			//printf("%s\n", *argv);
			if (execve(argv[0], argv, env) == -1)
			{
				perror("Error
						return (0);");
				exit(1);
			}
		}
		else
		{
			wait(&status);
			printf("I should be: %d pid\n", getpid());
			printf("i = %d\n", i++);
		}

		//sleep(3);
	}
	free(lineptr);
	return (0);
}

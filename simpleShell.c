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

	while (i++ < 5)
	{
		write(1, pmt, 2);
		gline = getline(&lineptr, &n, stdin);
		if (gline == EOF)
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
				perror("Error");
		}
		else
			wait(&status);

		sleep(3);
	}
	free(lineptr);
	return (0);
}

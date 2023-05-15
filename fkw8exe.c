#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int ac, char **av)
{
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	pid_t cpid;
	int i = 0, status;

	while (i++ < 5)
	{
		cpid = fork();
		if (cpid == -1)
			perror("Error:");
		if (cpid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
				perror("Error:");
		}
		else
			wait(&status);
	}
	return (0);
}

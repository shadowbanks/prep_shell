#include <stdio.>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(ac, av)
{
	struct stat statbuf;

	if (ac < 2)
	{
		printf("Usage :./%s file-name\n", av[0]);
		return (-1);
	}
	i = 1;
	while (av[i])
	{
		if (stat(av[i], &statbuf) == 0)
			printf(" FOUND\n");
		else
			printf(" NOT FOUND\n");
		i++;
	}
	return (0);
}

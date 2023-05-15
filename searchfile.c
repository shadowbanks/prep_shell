#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int ac, char **av)
{
	struct stat stbuf;
	int i;

	if (ac < 2)
	{
		printf("Usage :%s file-name\n", av[0]);
		return (-1);
	}
	i = 1;
	while (av[i])
	{
		if (stat(av[i], &stbuf) == 0)
			printf(" FOUND\n");
		else
			printf(" NOT FOUND\n");
		i++;
	}
	return (0);
}

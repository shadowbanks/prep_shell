#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char **av)
{
	char *tok = NULL;

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: strtok string delim\n");
		exit(98);
	}

	tok = strtok(av[1], av[2]);

	while (tok)
	{
		printf("%s\n", tok);
		tok = strtok(NULL, av[2]);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - using getline to read from stream
 * Return: 0
 */
int main()
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t getl;
	char *pmt = "$ ";

	while (getl != EOF)
	{
		write(1, pmt, 2);
		getl = getline(&lineptr, &n, stdin);
		write(1, lineptr, getl);
	}

	free(lineptr);
	return (0);
}

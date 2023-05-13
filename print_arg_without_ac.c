#include <unistd.h>

int _strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * main - print all arguments without the use of ac
 *
 * Return: 0
 */
int main(int ac, char **av)
{
	int i = 0;
	char n = '\n';
	while (av[i])
	{
		write(1, av[i], _strlen(av[i]));
		write(1, &n, 1);
		i++;
	}
	return (0);
}

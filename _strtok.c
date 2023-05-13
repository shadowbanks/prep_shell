#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char *_strtok(char *str, const char *delim)
{
	static char *position = NULL;
	int i = 0, j = 0, len = 0, check = 0, temp = 0;

	if (str != NULL)
		position = str;
	else
		str = position;
	len = strlen(delim);

	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		j = 0;
		while (j < len)
		{
			if (str[i] == delim[j])
			{
				str[i] = '\0';
				check++;
				break;
			}
			j++;
		}
		i++;
		if (check > 0)
		{
			temp++;
			if (temp > check)
			{
				position = &str[i - 1];
				return (str);
			}
		}
	}
	if (!str[i])
	{
		position = NULL;
		return(str);
	}
	return (NULL);
}

int main(int ac, char **av)
{
	char *tok = NULL;

	if (ac != 3)
	{
		dprintf(STDERR_FILENO, "Usage: strtok string delim\n");
		exit(98);
	}
	tok = _strtok(av[1], av[2]);

	while (tok)
	{
		printf("%s\n", tok);
		tok = _strtok(NULL, av[2]);
	}
}

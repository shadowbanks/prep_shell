#include "main.h"

extern char **environ;

char *_strtok(char *str, const char *delim);

char *_getenv(const char *name)
{
	char *token;

	//token = _strtok(env, ":");

	printf("%s\n", token);
}

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

int main()
{
	int i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i++]);
	}
	exit(98);
}

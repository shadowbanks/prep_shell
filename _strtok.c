#include <string.h>
#include <stdio.h>

char *_strtok(char *str, const char *delim)
{
	char *token = NULL;
	int i = 0, j = 0, len = 0, check = 0, temp = 0;

	token = str;
	len = strlen(delim);

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
				return (str += i);
		}
	}
	return (NULL);
}

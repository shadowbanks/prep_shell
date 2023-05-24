#include "main.h"

unsigned int _strcspn(char *s, char *reject)
{
	unsigned int i = 0, j;

	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}

	return (i);
}

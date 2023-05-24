#include "main.h"

/**
 * _strdup - make a copy of a string constant
 * @s: a string
 *
 * Return: pointer to string copy
 */
char *_strdup(const char *s)
{
	int i = 0;
	char *temp = NULL;

	while (s[i])
		i++;

	temp = malloc(sizeof(char) * (i + 1));

	if (temp == NULL)
		return (NULL);

	i = 0;
	while (s[i])
	{
		temp[i] = s[i];
		i++;
	} temp[i] = '\0';

	return (temp);
}

int main(void)
{
	char *temp = _strdup("Hello");
	printf("%s\n", temp);

	free(temp);
	return (0);
}

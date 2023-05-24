#include "main.h"

size_t _strlen(const char *s)
{
	size_t i = 0;

	while (*s != '\0')
		i++, s++;
	return (i);
}

/**
 * _strncmp - Compare (n)bytes of two strings
 * @s1: first string
 * @s2: second string
 * @n: bytes to be compared
 *
 * Return: the integer difference
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0, s1Len = _strlen(s1), s2Len = _strlen(s2);

	while (i < s1Len && i < s2Len && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	return (0);
}

/**
 * _strcpy - make a copy of a string
 * @dest: where the copy should be stored
 * @src: string to be copied
 *
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';

	return (dest);
}

int _setenv(char **my_env, const char *name, const char *value, int overwrite)
{
	int j = 0, i = 0;
	char *new_env = NULL;

	new_env = malloc(_strlen(name) + _strlen(value) + 2);
	if (!new_env)
		return (1);
	while (name[i])
	{
		new_env[i] = name[i];
		i++;
	}
	new_env[i++] = '=';
	while (value[j])
	{
		new_env[i] = value[j];
		i++, j++;
	}

	if (check_env(my_env, new_env, overwrite, name) == 1)
	{
		free(new_env);
		return (1);
	}
	return (0);
}

int check_env(char **my_env, char *new_env, int overwrite, const char *name)
{
	int k = 0, l;
	char *temp = NULL;

	/*search for "name", replace it's value if overwrite != 0*/
	while (my_env[k])
	{
		if (_strncmp(my_env[k], name, _strlen(name)) == 0)
		{
			if (my_env[k][_strlen(name)] == '=')
			{
				if (overwrite != 0)
				{
					temp = my_env[k];
					my_env[k] = new_env;
					free(temp);
				}
				else
					return (1);
				break;
			}
		}
		k++;
	}
	if (my_env[k] == NULL)
	{
		my_env[k++] = new_env;
		my_env[k] = NULL;
	}
	return (0);
}

int _unsetenv(char **my_env, const char *name)
{
	int k = 0, l, check = 0;
	char *temp = NULL;

	/*search for "name", replace it's value if overwrite != 0*/
	while (my_env[k])
	{
		if (_strncmp(my_env[k], name, _strlen(name)) == 0)
		{
			if (my_env[k][_strlen(name)] == '=')
			{
				check = 1;
				free(my_env[k]);
				break;
			}
		}
		k++;
	}

	if (check == 1)
	{
		l = k + 1;

		while (my_env[l])
		{
			my_env[k] = my_env[l];
			k++, l++;
		}
		my_env[k] = NULL;

		return (0);
	}
	return (-1);
}

int main(int ac, char **av, char **env)
{
	//char **my_env = environ;
	int i = 0, status = 0, a = 1, j = 0;

	char *my_env[100];

	while (env[j])
	{
		my_env[j] = malloc(_strlen(env[j]) * sizeof(char) + 1);
		if (my_env[j] == NULL)
			return (-1);
		_strcpy(my_env[j], env[j]);
		j++;
	}
	my_env[j] = NULL;

	_setenv(my_env, "VIP", "GhostProTech", 0);
	_setenv(my_env, "TEST", "1234", 1);
	_setenv(my_env, "VIP", "Ghost", 0);
	_unsetenv(my_env, "VIP");
	_unsetenv(my_env, "VIP2");
	_setenv(my_env, "VIP2", "Ghost", 0);
	//_unsetenv(my_env, "VIP2");
	_unsetenv(my_env, "TEST");

	j = 0;
	while (my_env[j])
		printf("%s\n", my_env[j++]);
	while (my_env[i])
		free(my_env[i++]);
	return (0);
}

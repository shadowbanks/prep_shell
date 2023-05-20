#include "main.h"

int _setenv(const char *name, const char *value, int overwrite)
{
	int size = 0, j = 0, k = 0, l = 0, i = 0;
	char **my_env = NULL,  *temp = NULL, *new_env = NULL, **temp_env = NULL;

	while (environ[size++]);

	//
	my_env = malloc(sizeof(char *) * (size + 1));
	if (!my_env)
			return (-1);

	//Make a copy of environ(env)
	while(environ[j])
	{
		my_env[j] = malloc(strlen(environ[j]) + 1);
		if (!my_env[j])
		{
			while (j)
				free(my_env[--j]);
			free(my_env);
			return (-1);
		}
		strcpy(my_env[j], environ[j]);
		j++;
	}

	my_env[j] = NULL;

	new_env = malloc(strlen(name) + strlen(value) + 2);
	if (!new_env)
	{
		while (my_env[l])
			free(my_env[l++]);
		free(my_env);
		return (-1);
	}
	strcpy(new_env, name);
	strcat(new_env, "=");
	strcat(new_env, value);

	//search for "name", replace it's value if overwrite != 0
	while (my_env[k])
	{
		if (strncmp(my_env[k], name, strlen(name)) == 0 && my_env[k][strlen(name)] == '=')
		{
			if (overwrite != 0)
			{
				temp = my_env[k];
				my_env[k] = new_env;
				free(temp);
			}
			else
			{
				l = 0;
				while (my_env[l])
					free(my_env[l++]);
				free(my_env);
				free(new_env);
				return (0);
			//printf("%s\n", my_env[k] + strlen(name) + 1);
			}
			break;
		}
		k++;
	}

	//Set the new env if it does not exist
	if (my_env[k] == NULL)
	{
		temp_env = realloc(my_env, (sizeof(char *) * (size + 2)));
		if (!temp_env)
		{
			l = 0;
			while (my_env[l])
				free(my_env[l++]);
			free(my_env);
			free(new_env);
			return (-1);
		}
		my_env = temp_env;
		my_env[k++] = new_env;
		my_env[k] = NULL;
		//printf("Works fine\n");
	}
	//my_env[size - 1] = NULL;
	environ = my_env;

	return (0);
}

int _unsetenv(const char *name)
{
	char **my_env = NULL;
	int k = 0, size = 0, i = 0;

	while (environ[size++]);

	//
	my_env = malloc(sizeof(char *) * (size + 1));
	if (!my_env)
		return (-1);


	//search for "name", if found skip while making a copy of environ
	while (environ[k])
	{
		//printf("size: %d, k: %d\n", size, k);
		if (strncmp(environ[k], name, strlen(name)) == 0 && environ[k][strlen(name)] == '=')
		{
			printf("%s SKIPPED k: %d\n", environ[k], k);
			k++;
			continue;
		}
		/*my_env[i] = malloc(strlen(environ[k]) + 1);
		if (!my_env[i])
		{
			while(i)
				free(my_env[--i]);
			free(my_env);
			return (-1);
		}*/
		if (i != k)
			environ[i] = environ[k];
		//printf("%s\n", environ[k]);
		//strcpy(my_env[i], environ[k]);
	//	printf("%s k: %d\n", my_env[k], k);
		k++, i++;
	}
	//printf("size: %d, %s k-1: %d\n", size, my_env[k-1], k-1);
	//my_env[i] = NULL;
	environ[i] = NULL;
	return (0);
}

int main()
{
	//char **my_env = environ;
	int i = 0;

	_setenv("VIP", "GhostProTech", 0);
	_setenv("TEST", "1234", 1);
	_setenv("VIP", "Ghost", 0);
	_unsetenv("VIP");
	_unsetenv("VIP2");
	_setenv("VIP2", "Ghost", 0);
	_unsetenv("VIP2");
	//_unsetenv("TEST");

	while (environ[i])
	{
		printf("%s\n", environ[i++]);
	}

	i = 0;
	while (environ[i])
		free(environ[i++]);
	free(environ);
}

#include "main.h"

int _setenv(const char *name, const char *value, int overwrite)
{
	int size = 0, j = 0, k = 0, l = 0;
	char **my_env = NULL, **env = environ, *temp = NULL, *new_env = NULL, **temp_env = NULL;

	while (env[size++]);

	my_env = malloc(sizeof(char *) * (size + 2));

	while(env[j])
	{
		my_env[j] = malloc(strlen(env[j]) + 1);
		strcpy(my_env[j], env[j]);
		j++;
	}

	my_env[j] = NULL;

	new_env = malloc(strlen(name) + strlen(value) + 2);
	strcpy(new_env, name);
	strcat(new_env, "=");
	strcat(new_env, value);

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
				free(new_env);
			//printf("%s\n", my_env[k] + strlen(name) + 1);
			break;
		}
		k++;
	}

	/*
	while (my_env[k])
	{
		if (strstr(my_env[k], name))
		{
			temp = my_env[k];
			my_env[k] = new_env;
			free(temp);
			break;
		}
		k++;
	}
	*/

	//Set the new env if it does not exist
	if (my_env[k] == NULL)
	{
		my_env[k++] = new_env;
		my_env[k] = NULL;
		//printf("Works fine\n");
	}

//	temp_env = realloc(my_env, (sizeof(my_env) * (size + 2)));
//	temp_env[k] = NULL;
//	my_env = temp_env;

	//Need to implement passing my_env to realloc and append NULL
	//as it's last value
	//
	//Also confirm it's been added and set environ = my_env and free(env)
	environ = my_env;

	return (0);
}

int main()
{
	//char **my_env = environ;
	int i = 0;

	_setenv("VIP", "GhostProTech", 0);
	_setenv("TEST", "1234", 1);
	_setenv("VIP", "Ghost", 1);

	while (environ[i])
	{
		printf("%s\n", environ[i++]);
	}
}

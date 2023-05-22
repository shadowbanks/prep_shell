#include "main.h"

char *_getenv(const char *name)
{
	int i = 0, j = 0, k = 0;
	char *token, **my_env = NULL, **env = environ, *temp = NULL;

	//Get the number of env variables
	while (environ[i] != NULL)
	{
		printf("%d", i++);
	//	printf("%s\n", environ[i++]);
	}
	printf("\n");
	//token = _strtok(env, ":");

	//create a buffer to hold pointers to the env
	my_env = malloc(sizeof(char *) * (i + 1));

	//Make a copy of environ
	while(environ[j])
	{
		my_env[j] = malloc(strlen(environ[j]) + 1); 
		strcpy(my_env[j], environ[j]);
		//printf("env: %s\n", env[j]);
		//printf("My_env: %s\n\n", my_env[j]);
		j++;
	}
	my_env[j] = NULL;

	/*
	//Search for specific env
	while (my_env[k] != NULL)
	{
		//printf("%s\n", my_env[k]);
		if (temp = strstr(my_env[k], name))
		{
			if (temp[strlen(name)] == '=')
			{
				printf("%s\n", temp + strlen(name) + 1);
				break;
			}
		}
		k++;
	}
	//printf("%s\n", token);
*/

	while (my_env[k])
	{
		if (_strncmp(my_env[k], name, strlen(name)) == 0 && my_env[k][strlen(name)] == '=')
		{
			printf("%s\n", my_env[k] + strlen(name) + 1);
			break;
		}
		k++;
	}
}

int main()
{
	_getenv("PATH");
	exit(98);
}

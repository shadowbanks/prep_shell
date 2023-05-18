#include "main.h"


char *_strtok(char *str, const char *delim);

char *_getenv(const char *name)
{
	int i = 0, j = 0, k = 0;
	char *token, **my_env = NULL, **env = environ, *temp = NULL;

	while (environ[i] != NULL)
	{
		printf("%d", i++);
	//	printf("%s\n", environ[i++]);
	}
	printf("\n");
	//token = _strtok(env, ":");


	my_env = malloc(sizeof(char *) * (i + 1));

	while(env[j])
	{
		my_env[j] = malloc(strlen(env[j] + 1)); 
		strcpy(my_env[j], env[j]);
		//printf("env: %s\n\n", env[j]);
		//printf("My_env: %s\n", my_env[j]);
		j++;
	}
	my_env[j] = NULL;

	while (my_env[k] != NULL)
	{
		if (temp = strstr(my_env[k], name))
		{
			printf("%s\n", temp + strlen(name) + 1);
			break;
		}
		k++;
	}
	//printf("%s\n", token);
}

int main()
{
	_getenv("PATH");
	exit(98);
}

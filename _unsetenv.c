#include "main.h"

int unsetenv(const char *name)
{
	int i = 0, j = 0, k = 0;
	char **my_env = NULL, **env = environ, *temp = NULL, *new_env = NULL;

	while (environ[i++]);

	my_env = malloc(sizeof(char *) * (i + 1));

	while(env[j])
	{
		my_env[j] = malloc(strlen(env[j]) + 1);
		strcpy(my_env[j], env[j]);
		j++;
	}

	new_env = malloc(strlen(name) + strlen(value) + 2);
	strcpy(new_env, name);
	strcat(new_env, "=");
	strcat(new_env, value);

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
	//Set the new env if it does not exist
	if (my_env[k] == NULL)
	{
		//my_env[k] = new_env;
		printf("Works fine\n");
	}

	//Need to implement passing my_env to realloc and append NULL
	//as it's last value
	//
	//Also confirm it's been added and set environ = my_env and free(env)
}

int main()
{
	unsetenv("Hello");
}

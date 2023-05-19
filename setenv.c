#include "main.h"

int setenv(const char *name, const char *value, int overwrite)
{
	int i = 0; j = 0; k = 0;
	char **my_env = NULL, **env = environ, *temp = NULL;

	while (environ[i++]);

	printf("%d\n", i);
}

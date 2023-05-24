#include "main.h"

char *comment(char *str);

int main(int ac, char **av, char **env)
{
	const char *var;
	char *first = av[1];
	char *find = strchr(first, '$');
	if (find != NULL)
	{
		char str[10], *temp, *filter;

		pid_t pid = getpid();

		/*replace this with base_conv()*/
		sprintf(str, "%d", pid);
		setenv("$", str, 0);
		find++;
		filter = comment(find);
		if (filter[0] == '$')
		{
			filter++;
			var = getenv("$");
			temp = malloc(strlen(var) + strlen(filter) + 1);
			strcpy(temp, var);
			strcat(temp, filter);
			printf("%s\n", temp);
			free(temp);
		}
		else
		{
			int found = strcspn(filter, " \t\n\r\v\f$,.");
			char *search = malloc(sizeof(char) * found + 1);
			if (search == NULL)
				return (-1);
			strncpy(search, filter, found);
			search[found] = '\0';

			var = getenv(search);
			free(search);
			if (var == NULL)
			{
				printf("NOT FOUND\n");
				return (-1);
			}
			printf("%s:\n", var);
		}
	}
}

char *comment(char *str)
{
	int find = strcspn(str, "#");
	char *filtered = malloc(sizeof(char) * find + 1);
	if (filtered == NULL)
		return  (NULL);
	strncpy(filtered, str, find);
	filtered[find] = '\0';

	return(filtered);
}

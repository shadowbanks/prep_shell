#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int ac, char **av, char **env)
{
	struct stat stbuf;
	char *path = getenv("PATH"), *path_dir = NULL, *buff = NULL;
	int i;

	if (ac < 2)
	{
		printf("Usage :%s file-name\n", av[0]);
		return (-1);
	}
	printf("PATH\n----\n%s\n", path);
	path_dir = strtok(path, ":");

	i = 1;
	while(path_dir)
	{
		while (av[i])
		{
			buff = malloc(strlen(path_dir) + strlen(av[i]) + 2);
			if (buff == NULL)
				return (1);
			strcpy(buff, path_dir);
			strcat(buff, "/");
			strcat(buff, av[i]);

			if (stat(buff, &stbuf) == 0)
			{
				printf("FOUND\n");
				break;
			}
			else
			{
				printf("%s: NOT FOUND\n", buff);
				break;
			}
		}

		//printf("%s\n", path_dir);
		path_dir = strtok(NULL, ":");
	}
	//if (path_dir
/*
	i = 1;
	while (av[i])
	{
		if (stat(av[i], &stbuf) == 0)
			printf(" FOUND\n");
		else
			printf(" NOT FOUND\n");
		i++;
	}
	return (0);*/
}

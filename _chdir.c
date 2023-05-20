#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int _cd(const char *dir)
{
        int result;
        char prev_dir[100] = "";
        if (!dir)
        {
                perror("Error");
                return (1);
        }
        if (strcmp(dir, "-") == 0)
        {
                if(strlen(prev_dir) > 0)
                {
                        result = chdir(prev_dir);
                        printf("%s", prev_dir);
                        if (result != 0)
                        {
                                perror("Error");
                        }
                }
        }
        else
        {
                result = chdir(dir);
                if (result != 0)
                {
                        perror("Error");
                }
                else
                {
                        printf("changed%s\n", dir);
                }
		}
        if(getcwd(prev_dir, sizeof(prev_dir)) == NULL)
        {
                perror("Error");
        }
        return(0);
}

int main(int argc, char *argv[])
{
        if (argc == 1)
        {
                const char *home = getenv("HOME");
                _cd(home);
        }
        else if (argc == 2)
        {
                const char *dir = argv[1];
                _cd(dir);
        }
        else
        {
                perror("Error");
        }
	return (0);
}

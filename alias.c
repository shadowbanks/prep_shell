#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct
{
        char* name;
        char* value;
}alias;

void ALias();

int main() 
{
        ALias();
        return 0;

}

void ALias()
{
        alias aliases[200];
        int num = 0, i, j;
        size_t n = 0;
        int length;
        char *args[100], *argument;
        char *command = NULL;
        char *name, *value;
        char *Alias;
        pid_t pid;


while(1)
{
        printf("$ ");
        if (getline(&command, &n, stdin) == -1)
        {
                perror("Error");
                break;
        }

        length = strlen(command);

        if (command[length - 1] == '\n')
        {
                command[length - 1] = '\0';
        }

        if (strncmp(command, "alias", 5) == 0)
        {
                if (strcmp(command + 6, "") == 0)
                {
                        if (num == 0)
                        {
                                printf("No aliases found\n");
                        }
                        else
                        {
                                printf("Available aliases:\n");
                                for (i = 0; i < num; i++)
                                {
                                        printf("%s=%s\n", aliases[i].name, aliases[i].value);
                                }
                        }
                }

                else
                {
                         argument = command + 6;

                        for (i = 0; i < num; i++)
                        {
                                if (strcmp(aliases[i].name, argument) == 0)
                                {
                                        printf("Alias already exists\n");
                                        return;
                                }
                        }


                if (num == 200)
                {
                        printf("Maximum number of aliases reached\n");
                        return;
                }

                name = strtok(argument, "=");
                value = strtok(NULL, "=");

                if (name == NULL || value == NULL)
                {
                        printf("Invalid alias format\n");
                        return;
                }

                aliases[num].name = malloc(strlen(name) + 1);
                aliases[num].value = malloc(strlen(value) + 1);

                strcpy(aliases[num].name, name);
                strcpy(aliases[num].value, value);

                num++;
                }
        }
                else if (strncmp(command, "unalias", 7) == 0)
                {
                         argument = command + 8;

                //delete alias
                        for (i = 0; i < num; i++)
                        {
                                if (strcmp(aliases[i].name, argument) == 0)
                                {
                                        free(aliases[i].name);
                                        free(aliases[i].value);

                                }
                        }

                                printf("Alias not found\n");
                }
/*
                else
                {
                        for (i = 0; i < num; i++)
                        {
                                if (strcmp(aliases[i].name, command) == 0)
                                {
                                        Alias = aliases[i].value;
                j = 0;
                args[j] = strtok(Alias, " ");

                while (Alias)
                {
                        args[j++] = Alias;
                        Alias = strtok(NULL, " ");
                }
                args[j] = NULL;

                pid = fork();

                if (pid == 0)
                {
                        if (execvp(args[0], args) == -1)
                        {
                                perror("Error");
                                exit(1);
                        }
                }
                perror("Error\n"); 
                return;
        }
*/
}
}

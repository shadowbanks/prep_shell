#include "main.h"
//#include "env.c"


const char* executable_path(const char* command, char *exec_path, char *path)
{
        int found = 0;
         
        char *dir = strtok(path, ":");

   while (dir)
    {
       int j = 0;

        strcpy(exec_path, dir);
        strcat(exec_path, "/");
        strcat(exec_path, command);

        //printf("%s\n", exec_path);
        if (access(exec_path, X_OK) == 0)
        {
            found = 1;
            break;
        }
        
        dir = strtok(NULL, ":");
    }

    if (!found)
    {
        perror("Error");
        return NULL;
    }
//      printf("return%s", dir);
    return exec_path;
}


int main(int ac, char **av, char **env)
{
        char *buff = NULL, *path = getenv("PATH");
        size_t n = 0;
        ssize_t line = 0;
        char face[] = ":)", *args[100], *token, *token1;
        pid_t pid;
        int i, j = 0;
        int status;
        const char *exec_path1;
        char exec_path[500];


        while(line != EOF)
        {
                write(1, face, 2);

                line = getline(&buff, &n, stdin);

                if(line == -1)
                {
                        return(-1);
                }

                if (strlen(buff) == 0)
                {
                        continue;
                }

                if(buff[line - 1] == '\n')
                        buff[line - 1] = '\0';

                j = 0;

                if((token1 = strtok(buff, ";")) != NULL)
                {
                        while(token1)
                        {
                                i = 0;

                                token = strtok(token1, " ");

                                while(token)
                                {
                                        args[i] = token;
                                        token = strtok(NULL, " ");
                                        i++;
                                }
                                args[i] = NULL;

								if(args[0] == NULL)
									continue;

								if(strcmp(args[0], "env") == 0)
								{
										//env1();
										continue;
								}
								if(strcmp(args[0], "exit") == 0)
										break;

								pid = fork();

								if (pid == -1)
								{
										perror("Error");
								}

								else if (pid == 0)
								{

									if (args[0][0] != '/')
											exec_path1 = executable_path(args[0], exec_path, path);
									else
											exec_path1 = args[0];

									if (exec_path1)
									{
											if(execve(exec_path1, args, NULL) == -1)
											{
													perror(exec_path1);
											}
									}
									exit(0);
								}

								else
								{
										wait(&status);
								}

								token1 = (NULL,";"); 
						}
                }
		}

        free(buff);

        return (0);
}

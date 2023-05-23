#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int status; 
	char *commands = NULL;
	char *command; 
	size_t bufsize = 0; 

	while (1)
	{
		printf("$ ");
		if (getline(&commands, &bufsize, stdin) == -1)
		{
			perror("Error reading commands");
			exit(1);
		}

		command = strtok(commands, "&&");

		while (command != NULL)
		{
			if ((command[strlen(command) - 1]) == '\n')
				command[strlen(command) - 1] = '\0';
			char *args[] = {command, NULL};
			pid_t pid = fork();
			
			if (pid == 0) 
			{
				/*char *args[] = {"/bin/sh","-c", command};*/
				if(execve(args[0], args, NULL) != 0)
				{
					printf("%s\n", args[0]);
					perror("Error executing command");
					break;
				}
			}

			else if (pid > 0)
			{
				wait(&status);
				
			if (status != 0)
			{
                		perror("Error");
 	          		free(commands);
				break;
			}
			}
		command = strtok(NULL, "&&");
	}
	}
    free(commands);
	return (0);	
}



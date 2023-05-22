#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int status;
	char *commands = NULL;
	char *command, *token;
	size_t bufsize = 0;
	int length, i;
	pid_t pid;
	char *args[100];

	while (1)
	{
		printf("$ ");
		if (getline(&commands, &bufsize, stdin) == -1)
		{
			perror("Error reading commands");
			exit(1);
		}

		command = strtok(commands, "||");
		
		while (command != NULL)
		{
			if (command[length - 1] == '\n')
			{
				command[length - 1] == '\0';
			}
			i = 0;
			
			token = strtok(command, " ");
			
			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			
			
			pid = fork();
			
			if (pid == 0)
			{
				execve(args[0], args, NULL);
				
				perror("Error executing command");
				exit(1);
			}
			
			else if (pid > 0)
			{
				wait(&status);
				
				if(status == 0)
				break;
			}
		
			else
			
			command = strtok(NULL, "||");
		}
		
		/*else
		{
			perror("Error");
			exit(1);
		}*/
	}
	}

	free(commands);
	return(0);
}

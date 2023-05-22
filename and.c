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
	size_t bufsize = 0, length;
	char *args[200], *token;
	int i;
	pid_t pid;

	while (1)
	{
		printf("$ ");
		if (getline(&commands, &bufsize, stdin) == -1)
		{
			perror("Error reading commands");
			exit(1);
		}
		
		length = strlen(commands);
     
		command = strtok(commands, "&&");

		while (command != NULL)
		{
<<<<<<< HEAD
	
			if (commands[length - 1] == '\n')
			{
				commands[length - 1] == '\0';
			}            
			i = 0;
				
			token = strtok(command, " ");
=======
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
>>>>>>> 085c185bdcaf43d42f53d55e0110f4cd8533e68d

			while (token != NULL)
			{
				args[i++] = token;
				token = strtok(NULL, " ");
			}
			args[i] = NULL;
			
			pid = fork();
			
			if (pid == 0)
			{
<<<<<<< HEAD
				if (execve(args[0], args, NULL) == -1);
				{
					printf("%s", args[0]);
					perror("Error executing command");
					exit(1);
				}
=======
                		perror("Error");
 	          		free(commands);
				break;
>>>>>>> 085c185bdcaf43d42f53d55e0110f4cd8533e68d
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


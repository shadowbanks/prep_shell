#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void execute_command(char* command) {
    char* argv[64];
    int argc = 0;
    
    // Tokenize the command string
    char* token = strtok(command, " ");
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;  // Null-terminate the argument list
    
    // Execute the command
    execvp(argv[0], argv);
    
    // If execvp returns, there was an error
    perror("Error executing command");
    exit(EXIT_FAILURE);
}

int main() {
    char command[256];
    
    while (1) {
        printf("Enter a command: ");
        fgets(command, sizeof(command), stdin);
        
        // Remove trailing newline character
        command[strcspn(command, "\n")] = '\0';
        
        // Split the command into separate commands on "&&" or "||"
        char* token = strtok(command, "&&||");
        while (token != NULL) {
            int status;
            int execute_next = 1;
            
            // Check if the command is negated with "!"
            int negated = 0;
            if (token[0] == '!') {
                negated = 1;
                token++;
            }
            
            // Execute the command in a child process
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // Child process
                execute_command(token);
            } else {
                // Parent process
                waitpid(pid, &status, 0);
                
                // Determine if the command should be executed based on the logical operator
                if ((status == 0 && !negated) || (status != 0 && negated))
                    execute_next = 1;
                else
                    execute_next = 0;
            }
            
            // Get the next command
            token = strtok(NULL, "&&||");
            
            // Check if the next command should be executed
            if (token != NULL && strcmp(token, "&&") == 0 && !execute_next)
                break;
            else if (token != NULL && strcmp(token, "||") == 0 && execute_next)
                break;
        }
    }
    
    return 0;
}


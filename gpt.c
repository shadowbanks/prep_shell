#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int execute_command(char *command) {
    char *arguments[MAX_ARGUMENTS];
    int argument_count = 0;

    // Split the command into arguments
    char *token = strtok(command, " \t\n");
    while (token != NULL && argument_count < MAX_ARGUMENTS - 1) {
        arguments[argument_count] = token;
        argument_count++;
        token = strtok(NULL, " \t\n");
    }
    arguments[argument_count] = NULL;

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() failed");
        return -1;
    } else if (pid == 0) {
        // Child process
        execvp(arguments[0], arguments);
        perror("execvp() failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            return exit_status;
        }
        return -1;
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    printf("Simple Shell\n");
    while (1) {
        printf("> ");
        fgets(command, sizeof(command), stdin);

        // Remove the trailing newline character
        command[strcspn(command, "\n")] = '\0';

        char *token = strtok(command, "&&");
        while (token != NULL) {
            int exit_status = execute_command(token);
            if (exit_status != 0) {
                printf("Command failed: %s\n", token);
                break;
            }
            token = strtok(NULL, "&&");
        }
    }

    return 0;
}


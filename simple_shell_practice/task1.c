#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char** environ; // Declare environ explicitly

#define MAX_COMMAND_LENGTH 256

int main() {
    char input[MAX_COMMAND_LENGTH];

    while (1) {
        // Display a prompt
        printf("simple_shell> ");

        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle Ctrl+D (end of file)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Execute the command using execve
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            // Child process
            char *args[] = {input, NULL};
            execve(input, args, environ);
            // If execve returns, it means an error occurred
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                printf("Exit status: %d\n", exit_status);
            } else if (WIFSIGNALED(status)) {
                int term_signal = WTERMSIG(status);
                printf("Terminated by signal: %d\n", term_signal);
            }
        }
    }

    return EXIT_SUCCESS;
}


#include "shell.h"

extern char** environ; // Declare environ explicitly

#define MAX_COMMAND_LENGTH 256
#define MAX_ARGS 64

int command_exists(const char* command) {
    char* path = getenv("PATH");
    if (path != NULL) {
        char path_copy[strlen(path) + 1];
        strcpy(path_copy, path);

        char* dir = strtok(path_copy, ":");
        while (dir != NULL) {
            char command_path[MAX_COMMAND_LENGTH];
            snprintf(command_path, sizeof(command_path), "%s/%s", dir, command);
            if (access(command_path, X_OK) == 0) {
                return 1; // Command exists
            }
            dir = strtok(NULL, ":");
        }
    }
    return 0; // Command not found


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

        // Parse the command and arguments
        char* args[MAX_ARGS];
        int num_args = 0;
        char* token = strtok(input, " ");
        while (token != NULL && num_args < MAX_ARGS - 1) {
            args[num_args] = token;
            num_args++;
            token = strtok(NULL, " ");
        }
        args[num_args] = NULL;

        if (num_args == 0) {
            // No command entered, just display the prompt again
            continue;
        }

        // Check if the command exists in the PATH
        if (!command_exists(args[0])) {
            printf("Command not found: %s\n", args[0]);
            continue;
        }

        // Execute the command using execvp
        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
        } else if (pid == 0) {
            // Child process
            execvp(args[0], args);
            // If execvp returns, it means an error occurred
            perror("execvp");
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

#include "lib/Main.h"

int main(int argc, char* argv[]) {
    pid_t pid;

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // This is the child process

        // Run the server
        run_server();

        // Exit the child process
        exit(EXIT_SUCCESS);
    } else {
        // This is the parent process

        // Wait for a command
        while (true) {
            printf("Enter a command: ");
            char command[100];
            if (fgets(command, sizeof(command), stdin) == NULL) {
                // If fgets returns NULL, an error occurred or the end of the file was reached
                if (feof(stdin)) {
                    printf("End of input reached\n");
                    break;
                } else {
                    perror("fgets");
                    exit(EXIT_FAILURE);
                }
            }

            // Strip the newline character from the end of the command
            int len = strlen(command);
            if (len > 0 && command[len-1] == '\n') {
                command[len-1] = '\0';
            }

            // Check the command
            if (strcmp(command, "stop") == 0) {
                // Send a SIGINT signal to the child process to stop the server
                if (kill(pid, SIGINT) == -1) {
                    perror("kill");
                    exit(EXIT_FAILURE);
                }

                // Wait for the child process to exit
                int status;
                if (waitpid(pid, &status, 0) == -1) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }

                break;
            } else {
                printf("Unknown command: %s\n", command);
            }
        }
    }

    return 0;
}

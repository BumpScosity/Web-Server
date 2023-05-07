#include "lib/Main.h"

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process runs the server
        run_server();
    } else {
        // Parent process waits for input from user
        char command[100];
        while (1) {
            printf("Enter a command (stop to quit): ");
            fgets(command, sizeof(command), stdin);
            command[strlen(command) - 1] = '\0';  // remove newline character
            
            if (strcmp(command, "stop") == 0) {
                kill(pid, SIGTERM);  // send termination signal to child process
                break;
            } else {
                printf("Unknown command\n");
            }
        }
    }

    return 0;
}
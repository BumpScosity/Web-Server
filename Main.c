#include "lib/Main.h"
#include <stdio.h>

int main() {
    pid_t pid = fork();
    printf("Pid1: %d\n", pid);

    if (pid == 0) {
        // Child process runs the server
        printf("Pid3: %d\n", pid);
        run_server();
        printf("Pid4: %d\n", pid);
    } else {
        // Parent process waits for input from user
        printf("Pid2: %d\n", pid);
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
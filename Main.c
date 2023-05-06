#include "lib/Main.h"

int main() {
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        // Error forking
        printf("Error: Could not fork.\n");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        run_server();
        exit(0);
    } else {
        // Parent process
        while (1) {
            char command[100];
            printf("(server) ");
            scanf("%99s", command);
            if (strcmp(command, "stop") == 0) {
                exit(1);
                break;
            }
        }
    }

    return 0;
}
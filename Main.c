#include "lib/Main.h"

int main() {
    pid_t pid;
    signals signal[1];
    signal[0].exit = 0;
    signal[0].close = 0;

    pid = fork();
    if (pid == 0) {
        // Child process
        run_server();
        exit(0);
    } else if (pid > 0) {
        // Parent process
        while (1) {
            if (signal[0].exit == 1) {
                kill(pid, SIGTERM);
                wait(NULL);
                exit(0);
            }
            else {
                char command[100];
                printf("Enter a command: ");
                scanf("%s", command);
                if (strcmp(command, "stop") == 0) {
                    signal[0].close = 1;
                    break;
                }
            }
        }

        // Wait for the child process to exit before terminating
        int status;
        waitpid(pid, &status, 0);
    } else {
        // Error forking
        printf("Error: Could not fork.\n");
        exit(1);
    }

    return 0;
}
#include "lib/Main.h"

int main() {
    pid_t pid;
    signals signal[1];
    signal[0].exit = 0;
    signal[0].close = 0;

    pid = fork();
    if (pid == -1) {
        // Error forking
        printf("Error: Could not fork.\n");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        run_server(signal);
        exit(0);
    } else {
        // Parent process
        while (1) {
            if (signal[0].exit == 1) {
                if (kill(pid, SIGTERM) < 0) {
                    perror("Error killing child process");
                }
                wait(NULL);
                exit(0);
            }
            else {
                char command[100];
                printf("(server) ");
                scanf("%99s", command);
                if (strcmp(command, "stop") == 0) {
                    signal[0].close = 1;
                    break;
                }
            }
        }
    }

    return 0;
}
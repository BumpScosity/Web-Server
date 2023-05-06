#include "lib/Main.h"
#include <stdio.h>

int main() {
    printf("1");
    signals signal[2];
    signal[0].exit = 0;
    signal[0].close = 0;
    pid_t pid = fork();
    printf("2");

    if (pid == 0) {
        // Child process runs the server
        run_server(signal);
        printf("3");
    } else {
        // Parent process waits for input from user
        char command[100];
        printf("4");
        while (1) {
            if (signal[0].exit == 1) {
                printf("5");
                kill(pid, SIGTERM);
                wait(NULL);
                exit(0);
            }
            else {
                printf("6");
                printf("(server) ");
                fgets(command, sizeof(command), stdin);
                command[strlen(command) - 1] = '\0';  // remove newline character
            
                if (strcmp(command, "stop") == 0) {
                    signal[1].close = 1;
                    break;
                } else {
                    printf("Unknown command, use \"help\" to get a list of commands.\n");
                }
            }
        }
    }

    return 0;
}


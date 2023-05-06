#include "lib/Main.h"

int main() {
    signals signal[2];
    signal[0].exit = 0;
    signal[0].close = 0;
    pid_t pid = fork();

    if (pid == 0) {
        // Child process runs the server
        run_server(signal);
    } else {
        // Parent process waits for input from user
        char command[100];
        while (1) {
            if (signal[0].exit == 1) {
                kill(pid, SIGTERM);
                wait(NULL);
                exit(0);
            }
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

    return 0;
}


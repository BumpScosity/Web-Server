#include "lib/Main.h"
#include <stdio.h>

int main(int argc, char** argv) {
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // child process
        printf("1");
        run_server();
        printf("2");
        exit(EXIT_SUCCESS);
        printf("3");
    } else {
        // parent process
        printf("Child process ID: %d\n", pid);
        char command[100];
        while(1) {
            printf("(server) ");
            fgets(command, sizeof(command), stdin);
            command[strlen(command) - 1] = '\0';  // remove newline character
            
            if (strcmp(command, "stop") == 0) {
                break;
            } else {
                printf("Unknown command\n");
            }
        }
        int status;
        waitpid(pid, &status, 0);
        printf("Child process exited with status %d\n", status);
    }

    return 0;
}

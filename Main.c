#include "lib/Main.h"

int main() {
    pid_t pid;

    pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // child process
        run_server();
        exit(EXIT_SUCCESS);
    } else {
        // parent process
        printf("Child process PID: %d\n", pid);
        // parent process code goes here
        // ...
        wait(NULL); // wait for child process to terminate
    }

    return 0;
}
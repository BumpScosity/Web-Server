#include "lib/Main.h"

int main(int argc, char** argv) {
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
        printf("Child process ID: %d\n", pid);

        // wait for child process to exit
        int status;
        waitpid(pid, &status, 0);
        printf("Child process exited with status %d\n", status);
    }

    return 0;
}

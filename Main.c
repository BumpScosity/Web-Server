#include "lib/Main.h"

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[1024];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pipefd[0]); // Close the read end of the pipe

        const char* message = "Hello, parent process!";
        write(pipefd[1], message, strlen(message) + 1); // Write the message to the pipe

        close(pipefd[1]); // Close the write end of the pipe

        exit(EXIT_SUCCESS);
    } else { // Parent process
        close(pipefd[1]); // Close the write end of the pipe

        read(pipefd[0], buffer, 1024); // Read the message from the pipe
        printf("Received message from child process: %s\n", buffer);

        close(pipefd[0]); // Close the read end of the pipe

        exit(EXIT_SUCCESS);
    }

    return 0;
}
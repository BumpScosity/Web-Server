#include "lib/Main.h"

void child_process(int read_pipe, int write_pipe) {
    // Read the function pointer from the pipe
    void (*func)(void);
    read(read_pipe, &func, sizeof(func));

    // Call the function
    run_server();

    // Close the pipes and exit
    close(read_pipe);
    close(write_pipe);
    exit(0);
}

int main() {
    int fd[2];
    pid_t pid;

    // Create a pipe for communication between the parent and child processes
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork the process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        const char* message = "Hello, parent process!";
        write(pipefd[1], message, strlen(message) + 1); // Write the message to the pipe
        close(fd[1]); // Close the write end of the pipe
        child_process(fd[0], fd[1]);
    } else {
        // Parent process
        read(pipefd[0], buffer, BUFFER_SIZE); // Read the message from the pipe
        printf("Received message from child process: %s\n", buffer);

        close(pipefd[0]); // Close the read end of the pipe

        // Send the function pointer to the child process through the pipe
        void (*func)(void) = &run_server;
        write(fd[1], &func, sizeof(func));

        // Wait for the child process to exit
        wait(NULL);
    }

    return 0;
}
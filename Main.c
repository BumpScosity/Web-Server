#include "lib/Main.h"

void child_process(int fd)
{
    char buf[1024];
    int n;

    // Read command from parent process
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        // Null terminate the command string
        buf[n] = '\0';

        // Execute the command function
        if (strcmp(buf, "print_hello") == 0) {
            printf("Hello from child process!\n");
        } else if (strcmp(buf, "exit") == 0) {
            break;
        } else {
            printf("Unknown command: %s\n", buf);
        }
    }

    // Close the pipe and exit
    close(fd);
    exit(0);
}

int main()
{
    int fd[2];
    pid_t pid;

    // Create pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Create child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        close(fd[1]);  // Close write end of pipe

        // Run child process function
        child_process(fd[0]);

        // Should not reach here
        exit(1);
    } else {
        // Parent process
        close(fd[0]);  // Close read end of pipe

        // Send commands to child process
        write(fd[1], "print_hello\n", strlen("print_hello\n"));
        write(fd[1], "exit\n", strlen("exit\n"));

        // Wait for child process to exit
        wait(NULL);

        // Close write end of pipe
        close(fd[1]);

        exit(0);
    }
}

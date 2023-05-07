#include "lib/Main.h"
#include <stdio.h>

int main()
{   
    signals signal[1];
    signal[0].close = 0;
    signal[0].exit = 0;
    signal[0].running = 0;
    char buffer[1024];
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
        close(fd[0]); // Close the read end of the pipe

        const char* message = "Hello, parent process!";
        write(fd[1], message, strlen(message) + 1); // Write the message to the pipe

        close(fd[1]); // Close the write end of the pipe

        // Run child process function
        run_server();

        // Should not reach here
        exit(1);
    } else {
        // Parent process
        close(fd[1]); // Close the write end of the pipe

        read(fd[0], buffer, 1024); // Read the message from the pipe
        printf("Received message from child process: %s\n", buffer);
        close(fd[0]);  // Close read end of pipe

        char command[100];
        while (1) {
            printf("(server) ");
            fgets(command, sizeof(command), stdin);
            command[strlen(command) - 1] = '\0';  // remove newline character
            
            if (strcmp(command, "exit") == 0) {
                break;
            } else {
                printf("Unknown command\n");
            }
        }

        // Wait for child process to exit
        wait(NULL);

        exit(0);
    }
}

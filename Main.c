#include "lib/Main.h"

int main()
{   
    signals signal[1];
    signal[0].close = 0;
    signal[0].exit = 0;
    signal[0].running = 0;
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
        int* child_var = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        signal[0].running = 1;
        munmap(child_var, sizeof(int));
        close(fd[1]);  // Close write end of pipe

        // Run child process function
        run_server();

        // Should not reach here
        exit(1);
    } else {
        // Parent process
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

        // Close write end of pipe
        close(fd[1]);

        exit(0);
    }
}

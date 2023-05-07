#include "lib/Main.h"

int main(int argc, char** argv) {
    int port = 8080;
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        server(port);
        exit(EXIT_SUCCESS);
    }
    else {
        printf("Server running on port %d\n", port);
        while (1) {
            char input[256];
            printf("> ");
            fflush(stdout);
            fgets(input, sizeof(input), stdin);
            if (strcmp(input, "stop\n") == 0) {
                kill(pid, SIGTERM);
                waitpid(pid, NULL, 0);
                printf("Server stopped\n");
                exit(EXIT_SUCCESS);
            }
            else {
                printf("Unknown command\n");
            }
        }
    }
}
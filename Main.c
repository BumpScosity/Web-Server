#include "lib/Main.h"

int main()
{   
    int shm_fd;
    pid_t pid;
    void *ptr;
    struct data *data;

    // create shared memory
    shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }
    ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    data = (struct data *) ptr;
    // Default presets
    data->log = 0;
    data->buffer = 1024;
    data->port = 8080;
    data->run = 1;
    start = 0;
    stop = 0;
    running = 0;
    quit = 0;
    config(data, "default_config.conf");

    // create child process
    pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        exit(EXIT_FAILURE);
    }
    
    else if (pid == 0) {
        while (data->run) {
            if (start == 1) {
                start = 0;
                run_server(data);
            }
        }
    }

    // parent process
    char command[1024];
    while (data->run) {
        printf("(server) ");
        fgets(command, 1024, stdin);
        command[strcspn(command, "\n")] = '\0';
        if (strcmp(command, "exit") == 0 && running == 0) {
            data->run = 0;
            kill(SIGTERM, pid);
        }

        else if (strcmp(command, "exit") == 0 && running == 1) {
            printf("\nPlease stop the server before exiting...\n");
        }

        else {
            input(data, command);
            strcpy(command, "\0");
        }
    }

    // cleanup
    if (munmap(ptr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }
    if (shm_unlink("/myshm") == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}

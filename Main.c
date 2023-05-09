#include "lib/Main.h"

int main()
{
    int shm_fd;
    pid_t pid;
    void *ptr;
    struct data *data;

    // create shared memory
    printf("1");
    shm_fd = shm_open("/myshm", O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    printf("2");
    if (ftruncate(shm_fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }
    printf("3");
    ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    data = (struct data *) ptr;
    data->exit = 0;
    data->start = 0;
    data->stop = 0;


    // create child process
    printf("4");
    pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        exit(EXIT_FAILURE);
    }
    
    else if (pid == 0) {
        while (data->exit == 0) {
            if (data->start == 1) {
                data->start = 0;
                run_server(data);
            }
        }
    }

    printf("5");

    // parent process
    char command[1024];
    strcpy(command, "\0");
    printf("data: %d", data->exit);
    while (data->exit != 0) {
        printf("(server) ");
        fgets(command, 1024, stdin);
        if (strcmp(command, "exit\n")) {
            printf("Exiting...");
            data->stop = 1;
            sleep(1);
            if (data->exit == 1) {
                exit(0);
            }
            else {
                printf("Exit unsuccessful, please stop the server and manually end it if it fails again.");
            }
        }
        input(data, command);
        strcpy(command, "\0");
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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SHM_SIZE sizeof(struct shared_data)

struct shared_data {
    int exit;
};

int main()
{
    int shm_fd;
    pid_t pid;
    void *ptr;
    struct shared_data *data;

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
    data = (struct shared_data *) ptr;
    data->exit = 0;

    // create child process
    pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        while (data->exit == 0) {
            
        }
    }

    // parent process
    printf("parent with pid %d is running\n", getpid());
    wait(NULL);
    printf("child with pid %d has terminated\n", pid);
    printf("value in shared memory: %d\n", data->value);

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

#ifndef MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE sizeof(data)

struct data {
    int exit;
    int start;
    int stop;
    int running;
};

void input(data *data, char command[1024]);
void run_server(data data);


#endif // MAIN_H

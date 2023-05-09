#ifndef MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE sizeof(struct shared_data)

typedef struct {
    int exit;
    int start;
    int stop;
    int running;
} data;

void input(data *data, char command[1024]);
void run_server(data data);


#endif // MAIN_H

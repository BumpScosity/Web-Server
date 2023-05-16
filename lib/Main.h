#ifndef MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>

#define SHM_SIZE sizeof(data)

#define start data->Start
#define stop data->Stop
#define running data->Running
#define quit data->Quit

struct data {
    int Start;
    int Stop;
    int Running;
    int Quit;
};

void input(struct data *data, char command[1024]);
void run_server(struct data *data);
void serve_file(int client_socket, const char *filename);

#endif // MAIN_H

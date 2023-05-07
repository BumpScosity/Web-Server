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
#include <sys/mman.h>

typedef struct {
    int port;
    int threads;
    int buffer;
} datalist;

typedef struct {
    char *key;
} keys;

typedef struct {
    int exit;
    int close;
    int running;
} signals;

typedef struct {
    int socket;
    datalist* list;
    keys* keylist;
    signals* signal;
    int* fd;
} connection_args;

typedef struct {
    datalist *list;
    connection_args *data;
} thread_args;

void* handle_connection(void* arg);
void error_handle(int ErrorCode);
int config(datalist *list);
void run_server(signals signal[3]);
void input(signals signalp[3]);


#endif // MAIN_H
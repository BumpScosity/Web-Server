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

#include "Server.h"

const double Codes[] = {
    0, // File failed to open

    1.1, // Invalid size format
    1.2, // Size not found

    2.1, // Invalid port format
    2.2, // Port not found
    2.3, // Invalid port number

    3.1, // Invalid thread format
    3.2, // Thread not found

    4.1, // Invalid buffer format
    4.2 // Buffer not found
};

typedef struct {
    int port;
    int threads;
    int buffer;
} datalist;

typedef struct {
    char *key;
} keys;

typedef struct {
    int socket;
    datalist* list;
    keys* keylist;
} connection_args;

typedef struct {
    datalist *list;
    connection_args *data;
} thread_args;

typedef struct {
    int exit;
    int close;
} signals;

void* handle_connection(void* arg);
void error_handle(int ErrorCode);
int config(datalist *list);
void run_server(signals *signal);


#endif // MAIN_H
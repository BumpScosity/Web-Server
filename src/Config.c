#include "../lib/Main.h"

int config(datalist *list) {
    FILE *conf = fopen("config.conf", "r");
    if (conf == NULL) {
        return 1; // File not found
    }

    char buffer[1024];
    size_t n = fread(buffer, 1, sizeof(buffer), conf);
    buffer[n] = '\0';
    fclose(conf);

    int port = -1;
    int threads = -1;
    int buffer_size = -1;

    char *p = buffer;
    while (*p) {
        if (sscanf(p, "Port: %d", &port) == 1) {
            p = strchr(p, '\n') + 1;
            continue;
        }
        if (sscanf(p, "Threads: %d", &threads) == 1) {
            p = strchr(p, '\n') + 1;
            continue;
        }
        if (sscanf(p, "Buffer: %d", &buffer_size) == 1) {
            p = strchr(p, '\n') + 1;
            continue;
        }
        p = strchr(p, '\n') + 1;
    }

    if (port == -1) {
        return 4; // Port not found
    }
    if (threads == -1) {
        return 7; // Threads not found
    }
    if (buffer_size == -1) {
        return 9; // Buffer not found
    }

    if (port < 1024 || port > 65535) {
        return 5; // Invalid port number
    }

    if (threads <= 0) {
        return 6; // Invalid number of threads
    }

    if (buffer_size <= 0) {
        return 7; // Invalid buffer size
    }

    list[0].port = port;
    list[1].threads = threads;
    list[2].buffer = buffer_size;

    return 0; // Success
}
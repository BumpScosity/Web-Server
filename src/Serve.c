#include "../lib/Main.h"

char* serve_file(int client_socket, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t read;

    while ((read = getline(&buffer, &buffer_size, file)) != -1) {
        send(client_socket, buffer, read, 0);
    }

    fclose(file);
    free(buffer);
}
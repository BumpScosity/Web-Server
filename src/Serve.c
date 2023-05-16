#include "../lib/Main.h"

char *serve_file(int client_socket, const char *filename) {
    char path[256];
    snprintf(path, sizeof(path), "HTML/%s", filename); // Assuming 'public' is the child directory

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(file_size);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    char response[512];
    snprintf(response, sizeof(response), "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %ld\r\n\r\n", file_size);

    send(client_socket, response, strlen(response), 0);
    send(client_socket, buffer, file_size, 0);

    free(buffer);
}
#include "../lib/Main.h"

void* handle_connection(void* arg) {
    connection_args* args = (connection_args*) arg;
    datalist* list = args->list;
    keys* keylist = args->keylist;
    signals* signal = args->signal;
    int PORT = list[0].port;
    int NUM_THREADS = list[1].threads;
    int BUFFER_SIZE = list[2].buffer;
    int socket = args->socket;
    free(args);
    char buffer[BUFFER_SIZE];
    int n;

    // Read the request
    n = read(socket, buffer, BUFFER_SIZE - 1);
    if (n <= 0) {
        close(socket);
        return NULL;
    }
    buffer[n] = '\0';

    // Print the request
    write(fd[1], buffer, strlen(buffer) + 1); // Write the message to the pipe

    close(fd[1]); // Close the write end of the pipe

    if (strstr(buffer, "GET /") != NULL) {
        // Open the index.html file
        FILE* file = fopen("HTML/index.html", "r");
        if (file == NULL) {
            // Return a 404 error
            const char* response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not found\n";
            write(socket, response, strlen(response));
            close(socket);
            return NULL;
        }

        // Send the response
        const char* response_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
        write(socket, response_header, strlen(response_header));
        while ((n = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
            write(socket, buffer, n);
        }

        // Close the file and connection
        fclose(file);
        close(socket);

        return NULL;
    }

    // Check for a POST request
    if (strstr(buffer, "POST /key1") != NULL) {
        // Find the content length
        char* content_length_ptr = strstr(buffer, "Content-Length:");
        if (content_length_ptr == NULL) {
            // Return a 400 error
            const char* response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nContent-Length header not found\n";
            write(socket, response, strlen(response));
            close(socket);
            return NULL;
        }
        int content_length = atoi(content_length_ptr + strlen("Content-Length:"));
        if (content_length <= 0) {
            // Return a 400 error
            const char* response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nContent-Length header invalid\n";
            write(socket, response, strlen(response));
            close(socket);
            return NULL;
        }

        // Read the request payload
        char payload[content_length + 1];
        printf("Payload: %s", payload);
        n = read(socket, payload, content_length);
        if (n <= 0) {
            close(socket);
            return NULL;
        }
        payload[n] = '\0';

        // Send the response
        const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nReceived the following data:\n";
        write(socket, response, strlen(response));
        write(socket, payload, strlen(payload));

        // Close the connection
        close(socket);

        return NULL;
    }

    else if (strstr(buffer, "POST /key2") != NULL) {
        // Extract the data from the request
        char* data_start = strstr(buffer, "\r\n\r\n") + 4;
        int data_length = strlen(data_start);
        char* data = (char*) malloc(data_length + 1);
        strncpy(data, data_start, data_length);
        data[data_length] = '\0';

        // Send the response
        const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nData received\n";
        write(socket, response, strlen(response));
        close(socket);

        keylist[1].key = data;

        // Free the data buffer
        free(data);

        return NULL;
    }

    else if (strstr(buffer, "POST /key3") != NULL) {
        // Extract the data from the request
        char* data_start = strstr(buffer, "\r\n\r\n") + 4;
        int data_length = strlen(data_start);
        char* data = (char*) malloc(data_length + 1);
        strncpy(data, data_start, data_length);
        data[data_length] = '\0';

        // Send the response
        const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nData received\n";
        write(socket, response, strlen(response));
        close(socket);

        keylist[2].key = data;

        // Free the data buffer
        free(data);

        return NULL;
    }

    else if (strstr(buffer, "POST /test") != NULL) {
        printf("Key1: %s\n", keylist[0].key);
        printf("Key2: %s\n", keylist[1].key);
        printf("Key3: %s\n", keylist[2].key);

        // Send the response
        const char* response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nData received\n";
        write(socket, response, strlen(response));
        close(socket);

        return NULL;
    }

    else {
        // Return a 404 error
        const char* response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\n404 not found\n";
        write(socket, response, strlen(response));
        close(socket);
        return NULL;
    }
}
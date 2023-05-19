#include "../lib/Main.h"

void run_server(struct data *data) {
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {   
        printf("\nServer error: ");
        perror("socket failed");
        running = 0;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {   
        printf("\nServer error: ");
        perror("bind failed");
        running = 0;
        exit(EXIT_FAILURE);
    }   

    if (listen(server_fd, 3) < 0)
    {
        printf("\nServer error: ");
        perror("listen failed");
        running = 0;
        exit(EXIT_FAILURE);
    }

    while (1)
    {   
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {   
            printf("\nServer error: ");
            perror("accept failed");
            running = 0;
            exit(EXIT_FAILURE);
        }

        if (stop == 1) {
            stop = 0;
            start = 0;
            exit(0);
        }

        valread = read(new_socket, buffer, 1024);
        if (data->log == 1) {
            printf("%s\n", buffer);
        }
        char *method = strtok(buffer, " ");
        char *url = strtok(buffer, " ");

        if (method != NULL && url != NULL) {
            if (strcmp(method, "GET") == 0) {
                if (strcmp(url, "/test") == 0) {
                    serve_file(new_socket, "../HTML/index.html");
                }
            }
        }

        free(method);
        free(url);
        close(new_socket);
    }
}
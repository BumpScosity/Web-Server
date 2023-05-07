#include "../lib/Main.h"

void run_server() {
    printf("Ran1");
    keys keylist[3];
    keylist[0].key = "123";
    keylist[1].key = "467";
    keylist[2].key = "890";

    FILE* conf = fopen("config/config.conf", "r");
    if (conf == NULL) {
        error_handle(0);
    }

    int size = -1;
    char line[100];
    while (fgets(line, sizeof(line), conf) != NULL) {
        if (sscanf(line, "Size: %d", &size) == 1) {
            break;
        }
    }

    fclose(conf);

    if (size == -1) {
        
    }

    datalist list[size];
    int result = config(list);
    if (result != 0) {
        fprintf(stderr, "Failed to read configuration\n");
        exit(EXIT_FAILURE);
    }

    int PORT = list[0].port;
    int NUM_THREADS = list[1].threads;
    int BUFFER_SIZE = list[2].buffer;

    int server_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len;
    pthread_t threads[NUM_THREADS];
    int thread_index = 0;

    // Create the server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Bind the server socket to the port
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);
    if (bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address)) < 0) {
        close(server_socket);
        printf("\033[31mFAILURE:\033[36m Bind failed at port \"%d\"", PORT);
        exit(1);
    }

    // Listen for connections
    if (listen(server_socket, SOMAXCONN) < 0) {
        close(server_socket);
        printf("\033[31mFAILURE:\033[36m Listen failed at port \"%d\"\n\n", PORT);
        exit(1);
    }

    // Create the thread pool
    while (1) {
        // Accept a connection
        client_address_len = sizeof(client_address);
        int client_socket = accept(server_socket, (struct sockaddr*) &client_address, &client_address_len);
        if (client_socket < 0) {
            close(server_socket);
            printf("\033[31mFAILURE:\033[36m Accept failed at port \"%d\"\n", PORT);
            exit(1);
        }

        // Create a thread to handle the connection
        connection_args* args = (connection_args*) malloc(sizeof(connection_args));
        if (args == NULL) {
            printf("\033[31mFAILURE:\033[36m Failed to allocate memory for connection arguments\n");
            close(server_socket);
            close(client_socket);
            exit(1);
        }
        args->socket = client_socket;
        args->list = list;
        args->keylist = keylist;
        if (pthread_create(&threads[thread_index], NULL, handle_connection, args) != 0) {
            printf("\033[31mFAILURE:\033[36m Failed to create thread to handle connection\n");
            free(args);
            close(server_socket);
            close(client_socket);
            exit(1);
        }

        thread_index = (thread_index + 1) % NUM_THREADS;
    }

    // Close the server socket
    close(server_socket);
}
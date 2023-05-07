#include "lib/Main.h"

int main() {
    settings setting[3];
    setting[0].log = 1;

    signals signal[3];
    signal[0].close = 0;
    signal[0].exit = 0;
    signal[0].running = 1;
    pthread_t input_thread;
    if (pthread_create(&input_thread, NULL, input, signal) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    run_server(signal, setting);

    while (1) {
        if (signal[0].running == 0) {
            pthread_cancel(input_thread);
            signal[0].close = 1;
        }
        else if (signal[0].exit == 1) {
            printf("\nExiting server... \n");
            break;
        }
    }

    return 0;
}
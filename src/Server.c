#include "../lib/Main.h"

void run_server(struct data *data) {
    while (1) {
        if (data->stop == 1) {
            data->running = 0;
            data->stop = 0;
            break;
        }
    }
}
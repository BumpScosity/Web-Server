#include "../lib/Main.h"

void input(struct data *data, char command[1024]) {
    while(1) {
        if (strcmp(command, "run\n") == 0) {
            data->start = 1;
            data->running = 1;
            break;
        }
    }
}

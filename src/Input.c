#include "../lib/Main.h"
#include <stdio.h>

void input(struct data *data, char command[1024]) {
    while(1) {
        if (strcmp(command, "run\n") == 0) {
            data->start = 1;
            data->running = 1;
            break;
        }
        else if (strcmp(command, "stop\n") == 0) {
            data->stop = 1;
            break;
        }
        else {
            printf("Unknown command, use \"To get a list of commands\"");
            break;
        }
    }
}

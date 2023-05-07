#include "lib/Main.h"

void input(signals signal[3]) {
    char command[1024];
    while(1) {
        printf("(server) ");
        fgets(command, 1024, stdin);
        if (strcmp(input, "exit\n") == 0) {
            signal[0].running = 0;
            break;
        }
    }
}
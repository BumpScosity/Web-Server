#include "../lib/Main.h"

void input(struct data *data, char c[1024]) {
    while(1) {
        /*SERVER*/
        // START
        if (strcmp(c, "start") == 0) {
            printf("1");
            start = 1;
            running = 1;
            break;
        }
        // START

        // STOP
        else if(strcmp(c, "stop") == 0) {
            printf("2");
            stop = 1;
            running = 0;
            break;
        }
        // STOP
        /*SERVER*/
        else {
            printf("Unknown command, use \"To get a list of commands\"");
            break;
        }
    }
}

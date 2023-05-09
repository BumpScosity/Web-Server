#include "../lib/Main.h"

int command(char input[1024], char output[]) {
    char c[sizeof(output+1)];
    strcpy(c, output);
    strcat(c, "\n");

    printf("%s", c);
    if (strcmp(input, output) == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void input(struct data *data, char c[1024]) {
    while(1) {
        /*SERVER*/
        // START
        if (command(c, "start") == 1) {
            printf("1");
            start = 1;
            running = 1;
            break;
        }
        // START
        // STOP
        else if(command(c, "stop") == 1) {
            printf("2");
            stop = 1;
            running = 0;
            break;
        }
        // STOP

        // RESTART
        else if (command(c, "restart") == 1) {
            if (running == 1) {
                stop = 1;
                sleep(1);
                if (stop == 1) {
                    stop = 0;
                    printf("Restart failed, try it manually.");
                }
                else {
                    start = 1;
                    sleep(1);
                    if (start == 1) {
                        start = 0;
                        printf("Restart failed, try it manually.");
                    }
                    else {
                        printf("Restarted successfully.");
                        break;
                    }
                }
            }
        }
        // RESTART

        /*SERVER*/

        else {
            printf("Unknown command, use \"To get a list of commands\"");
            break;
        }
    }
}

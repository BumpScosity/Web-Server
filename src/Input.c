#include "../lib/Main.h"

void input(struct data *data, char c[1024]) {
    while(1) {
        /*GENERAL*/
        // HELP
        if (strcmp(c, "help") == 0) {
            printf("help: Provides a list of commands\n");
            printf("start: Starts the server\n");
            printf("stop: Stops the server\n");
            printf("log: Shows if logging is disabled or enabled\n");
            printf("log -b true: Enables logging\n");
            printf("log -b false: Disables logging\n");
            break;
        }
        // HELP
        /*GENERAL*/
        /*SERVER*/
        // START
        else if (strcmp(c, "start") == 0) {
            start = 1;
            running = 1;
            break;
        }
        // START

        // STOP
        else if(strcmp(c, "stop") == 0) {
            stop = 1;
            running = 0;
            break;
        }
        // STOP

        // LOG
        else if (strcmp(c, "log") == 0) {
            if (data->log == 0) {
                printf("Logging is disabled");
            }
            else {
                printf("Logging is enabled");
            }
            break;
        }
        // LOG
        /*SERVER*/
        else {
            printf("Unknown command, use \"help\" to get a list of commands...\n");
            break;
        }
    }
}

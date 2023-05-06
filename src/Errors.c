#include "../lib/Main.h"

const double Codes[] = {
    0, // File failed to open

    1.1, // Invalid size format
    1.2, // Size not found

    2.1, // Invalid port format
    2.2, // Port not found
    2.3, // Invalid port number

    3.1, // Invalid thread format
    3.2, // Thread not found

    4.1, // Invalid buffer format
    4.2 // Buffer not found
};

void error_handle(int ErrorCode) {
    switch (ErrorCode) {
        case 0:
            printf("\033[31mERROR %.1f:\033[0m Config file missing!\n\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m Config file name should be \"config.conf\".\n\n", Codes[ErrorCode]);

        case 1:
            printf("\033[31mERROR %.1f:\033[0m Size format is invalid!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m The correct format for size is \"Size: YOUR_SIZE_HERE\".\n\n", Codes[ErrorCode]);
        case 2:
            printf("\033[31mERROR %.1f:\033[0m Size value not found!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m Make sure to include: \"Size: YOUR_SIZE_HERE\" in the config file.\n\n", Codes[ErrorCode]);

        case 3:
            printf("\033[31mERROR %.1f:\033[0m Port format is invalid!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m The correct format for size is \"Port: YOUR_PORT_HERE\".\n\n", Codes[ErrorCode]);
        case 4:
            printf("\033[31mERROR %.1f:\033[0m Port value not found!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m Make sure to include: \"Port: YOUR_PORT_HERE\" in the config file.\n\n", Codes[ErrorCode]);
        case 5:
            printf("\033[31mERROR %.1f:\033[0m Port value is to big!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m Make sure the port value is under 65536 and above 1023.\n\n", Codes[ErrorCode]);

        case 6:
            printf("\033[31mERROR %.1f:\033[0m Thread format is valid!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m The correct format for size is \"Threads: YOUR_THREAD_NUMBER_HERE\".\n\n", Codes[ErrorCode]);
        case 7:
            printf("\033[31mERROR %.1f:\033[0m Thread value not found!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m Make sure to include: \"Threads: YOUR_THREAD_NUMBER_HERE\" in the config file.\n\n", Codes[ErrorCode]);

        case 8:
            printf("\033[31mERROR %.1f:\033[0m Buffer format is invalid!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m The correct format for size is \"Buffer: YOUR_BUFFER_SIZE_HERE\".\n\n", Codes[ErrorCode]);
        case 9:
            printf("\033[31mERROR %.1f:\033[0m Buffer value not found!\n", Codes[ErrorCode]);
            printf("\033[0;36mNote %.1f:\033[0m Make sure to include: \"Buffer: YOUR_BUFFER_SIZE_HERE\" in the config file.\n\n", Codes[ErrorCode]);
    }
    exit(1);
}
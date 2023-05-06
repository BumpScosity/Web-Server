#include "Main.h"

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

void error_handle(int ErrorCode);


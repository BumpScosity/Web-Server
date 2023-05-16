#include "../lib/Main.h"

void config(struct data *data, const char *filename)
{   
    char path[256];
    int result;

    const char *pattern1 = "port:";
    const char *pattern2 = "buffer:";

    snprintf(path, sizeof(path), "config/%s", filename); // Assuming 'public' is the child directory

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("File opening failed");
        exit(EXIT_FAILURE);
    }
    char line[1024];
    while (fgets(line, 1024, file)) {
        if (strncmp(line, pattern1, strlen(pattern1)) == 0) {
            result = atol(line);
            data->port = result;
            continue;
        }
        else if (strncmp(line, pattern2, strlen(pattern2)) == 0) {
            result = atol(line);
            data->buffer = result;
            continue;
        }
        break;
    }
    fclose(file);
}
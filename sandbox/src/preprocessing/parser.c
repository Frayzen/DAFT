#include "../../include/preprocessing/parser.h"

void parseFile(char* path, void (*callback)(char* line, void* data), void* data) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", path);
        exit(1);
    }
    
    char* line = NULL;
    size_t len = 0;
    int read;
    
    while ((read = getline(&line, &len, file)) != -1) {
        callback(line, data);
    }
    
    fclose(file);
    if (line) {
        free(line);
    }
}
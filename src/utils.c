#include "utils.h"
#include <stdlib.h>
#include <stdarg.h>


void Log(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);

    fflush(stdout);
}



// malloc wrapper, checks for null
void* safe_malloc(const size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        perror("Failed malloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

// fopen wrapper, checks for null
FILE* file_open(const char* path) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        perror("Failed to open rom");
        exit(EXIT_FAILURE);
    }
    return file;
}

// Returns size of file in bytes
size_t file_get_size(FILE* file) {
    fseek(file, 0, SEEK_END);
    const size_t fsize = ftell(file);
    fseek(file, 0, SEEK_SET);
    return fsize;
}

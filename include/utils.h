#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

void* safe_malloc(const size_t size);
FILE* file_open(const char* path);
size_t file_get_size(FILE* file);

#endif

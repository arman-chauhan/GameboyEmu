#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define SET_BIT(byte, bit) (*(byte) |= (1 << (bit)))
#define CLEAR_BIT(byte, bit) (*(byte) &= ~(1 << (bit)))
#define GET_BIT(value, bit) (((value) >> (bit)) & 0x01)



void* safe_malloc(const size_t size);
FILE* file_open(const char* path);
size_t file_get_size(FILE* file);
void Log(char* fmt, ...);


#endif

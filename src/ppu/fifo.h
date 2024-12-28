#ifndef FIFO_H
#define FIFO_H

#include <common.h>

typedef struct pixel_t {
    struct pixel_t* next;
    u8 value;
} pixel_t;

typedef struct fifo_t {
    pixel_t* head;
    pixel_t* tail;
    u8 size;
} fifo_t;

void fifo_push(fifo_t* fifo, u8 value);
u8 fifo_pop(fifo_t* fifo);
void fifo_clear(fifo_t* fifo);

#endif
#include <common.h>
#include <fifo.h>
#include <utils.h>


void fifo_push(fifo_t *fifo, u8 value, u8 palatte, u8 bgOsp) {
    pixel_t *newPixel = malloc(sizeof(pixel_t));
    if (newPixel == NULL) {
        Log("Failed allocating new pixel for the fifo!");
        exit(EXIT_FAILURE);
    }
    newPixel->value = value;
    newPixel->next = NULL;
    newPixel->palatte = palatte;
    newPixel->bgOsp = bgOsp;

    if (fifo->size == 0) {
        fifo->head = newPixel;
        fifo->tail = newPixel;
    } else {
        fifo->tail->next = newPixel;
        fifo->tail = newPixel;
    }

    fifo->size++;
}

pixel_t fifo_pop(fifo_t *fifo) {
    if (fifo->size == 0) {
        Log("Can't pop from a empty queue!");
        exit(EXIT_FAILURE);
    }

    pixel_t *popped = fifo->head;
    pixel_t pixel = {
        .value = popped->value,
        .palatte = popped->palatte,
        .bgOsp = popped->bgOsp,
    };
    fifo->head = fifo->head->next;

    if (fifo->head == NULL) {
        fifo->tail = NULL;
    }

    free(popped);
    fifo->size--;
    return pixel;
}

void fifo_clear(fifo_t *fifo) {
    pixel_t *current = fifo->head;
    while (current != NULL) {
        pixel_t *next = current->next;
        free(current);
        current = next;
    }
    fifo->head = fifo->tail = NULL;
    fifo->size = 0;
}

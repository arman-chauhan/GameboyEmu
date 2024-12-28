#ifndef DMA_H
#define DMA_H

#include <stdint.h>
#include <stdbool.h>

void dma_tick(uint8_t cycles);
void dma_start(uint8_t addr);
bool dma_is_active();
void test(void);

void DrawTilesFromVRAM();
#endif
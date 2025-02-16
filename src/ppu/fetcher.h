#ifndef FETCHER_H
#define FETCHER_H
#include <common.h>
#include <ppu.h>



void fetcher_tick(ppu_t* ppu, fetcher_t* fetcher);
void fetcher_start(fetcher_t* fetcher, u16 tileMapAddr, u16 tileData, u8 tileOffset, u8 tileLine);

#endif
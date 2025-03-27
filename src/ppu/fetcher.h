#ifndef FETCHER_H
#define FETCHER_H
#include <common.h>
#include <ppu.h>



void fetcher_tick(ppu_t* ppu, fetcher_t* fetcher);
void fetcher_start(fetcher_t* fetcher);
void fetcher_start_sprite_fetch(ppu_t* ppu, u8 sprite_index);
#endif

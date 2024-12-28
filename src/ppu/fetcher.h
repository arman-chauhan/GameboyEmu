#ifndef FETCHER_H
#define FETCHER_H

#include <common.h>
#include <fifo.h>

enum FetcherState {
    ReadTileID,
    ReadTileData0,
    ReadTileData1,
    PushToFIFO,
};



typedef struct {
    enum FetcherState state;
    fifo_t fifo;
    u8 ticks;

    u16 mapAddr;
    u8 tileLine;
    u16 tileIndex;
    u8 tileID;
    u8 tileLineLow;
    u8 tileLineHigh;
} fetcher_t;

void fetcher_tick(fetcher_t *);
void fetcher_start(fetcher_t *fetcher, u16 tileMapAddr, u8 tileLine);

#endif
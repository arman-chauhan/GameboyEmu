#include <fetcher.h>
#include <mmu.h>
#include <utils.h>

void fetcher_start(fetcher_t* fetcher, u16 mapAddr, u8 tileLine) {
    fetcher->state = ReadTileID;
    fetcher->ticks = 0;

    fetcher->tileIndex = 0;
    fetcher->tileLine = tileLine;
    fetcher->mapAddr = mapAddr;

    // fifo_clear(&fetcher->fifo);
}

void fetcher_tick(fetcher_t* fetcher) {
    fetcher->ticks++;
    if (fetcher->ticks < 2) {
        return;
    }

    fetcher->ticks = 0;

    switch (fetcher->state) {
    case ReadTileID:
        fetcher->tileID = mmu_readU8(fetcher->mapAddr + fetcher->tileIndex);
        fetcher->state = ReadTileData0;
        break;
    case ReadTileData0: {
        u16 offset = 0x8000 + fetcher->tileID * 16;
        u16 addr = offset + fetcher->tileLine * 2;
        fetcher->tileLineLow = mmu_readU8(addr);

        fetcher->state = ReadTileData1;
    } break;
    case ReadTileData1: {
        u16 offset = 0x8000 + fetcher->tileID * 16;
        u16 addr = offset + fetcher->tileLine * 2;
        fetcher->tileLineHigh = mmu_readU8(addr + 1);

        fetcher->state = PushToFIFO;
    } break;
    case PushToFIFO:
        if (fetcher->fifo.size <= 8) {
            uint8_t hi = fetcher->tileLineHigh;
            u8 lo = fetcher->tileLineLow;

            u8 tile_row[8];
            for (u8 i = 0; i < 8; i++) {
                uint8_t p = GET_BIT(hi, (7 - i)) << 1 | GET_BIT(lo, (7 - i));
                tile_row[i] = p;
            }

            for (int i = 0; i < 8; i++) {
                fifo_push(&fetcher->fifo, tile_row[i]);
            }

            fetcher->tileIndex++;
            fetcher->state = ReadTileID;
        }
        break;
    default:
        Log("Invalid fetcher state!");
        exit(EXIT_FAILURE);
    }
}
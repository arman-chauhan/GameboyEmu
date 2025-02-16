#include <fetcher.h>
#include <mmu.h>
#include <string.h>
#include <utils.h>

void fetcher_start(fetcher_t* fetcher, u16 tileMapAddr, u16 tileData, u8 tileOffset, u8 tileLine) {
    fetcher->state = ReadTileID;
    fetcher->ticks = 0;

    fetcher->tileIndex = 0;
    fetcher->tileLine = tileLine;
    fetcher->mapAddr = tileMapAddr;
    fetcher->addrMethod = tileData;
    fetcher->tileOffset = tileOffset;

    fetcher->tileLineLow = 0;
    fetcher->tileLineHigh = 0;
}

u16 read_tile_addr(fetcher_t* f) {
    u16 tile_addr;
    if (f->addrMethod == 0x8000) {
        // Unsigned mode (8000-8FFF)
        tile_addr = 0x8000 + (f->tileID * 16) + (f->tileLine * 2);
    } else {
        // Signed mode (9000-9FFF)
        int8_t signed_id = (int8_t)f->tileID;
        tile_addr = 0x9000 + (signed_id  * 16) + (f->tileLine * 2);
    }

    return tile_addr;
}

static u16 get_tile_map(ppu_t* p, fetcher_t* f) {
    const u8 x = ((*p->scx) / 8 + f->tileIndex) & 0x1f;
    return f->mapAddr + x;
}


void fetcher_tick(ppu_t* ppu, fetcher_t* fetcher) {
    fetcher->ticks++;
    if (fetcher->ticks < 2) {
        return;
    }

    fetcher->ticks = 0;

    switch (fetcher->state) {
    case ReadTileID: {
        fetcher->tileID = mmu_readU8(get_tile_map(ppu,fetcher));
        fetcher->tileOffset = (fetcher->tileOffset + 1) % 32;
        fetcher->tileIndex++;
        fetcher->state = ReadTileData0;
    }
    case ReadTileData0: {
        fetcher->tileLineLow = mmu_readU8(read_tile_addr(fetcher));
        fetcher->state = ReadTileData1;
    } break;
    case ReadTileData1: {
        fetcher->tileLineHigh = mmu_readU8(read_tile_addr(fetcher) + 1);
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

            fetcher->state = ReadTileID;
        }
        break;
    default:
        Log("Invalid fetcher state!");
        exit(EXIT_FAILURE);
    }
}
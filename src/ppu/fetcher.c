#include "ppu.h"
#include <fetcher.h>
#include <mmu.h>
#include <string.h>
#include <utils.h>

void fetcher_start(fetcher_t* fetcher) {
    fetcher->state = ReadTileID;
    fetcher->ticks = 0;

    fetcher->tileIndex = 0;

    fetcher->tileLineLow = 0;
    fetcher->tileLineHigh = 0;
}

u16 read_tile_addr(ppu_t *ppu, fetcher_t* f) {
    u16 tileData = GET_BIT(*ppu->lcdc, 4) ? 0x8000 : 0x8800;
    u8 tileLine;
    if (ppu->window_enabled) {
        u8 y = ppu->fetcher.window_line_counter;
        tileLine = y % 8;
    }else {
        u8 y = (*ppu->ly + *ppu->scy) & 0xff;
        tileLine = y % 8;
    }

    u16 tile_addr;
    if (tileData == 0x8000) {
        // Unsigned mode (8000-8FFF)
        tile_addr = 0x8000 + (f->tileID * 16) + (tileLine * 2);
    } else {
        // Signed mode (9000-9FFF)
        int8_t signed_id = (int8_t)f->tileID;
        tile_addr = 0x9000 + (signed_id * 16) + (tileLine * 2);
    }

    return tile_addr;
}

static u16 get_tile_map(ppu_t *ppu, fetcher_t *fetcher) {
    if (ppu->window_enabled) {
        const u16 bg_base = GET_BIT(*ppu->lcdc, 6) ? 0x9C00 : 0x9800;
        const u8 y = ppu->fetcher.window_line_counter;
        const u16 tileMapRow = bg_base + (y / 8) * 32;
        return tileMapRow + fetcher->tileIndex;
    }

    const u16 bg_base = GET_BIT(*ppu->lcdc, 3) ? 0x9C00 : 0x9800;
    const u8 x = ((*ppu->scx) / 8 + fetcher->tileIndex) & 0x1f;
    const u8 y = (*ppu->ly + *ppu->scy) & 0xff;
    const u16 tileMapRow = bg_base + (y / 8) * 32;
    return tileMapRow + x;
}

void fetcher_start_sprite_fetch(ppu_t* ppu, u8 sprite_index) {
    ppu->fetcher.spriteToFetch = &ppu->sprite_buffer.sprites[sprite_index];

    ppu->fetcher.paused_state = ppu->fetcher.state;
    ppu->fetcher.state = ReadSpriteID;
}

bool try_push(fetcher_t* fetcher, fifo_t* f) {
    if (f->size == 0) {
        uint8_t hi = fetcher->tileLineHigh;
        u8 lo = fetcher->tileLineLow;

        u8 tile_row[8];
        for (u8 i = 0; i < 8; i++) {
            u8 p = GET_BIT(hi, (7 - i)) << 1 | GET_BIT(lo, (7 - i));
            tile_row[i] = p;
        }

        for (int i = 0; i < 8; i++) {
            fifo_push(f, tile_row[i]);
        }
        return true;
    }

    return false;
};

void fetcher_tick(ppu_t* ppu, fetcher_t* fetcher) {
    fetcher->ticks++;
    if (fetcher->ticks < 2) {
        return;
    }

    fetcher->ticks = 0;

    switch (fetcher->state) {
    case ReadTileID: {
        fetcher->tileID = mmu_readU8(get_tile_map(ppu, fetcher));

        fetcher->tileIndex++;
        fetcher->state = ReadTileData0;
    } break;
    case ReadTileData0: {
        fetcher->tileLineLow = mmu_readU8(read_tile_addr(ppu, fetcher));
        fetcher->state = ReadTileData1;
    } break;
    case ReadTileData1: {
        fetcher->tileLineHigh = mmu_readU8(read_tile_addr(ppu, fetcher) + 1);
        fetcher->state = PushToFIFO;
    } break;

    case ReadSpriteID: {
        /*
         * Already fetched during oam scan, in ppu read_sprite(),
         * Kept this state here just to make it like the docs said and to consume the cycles.
         */
        fetcher->state = PushSpriteFIFO;

    } break;
    case ReadSpriteData0: {
        // u8 sprite_id = fetcher->spriteToFetch->tile_index;
        // u8 sprite_line = (*ppu->ly) - 16 + fetcher->spriteToFetch->y;
        // u16 tile_addr = 0x8000 + (sprite_id * 16) + (sprite_line * 2);
        //
        // fetcher->spriteLineLow = mmu_readU8(tile_addr);
        fetcher->state = ReadSpriteData1;
    } break;
    case ReadSpriteData1: {
        // u8 sprite_id = fetcher->spriteToFetch->tile_index;
        // u8 sprite_line = (*ppu->ly) - 16 + fetcher->spriteToFetch->y;
        // u16 tile_addr = 0x8000 + (sprite_id * 16) + (sprite_line * 2);
        //
        // fetcher->spriteLineHigh = mmu_readU8(tile_addr + 1);
        fetcher->state = PushSpriteFIFO;
    } break;
    case PushSpriteFIFO: {
        // if (fetcher->sprite_fifo.size == 0) {
        //     uint8_t hi = fetcher->spriteLineHigh;
        //     u8 lo = fetcher->spriteLineLow;
        //
        //     u8 tile_row[8];
        //     for (u8 i = 0; i < 8; i++) {
        //         u8 p = GET_BIT(hi, (7 - i)) << 1 | GET_BIT(lo, (7 - i));
        //         tile_row[i] = p;
        //     }
        //
        //     for (int i = 0; i < 8; i++) {
        //         fifo_push(&fetcher->sprite_fifo, tile_row[i]);
        //     }
        //
        // }
        fetcher->state = fetcher->paused_state;
    }break;
    case PushToFIFO:
        if (fetcher->bg_fifo.size == 0) {
            uint8_t hi = fetcher->tileLineHigh;
            u8 lo = fetcher->tileLineLow;

            u8 tile_row[8];
            for (u8 i = 0; i < 8; i++) {
                u8 p = GET_BIT(hi, (7 - i)) << 1 | GET_BIT(lo, (7 - i));
                tile_row[i] = p;
            }

            for (int i = 0; i < 8; i++) {
                fifo_push(&fetcher->bg_fifo, tile_row[i]);
            }

            fetcher->state = ReadTileID;
        }
        break;

    default:
        Log("Invalid fetcher state!");
        exit(EXIT_FAILURE);
    }
}

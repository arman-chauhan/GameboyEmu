#include "ppu.h"
#include "fetcher.h"
#include "interrupt.h"
#include "string.h"
#include "utils.h"

#include <assert.h>

typedef enum {
    STAT_SOURCE_LYC,
    STAT_SOURCE_OAM_SCAN,
    STAT_SOURCE_VBLANK,
    STAT_SOURCE_HBLANK,
} StatInterruptSource;

ppu_t* ppu_create(void) {
    ppu_t* ppu = malloc(sizeof(ppu_t));
    if (ppu == NULL) {
        Log("Failed to allocate ppu!");
        exit(EXIT_FAILURE);
    }
    return ppu;
}

void ppu_init(ppu_t* ppu, mmu_t* mmu) {
    ppu->lcdc = &mmu->addr[0xFF40];
    ppu->stat = &mmu->addr[STAT];
    ppu->scy = &mmu->addr[SCY];
    ppu->scx = &mmu->addr[SCX];
    ppu->ly = &mmu->addr[LY];
    ppu->lyc = &mmu->addr[LYC];
    ppu->dma = &mmu->addr[DMA];
    ppu->bgp = &mmu->addr[BGP];
    ppu->obp0 = &mmu->addr[OBP0];
    ppu->obp1 = &mmu->addr[OBP1];
    ppu->wy = &mmu->addr[WY];
    ppu->wx = &mmu->addr[WX];

    ppu->vram = mmu->vram;
    ppu->oam = mmu->oam;

    ppu->window_enabled = false;
    ppu->ticks = 0;
    ppu->x_pos = 0;

    ppu->state = PPU_MODE_OAM_SCAN;
}

static void eval_ly_lyc(ppu_t* ppu) {
    if ((*ppu->ly) == (*ppu->lyc)) {
        SET_BIT(ppu->stat, 2);
        SET_BIT(&ppu->stat_if, 6);
    } else {
        CLEAR_BIT(ppu->stat, 2);
        CLEAR_BIT(&ppu->stat_if, 6);
    }
}

void eval_stat(ppu_t* ppu) {
    eval_ly_lyc(ppu);

    const u8 mask = ppu->stat_ie & ppu->stat_if;
    if (ppu->old_mask == 0 && mask != 0) {
        RaiseInterrupt(INTERRUPT_STAT);
    }
    ppu->old_mask = mask;
}

static void update_ppu_state(ppu_t* ppu, enum PPUState state) {
    ppu->state = state;
    // Last two bits of lcdc denote current mode
    (*ppu->stat) = (*ppu->stat & 0b11111100) | state;

    ppu->stat_if &= 0b01000000;
    if (state == PPU_MODE_OAM_SCAN)
        ppu->stat_if |= 0b00100000;
    if (state == PPU_MODE_VBLANK)
        ppu->stat_if |= 0b00010000;
    if (state == PPU_MODE_HBLANK)
        ppu->stat_if |= 0b00001000;

    eval_stat(ppu);
}

/* Only return true if, fetcher is not already fetching the window. */
static bool should_start_window(ppu_t* ppu) {
    bool new_window_enable = false;
    if (GET_BIT(*ppu->lcdc, 5) && (ppu->x_pos + 7 >= *ppu->wx) && ((*ppu->ly) >= (*ppu->wy))) {
        new_window_enable = true;
        ppu->fetcher.had_window_pixel = true;
    }

    if (new_window_enable && !ppu->window_enabled) {
        ppu->window_enabled = true;
        return true;
    }

    if (!new_window_enable && ppu->window_enabled) {
        ppu->window_enabled = false;
    }

    return false;
}

static void increment_ly(ppu_t* ppu) {
    (*ppu->ly)++;
    eval_stat(ppu);
}

// Reads the specified sprite from the oam and returns struct sprite_t for it.
sprite_t read_sprite(ppu_t* ppu, u8 sprite_index) {
    sprite_t s = {.fetched = false};
    memcpy(&s, &ppu->oam[sprite_index * 4], 4);
    return s;
}

// Checks if a sprite is eligible to be put in the buffer.
bool check_sprite(sprite_t* sprite, u8 sprite_height, u8 ly) {
    if (sprite->x > 0 && (sprite->y <= ly + 16) && (ly + 16 < sprite->y + sprite_height)) {
        return true;
    }

    return false;
}

// Loads a new sprite to buffer, pointer by the oam_scan_index, if it is eligible.
void load_new_sprite(ppu_t* ppu) {
    if (ppu->sprite_buffer.count == 10) {
        return;
    }

    sprite_t new_sprite = read_sprite(ppu, ppu->oam_scan_index);
    u8 sprite_height = GET_BIT(*ppu->lcdc, 2) == 0 ? 8 : 16;
    if (check_sprite(&new_sprite, sprite_height, *ppu->ly)) {
        ppu->sprite_buffer.sprites[ppu->sprite_buffer.count] = new_sprite;
        ppu->sprite_buffer.sprites[ppu->sprite_buffer.count].fetched = false;
        ppu->sprite_buffer.count++;
    }

    ppu->oam_scan_index++;
}

u8 mix_pixels(ppu_t *ppu, u8 bg_pixel, u8 sp_pixel) {
   return sp_pixel;
}

void ppu_tick(ppu_t* ppu) {
    ppu->ticks++;

    switch (ppu->state) {
    case PPU_MODE_OAM_SCAN: {
        // Takes 2 cycles to check and load a new sprite.
        if (ppu->ticks % 2 == 0) {
            load_new_sprite(ppu);
        }

        // Initialize fetcher for background and change mode ot PIXEL TRANSFER
        if (ppu->ticks == 80) {
            ppu->x_pos = 0;
            fetcher_start(&ppu->fetcher);
            update_ppu_state(ppu, PPU_MODE_PIXEL_TRANSFER);
        }
    } break;
    case PPU_MODE_PIXEL_TRANSFER: {
        // Reinitialize the fetcher for a window fetch.
        if (should_start_window(ppu)) {
            fifo_clear(&ppu->fetcher.bg_fifo);
            fetcher_start(&ppu->fetcher);
        }

        fetcher_tick(ppu, &ppu->fetcher);


        // heres the fucking problem
        // if (GET_BIT(*ppu->lcdc, 1)) {
        //     if (ppu->fetcher.state == ReadSpriteData0 || ppu->fetcher.state == ReadSpriteData1 ||
        //         ppu->fetcher.state == ReadSpriteID)
        //         return;
        //
        //     for (int sprite_index = 0; sprite_index < ppu->sprite_buffer.count; sprite_index++) {
        //         if (ppu->sprite_buffer.sprites[sprite_index].fetched)
        //             continue;
        //
        //         if (ppu->sprite_buffer.sprites[sprite_index].x <= ppu->x_pos + 8) {
        //             fetcher_start_sprite_fetch(ppu, sprite_index);
        //             ppu->sprite_buffer.sprites[sprite_index].fetched = true;
        //             return;
        //         }
        //     }
        // }


        if (ppu->fetcher.bg_fifo.size > 0) {
            u8 pixel = fifo_pop(&ppu->fetcher.bg_fifo);
            pixel = (*ppu->bgp >> pixel * 2) & 0x3; // Pick color from palette
            ppu->pixel_data[*ppu->ly * 160 + ppu->x_pos] = pixel;

            if (GET_BIT(*ppu->lcdc, 0) == 0) {
                ppu->pixel_data[*ppu->ly * 160 + ppu->x_pos] = 0;
            }

            ppu->x_pos++;
        }

        if (ppu->x_pos >= 160) {
            ppu->sprite_buffer.count = 0;
            assert(ppu->ticks <= 456 && "cycle overflowed");
            fifo_clear(&ppu->fetcher.bg_fifo);
            fifo_clear(&ppu->fetcher.sprite_fifo);
            update_ppu_state(ppu, PPU_MODE_HBLANK);
        }
    } break;
    case PPU_MODE_HBLANK: {
        if (ppu->ticks >= 456) {
            ppu->ticks = 0;
            increment_ly(ppu);

            if (ppu->fetcher.had_window_pixel)
                ppu->fetcher.window_line_counter++;
            ppu->fetcher.had_window_pixel = false;

            if (*ppu->ly >= 144) {
                update_ppu_state(ppu, PPU_MODE_VBLANK);
                RaiseInterrupt(INTERRUPT_VBLANK);
            } else {
                ppu->oam_scan_index = 0;
                update_ppu_state(ppu, PPU_MODE_OAM_SCAN);
            }
        }
    } break;
    case PPU_MODE_VBLANK: {
        if (ppu->ticks != 456) {
            return;
        }

        increment_ly(ppu);
        ppu->ticks = 0;

        if (*ppu->ly >= 153) {
            (*ppu->ly) = 0;
            ppu->fetcher.window_line_counter = 0;
            update_ppu_state(ppu, PPU_MODE_OAM_SCAN);
        }
    } break;
    default:
        Log("Invalid ppu state!");
        exit(EXIT_FAILURE);
    }
}

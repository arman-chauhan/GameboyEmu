#include "fetcher.h"
#include "interrupt.h"
#include "ppu.h"
#include "string.h"
#include "utils.h"

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

    ppu->state = OAM_SCAN;
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
    if (state == OAM_SCAN) ppu->stat_if |= 0b00100000;
    if (state == VBLANK) ppu->stat_if |= 0b00010000;
    if (state == HBLANK) ppu->stat_if |= 0b00001000;

    eval_stat(ppu);
}


static void increment_ly(ppu_t* ppu) {
    (*ppu->ly)++;
    eval_stat(ppu);
}


void ppu_tick(ppu_t* ppu) {
    ppu->ticks++;

    switch (ppu->state)
    case OAM_SCAN: {
        if (ppu->ticks >= 80) {
            ppu->x_pos = 0;

            u16 bg_base = GET_BIT(*ppu->lcdc, 3) ? 0x9C00 : 0x9800;
            u8 y = (*ppu->ly + *ppu->scy) & 0xff;
            u8 tileLine = y % 8;
            u8 tileOffset = (*ppu->scx / 8);
            u16 tileMapRow = bg_base + (y / 8) * 32;
            u16 tileData = GET_BIT(*ppu->lcdc, 4) ? 0x8000 : 0x8800;

            fetcher_start(&ppu->fetcher, tileMapRow, tileData, tileOffset, tileLine);
            update_ppu_state(ppu, PIXEL_TRANSFER);
        }
        break;
    case PIXEL_TRANSFER:
        fetcher_tick(ppu, &ppu->fetcher);
        if (ppu->fetcher.fifo.size > 8) {
            u8 f = fifo_pop(&ppu->fetcher.fifo);
            f = (*ppu->bgp >> f * 2) & 0x3; // Pick color from palette
            ppu->pixel_data[*ppu->ly * 160 + ppu->x_pos] = f;
            ppu->x_pos++;
        }
        if (ppu->x_pos >= 160) {
            fifo_clear(&ppu->fetcher.fifo);
            update_ppu_state(ppu, HBLANK);
        }
        break;
    case HBLANK: {
        if (ppu->ticks >= 456) {
            increment_ly(ppu);
            ppu->ticks = 0;
            ppu->fetcher.window_line_counter += ppu->fetcher.had_window_pixel;

            if (*ppu->ly >= 144) {
                update_ppu_state(ppu, VBLANK);
                RaiseInterrupt(INTERRUPT_VBLANK);
            } else {
                update_ppu_state(ppu, OAM_SCAN);
            }
        }
    } break;
    case VBLANK: {
        if (ppu->ticks != 456) {
            return;
        }

        increment_ly(ppu);
        ppu->ticks = 0;

        if (*ppu->ly >= 153) {
            (*ppu->ly) = 0;
            update_ppu_state(ppu, OAM_SCAN);
        }
    } break;
    default:
        Log("Invalid ppu state!");
        exit(EXIT_FAILURE);
    }
}

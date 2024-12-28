#include <fetcher.h>
#include <ppu.h>
#include <renderer.h>
#include <unistd.h>
#include <utils.h>

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
}

void ppu_tick(ppu_t* ppu, u8 cycles) {
    for (u8 i = 0; i < cycles; i++) {
        ppu->ticks++;

        switch (ppu->state)
        case OAM_SCAN: {

            if (ppu->ticks == 80) {
                ppu->x_pos = 0;
                u8 tileLine = *ppu->ly % 8;
                u16 tileMapAddr = 0x9800 + ((*ppu->ly / 8) * 32);
                fetcher_start(&ppu->fetcher, tileMapAddr, tileLine);

                ppu->state = PIXEL_TRANSFER;
            }
            break;
        case PIXEL_TRANSFER:
            fetcher_tick(&ppu->fetcher);

            if (ppu->fetcher.fifo.size > 8) {
                // RenderPixel(fifo_pop(&ppu->fetcher.fifo));
                u8 f = fifo_pop(&ppu->fetcher.fifo);
                ppu->pixel_data[*ppu->ly * 160 + ppu->x_pos] = f;
                Write(f);
                ppu->x_pos++;
            }
            if (ppu->x_pos == 160) {
                // RendererHblank();
                HBlank();
                ppu->state = HBLANK;
            }
            break;
        case HBLANK:
            if (ppu->ticks == 456) {
                ppu->ticks = 0;
                (*ppu->ly)++;
                if (*ppu->ly == 144) {
                    // RendererVblank();
                    VBlank();

                    ppu->state = VBLANK;
                } else {
                    ppu->state = OAM_SCAN;
                }
            }
            break;
        case VBLANK:
            if (ppu->ticks == 456) {
                ppu->ticks = 0;
                (*ppu->ly)++;
                if (*ppu->ly == 153) {
                    *ppu->ly = 0;
                    ppu->state = OAM_SCAN;
                }
            }
            break;
        default:
            Log("Invalid ppu state!");
            exit(EXIT_FAILURE);
        }
    }
}

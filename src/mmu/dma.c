#include <dma.h>
#include <mmu.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>
typedef struct {
    bool active;
    uint8_t byte;
    uint8_t start;
    uint8_t start_delay;
} dma_contex;

dma_contex ctx = {
    .active = false,
};

void dma_start(uint8_t addr) {
    ctx.start = addr;
    ctx.byte = 0;
    ctx.active = true;
    ctx.start_delay = 2;

    uint16_t start = addr * 0x100;
    uint16_t oam_addr = 0xFE00;

    for (int i = 0; i < 160; i++) {
        uint8_t data = get_mmu_ctx()->addr[start + i];
        get_mmu_ctx()->addr[oam_addr + i] = data;
    }
    ctx.active = false;
}

void dma_tick(uint8_t cycles) {
    for (int i = 0; i < cycles; i++) {
        if (!ctx.active) {
            return;
        }

        if (ctx.start_delay) {
            ctx.start_delay--;
            return;
        }

        const uint8_t data = get_mmu_ctx()->addr[(ctx.start << 8) + ctx.byte];
        get_mmu_ctx()->addr[0xFE00 + ctx.byte] = data;

        ctx.byte++;
        ctx.active = ctx.byte < 0xA0;
    }
}

bool dma_is_active() { return ctx.active; }

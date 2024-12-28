#include <dma.h>
#include <mmu.h>
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
}

void dma_tick(uint8_t cycles) {
    for (int i = 0; i < cycles; i++) {
        if (!ctx.active) {
            return;
        }

        if(ctx.start_delay) {
            ctx.start_delay--;
            return;
        }

        const uint8_t data = mmu_readU8((ctx.start * 0x100) + ctx.byte);
        MMU_WriteU8(0xFE00 + ctx.byte, data);

        ctx.byte++;
        ctx.active = ctx.byte < 0xA0;

    }
}

bool dma_is_active() { return ctx.active; }

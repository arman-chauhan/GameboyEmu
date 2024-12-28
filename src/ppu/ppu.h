#ifndef PPU_H
#define PPU_H

#include <common.h>
#include <mmu.h>
#include <fetcher.h>

#define LCDC 0xFF40
#define STAT 0xFF41
#define SCY  0xFF42
#define SCX  0xFF43
#define LY   0xFF44
#define LYC  0xFF45
#define DMA  0xFF46
#define BGP  0xFF47
#define OBP0 0xFF48
#define OBP1 0xFF49
#define WY   0xFF4A
#define WX   0xFF4B

enum PPUState {
    HBLANK,
    VBLANK,
    OAM_SCAN,
    PIXEL_TRANSFER,
};


typedef struct pixel_processing_unit_t {
    uint8_t *lcdc;  // FF40
    uint8_t *stat;  // FF41
    uint8_t *scy;   // FF42
    uint8_t *scx;   // FF43
    uint8_t *ly;    // FF44
    uint8_t *lyc;   // FF45
    uint8_t *dma;   // FF46
    uint8_t *bgp;   // FF47
    uint8_t *obp0;  // FF48
    uint8_t *obp1;  // FF49
    uint8_t *wy;    // FF4A
    uint8_t *wx;    // FF4B

    uint8_t *vram;
    uint8_t *oam;

    uint16_t ticks;
    enum PPUState state;
    fetcher_t fetcher;
    uint8_t x_pos;
    uint8_t pixel_data[160 * 144];

    bool in_Window;
    bool window_enabled;

} ppu_t;



void ppu_tick(ppu_t* ppu, u8 cycles);
ppu_t* ppu_create(void);
void ppu_init(ppu_t* ppu, mmu_t* mmu);

#endif
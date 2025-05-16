#ifndef PPU_H
#define PPU_H

#include <common.h>
#include <fifo.h>
#include <mmu.h>

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

enum FetcherState {
    ReadTileID,
    ReadTileData0,
    ReadTileData1,
    PushToFIFO,
    ReadSpriteID,
    ReadSpriteFlag,
    ReadSpriteData0,
    ReadSpriteData1,
    PushSpriteFIFO,
};



typedef struct {
    u8 y;
    u8 x;
    u8 tile_index;
    u8 flags;

    bool fetched;
}sprite_t;

typedef struct {
    sprite_t sprites[10];
    u8 count;
}sprite_buffer_t;

typedef struct {
    enum FetcherState state;
    fifo_t bg_fifo;
    fifo_t sprite_fifo;
    u8 ticks;

    u16 tileIndex;
    u8 tileID;
    u8 tileLineLow;
    u8 tileLineHigh;
    u8 tileData;

    u8 spriteLineLow;
    u8 spriteLineHigh;
    u8 spriteData;

    sprite_t *spriteToFetch;
    enum FetcherState paused_state;

    bool had_window_pixel;
    u8 window_line_counter;
} fetcher_t;

enum PPUState {
    PPU_MODE_HBLANK,
    PPU_MODE_VBLANK,
    PPU_MODE_OAM_SCAN,
    PPU_MODE_PIXEL_TRANSFER,
};

typedef struct pixel_processing_unit_t {
    uint8_t* lcdc; // FF40
    uint8_t* stat; // FF41
    uint8_t* scy;  // FF42
    uint8_t* scx;  // FF43
    uint8_t* ly;   // FF44
    uint8_t* lyc;  // FF45
    uint8_t* dma;  // FF46
    uint8_t* bgp;  // FF47
    uint8_t* obp0; // FF48
    uint8_t* obp1; // FF49
    uint8_t* wy;   // FF4A
    uint8_t* wx;   // FF4B


    uint8_t* vram; // Reference to oam in mmu.
    uint8_t* oam; // Reference to oam in mmu.

    sprite_buffer_t sprite_buffer; // Buffer to store up to 10 sprites.
    u8 oam_scan_index; // Keeps track of which sprite to check in oam scan.

    uint16_t ticks;
    enum PPUState state;
    fetcher_t fetcher;
    uint8_t x_pos;
    uint8_t pixel_data[160 * 144];

    bool window_enabled;
    bool stat_interrupt;
    u8 stat_if;
    u8 stat_ie;
    u8 old_mask;
} ppu_t;

void ppu_tick(ppu_t* ppu);
ppu_t* ppu_create(void);
void ppu_init(ppu_t* ppu, mmu_t* mmu);
void eval_stat(ppu_t* ppu);

#endif

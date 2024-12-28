#include <raylib.h>
#include <renderer.h>
#include <unistd.h>
#include <utils.h>

#include "dma.h"

#define SCALE 4

#define TILE_LEN   8
#define ROW_COUNT  144
#define COL_COUNT  160
#define TILE_COUNT (ROW_COUNT * COL_COUNT)

void renderer_init() { InitWindow(COL_COUNT * SCALE, ROW_COUNT * SCALE, "Gameboy"); }

const Color colors[] = {WHITE, RED, DARKGRAY, BLACK};

void RenderFrame(GameBoyState* state, u8 frameBuffer[]) {
    BeginDrawing();
    ClearBackground(BLACK);

    for (int y = 0; y < ROW_COUNT; y++) {
        for (int x = 0; x < COL_COUNT; x++) {
            uint8_t color = frameBuffer[y * 160 + x];
            Color raylib_color = colors[color];
            DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, raylib_color);
        }
    }
    EndDrawing();

    if (WindowShouldClose())
        state->terminate = 1;
}

uint16_t addr = 0x8000;
void get_tiles(uint16_t tiles[TILE_COUNT][8]) {
    for (int tile_idx = 0; tile_idx < TILE_COUNT; tile_idx++) {
        for (int i = 0; i < TILE_LEN; i++) {
            const uint8_t hi = mmu_readU8(addr + tile_idx * 16 + i * 2 + 1);
            const uint8_t lo = mmu_readU8(addr + tile_idx * 16 + i * 2);

            for (int j = 0; j < 8; j++) {
                uint8_t p = GET_BIT(hi, j) << 1 | GET_BIT(lo, j);
                tiles[tile_idx][i] |= p << (14 - j * 2);
            }
        }
    }
}

void draw_vram_tiles(uint16_t tiles[TILE_COUNT][8]) {
    for (int i = 0; i < TILE_COUNT; i++) {
        const uint16_t screenX = (i % COL_COUNT) * 8 * SCALE;
        const uint16_t screenY = (i / COL_COUNT) * 8 * SCALE;

        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                const uint8_t colorIndex = (tiles[i][y] >> x * 2) & 0b11;
                DrawRectangle(screenX + x * SCALE, screenY + y * SCALE, SCALE, SCALE,
                              colors[colorIndex]);
            }
        }
    }
}

void renderVRAM() {
    uint16_t tiles[384][8] = {0};

    get_tiles(tiles);
    draw_vram_tiles(tiles);
}


// Render int the console
typedef struct {
    char* Palette[4];
} Console;

Console console = {{"\u2588", "\u2592", "\u2591", " "}};
Console* c = &console;
void Write(int colorIndex) { printf("%s", c->Palette[colorIndex]); }

void HBlank() { printf("\n"); }

void VBlank() { printf("\n === VBLANK ===\n"); }

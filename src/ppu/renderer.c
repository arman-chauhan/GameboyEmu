#include <raylib.h>
#include <renderer.h>
#include <unistd.h>
#include <utils.h>

#include "dma.h"

#define SCALE 4
#define PADDING 2  // Space around each tile

#define TILE_LEN   8
#define ROW_COUNT  144
#define COL_COUNT  160
#define TILE_COUNT (ROW_COUNT * COL_COUNT)

void renderer_init() {
    InitWindow(COL_COUNT * SCALE, ROW_COUNT * SCALE, "Gameboy"); // Gameboy window
    // InitWindow(16 * (8  * SCALE + PADDING)  , 24 * (8  * SCALE + PADDING), "Gameboy-debug"); // Debug window
    SetTargetFPS(60);
}

const Color colors[] = {
    {255, 255, 255, 255},  // White (0xFFFFFFFF)
    {170, 170, 170, 255},  // Light gray (0xFFAAAAAA)
    {85,  85,  85,  255},  // Dark gray (0xFF555555)
    {0,   0,   0,   255}   // Black (0xFF000000)
};

// const Color colors[] = {
//     {224, 248, 208, 255},
//     {136, 192, 112, 255},
//     {52, 104, 86, 255},
//     {8, 24, 32, 255},
// };
//
// const Color colors[] = {
//     RAYWHITE,
//     LIGHTGRAY,
//     DARKGRAY,
//     BLACK,
// };

void RenderFrame(GameBoyState* state, u8 frameBuffer[]) {

    ClearBackground(RED);

    for (int y = 0; y < ROW_COUNT; y++) {
        for (int x = 0; x < COL_COUNT; x++) {
            uint8_t color = frameBuffer[y * 160 + x];
            Color raylib_color = colors[color];
            DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, raylib_color);
        }
    }

}

uint16_t addr = 0x8000;
void get_tiles(uint16_t tiles[384][8]) {
    for (int tile_idx = 0; tile_idx < 384; tile_idx++) {
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


void draw_vram_tiles(uint16_t tiles[384][8]) {
    for (int i = 0; i < 384; i++) {
        // Calculate position with padding to separate tiles
        const uint16_t screenX = (i % 16) * ((8 * SCALE + PADDING));
        const uint16_t screenY = (i / 16) * ((8 * SCALE + PADDING));

        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                const uint8_t colorIndex = (tiles[i][y] >> (x * 2)) & 0b11;

                // Draw the tile pixels with space for padding
                DrawRectangle(screenX + x * SCALE, screenY + y * SCALE, SCALE, SCALE, colors[colorIndex]);
            }
        }
    }
}


void renderVRAM(GameBoyState* state) {
    uint16_t tiles[384][8] = {0};
    BeginDrawing();
    ClearBackground(BLACK);
    get_tiles(tiles);
    draw_vram_tiles(tiles);
    EndDrawing();

    if (WindowShouldClose())
        state->terminate = 1;
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

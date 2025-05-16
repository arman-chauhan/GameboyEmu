#include "joypad.h"
#include "raylib.h"

#include <cartridge.h>
#include <common.h>
#include <dma.h>
#include <emu.h>
#include <interrupt.h>
#include <renderer.h>
#include <string.h>
#include <timer.h>
#include <utils.h>

#define FPS        59.73
#define MAX_CYCLES 70224



void emu_runFrame(GameBoyState* state) {
    uint32_t cyclesThisFrame = 0;
    while (cyclesThisFrame < MAX_CYCLES) {
        handle_interrupts(state->cpu, state->mmu);

        const uint8_t cycles = cpu_step(state->cpu, state->mmu);
        for (int i = 0; i < cycles; i++) {
            ppu_tick(state->ppu);
        }
        timer_tick(cycles);
        cyclesThisFrame += cycles;
    }
}


void handle_input(GameBoyState* state) {
    u8 buttons = 0x0F;
    u8 directions = 0x0F;

    if (IsKeyDown(KEY_Z))         buttons &= ~BTN_A;
    if (IsKeyDown(KEY_X))         buttons &= ~BTN_B;
    if (IsKeyDown(KEY_BACKSPACE)) buttons &= ~BTN_SELECT;
    if (IsKeyDown(KEY_ENTER))     buttons &= ~BTN_START;

    if (IsKeyDown(KEY_RIGHT))     directions &= ~BTN_RIGHT;
    if (IsKeyDown(KEY_LEFT))      directions &= ~BTN_LEFT;
    if (IsKeyDown(KEY_UP))        directions &= ~BTN_UP;
    if (IsKeyDown(KEY_DOWN))      directions &= ~BTN_DOWN;

    state->joypad->buttons = buttons;
    state->joypad->directions = directions;
}

void emu_run(GameBoyState* state, char* path) {
    if (!read_cart(path, state->mmu)) {
        Log("Failed to load the cartridge: %s", path);
        exit(EXIT_FAILURE);
    };

    renderer_init();
    while (!state->terminate) {

        if (WindowShouldClose()) state->terminate = true;
        handle_input(state);
        emu_runFrame(state);
        BeginDrawing();
        RenderFrame(state, state->ppu->pixel_data);
        EndDrawing();
    }
    CloseWindow();
}

void emu_init(GameBoyState* state) {
    cpu_init(state->cpu);
    timer_init(state->mmu);
    ppu_init(state->ppu, state->mmu);
    joypad_init(state->joypad);
    state->mmu->gb = state;
}

GameBoyState* emu_create(void) {
    GameBoyState* state = malloc(sizeof(GameBoyState));
    if (state == NULL) {
        Log("Failed to allocated the gameboy state!");
        exit(EXIT_FAILURE);
    }

    state->terminate = false;
    state->cpu = cpu_create();
    state->mmu = mmu_create();
    state->ppu = ppu_create();

    emu_init(state);
    return state;
}

#ifndef GBC_H
#define GBC_H

#include "cpu.h"
#include "mmu.h"
#include "stdbool.h"
#include "ppu.h"
#include "joypad.h"

typedef  struct GameBoyState{
    cpu_t *cpu;
    mmu_t *mmu;
    ppu_t *ppu;
    joypad_t *joypad;
    bool terminate;
}GameBoyState;

GameBoyState* emu_create();
void emu_init(GameBoyState *state);
void emu_run(GameBoyState* state, char* path);

#endif

#include "mmu.h"

#include "ppu.h"
#include "timer.h"
#include "utils.h"
#include <dma.h>
#include <emu.h>
#include <joypad.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static mmu_t mmu;

mmu_t* mmu_create(void) { return &mmu; }

static uint8_t readROM(uint16_t addr) { return mmu.addr[addr]; }
static uint8_t readVRAM(uint16_t addr) { return mmu.addr[addr]; }
static uint8_t readExternalRAM(uint16_t addr) { return mmu.addr[addr]; }
static uint8_t readWRAM(uint16_t addr) { return mmu.addr[addr]; }
static uint8_t readOAM(uint16_t addr) { return mmu.addr[addr]; }
static uint8_t readHRAM(uint16_t addr) { return mmu.addr[addr]; }

static uint8_t readIOPorts(uint16_t addr) {
    if (addr == 0xFF00) {
        return joypad_read(mmu.gb->joypad);
    }
    return mmu.addr[addr];
}

uint8_t mmu_readU8(uint16_t addr) {
    if (addr <= 0x7FFF) {
        return readROM(addr);
    } else if (addr <= 0x9FFF) {
        return readVRAM(addr);
    } else if (addr <= 0xBFFF) {
        return readExternalRAM(addr);
    } else if (addr <= 0xDFFF) {
        return readWRAM(addr);
    } else if (addr <= 0xFDFF) {
        return readWRAM(addr - 0x2000); // Echo RAM
    } else if (addr <= 0xFE9F) {
        return dma_is_active() ? 0xFF : readOAM(addr);
    } else if (addr <= 0xFF7F) {
        return readIOPorts(addr);
    } else if (addr <= 0xFFFE) {
        return readHRAM(addr);
    } else if (addr == 0xFFFF) {
        return mmu.ie_reg;
    }
    Log("Invalid memory read at address: 0x%04X\n", addr);
    exit(EXIT_FAILURE);
}

int8_t mmu_readI8(uint16_t addr) { return (int8_t)mmu.addr[addr]; }

uint16_t mmu_readU16(uint16_t addr) { return (mmu_readU8(addr + 1) << 8) | mmu_readU8(addr); }

uint8_t MMU_ReadIO(uint8_t addr) {
    if (addr == 0x00) {
        return joypad_read(mmu.gb->joypad);
    }
    return mmu.io_regs[addr];
}

void MMU_WriteIO(uint8_t addr, uint8_t value) {
    if (addr == 0x44) {
        printf("Writes to LY register are ignored.\n");
        return;
    }

    if (addr == 0x04) {
        mmu.io_regs[addr] = 0;
        GetTimer()->divider_counter = 0;
        return;
    }

    if (addr == 0x00) {
        joypad_write(mmu.gb->joypad, value);
        return;
    }

    if (addr == 0x46 && !dma_is_active()) {
        dma_start(value);
    }

    mmu.io_regs[addr] = value;
}

void MMU_WriteU8(uint16_t addr, uint8_t value) {
    if (addr <= 0x7FFF)
        return;

    switch (addr) {
    case 0xFF00:
        joypad_write(mmu.gb->joypad, value);
        return;
    case 0xFF41:
        mmu.gb->ppu->stat_ie = value & 0b01111000;
        eval_stat(mmu.gb->ppu);
        break;
    case 0xFF44:
        Log("Writes to LY register are ignored.\n");
        return;
    case 0xFF45:
        eval_stat(mmu.gb->ppu);
        break;
    case 0xFF46:
        dma_start(value);
        break;
    }

    mmu.addr[addr] = value;
}

void MMU_WriteU16(uint16_t addr, uint16_t value) {
    MMU_WriteU8(addr, value & 0xFF);
    MMU_WriteU8(addr + 1, value >> 8);
}

mmu_t* get_mmu_ctx() { return &mmu; }
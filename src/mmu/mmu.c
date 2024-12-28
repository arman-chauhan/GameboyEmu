#include "mmu.h"

#include <dma.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "timer.h"
#include "utils.h"

static mmu_t ctx;

mmu_t* mmu_create(void) {
    // mmu_t* mmu = malloc(sizeof(mmu));
    // if (mmu == NULL) {
    //     Log("Failed to allocate the mmu!");
    //     exit(EXIT_FAILURE);
    // }
    return &ctx;
}
// void mmu_init(mmu_t* mmu) { return &ctx; }

uint8_t readROM(uint16_t addr) { return ctx.addr[addr]; }

uint8_t readVRAM(uint16_t addr) { return ctx.addr[addr]; }

uint8_t readExternalRAM(uint16_t addr) { return ctx.addr[addr]; }

uint8_t readWRAM(uint16_t addr) { return ctx.addr[addr]; }

uint8_t readOAM(uint16_t addr) { return ctx.addr[addr]; }

uint8_t readIOPorts(uint16_t addr) { return ctx.addr[addr]; }

uint8_t readHRAM(uint16_t addr) { return ctx.addr[addr]; }

uint8_t mmu_readU8(uint16_t addr) {
    if (addr <= 0x7FFF) {
        // ROM: 0x0000-0x7FFF
        return readROM(addr);
    } else if (addr >= 0x8000 && addr <= 0x9FFF) {
        // VRAM: 0x8000-0x9FFF
        return readVRAM(addr);
    } else if (addr >= 0xA000 && addr <= 0xBFFF) {
        // External RAM: 0xA000-0xBFFF
        return readExternalRAM(addr);
    } else if (addr >= 0xC000 && addr <= 0xDFFF) {
        // WRAM: 0xC000-0xDFFF
        return readWRAM(addr);
    } else if (addr >= 0xE000 && addr <= 0xFDFF) {
        // WRAM Echo: 0xE000-0xFDFF (mirrors 0xC000-0xDFFF)
        return readWRAM(addr - 0x2000);
    } else if (addr >= 0xFE00 && addr <= 0xFE9F) {
        // OAM: 0xFE00-0xFE9F
        return readOAM(addr);
    } else if (addr >= 0xFF00 && addr <= 0xFF7F) {
        // I/O Ports: 0xFF00-0xFF7F
        return readIOPorts(addr);
    } else if (addr >= 0xFF80 && addr <= 0xFFFE) {
        // HRAM: 0xFF80-0xFFFE
        return readHRAM(addr);
    } else if (addr == 0xFFFF) {
        // Interrupt Enable Register: 0xFFFF
        return ctx.ie_reg;
    } else {
        Log("Invalid memory read at address: 0x%04X\n", addr);
        exit(EXIT_FAILURE);
    }
}

int8_t mmu_readI8(uint16_t addr) { return (int8_t)ctx.addr[addr]; }

uint16_t mmu_readU16(const uint16_t addr) { return mmu_readU8(addr + 1) << 8 | mmu_readU8(addr); }

void MMU_WriteU8(const uint16_t addr, const uint8_t value) {
    if (addr == 0xFF44) {
        printf("Writes to LY register are ignored.");
        return;
    }
    ctx.addr[addr] = value;
}

void MMU_WriteU16(const uint16_t addr, const uint16_t value) {
    ctx.addr[addr] = (uint8_t)value & 0xff;
    ctx.addr[addr + 1] = (uint8_t)(value >> 8);
}

#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include <stdint.h>

#define MEM_SIZE          0x10000 // Total memory size (1 MB)
#define ROM_SIZE          0x8000  // Total rom size 32 KB, without banking
#define ROM_BANK_SIZE     0x4000  // 16 KB per ROM bank
#define ROM_NUM           2       // Number of ROM banks
#define VRAM_SIZE         0x2000  // 8 KB for Video RAM
#define EXTERNAL_RAM_SIZE 0x2000  // 8 KB for External RAM (SRAM)
#define WRAM_SIZE         0x2000  // 8 KB for Work RAM
#define ECHO_RAM_SIZE     0x1E00  // Echo RAM (7.25 KB)
#define OAM_SIZE          0x00A0  // 160 bytes for Object Attribute Memory (OAM)
#define UNUSED_SIZE       0x60    // 96 bytes of unused memory space
#define IO_REGS_SIZE      0x0080  // 128 bytes for I/O registers
#define HIGH_RAM_SIZE     0x007F  // 127 bytes for High RAM (HRAM)

typedef union memory_t {
    uint8_t addr[MEM_SIZE]; // Raw address access
    struct {
        uint8_t rom[ROM_NUM][ROM_BANK_SIZE]; // Cartridge ROM (multiple banks)
        uint8_t vram[VRAM_SIZE];             // Video RAM (VAM)
        uint8_t sram[EXTERNAL_RAM_SIZE];     // External RAM (SRAM)
        uint8_t wram[WRAM_SIZE];             // Work RAM (WRAM)
        uint8_t echo_ram[ECHO_RAM_SIZE];     // Echo RAM, mirror of work ram
        uint8_t oam[OAM_SIZE];               // Object Attribute Memory (OAM)
        uint8_t unused[UNUSED_SIZE];         // Unused memory space
        uint8_t io_regs[IO_REGS_SIZE];       // I/O registers
        uint8_t hram[HIGH_RAM_SIZE];         // High RAM (HRAM)
        uint8_t ie_reg;                      // Interrupt Enable Register, 0xFFFF
    };
} mmu_t;

mmu_t* MMU_Init(void);
uint8_t MMU_ReadIO(uint8_t addr);
uint8_t mmu_readU8(uint16_t addr);
int8_t mmu_readI8(uint16_t addr);
uint16_t mmu_readU16(uint16_t addr);
void MMU_WriteIO(uint8_t addr, uint8_t value);
void MMU_WriteU8(uint16_t addr, uint8_t value);
void MMU_WriteU16(uint16_t addr, uint16_t value);

mmu_t *mmu_create(void);
#endif

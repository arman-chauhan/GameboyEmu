#ifndef CPU_H
#define CPU_H

#include "common.h"
#include "mmu.h"

#define FLAG_Z 7
#define FLAG_N 6
#define FLAG_H 5
#define FLAG_C 4

typedef struct registers_t {
    union {
        struct {
            uint8_t F;  // Flag register
            uint8_t A;  // Accumulator register
        };

        uint16_t AF;
    };

    union {
        struct {
            uint8_t C;
            uint8_t B;
        };

        uint16_t BC;
    };

    union {
        struct {
            uint8_t E;
            uint8_t D;
        };

        uint16_t DE;
    };

    union {
        struct {
            uint8_t L;
            uint8_t H;
        };

        uint16_t HL;
    };

    uint16_t SP;  // stack pointer
    uint16_t PC;  // program counter
} regs_t;

typedef struct {
    regs_t regs;
    uint8_t IME;
    uint8_t IME_enable;
    uint8_t halt;
    uint8_t stop;
} cpu_t;

void cpu_init(cpu_t* cpu);
void cpu_destroy(cpu_t* cpu);
cpu_t* cpu_create(void);
void cpu_reset(cpu_t* cpu);
uint8_t cpu_step(cpu_t* cpu, mmu_t* mmu);

#endif

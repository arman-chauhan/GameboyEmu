#ifndef CPU_H
#define CPU_H

#include <stdint.h>

typedef struct _regs_t {
    union {
        struct {
            uint8_t F; // Flag register
            uint8_t A; // Accumulator register
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

    uint16_t SP; // stack pointer
    uint16_t PC; // program counter
} regs_t;

#define FLAG_Z 7
#define FLAG_N 6
#define FLAG_H 5
#define FLAG_C 4

typedef struct _cpu_t {
    regs_t regs;
} cpu_t;

cpu_t* cpu_create(void);
void cpu_reset(cpu_t* cpu);
uint8_t cpu_step(cpu_t* cpu);

#endif
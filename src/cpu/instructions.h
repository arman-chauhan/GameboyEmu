#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "cpu.h"

typedef enum {
    CONTEXT_REGS,
    CONTEXT_CPU,
    CONTEXT_MMU
} context_type_t;



typedef struct
{
    context_type_t type;
    union {
        void (*ctx_regs)(regs_t* regs);
        void (*ctx_cpu)(cpu_t* cpu);
        void (*ctx_mmu)(cpu_t* cpu, mmu_t* mmu);
    };
} context_t;


typedef struct
{
    context_t execute;
    char* mnemonic;
    uint8_t length;
    uint8_t cycle[2];
} instruction_t;


extern uint8_t pc_udated_needed;
extern uint8_t branched;
extern instruction_t instruction_table[256];
extern instruction_t instruction_prefixed_table[256];

void restart(const uint8_t addr, uint16_t* PC, uint16_t* SP);
void instructions_init(void);

#endif

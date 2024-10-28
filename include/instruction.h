#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "cpu.h"

typedef void (*ophandler)(void*);

typedef union {
    void (*ctx_regs)(regs_t* regs);
    void (*ctx_cpu)(cpu_t* cpu);
} context;

typedef struct _inst_t {
    context execute;
    char* mnemonic;
    uint8_t length;
    uint8_t cycle[2];
} inst_t;

#endif

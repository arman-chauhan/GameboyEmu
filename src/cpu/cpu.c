#include "cpu.h"
#include "debug.h"
#include "instructions.h"
#include "mmu.h"
#include "utils.h"
#include <stdlib.h>

cpu_t* cpu_create(void) {
    cpu_t* cpu = malloc(sizeof(cpu_t));
    if (cpu == NULL) {
        Log("Failed to allocate the cpu!");
        exit(EXIT_FAILURE);
    }
    return cpu;
}

void cpu_init(cpu_t* cpu) {
    cpu->regs.A = 0x01;
    cpu->regs.F = 0xB0;
    cpu->regs.B = 0;
    cpu->regs.C = 0x13;
    cpu->regs.D = 0;
    cpu->regs.E = 0xD8;
    cpu->regs.H = 0x01;
    cpu->regs.L = 0x4D;
    cpu->regs.SP = 0xFFFE;
    cpu->regs.PC = 0x100;
    cpu->halt = 0;
    cpu->stop = 0;
    cpu->IME = 0;
    cpu->IME_enable = 0;

    instructions_init();
}

void cpu_destroy(cpu_t* cpu) { free(cpu); }

uint8_t cpu_fetch(const cpu_t* cpu) { return mmu_readU8(cpu->regs.PC); }

#define SERIAL_DATA 0xFF01 // SB register
#define SERIAL_CTRL 0xFF02 // SC register

uint8_t halt_bug = 0;
uint8_t cpu_step(cpu_t* cpu, mmu_t* mmu) {
    if (cpu->halt) {
        if (!cpu->IME && ((mmu->addr[0xff0f] & 0x1f) & (mmu->addr[0xffff] & 0x1f))) {
            cpu->halt = 0;
            halt_bug = 1;
        }
        return 4;
    }

    const uint8_t opcode = cpu_fetch(cpu);

    instruction_t instr = instruction_table[opcode];
    if (opcode == 0xCB) { instr = instruction_prefixed_table[mmu_readU8(cpu->regs.PC + 1)]; }

    if (mmu->addr[SERIAL_CTRL] & 0x80) {
        uint8_t data = mmu->addr[SERIAL_DATA];
        printf("%c", data);
        mmu->addr[SERIAL_CTRL] &= ~0x80;
    }

    if (cpu->IME_enable) {
        cpu->IME = 1;
        cpu->IME_enable = 0;
    }

    pc_udated_needed = 1;

    // disassemble(cpu->regs.PC);
    switch (instr.execute.type) {
    case CONTEXT_REGS: instr.execute.ctx_regs(&cpu->regs); break;
    case CONTEXT_CPU: instr.execute.ctx_cpu(cpu); break;
    case CONTEXT_MMU: instr.execute.ctx_mmu(cpu, mmu); break;
    default: Log("Invalid instruction type"); exit(69);
    }

    uint8_t cycles;

    switch (branched) {
    case 0: cycles = instr.cycle[0]; break;
    case 1: cycles = instr.cycle[1]; break;
    default: Log("Inavlid branched variable value"); exit(69);
    }

    branched = 0;
    if (pc_udated_needed) { cpu->regs.PC += instr.length; }
    if (halt_bug) {
        cpu->regs.PC -= instr.length;
        halt_bug = 0;
    }
    return cycles;
}

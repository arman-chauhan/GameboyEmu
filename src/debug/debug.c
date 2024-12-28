#include "debug.h"

#include "cpu.h"
#include "instructions.h"
#include "utils.h"
int tickcounter = 0;
FILE *logFile;
int disassemble(const uint16_t PC) {
    const uint8_t opcode = mmu_readU8(PC);
    instruction_t instr = instruction_table[opcode];

    if (opcode == 0xCB) { instr = instruction_prefixed_table[mmu_readU8(PC + 1)]; }

    const uint8_t len = instr.length;
    printf("%04X %#04X ", PC, opcode);

    switch (len) {
    case 1: Log(instr.mnemonic); break;
    case 2: Log(instr.mnemonic, mmu_readU8(PC + 1)); break;
    case 3: Log(instr.mnemonic, (mmu_readU8(PC + 2) << 8) | mmu_readU8(PC + 1)); break;
    default: Log("Unknown instruction: %s, len: %u", instr.mnemonic, len); return 1;
    }

    return len;
}

void disassemble_cartridge(const uint16_t start_address, const size_t file_size) {
    uint16_t PC = start_address;
    while (PC < file_size) {
        const uint8_t instr_len = disassemble(PC);
        PC += instr_len;
    }
}


void Log_CPU_State(cpu_t* cpu) {
    fprintf(logFile, "A:%02X F:%02X B:%02X C:%02X D:%02X E:%02X H:%02X L:%02X SP:%04X PC:%04X ",
            cpu->regs.A, cpu->regs.F, cpu->regs.B, cpu->regs.C, cpu->regs.D, cpu->regs.E,
            cpu->regs.H, cpu->regs.L, cpu->regs.SP, cpu->regs.PC);

    uint8_t mem[4] = {mmu_readU8(cpu->regs.PC), mmu_readU8(cpu->regs.PC + 1),
                      mmu_readU8(cpu->regs.PC + 2), mmu_readU8(cpu->regs.PC + 3)};
    fprintf(logFile, "PCMEM:%02X,%02X,%02X,%02X\n", mem[0], mem[1], mem[2], mem[3]);

}

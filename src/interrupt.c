#include "interrupt.h"
#include "instructions.h"

#include <stdio.h>

const uint16_t interrupt_vectors[] = {
    0x40, // V-Blank Interrupt
    0x48, // LCD STAT Interrupt
    0x50, // Timer Interrupt
    0x58, // Serial Interrupt
    0x60  // Joypad Interrupt
};

void RaiseInterrupt(const uint8_t interrupt) {
    uint8_t if_reg = mmu_readU8(0xFF0F);
    if_reg |= (1 << interrupt);
    MMU_WriteU8(0xFF0F, if_reg);
}

void handle_interrupts(cpu_t* cpu, mmu_t* mmu) {
    const uint8_t ie_reg = MMU_ReadIO(0xff) & 0x1f;
    const uint8_t if_reg = MMU_ReadIO(0x0f) & 0x1f;
    const uint8_t possible_interrupts = ie_reg & if_reg;
    if (cpu->IME) { cpu->halt = 0; }
    if (possible_interrupts) { cpu->halt = 0; }

    if (possible_interrupts != 0 && cpu->IME) {
        for (uint8_t i = 0; i < 5; i++) {
            const uint8_t interrupt = (possible_interrupts >> i) & 0x01;

            if (interrupt) {
                cpu->IME = 0;
                cpu->halt = 0;
                mmu->io_regs[0x0f] &= ~(1 << i);

                restart(interrupt_vectors[i], &cpu->regs.PC, &cpu->regs.SP);
                return;
            }
        }
    }
}

#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "cpu.h"
#include "mmu.h"

#define VBLANK_ISR 0x40
#define LCD_ISR    0x48
#define TIMER_ISR  0x50
#define IO_ISR     0x58
#define JOYPAD_ISR 0x60

typedef enum {
    INTERRUPT_VBLANK,
    INTERRUPT_STAT,
    INTERRUPT_TIMER,
    INTERRUPT_IO,
    INTERRUPT_JOYPAD,
} Interrupt;

void handle_interrupts(cpu_t* cpu, mmu_t* mmu);
void RaiseInterrupt(uint8_t interrupt);
#endif
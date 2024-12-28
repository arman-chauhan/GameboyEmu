#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"
#include "mmu.h"

typedef struct {
    uint8_t* DIV;             // Divider register
    uint8_t* TIMA;            // Timer counter
    uint8_t* TMA;             // Timer modulo
    uint8_t* TAC;             // Timer control
    uint16_t divider_counter; // Internal counter for divider
    uint16_t timer_counter;   // Internal counter for timer
    uint8_t previous_result;  // Result of the AND operation (div_bit & timer_enable)
} timer_t;

void timer_tick(const uint8_t cycles);
void timer_init(mmu_t* mmu);
timer_t* GetTimer();

#endif
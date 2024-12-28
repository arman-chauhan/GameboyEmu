#include "timer.h"
#include "interrupt.h"
#include "mmu.h"
#include "utils.h"
#include <stdint.h>
#include <stdlib.h>

#define CPU_CLOCK_SPEED 4194304
#define TIMER_OVERFLOW  0xFF

static timer_t timer = {0};

// {4096, 262144, 65536, 16384}; timerfrequency in hertz
static const uint32_t TimerFrequency[4] = {1024, 16, 64, 256};
static const uint8_t DivBitPositions[4] = {9, 3, 5, 7};

void timer_init(mmu_t* mmu) {
    timer.DIV = &mmu->addr[0xFF04];
    timer.TIMA = &mmu->addr[0xFF05];
    timer.TMA = &mmu->addr[0xFF06];
    timer.TAC = &mmu->addr[0xFF07];
}

timer_t* GetTimer() { return &timer; }

uint8_t IsTimerEnabled() { return GET_BIT(*timer.TAC, 2); }

uint32_t GetTimerFrequency(uint8_t mode) { return TimerFrequency[mode]; }

uint8_t GetDividerBit(uint8_t mode) {
    return GET_BIT((*timer.DIV << 8) | (timer.divider_counter & 0xff), DivBitPositions[mode]);
}

static void UpdateDivider(uint8_t cycles) {
    timer.divider_counter += cycles;
    if (timer.divider_counter >= 256) {
        (*timer.DIV)++;
        timer.divider_counter -= 256;
    }
}

void timer_tick(uint8_t cycles) {
    UpdateDivider(cycles);

    const uint8_t mode = *timer.TAC & 0x03;
    const uint8_t timer_enabled = IsTimerEnabled();
    const uint8_t current_result = GetDividerBit(mode) & timer_enabled;

    timer.timer_counter += cycles;
    if (timer.previous_result == 1 && current_result == 0) {
        const uint32_t timer_freq = GetTimerFrequency(mode);
        const int32_t increments = timer.timer_counter / timer_freq;
        if (increments > 0) {
            for (uint32_t i = 0; i < increments; i++) {
                if (*timer.TIMA == 0xFF) {
                    *timer.TIMA = *timer.TMA;
                    // UpdateDivider(4);
                    RaiseInterrupt(2);
                } else {
                    (*timer.TIMA)++;
                }
            }

            timer.timer_counter %= timer_freq;
        }
    }

    timer.previous_result = current_result;
}

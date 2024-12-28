#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>
#include <stdio.h>
#include "cpu.h"

int disassemble(const uint16_t PC);
void disassemble_cartridge(const uint16_t start_address, const size_t file_size);
void Log_CPU_State(cpu_t* cpu);
extern FILE* logFile;
extern int tickcounter;
#endif


#ifndef  CARTRIDGE_H
#define CARTRIDGE_H

#include <common.h>
#include <mmu.h>

bool read_cart(char * path, mmu_t *mmu);


#endif
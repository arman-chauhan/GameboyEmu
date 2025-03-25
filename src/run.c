#include "mmu.h"
#include <common.h>
#include <emu.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Usage: ./Gameboy /path/to/rom>");
        exit(EXIT_FAILURE);
    }


    // GameBoyState *state = emu_create();
    ppu_t p;
    cpu_t c;

    /* gets the pointer to the mmu context used in mmu.c
     * please later refactor and make it so that mmu takes mmu pointer.
    */
    mmu_t *m = mmu_create();


    GameBoyState state = {
        .cpu = &c,
        .ppu = &p,
        .mmu = m,
    };

    emu_init(&state);
    emu_run(&state, argv[1]);
    return 1;
}

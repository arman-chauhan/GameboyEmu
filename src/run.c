#include <common.h>
#include <emu.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Usage: ./Gameboy /path/to/rom>");
        exit(EXIT_FAILURE);
    }

    GameBoyState *state = emu_create();
    emu_run(state, argv[1]);
    return 1;
}

#include <common.h>
#include <mmu.h>
#include <string.h>
#include <utils.h>

u8 nintendo_logo[] = {0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
                      0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
                      0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63,
                      0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

bool read_cart(char* path, mmu_t* mmu) {
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        Log("Failed to open cartridge: %s", path);
        return false;
    }

    fseek(file, 0, SEEK_END);
    const size_t file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    const size_t bytesRead = fread(mmu->rom, 1, file_size, file);
    if (bytesRead != file_size) {
        Log("Expected %zu bytes, but read %zu bytes", file_size, bytesRead);
        perror("Failed ");
        fclose(file);
        return false;
    }

    memcpy(&mmu->addr[0x0104], nintendo_logo, sizeof(nintendo_logo));
    uint8_t checksum = 0;
    for (uint16_t address = 0x0134; address <= 0x014C; address++) {
        checksum = checksum - mmu->addr[address] - 1;
    }

    mmu->addr[0x014D] = 231;
    // TODO: 014E-014F — Global checksum

    fclose(file);
    return true;
}


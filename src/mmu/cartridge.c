#include <common.h>
#include <mmu.h>
#include <utils.h>

bool read_cart(char *path, mmu_t *mmu) {
    FILE *file = fopen(path, "rb");
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
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

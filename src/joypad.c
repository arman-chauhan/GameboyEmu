#include <joypad.h>
#include <string.h>
#include <utils.h>

void joypad_init(joypad_t* joypad) {
    memset(joypad, 0, sizeof(joypad_t));
    joypad->joyp = 0xCF;
}

void joypad_write(joypad_t* joypad, u8 value) { joypad->joyp = (joypad->joyp & 0xCF) | (value & 0x30); }

u8 joypad_read(joypad_t* joypad) {
    u8 result = joypad->joyp & 0xF0;

    if (!GET_BIT(joypad->joyp, 4)) {
        result |= (0xF0 | joypad->directions);
    } else if (!GET_BIT(joypad->joyp, 5)) {
        result |= (0xF0 | joypad->buttons);
    }else {
        result |= 0x0F;
    }

    return result;
}

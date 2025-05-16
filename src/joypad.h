#ifndef JOYPAD_H
#define JOYPAD_H

#include <common.h>

#define BTN_A      (1 << 0)
#define BTN_B      (1 << 1)
#define BTN_SELECT (1 << 2)
#define BTN_START  (1 << 3)
#define BTN_RIGHT  (1 << 0)
#define BTN_LEFT   (1 << 1)
#define BTN_UP     (1 << 2)
#define BTN_DOWN   (1 << 3)

typedef struct {
    u8 joyp;
    u8 buttons;
    u8 directions;
} joypad_t;

void joypad_init(joypad_t *joypad);
void joypad_write(joypad_t *joypad, u8 value);
u8 joypad_read(joypad_t *joypad);

#endif

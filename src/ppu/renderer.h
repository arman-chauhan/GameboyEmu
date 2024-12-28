#ifndef RENDERER_H
#define RENDERER_H

#include "emu.h"

void renderer_init();
void RenderFrame(GameBoyState* state, u8 frameBuffer[]);

void HBlank();
void VBlank();
void Write(int colorIndex);

#endif
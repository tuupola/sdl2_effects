/*

MIT No Attribution

Copyright (c) 2020 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

SPDX-License-Identifier: MIT-0

*/

#include <stdint.h>
#include <math.h>
#include <hagl.h>

#include "rgbplasma.h"

static const uint8_t PLASMA_SPEED = 4;
static uint32_t step;

void rgbplasma_render()
{
    for (uint16_t x = 0; x < DISPLAY_WIDTH; x++) {
        for (uint16_t y = 0; y < DISPLAY_HEIGHT; y++) {
                float v1 = 128.0 + (128.0 * sin((x + step) / 32.0));
                float v2 = 128.0 + (128.0 * sin((y + step) / 24.0));
                float v3 = 128.0 + (128.0 * sin(sqrt((x * x) + y * y) / 12.0));
                float v = (v1 + v2 + v3) / 3;
                color_t color = hagl_color(v, 256 - v, 128);
                hagl_put_pixel(x, y, color);
        }
    }
}

void rgbplasma_animate()
{
    step = step + PLASMA_SPEED;
}

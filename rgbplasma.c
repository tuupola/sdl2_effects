/*

MIT No Attribution

Copyright (c) 2020-2022 Mika Tuupola

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
static uint32_t frame;

void rgbplasma_render(hagl_surface_t *surface)
{
    for (uint16_t x = 0; x < DISPLAY_WIDTH; x++) {
        for (uint16_t y = 0; y < DISPLAY_HEIGHT; y++) {
                uint8_t v1 = 128 + (128 * sin((x + frame) / 32.0));
                uint8_t v2 = 128 + (128 * sin((y + frame) / 24.0));
                uint8_t v3 = 128 + (128 * sin(sqrt((x * x) + y * y) / 12.0));
                uint8_t v = (v1 + v2 + v3) / 3;
                color_t color = hagl_color(surface, v, 255 - v, 128);
                hagl_put_pixel(surface, x, y, color);
        }
    }
}

void rgbplasma_animate()
{
    frame = frame + PLASMA_SPEED;
}

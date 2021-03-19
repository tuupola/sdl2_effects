/*

MIT No Attribution

Copyright (c) 2021 Mika Tuupola

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

Adapted from article by Inigo Quilez:
https://iquilezles.org/www/articles/deform/deform.htm

SPDX-License-Identifier: MIT-0

*/

#include <stdint.h>
#include <math.h>
#include <hagl.h>

#include "head.h"
#include "deform.h"

static const uint8_t SPEED = 1;
static uint32_t step;

static int8_t lut[DISPLAY_HEIGHT * DISPLAY_WIDTH * 2];

void deform_init()
{
    int k = 0;
    for (uint16_t j = 0; j < DISPLAY_HEIGHT; j++) {
        for (uint16_t i = 0; i < DISPLAY_WIDTH; i++) {

            const float x = -1.00f + 2.00f * (float)i / (float)DISPLAY_WIDTH;
            const float y = -1.00f + 2.00f * (float)j / (float)DISPLAY_HEIGHT;
            const float r = sqrtf(x * x + y * y);
            const float a = atan2f(y, x);

            float u = cosf(a) / r;
            float v = sinf(a) / r;

            // float u = 0.5 * a / M_PI;
            // float v = sin(7 * r);

            // float u = 0.02 * y + 0.03 * cos(a * 3) / r;
            // float v = 0.02 * x + 0.03 * sin(a * 3) / r;

            // float u = 1 / (r + 0.5 + 0.5 * sin(5 * a));
            // float v = a * 3 / M_PI;


            // float u = x * cos(2 * r) - y * sin(2 * r);
            // float v = y * cos(2 * r) + x * sin(2 * r);

            // float u = 0.3 / (r + 0.5 * x);
            // float v = 3 * a / M_PI;

            // float u = 0.1 * x / (0.11 + r * 0.5);
            // float v = 0.1 * y / (0.11 + r * 0.5);

            // float u = r * cos(a + r);
            // float v = r * sin(a + r);

            // float u = x / fabs(y);
            // float v = 1 / fabs(y);

            // float u = x;
            // float v = y;

            int8_t tx = ((int8_t)(HEAD_WIDTH * u)) % HEAD_WIDTH;
            int8_t ty = ((int8_t)(HEAD_HEIGHT * v)) % HEAD_HEIGHT;
            //printf("%f,%f -> %d,%d\n", u, v, tx, ty);

            lut[k++] = tx;
            lut[k++] = ty;
        }
    }
}

void deform_render()
{
    for (uint16_t y = 0; y < DISPLAY_HEIGHT; y++) {
        for (uint16_t x = 0; x < DISPLAY_WIDTH; x++) {

            int32_t o = DISPLAY_WIDTH * y + x;
            int16_t u = lut[2 * o + 0] + step;
            int16_t v = lut[2 * o + 1] + step;

            u = abs(u) % HEAD_WIDTH;
            v = abs(v) % HEAD_HEIGHT;

            color_t *color = (color_t*) (head + HEAD_WIDTH * sizeof(color_t) * v + sizeof(color_t) * u);
            hagl_put_pixel(x, y, *color);
        }
    }
}

void deform_animate()
{
    step = step + SPEED;
}

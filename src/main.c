/*

MIT No Attribution

Copyright (c) 2019-2020 Mika Tuupola

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
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include <hagl.h>
#include <hagl_hal.h>
#include <fps.h>

#include "metaballs.h"

const int NUM_BALLS = 10;
const int MIN_VELOCITY = 1;
const int MAX_VELOCITY = 5;
const int MIN_RADIUS = 10;
const int MAX_RADIUS = 20;

float current_fps = 0;

uint32_t fps_callback(uint32_t interval, void *param)
{
    printf("%.*f FPS\n", 1, *(float *)param);
    return interval;
}

int main()
{
    uint32_t fps_delay = 2000; /* 0.5 fps */

    bool quit = false;

    SDL_Event event;
    SDL_TimerID fps_id;

    srand(time(0));
    hagl_init();

    fps_id = SDL_AddTimer(fps_delay, fps_callback, &current_fps);

    /* Settings for metaballs. */
    struct settings settings;

    settings.num = NUM_BALLS;
    settings.velocity.min = MIN_VELOCITY;
    settings.velocity.max = MAX_VELOCITY;
    settings.radius.min = MIN_RADIUS;
    settings.radius.max = MAX_RADIUS;
    settings.min.x = 0;
    settings.min.y = 0;
    settings.max.x = DISPLAY_WIDTH - 1;
    settings.max.y = DISPLAY_HEIGHT - 1;

    settings.color[0] = hagl_color(0, 0, 0);
    settings.color[1] = hagl_color(255, 255, 255);
    settings.color[2] = hagl_color(0, 255, 0);

    metaballs_init(settings);

    printf("\nPress ESC to quit.\n\n");

    while (!quit) {
        hagl_clear_screen();

        metaballs_animate();
        metaballs_render();

        hagl_flush();
        current_fps = fps();

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (SDLK_ESCAPE ==event.key.keysym.sym) {
                    quit = true;
                } else {
                    hagl_clear_screen();
                }
            }
        }
    }

    SDL_RemoveTimer(fps_id);
    hagl_close();

    return 0;
}

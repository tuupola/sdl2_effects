/*

MIT No Attribution

Copyright (c) 2019-2022 Mika Tuupola

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
#include <aps.h>
#include <fps.h>

#include "metaballs.h"
#include "plasma.h"
#include "rgbplasma.h"
#include "rotozoom.h"
#include "deform.h"

static fps_instance_t fps;
static aps_instance_t bps;

typedef struct stats {
    float fps;
    float bps;
} stats_t;

static stats_t stats;

static const uint64_t MS_PER_FRAME_100_FPS = 1000 / 100;

uint32_t stats_callback(uint32_t interval, void *param)
{
    stats_t *data = (stats_t *)param;
    printf("%.*f fps / %.*f kBps\n", 1, data->fps, 1, data->bps / 1000);

    return interval;
}

int main()
{
    uint32_t stats_delay = 2000; /* 0.5 fps */
    uint8_t effect = 3;
    size_t bytes = 0;
    bool quit = false;

    SDL_Event event;
    SDL_TimerID fps_id;

    srand(time(0));
    hagl_backend_t *display = hagl_init();

    fps_id = SDL_AddTimer(stats_delay, stats_callback, &stats);

    printf("\nPress space for next demo.\n");
    printf("Press ESC to quit.\n\n");

    fps_init(&fps);
    aps_init(&bps);

    while (!quit) {

        uint32_t start = SDL_GetTicks();

        switch(effect) {
        case 0:
            rgbplasma_animate();
            rgbplasma_render(display);
            break;
        case 1:
            metaballs_animate();
            metaballs_render(display);
            break;
        case 2:
            plasma_animate();
            plasma_render(display);
            break;
        case 3:
            rotozoom_animate();
            rotozoom_render(display);
            break;
        case 4:
            deform_animate();
            deform_render(display);
            break;
        }

        bytes = hagl_flush(display);

        uint32_t end = SDL_GetTicks();
        int32_t delay = MS_PER_FRAME_100_FPS - (end - start);

        if (delay > 0) {
            SDL_Delay(delay);
        }

        stats.bps = aps_update(&bps, bytes);
        stats.fps = fps_update(&fps);

        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                if (SDLK_ESCAPE ==event.key.keysym.sym) {
                    quit = true;
                } else {

                    hagl_clear(display);

                    switch(effect) {
                    case 0:
                        //rgbplasma_close();
                        break;
                    case 1:
                        //metaballs_close();
                        break;
                    case 2:
                        plasma_close();
                        break;
                    case 3:
                        //rotozoom_close();
                        break;
                    case 4:
                        deform_close();
                        break;
                    }

                    effect = (effect + 1) % 5;

                    switch(effect) {
                    case 0:
                        //rgbplasma_init();
                        break;
                    case 1:
                        metaballs_init();
                        break;
                    case 2:
                        plasma_init(display);
                        break;
                    case 3:
                        rotozoom_init();
                        break;
                    case 4:
                        deform_init();
                        break;
                    }

                    fps_reset(&fps);
                    aps_reset(&bps);

                }
            }
        }
    }

    SDL_RemoveTimer(fps_id);
    hagl_close(display);

    return 0;
}

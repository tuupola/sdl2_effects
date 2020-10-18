## Old schoold demo effects

Created to test the [HAGL graphics library](https://github.com/tuupola/hagl). You need [SDL2](https://www.libsdl.org/) to run the demos.

![2nd Reality](https://appelsiini.net/img/2020/hagl_rotozoom.png)

```
$ brew install sdl2 # macOs
$ sudo apt-get install libsdl2-dev # Debian based distros
```

```
$ git clone git@github.com:tuupola/sdl2_effects.git --recursive
$ cd sdl2_effects
$ make clean && make
$ ./demo
```

## Run on ESP32

HAGL is hardware agnostic. You can run the demos also [ESP32 based boards](https://github.com/tuupola/esp_effects).


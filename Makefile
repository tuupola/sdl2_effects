CC = gcc
CFLAGS = -Wall -Ilib/hagl/include -Ilib/hagl_sdl2 -DNO_MENUCONFIG
LDFLAGS = -lm
SDLFLAGS = $(shell sdl2-config --libs --cflags)

src = $(wildcard *.c) \
      $(wildcard lib/hagl/src/*.c) \
      $(wildcard lib/hagl_sdl2/hagl_hal.c)

obj = $(src:.c=.o)

demo: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)


.PHONY: clean
clean:
	rm -f $(obj) demo

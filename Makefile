CC = gcc
CFLAGS = -Wall -Icomponents/hagl/include -Icomponents/hagl_sdl2 -DNO_MENUCONFIG
LDFLAGS = -lm
SDLFLAGS = $(shell sdl2-config --libs --cflags)

src = $(wildcard *.c) \
      $(wildcard components/hagl/src/*.c) \
      $(wildcard components/hagl_sdl2/hagl_hal.c)

obj = $(src:.c=.o)

demo: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)


.PHONY: clean
clean:
	rm -f $(obj) demo

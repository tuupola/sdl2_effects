CC = gcc
CFLAGS = -Wall -Iinclude -Icomponents/hagl/include -Icomponents/hagl_sdl2 -Icomponents/libfixmath/libfixmath -DNO_MENUCONFIG
SDLFLAGS = $(shell sdl2-config --libs --cflags)

src = $(wildcard src/*.c) \
      $(wildcard components/hagl/*.c) \
      $(wildcard components/hagl_sdl2/hagl_hal.c) \
      $(wildcard components/libfixmath/libfixmath/*.c)

obj = $(src:.c=.o)

demo: $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)


.PHONY: clean
clean:
	rm -f $(obj) demo

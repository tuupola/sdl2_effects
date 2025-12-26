CC = gcc
CFLAGS = -Wall -Iexternal/hagl/include -Iexternal/hagl_sdl2
LDFLAGS = -lm
SDLFLAGS = $(shell sdl2-config --libs --cflags)

src = $(wildcard *.c) \
      $(wildcard external/hagl/src/*.c) \
      $(wildcard external/hagl_sdl2/hagl_hal.c)

obj = $(src:.c=.o)

TARGET = demo

all: $(TARGET)

clean:
	rm -f $(obj) $(TARGET)

$(TARGET): $(obj)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

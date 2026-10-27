CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=c11 -Iinclude
TARGET  = linkedlist
SRCS    = src/main.c src/list.c src/io.c
OBJS    = $(SRCS:src/%.c=build/%.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

build/%.o: src/%.c include/list.h include/io.h
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build $(TARGET)

.PHONY: clean
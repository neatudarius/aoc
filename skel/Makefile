# Copyright 2020 Darius Neatu (neatudarius@gmail.com)

CC = g++
CFLAGS = -std=c++2a -Wall -Wextra -O0 -I../../skel
LDFLAGS = -lm -lfmt -lpthread

SRCS = $(sort $(wildcard *.cpp))
TARGETS = $(patsubst %.cpp,%,$(SRCS))
TARGET = $(src:.c=)

# build all targets
all: $(TARGETS)

# general rule for building a target
%: %.cpp
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# run a single target
run: $(TARGET)
	./$(TARGET)

# clean all related target files
clean:
	rm -f *.o $(TARGETS)

# pack directory
pack:
	zip $(ZIP).zip *.c *.h Makefile README

.PHONY: pack clean

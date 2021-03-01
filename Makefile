CC := gcc
CFLAGS := -Wall 
OBJS := list.o

all: test

test: $(OBJS) test.c
list.o: list.h

.PHONY: clean

clean:
	rm -f $(OBJS) test

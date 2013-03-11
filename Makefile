all: program/app



HEADERS = $(wildcard *.h)
CFLAGS = -g -Wall
CDEF= -DEMUL
CC = gcc

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(CDEF)

program/app: lib/emulator.o  program/main.o lib/platform.o lib/timers.o lib/util.o
	$(CC) $+ -Wall -o $@

clean:
	rm -f *.o
	rm -f program/app

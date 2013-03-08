all: blinker



HEADERS = $(wildcard *.h)
CFLAGS = -g -Wall
CDEF= -DEMUL
CC = gcc

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ $(CDEF)

blinker: emulator.o  main.o ../socket.o ../lib/platform.o ../lib/timers.o ../util.o
	$(CC) $+ -Wall -o $@

clean:
	rm -f *.o
	rm -f blinker

all: debugger


HEADERS = $(wildcard *.h)
CFLAGS = -g -Wall
CC = gcc

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


debugger: debugger.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f debugger

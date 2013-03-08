all: socket_server



HEADERS = $(wildcard *.h)
CFLAGS = -g -Wall
CC = gcc

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

socket_server: main.o ../socket.o
	$(CC) $+ -Wall -o $@

clean:
	rm -f *.o
	rm -f socket_server

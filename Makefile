all: socket_test_server debugger/client


OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))
HEADERS = $(wildcard *.h)
CFLAGS = -g -Wall
CC = gcc

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

socket_test_server: $(OBJECTS)
	$(CC) $(OBJECTS) -Wall -o $@

debugger/client: debugger/client.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f socket_test_server
	rm -f debugger/client

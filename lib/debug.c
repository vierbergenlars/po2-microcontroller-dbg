#include "socket.h"
#include <stdio.h> // printf();

unsigned int debug_socket;

void debug_register_socket(unsigned int sock) {
	debug_socket = sock;
}

void debug_write(char data[]) {
	if(debug_socket)
		socket_write(debug_socket, data);
	else
		printf("DEBUG: %s", data);
}

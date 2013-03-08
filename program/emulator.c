#include "../socket.h"
#include "main.h"
#include <string.h> // strcmp(), strlen(), strcpy(), itoa()
#include <stdio.h> // printf()
#include <stdlib.h> //atoi()
#include <unistd.h> // sleep(), usleep()
#include "../lib/platform.h"
#include "../util.h"
#include "../lib/debug.h"

int started = 0;
void handler(char in[100], char out[100]) {

	if(strncmp(in, "set", 3) == 0) {

		char set_pin_id[2];
		substring(4,5,in, set_pin_id, sizeof set_pin_id);
		int pin_num = atoi(set_pin_id);


		char set_pin_val[2];
		substring(6,7, in, set_pin_val, sizeof set_pin_val);
		int pin_val = atoi(set_pin_val);
		
		printf(out, "pin %d: %d");
		setData(pin_num, pin_val);
		
	}
	else if(strncmp(in, "get", 3) == 0) {
		if(strncmp(in, "get all", 7) == 0) {
			int i;
			for(i =1; i <=7; i++) {
				int pin_val = getData(i);
				char bit[100];
				sprintf(bit, "pin %d: %d\n", i, pin_val);
				strcat(out, bit);
			}
		}
		else {
			char get_pin_id[2];
			substring(4,5, in, get_pin_id, sizeof get_pin_id);

			int pin_num = atoi(get_pin_id);

			int pin_val = getData(pin_num);

			sprintf(out, "pin %d: %d", pin_num, pin_val);
		}

		
	}
	else if(strncmp(in, "cont", 4) == 0) {
		if(!started) {
			init();
			started = 1;
		}
		printf("----[Main]----");
		loop();
		printf("----[End]-----");

	}
	else if(strcmp(in, "restart") == 0) {
		init();
	}
	else {
		sprintf(out, "Commands: restart, cont [runs], set <pin> <val>, get <pin>"); 
	}
}

int main() {
	// Inits the socket controller
	unsigned int ctl_sock = socket_init("socket");
	unsigned int client_sock = socket_wait_client(ctl_sock);
	
	debug_register_socket(client_sock);
	socket_loop(client_sock, handler);
	socket_close(ctl_sock);
	return 0;
}

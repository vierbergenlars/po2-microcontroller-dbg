/*
 * Copyright (c) 2013 Lars Vierbergen
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#include "main.h"
#include <string.h> // strcmp(), strlen(), strcpy(), itoa()
#include <stdio.h> // printf()
#include <stdlib.h> //atoi()
#include "../lib/platform.h"
#include "../lib/util.h"

int started = 0;
void handler(char in[100]) {

	if(strncmp(in, "set", 3) == 0) {

		char set_pin_id[2];
		substring(4,5,in, set_pin_id, sizeof set_pin_id);
		int pin_num = atoi(set_pin_id);


		char set_pin_val[2];
		substring(6,7, in, set_pin_val, sizeof set_pin_val);
		int pin_val = atoi(set_pin_val);
		
		setData(pin_num, pin_val);
		
	}
	else if(strncmp(in, "get", 3) == 0) {
		if(strncmp(in, "get all", 7) == 0) {
			int i;
			for(i =1; i <=7; i++) {
				int pin_val = getData(i);
				printf("pin %d: %d\n", i, pin_val);
			}
		}
		else {
			char get_pin_id[2];
			substring(4,5, in, get_pin_id, sizeof get_pin_id);

			int pin_num = atoi(get_pin_id);

			int pin_val = getData(pin_num);

			printf("pin %d: %d", pin_num, pin_val);
		}

		
	}
	else if(strncmp(in, "gio", 3) == 0) {
		if(strncmp(in, "gio all", 7) == 0) {
			int i;
			for(i =1; i <=7; i++) {
				int pin_val = getInOut(i);
				printf("io %d: %d\n", i, pin_val);
			}
		}
		else {
			char get_pin_id[2];
			substring(4,5, in, get_pin_id, sizeof get_pin_id);

			int pin_num = atoi(get_pin_id);

			int pin_val = getInOut(pin_num);

			printf("io %d: %d", pin_num, pin_val);
		}
	}
	else if(strncmp(in, "cont", 4) == 0) {
		if(!started) {
			init();
			started = 1;
		}
		printf("----[Loop]----\n");
		loop();
		printf("----[End]----\n");


	}
	else if(strncmp(in, "restart",7) == 0) {
		printf("----[Restart]----\n");
		init();
		printf("----[End]----\n");

	}
	else {
		printf("Commands: restart, cont [runs], set <pin> <val>, get <pin>, gio <pin>"); 
	}
	printf("done\n");
}

int main() {
	char in[100];
	printf("----[Init]---\n");
	init();
	printf("----[REPL init]----\n");
	while(1) {
		printf(">");
		fgets(in, 100, stdin);
		handler(in);
		fflush(stdout);
	}
	return 0;
}

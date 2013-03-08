/*
 * timers.c
 *
 * Copyright (C) 2013 - Lars Vierbergen
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <unistd.h> // usleep()

void Delay1TCY() {
	usleep(1);
};

void Delay10TCYx(unsigned char unit) {
	while(unit > 0) {
		for(int i = 0; i < 10; i++) {
			Delay1TCY();
		}
		unit--;
	}
};

void Delay100TCYx(unsigned char unit) {
	for(int i = 0; i < 10; i++) {
		Delay10TCYx(unit);
	}
};

void Delay1KTCYx(unsigned char unit) {
	for(int i = 0; i < 10; i++) {
		Delay100TCYx(unit);
	}
};

void Delay10KTCYx(unsigned char unit) {
	for(int i = 0; i < 10; i++) {
		Delay1KTCYx(unit);
	}
};
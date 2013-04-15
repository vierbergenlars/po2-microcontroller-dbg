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


// Used libraries
#include "timers.h" // Just to get the timer functions
#include "platform.h"
#include <unistd.h> // sleep(), usleep()
#include <stdio.h> // printf()




// Define data (DataIn, DataOut) and in/out (InOut) registers
int DataOut1; 
int InOut1;
int DataOut2;
int InOut2;
int DataOut3;
int InOut3;
int DataOut4;
int InOut4;
int DataOut5;
int InOut5;
int DataOut6;
int InOut6;
int DataOut7;
int InOut7;


/*
 * Sets the in/out setting of the given pin.
 *
 * pin should be a number between 1 and 7, inOut should be 0 (output) or 1 (input).
 * Other values are considered to be 1.
 */
void setInOut(int pin, int inOut) {
	printf("io %d: %d\n", pin, inOut);
	fflush(stdout);
	inOut = (inOut != 0);
	switch(pin) {
		case 1:
			InOut1 = inOut;
			break;
		case 2:
			InOut2 = inOut;
			break;
		case 3:
			InOut3 = inOut;
			break;
		case 4:
			InOut4 = inOut;
			break;
		case 5:
			InOut5 = inOut;
			break;
		case 6:
			InOut6 = inOut;
			break;
		case 7:
			InOut7 = inOut;
			break;
	}	
}

/*
 * Gets the in/out setting of the given pin.
 *
 * pin should be a number between 1 and 7. The result is 0 (output) or 1 (input).
 */
int getInOut(int pin) {
	int inOut;
	switch(pin) {
		case 1:
			inOut = InOut1;
			break;
		case 2:
			inOut = InOut2;
			break;
		case 3:
			inOut = InOut3;
			break;
		case 4:
			inOut = InOut4;
			break;
		case 5:
			inOut = InOut5;
			break;
		case 6:
			inOut = InOut6;
			break;
		case 7:
			inOut = InOut7;
			break;
	}
	return inOut;
}

/*
 * Sets the data of the given pin.
 *
 * pin should be a number between 1 and 7, data should be 0 or 1.
 * Other values are considered to be 1. Values are only visible at
 * the controller pins if the corresponding InOut register is set
 * to 0.
 */
void setData(int pin, int data) {
	printf("pin %d: %d\n", pin, data);
	fflush(stdout);
	data =  (data != 0);
	switch(pin) {
		case 1:
			DataOut1 = data;
			break;
		case 2:
			DataOut2 = data;
			break;
		case 3:
			DataOut3 = data;
			break;
		case 4:
			DataOut4 = data;
			break;
		case 5:
			DataOut5 = data;
			break;
		case 6:
			DataOut6 = data;
			break;
		case 7:
			DataOut7 = data;
			break;
	}	
}

/*
 * Gets the data of the given pin.
 *
 * pin should be a number between 1 and 7. When the corresponding
 * InOut register is set to 0 (output), the data written by the user
 * is returned. When it is set to 1 (input), the electrical data read
 * by the pin is returned.
 */
int getData(int pin) {
	int data;
		switch(pin) {
			case 1:
				data = DataOut1;
				break;
			case 2:
				data = DataOut2;
				break;
			case 3:
				data = DataOut3;
				break;
			case 4:
				data = DataOut4;
				break;
			case 5:
				data = DataOut5;
				break;
			case 6:
				data = DataOut6;
				break;
			case 7:
				data = DataOut7;
				break;
		}
	return data;
}

/*
 * Starts the timer.
 * (is a no-op)
 */
void startTimer() {

}

/*
 * Waits until nbMs miliseconds have passed since the last call to startTimer().
 */
void waitForTimerMs(unsigned int nbMs) {
	unsigned int nbSecs;
	unsigned int nbMsecs;

	nbSecs = nbMs/1000;
	nbMsecs = nbMs%1000;

	sleep(nbSecs);
	usleep(1000*nbMsecs);
}

/*
 * Waits until nbUs microseconds have passed since the last call to startTimer().
 */
void waitForTimerUs(unsigned int nbUs) {
	usleep(nbUs);
}

/*
 * Reads the x-direction acceleration from the accelerometer.
 */
int readXacceleration() {
	return 0;
}

/*
 * Reads the y-direction acceleration from the accelerometer.
 */
int readYacceleration() {
	return 0;
}

/*
 * Reads the z-direction acceleration from the accelerometer.
 */
int readZacceleration() {
	return 0;
}

/*
 * Contains all initialization code.
 */
void platformInit() {
	int i;
	for (i = 1; i <= 7; ++i) {
		setInOut(i,0);
		setData(i,0);
	}
	acceleroInit();
	timerInit();

}

/*
 * Contains the initialization for the accelerometer.
 * (is a no-op)
 */
void acceleroInit() {
}

/*
 * Contains the initialization for the timer.
 * (is a no-op)
 */
void timerInit() {
}

/*
 * Reads the byte at the given address from the accelerometer.
 */
unsigned char accReadByte(unsigned char address) {
	return 0;
}

/*
 * Writes the given data byte at the given address to the accelerometer.
 * (is a no-op)
 */
void accWriteByte(unsigned char address, unsigned char data) {
}

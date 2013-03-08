// This file contains all code available for students to control the P&O2 platform.
// More information can be found in the workbook.

// Used libraries
//#include <p18f4550.h>
//#include <delays.h>
//#include <spi.h>
#include "timers.h" // Just to get the eimer functions
//#include <timers.h>
#include "platform.h"
#include <unistd.h> // sleep(), usleep()
#include <stdio.h> // printf()
#include "debug.h"


// Some general configurations
/*#pragma config FOSC = HSPLL_HS // use crystal oscillator
#pragma config PLLDIV = 3
#pragma config CPUDIV = OSC3_PLL4
#pragma config WDT = OFF //disable watch dog timer*/

// Define data (DataIn, DataOut) and in/out (InOut) registers
int DataOut1; //LATAbits.LATA0 // A0 -> 1
int DataIn1; // PORTAbits.RA0
int InOut1; //  TRISAbits.TRISA0
int DataOut2; //LATAbits.LATA1 // A1 -> 2
int DataIn2; // PORTAbits.RA1
int InOut2; //  TRISAbits.TRISA1
int DataOut3; //LATAbits.LATA2 // A2 -> 3
int DataIn3; // PORTAbits.RA2
int InOut3; //  TRISAbits.TRISA2
int DataOut4; //LATAbits.LATA3 // A3 -> 4
int DataIn4; // PORTAbits.RA3
int InOut4; //  TRISAbits.TRISA3
int DataOut5; //LATAbits.LATA4 // A4 -> 5
int DataIn5; // PORTAbits.RA4
int InOut5; //  TRISAbits.TRISA4
int DataOut6; //LATAbits.LATA5 // A5 -> 6
int DataIn6; // PORTAbits.RA5
int InOut6; //  TRISAbits.TRISA5
int DataOut7; //LATEbits.LATE1 // E1 -> 7
int DataIn7; // PORTEbits.RE1
int InOut7; //  TRISEbits.TRISE1


/*
 * Sets the in/out setting of the given pin.
 *
 * pin should be a number between 1 and 7, inOut should be 0 (output) or 1 (input).
 * Other values are considered to be 1.
 */
void setInOut(int pin, int inOut) {
	char debug[50];
	snprintf(debug, sizeof debug, "io %d: %d\n", pin, data);
	debug_write(debug);
	//printf("setInOut: pin %d to %d\n", pin, inOut); 
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
	//printf("getInOut: pin %d is %d\n", pin, inOut); 
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
	printf("setData: pin %d to %d\n", pin, data);
	char debug[50];
	snprintf(debug, sizeof debug, "pin %d: %d\n", pin, data);
	debug_write(debug);

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
	if (getInOut(pin) == 0) {
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
	}
	else {
		switch(pin) {
			case 1:
				data = DataIn1;
				break;
			case 2:
				data = DataIn2;
				break;
			case 3:
				data = DataIn3;
				break;
			case 4:
				data = DataIn4;
				break;
			case 5:
				data = DataIn5;
				break;
			case 6:
				data = DataIn6;
				break;
			case 7:
				data = DataIn7;
				break;
		}
	}

	printf("getData: pin %d is %d\n", pin, data); 
	return data;
}

/*
 * Starts the timer.
 */
void startTimer() {
	//WriteTimer0(0);
	//WriteTimer1(0);
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
 */;
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
	// solving floating pin-issues of not soldered connector
	/*PORTBbits.RB2 = 1;
	TRISBbits.TRISB2 = 1;
	PORTBbits.RB4 = 1;
	TRISBbits.TRISB4 = 1;
	PORTBbits.RB5 = 1;
	TRISBbits.TRISB5 = 1;*/
	acceleroInit();
	timerInit();

}

/*
 * Contains the initialization for the accelerometer.
 */
void acceleroInit() {
	/*ADCON1 = 0b00001111;
	TRISBbits.TRISB0 = 1;
	TRISCbits.TRISC7 = 0;
	TRISBbits.TRISB1 = 0;
	OpenSPI(SPI_FOSC_16, MODE_00, SMPEND);
	TRISCbits.TRISC6 = 0;
	accWriteByte(0b00100000,0b11000111);
	accWriteByte(0b00100001,0b11000000);
	accWriteByte(0b00100010,0b00000000);*/
}

/*
 * Contains the initialization for the timer.
 */
void timerInit() {
	//OpenTimer0(TIMER_INT_OFF & T0_16BIT & T0_SOURCE_INT & T0_PS_1_256);
	//OpenTimer1(TIMER_INT_OFF & T1_16BIT_RW & T1_SOURCE_INT & T1_PS_1_1 & T1_OSC1EN_OFF & T1_SYNC_EXT_OFF);
}

/*
 * Reads the byte at the given address from the accelerometer.
 */
unsigned char accReadByte(unsigned char address) {
	/*unsigned char var;
	LATCbits.LATC6 = 0;
	WriteSPI(address+0b10000000);
	var = ReadSPI();
	LATCbits.LATC6 = 1;
	return var;*/
	return 0;
}

/*
 * Writes the given data byte at the given address to the accelerometer.
 */
void accWriteByte(unsigned char address, unsigned char data) {
	/*LATCbits.LATC6 = 0;
	WriteSPI(address);
	WriteSPI(data);
	LATCbits.LATC6 = 1;*/
}

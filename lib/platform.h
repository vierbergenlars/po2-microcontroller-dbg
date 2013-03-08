// This file contains all method definitions available for students to control the P&O2 platform.
// More information can be found in the workbook.

#ifndef PLATFORM
#define PLATFORM

// Methods for the students
void setInOut(int pin, int inOut);
int getInOut(int pin);
void setData(int pin, int data);
int getData(int pin);
void startTimer(void);
void waitForTimerMs(unsigned int nbMs);
void waitForTimerUs(unsigned int nbUs);
int readXacceleration(void);
int readYacceleration(void);
int readZacceleration(void);

// Auxiliary methods
void platformInit(void);
void acceleroInit(void);
void timerInit(void);
unsigned char accReadByte(unsigned char address);
void accWriteByte(unsigned char address, unsigned char data);

#endif
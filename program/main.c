#ifdef EMUL
#include "../lib/platform.h"	// includes all libraries you can use	
#else
#include "platform.h"
#endif

// @vars start
int i;
// @vars end

void loop() {
// @loop start
waitForTimerMs(1000);
startTimer();
for(i = 1; i <= 7; ++i) {
	setData(i, 1-getData(i));
}
// @loop end
}

void init() {
// @init start
int i;
platformInit();
for(i = 1; i <= 7; ++i) {
	setInOut(i, 0);
	setData(i, i%2);
}
startTimer();
// @init end
}

# P&O 2 microcontroller debugger

## Installation

Requirements:

 * linux (any flavor will do), [Ubuntu](http://www.ubuntu.com)
 * [nodejs](http://nodejs.org)
 * npm (comes with nodejs)
 * make: `apt-get install make`
 * gcc: `apt-get install gcc`

1. Clone this repository `git clone git://github.com/vierbergenlars/po2-microcontroller-debugger.git` or [get a tarball](https://github.com/vierbergenlars/po2-microcontroller-debugger/tarball/master)
2. Open gui/
3. Run `npm install`

## Usage

1. Start the IDE. (run ide)
2. Click edit, write your program
3. Once ready, click compile. Your program will be compiled and run
4. The debugger opens
    * Continue: to run the next iteration of the loop. (Check run to automatically run the loop)
    * Restart: to rerun the initialisation code.
    * Terminate: Stop the program. **Do this before compiling the code again**
    * Kill: If the program is stuck (infinite loop etc). This will terminate the program immediately

5. Once everything works, copy-paste the code in the edit screen to the project in PICkit
6. Use exit to stop the IDE **(make sure the program is terminated in the debugger before clicking this)**
7. ??
8. Profit!


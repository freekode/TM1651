/**
 * Demo for the the Battery Display by Catalex
 * Hardware: Battery Display *1
 * Board:  Arduino UNO R3
 * IDE:	  Arduino-1.0
 * Function:  The Battery Display blinks once per second.
 * Store: http://www.aliexpress.com/store/1199788 http://www.dx.com/
 * Modified record:
 * Autor: 	Detlef Giessmann Germany
 * Mail:	mydiyp@web.de
 * Demo for the new 7 LED Battery-Display 2017
 * IDE:  	Arduino-1.6.5
 * Typ.: 	OPEN-SMART CX10*4RY68  4Color
 * Date: 	01.05.2017
 */
#include "TM1651.h"

// pins definitions for TM1651 and can be changed to other ports
#define CLK 3
#define DIO 2

TM1651 batteryDisplay(CLK, DIO);

void charging() {
  for (uint8_t level = 0; level < 8; level++) {
    batteryDisplay.displayLevel(level);
    delay(500);
  }
}

void setup() {
  batteryDisplay.init();

  // BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  batteryDisplay.set(BRIGHTEST);

  // light the frame of the battery display
  batteryDisplay.frame(true);
}

void loop() { charging(); }

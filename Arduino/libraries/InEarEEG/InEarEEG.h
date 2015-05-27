#ifndef _____InEarEEG__
#define _____InEarEEG__

#include <Arduino.h>
//#include <SPI.h>

enum state_e {
  INIT,
  ENABLE_OSC,
	RESET_1,
	RESET_2,
	PRE_CONFIG,
	CONFIG,
	START_SAMP,
	MAIN
};

byte xfer(byte);



#endif
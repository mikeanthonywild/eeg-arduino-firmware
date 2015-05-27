#include "InEarEEG.h" 
#include "EEGDefinitions.h"
#include <SPI.h>

state_e state = INIT;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);
}

void loop() {
  state = next_state(state);
  
}



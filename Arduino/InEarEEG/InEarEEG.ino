#include "InEarEEG.h" 

state_e state = INIT;

void setup() {
  Serial.begin(115200);
}

void loop() {
  state = next_state(state);
  
}



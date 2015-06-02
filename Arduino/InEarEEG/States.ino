state_e next_state(state_e current_state) {
  Serial.println(current_state);
  switch (current_state) {
    case INIT:
      return do_state_init();
    case ENABLE_OSC:
      return do_state_enable_osc();
    case RESET_1:
      return do_state_reset_1();
    case RESET_2:
      return do_state_reset_2();
    case PRE_CONFIG:
      return do_state_pre_config();
    case CONFIG:
      return do_state_config();
    case START_SAMP:
      return do_state_start_samp();
    case MAIN:
      return do_state_main();
    default:
      return current_state;
  }
}


state_e do_state_init(void) {
  // Do something interesting...
  return ENABLE_OSC;
}

state_e do_state_enable_osc(void) {
  delay(0.021); //Wait for Oscillator to wake up (Page 5 Reference ADS1299)
  return RESET_1;
}

state_e do_state_reset_1(void) {
  digitalWrite(ADS_RST, HIGH); 
  delay(1000); //Wait for it to stabilize
  return RESET_2;
}

state_e do_state_reset_2(void) {
  digitalWrite(ADS_RST, LOW);
  delay(150); //Page 4 ADS1299 Datasheet
  digitalWrite(ADS_RST, HIGH);
  delay(150);
  digitalWrite(ADS_CS, LOW);
  return PRE_CONFIG;
}

state_e do_state_pre_config(void) {
  xfer (_SDATAC);
  delay(0.03); 
  return CONFIG;
}


state_e do_state_config(void) {
  // Do something interesting...
  return START_SAMP;
}

state_e do_state_start_samp(void) {
  xfer(_RDATAC);
  delay(0.03);
  xfer(_START);
  return MAIN;
}

state_e do_state_main(void) {
  // Do something interesting...
  return MAIN;
}

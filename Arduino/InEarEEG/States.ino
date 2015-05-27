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
  // Do something interesting...
  return RESET_1;
}

state_e do_state_reset_1(void) {
  // Do something interesting...
  return RESET_2;
}

state_e do_state_reset_2(void) {
  // Do something interesting...
  return PRE_CONFIG;
}

state_e do_state_pre_config(void) {
  // Do something interesting...
  return CONFIG;
}


state_e do_state_config(void) {
  // Do something interesting...
  return START_SAMP;
}

state_e do_state_start_samp(void) {
  // Do something interesting...
  return MAIN;
}

state_e do_state_main(void) {
  // Do something interesting...
  return MAIN;
}




#include "InEarEEG.h"


byte xfer(byte _data) {
  cli();
    SPDR = _data;
    while (!(SPSR & _BV(SPIF)));
  sei();
    return SPDR;
}

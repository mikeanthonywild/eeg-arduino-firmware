#include <SPI.h>
 
char buf [100];
volatile byte pos;
volatile boolean process_it;
 
void setup (void)
{
  Serial.begin (115200);   // debugging
  while(!Serial.available()){} //wait for char
 
  // have to send on master in, *slave out*
  pinMode(MISO, OUTPUT);
  //pinMode(3, OUTPUT); //debug
  
  // turn on SPI in slave mode
  SPCR |= _BV(SPE);
  
  // get ready for an interrupt 
  pos = 0;   // buffer empty
  process_it = false;
 
 
  // now turn on interrupts
  SPI.attachInterrupt();
  //digitalWrite(3, HIGH); //debug
}  // end of setup
 
void software_Reset()
// Restarts program from beginning but 
// does not reset the peripherals and registers
{
  asm volatile ("  jmp 0");  
} 
 
// SPI interrupt routine
ISR (SPI_STC_vect)
{
  //Serial.println("oi");
  byte c = SPDR;  // grab byte from SPI Data Register
  
  // add to buffer if room
  buf [pos++] = c;
  
  // example: newline means time to process buffer
  if (pos > 0)
    process_it = true;  
    // end of room available
}  // end of interrupt routine SPI_STC_vect
 
// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (process_it)
    {
    buf [pos] = 0;  
    Serial.print (buf);
    pos = 0;
    process_it = false;
    }  // end of flag set
    while(Serial.read() == 's'){
   //   digitalWrite(3, LOW);
      delay(1);
      while(Serial.read() != 's'){
      software_Reset();
    }
  }
}  // end of loop

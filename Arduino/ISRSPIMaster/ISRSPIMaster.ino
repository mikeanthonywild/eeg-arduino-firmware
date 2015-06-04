#include <SPI.h>

void setup (void)
{

  digitalWrite(SS, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin ();

  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
}  // end of setup


void loop (void)
{

  char c;

  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10

  // send test string
  for (const char * p = "Hello, dfghfdgdfsgdsgsdfg world!\n" ; c = *p; p++)
    SPI.transfer (c);

  // disable Slave Select
  digitalWrite(SS, HIGH);

  delay (1000);  // 1 seconds delay 
}  // end of loop

/*
void loop (void)
{
  
  int c = random(16777216);
  byte f = (byte)c;
  c = c >> 8;
  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 10
  
  SPI.transfer (f);

  f = (byte)c;
  c = c >> 8;

  SPI.transfer (f);

  
  f = (byte)c;
 
  SPI.transfer (f);


  char m = 'm';
  
  SPI.transfer (m);

  // disable Slave Select
  digitalWrite(SS, HIGH);

  delay (8); 
} */

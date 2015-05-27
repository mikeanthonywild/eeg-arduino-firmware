

#include "LIS3DH.h"

void LIS3DH::initialize(byte g){ 
	byte setting =  g | 0x08; 			  	// mask the g range for REG4    
  pinMode(LIS3DH_SS,OUTPUT); digitalWrite(LIS3DH_SS,HIGH);
  pinMode(LIS3DH_DRDY,INPUT);   // setup dataReady interupt from accelerometer
  LIS3DH_write(TMP_CFG_REG, 0x00);  // DISable ADC inputs, enable temperature sensor
  LIS3DH_write(CTRL_REG1, 0x08);    // disable accel, low power mode
  LIS3DH_write(CTRL_REG2, 0x00);    // don't use the high pass filter
  LIS3DH_write(CTRL_REG3, 0x00);    // no interrupts yet
  LIS3DH_write(CTRL_REG4, setting);   // set scale to g, high resolution
  LIS3DH_write(CTRL_REG5, 0x00);    // no boot, no fifo
  LIS3DH_write(CTRL_REG6, 0x00);
  LIS3DH_write(REFERENCE, 0x00);
  DRDYpinValue = lastDRDYpinValue = digitalRead(LIS3DH_DRDY);  // take a reading to seed these variables
}
  
void LIS3DH::enable_accel(byte Hz){    // ADD ABILITY TO SET FREQUENCY & RESOLUTION
  for(int i=0; i<3; i++){
    axisData[i] = 0;            // clear the axisData array so we don't get any stale news
  }
  byte setting = Hz | 0x07;						// mask the desired frequency
  LIS3DH_write(CTRL_REG1, setting);   // set freq and enable all axis in normal mode
  LIS3DH_write(CTRL_REG3, 0x10);      // enable DRDY1 on INT1 (tied to Arduino pin3, LIS3DH_DRDY)
}

void LIS3DH::disable_accel(){
  LIS3DH_write(CTRL_REG1, 0x08);      // power down, low power mode
  LIS3DH_write(CTRL_REG3, 0x00);      // disable DRDY1 on INT1
}

byte LIS3DH::getDeviceID(){
  return LIS3DH_read(0x0F);
}

boolean LIS3DH::LIS3DH_DataReady(){
  boolean r = false;
  DRDYpinValue = digitalRead(LIS3DH_DRDY);  // take a look at LIS3DH_DRDY pin
  if(DRDYpinValue != lastDRDYpinValue){     // if the value has changed since last looking
    if(DRDYpinValue == HIGH){               // see if this is the rising edge
      r = true;                             // if so, there is fresh data!
    }
    lastDRDYpinValue = DRDYpinValue;        // keep track of the changing pin
  }
  return r;
}

boolean LIS3DH::LIS3DH_DataAvailable(){
	boolean x = false;
  if((LIS3DH_read(STATUS_REG2) & 0x08) > 0) x = true;  // read STATUS_REG
  return x;
}

void LIS3DH::writeLIS3DHdata(void){
	for(int i=0; i<3; i++){
	  Serial.write(highByte(axisData[i]));	// write 16 bit axis data MSB first
	  Serial.write(lowByte(axisData[i]));
	  axisData[i] = 0;
	}
}

byte LIS3DH::LIS3DH_read(byte reg){
	reg |= READ_REG;                    // add the READ_REG bit
	csLow();                            // take spi
	SPI.transfer(reg);                  // send reg to read
	byte inByte = SPI.transfer(0x00);   // retrieve data
	csHigh();                           // release spi
	return inByte;  
}

void LIS3DH::LIS3DH_write(byte reg, byte value){
	csLow();                  // take spi
	SPI.transfer(reg);        // send reg to write
	SPI.transfer(value);      // write value
	csHigh();                 // release spi
}

int LIS3DH::LIS3DH_read16(byte reg){    // use for reading axis data. 
	int inData;  
	reg |= READ_REG | READ_MULTI;   // add the READ_REG and READ_MULTI bits
	csLow();	                // take spi
	SPI.transfer(reg);              // send reg to start reading from
	inData = SPI.transfer(0x00) | (SPI.transfer(0x00) << 8);  // get the data and arrange it
	csHigh();                       // release spi
	return inData;
}

int LIS3DH::LIS3DH_readAxis(byte reg){
  byte Lbyte = LIS3DH_read(reg);
  byte Hbyte = LIS3DH_read(reg+1);
  int inData = Hbyte;
  inData <<= 8;
  inData |= Lbyte;
  return inData;
}

int LIS3DH::getX(){
	return LIS3DH_readAxis(OUT_X_L);
}

int LIS3DH::getY(){
	return LIS3DH_readAxis(OUT_Y_L);
}

int LIS3DH::getZ(){
	return LIS3DH_readAxis(OUT_Z_L);
}

int LIS3DH::getX16(){
	return LIS3DH_read16(OUT_X_L);
}

int LIS3DH::getY16(){
	return LIS3DH_read16(OUT_Y_L);
}

int LIS3DH::getZ16(){
	return LIS3DH_read16(OUT_Z_L);
}

void LIS3DH::LIS3DH_updateAxisData(){
	axisData[0] = getX();
  axisData[1] = getY();
  axisData[2] = getZ();
}

void LIS3DH::readAllRegs(){
  
	byte inByte;

	for (int i = STATUS_REG_AUX; i <= WHO_AM_I; i++){
		inByte = LIS3DH_read(i);
		Serial.print(F("0x0"));Serial.print(i,HEX);
		Serial.print(F("\t"));Serial.println(inByte,HEX);
		delay(20);
	}
	Serial.println();

	for (int i = TMP_CFG_REG; i <= INT1_DURATION; i++){
		inByte = LIS3DH_read(i);
		Serial.print(F("0x"));Serial.print(i,HEX);
		Serial.print(F("\t"));Serial.println(inByte,HEX);
		delay(20);
	}
	Serial.println();

	for (int i = CLICK_CFG; i <= TIME_WINDOW; i++){
		inByte = LIS3DH_read(i);
		Serial.print(F("0x"));Serial.print(i,HEX);
		Serial.print(F("\t"));Serial.println(inByte,HEX);
		delay(20);
	}
	
}

void LIS3DH::csLow(void)
{
	SPI.setDataMode(SPI_MODE3);    // switch modes
	digitalWrite(LIS3DH_SS, LOW);  // drop Slave Select
}

void LIS3DH::csHigh(void)
{
	digitalWrite(LIS3DH_SS, HIGH);  // raise select
	SPI.setDataMode(SPI_MODE0);
}

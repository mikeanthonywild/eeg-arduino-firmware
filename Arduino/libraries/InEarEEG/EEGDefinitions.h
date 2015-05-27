#ifndef _EEGDefinitions_h	// add _8_
#define _EEGDefinitions_h

//PIN CONNECTIONS 
#define ADS_DRDY (8)
#define ADS_RST (9) //IMPORTANT: replace witht he actual pin
#define SCK_MHZ (4)
#define ADS_CS (10) //IMPORTANT: replace with actual pin ADS chip select (Always down)

//ADS1299 SPI Command Definition Byte Assignments
#define _WAKEUP 0x02 // Wake-up from standby mode
#define _STANDBY 0x04 // Enter Standby mode
#define _RESET 0x06 // Reset the device registers to default
#define _START 0x08 // Start and restart (synchronize) conversions
#define _STOP 0x0A // Stop conversion
#define _RDATAC 0x10 // Enable Read Data Continuous mode (default mode at power-up)
#define _SDATAC 0x11 // Stop Read Data Continuous mode
#define _RDATA 0x12 // Read data by command; supports multiple read back

#endif
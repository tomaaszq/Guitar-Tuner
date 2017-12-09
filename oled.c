#include <soc.h>
#include <csl_gpio.h>
#include <csl_i2c.h>

#include "common.h"

#define ROW_UPPER (1)
#define ROW_LOWER (2)

static CSL_Status sendOLED(Uint16 cmd_dat, Uint16 data, Uint16 data2, int len);
static CSL_Status sendLetter(Uint16 character);
static CSL_Status clearOLED(int row);

CSL_GpioObj GpioObj;
GPIO_Handle hGpio;

// not implemented characters are shown as "?"
const Uint16 alphanum[][4] = {
  {0x00, 0x00, 0x00, 0x00},   // <space> 
  {0x06, 0x59, 0x01, 0x02},   // !  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // "  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // #  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // $  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // %  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // &  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // '  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // (  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // )  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // *  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // +  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // ,  (not implemented)
  {0x08, 0x08, 0x08, 0x08},   // -
  {0x00, 0x60, 0x60, 0x00},   // .
  {0x06, 0x59, 0x01, 0x02},   // /  (not implemented)
  {0x3E, 0x45, 0x49, 0x3E},   // 0
  {0x00, 0x40, 0x7F, 0x42},   // 1  
  {0x46, 0x49, 0x51, 0x62},   // 2  
  {0x36, 0x49, 0x49, 0x22},   // 3  
  {0x08, 0x7C, 0x08, 0x0F},   // 4  
  {0x31, 0x49, 0x49, 0x27},   // 5
  {0x32, 0x49, 0x49, 0x3E},   // 6  
  {0x03, 0x05, 0x79, 0x01},   // 7  
  {0x36, 0x49, 0x49, 0x36},   // 8  
  {0x3E, 0x49, 0x49, 0x06},   // 9  
  {0x06, 0x59, 0x01, 0x02},   // :  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // ;  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // <  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // =  (not implemented)
  {0x06, 0x59, 0x01, 0x02},   // >  (not implemented)  
  {0x06, 0x59, 0x01, 0x02},   // ?  
  {0x06, 0x59, 0x01, 0x02},   // @  (not implemented)
  {0x7E, 0x09, 0x09, 0x7E},   // A
  {0x36, 0x49, 0x49, 0x7F},   // B
  {0x22, 0x41, 0x41, 0x3E},   // C
  {0x3E, 0x41, 0x41, 0x7F},   // D
  {0x41, 0x49, 0x49, 0x7F},   // E
  {0x01, 0x09, 0x09, 0x7F},   // F
  {0x32, 0x51, 0x41, 0x3E},   // G
  {0x7F, 0x08, 0x08, 0x7F},   // H
  {0x00, 0x41, 0x7F, 0x41},   // I
  {0x3F, 0x40, 0x40, 0x20},   // J
  {0x41, 0x22, 0x14, 0x7F},   // K
  {0x40, 0x40, 0x40, 0x7F},   // L
  {0x7F, 0x02, 0x02, 0x7F},   // M
  {0x7F, 0x10, 0x08, 0x7F},   // N
  {0x3E, 0x41, 0x41, 0x3E},   // O
  {0x06, 0x09, 0x09, 0x7F},   // P
  {0x7E, 0x61, 0x41, 0x3E},   // Q
  {0x46, 0x29, 0x19, 0x7F},   // R
  {0x32, 0x49, 0x49, 0x26},   // S
  {0x00, 0x01, 0x7F, 0x01},   // T
  {0x3F, 0x40, 0x40, 0x3F},   // U
  {0x1F, 0x60, 0x60, 0x1F},   // V
  {0x3F, 0x70, 0x70, 0x3F},   // W
  {0x67, 0x18, 0x18, 0x67},   // X
  {0x07, 0x78, 0x78, 0x07},   // Y
  {0x47, 0x49, 0x51, 0x61},   // Z
  {0x02, 0x01, 0x02, 0x01}    // [ ==> ~	bring ~ to a lower ASCII code, otherwise the field would be much longer
};

CSL_Status DisplayString(char* strValue)
{
	int i;
	clearOLED(ROW_UPPER);
	clearOLED(ROW_LOWER);
	for(i=0;i<19;i++) {
		sendOLED(0x40, 0x00, 0x00, 2);
	}
	for(i=11; i>=0; i--) {
		sendLetter((Uint16)strValue[i]);
	}
	return 0;	
}

CSL_Status init_OLED()
{
	CSL_GpioPinConfig cfgGpio;
	CSL_Status status;
	
	// init LCD power
    hGpio = GPIO_open(&GpioObj, &status);
    cfgGpio.pinNum = CSL_GPIO_PIN12;
    cfgGpio.direction = CSL_GPIO_DIR_OUTPUT;
    GPIO_configBit (hGpio, &cfgGpio);
    GPIO_write(hGpio, cfgGpio.pinNum, 1);

    /* Initialize OSD9616 display */
    if (sendOLED(0x00, 0xae, 0x00, 2) != CSL_SOK) {	// Turn off oled panel
        return -1; 								// Don't setup display if not connected
    }
    sendOLED(0x00, 0x00, 0x00, 2);				// Set low column address
    sendOLED(0x00, 0x10, 0x00, 2); 				// Set high column address
    sendOLED(0x00, 0x40, 0x00, 2); 				// Set start line address
	sendOLED(0x00, 0x81, 0x7f, 3); 				// Set contrast control register
    sendOLED(0x00, 0xa1, 0x00, 2); 				// Set segment re-map 95 to 0
    sendOLED(0x00, 0xa6, 0x00, 2); 				// Set normal display
	sendOLED(0x00, 0xa8, 0x0f, 3); 				// Set multiplex ratio(1 to 16)
	
	sendOLED(0x00, 0x2e, 0x00, 2);

    sendOLED(0x00, 0xd3, 0x00, 2); 				// Set display offset
    sendOLED(0x00, 0x00, 0x00, 2); 				// Not offset
	sendOLED(0x00, 0xd5, 0x00, 2); 				// Set display clock divide ratio/oscillator frequency
    sendOLED(0x00, 0xf0, 0x00, 2); 				// Set divide ratio

	sendOLED(0x00, 0xd9, 0x22, 3);				// Set pre-charge period
	sendOLED(0x00, 0xda, 0x02, 3);				// Set com pins hardware configuration

    sendOLED(0x00, 0xdb, 0x00, 2); 				// Set vcomh
    sendOLED(0x00, 0x49, 0x00, 2); 				// 0.83*vref
    
    sendOLED(0x00, 0x8d, 0x14, 3);				// Set DC-DC enable

    sendOLED(0x00, 0xaf, 0x00, 2); 				// Turn on oled panel    
    
	clearOLED(ROW_UPPER|ROW_LOWER);
   	return 0;
}

static CSL_Status sendOLED(Uint16 cmd_dat, Uint16 data, Uint16 data2, int len)
{
    CSL_Status status;
    
    Uint16 i2c_addr_data[3];
    volatile Uint16 delay;
    
    i2c_addr_data[0] = cmd_dat & 0x00FF;     	// Specifies whether data is Command or Data
    i2c_addr_data[1] = data;                	// Command / Data
	i2c_addr_data[2] = data2;                	// Command / Data

	status = I2C_write(i2c_addr_data, len, OLED9616_I2C_ADDR, TRUE, (CSL_I2C_START | CSL_I2C_STOP), CSL_I2C_MAX_TIMEOUT);
	
	delay = 4096;
	while(delay--);
	
	return status;
}

static CSL_Status sendLetter(Uint16 character)
{
	if (character == '~') {		// move in 8.3 SFN often used '~' to a lower number to avoid longer <alphanum> table
		character = '[';
	}
	character = character - ' ';
	sendOLED(0x40, alphanum[character][0], 0x00, 2);	// each char consists of 5 columns 
	sendOLED(0x40, alphanum[character][1], 0x00, 2);
	sendOLED(0x40, alphanum[character][2], 0x00, 2);
	sendOLED(0x40, alphanum[character][3], 0x00, 2);
	sendOLED(0x40, 0x00, 0x00, 2);						// last column always empty
	return 0;		
}

static CSL_Status clearOLED(int row)
{
	int i;

	if (row & ROW_UPPER) {	
    	/* Fill page 0 */ 
    	sendOLED(0x00, 0x00, 0x00, 2);   			// Set low column address
    	sendOLED(0x00, 0x10, 0x00, 2);   			// Set high column address
    	sendOLED(0x00, 0xb0+0, 0x00, 2); 			// Set page for page 0 to page 5
    
    	for(i=0;i<128;i++) {
    		sendOLED(0x40, 0x00, 0x00, 2);
    	}
	}
	if (row & ROW_LOWER) {
    	sendOLED(0x00, 0x00, 0x00, 2);   			// Set low column address
    	sendOLED(0x00, 0x10, 0x00, 2);   			// Set high column address
    	sendOLED(0x00, 0xb0+1, 0x00, 2); 			// Set page for page 0 to page 5
    
    	for(i=0;i<128;i++) {
    		sendOLED(0x40, 0x00, 0x00, 2);
    	}
	}
	return 0;
}

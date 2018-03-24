#include <reg51.h>
#include "delay.h"
#include "keypad4x4.h"
#include "lcd8bit.h"


void main()
{
	unsigned char key;
	lcd_init();				// Initailzed LCD
	lcd_string("Zehn spinster");
	while(1)
	{
		key = keyscan();	// Keyscan function called and return key press number in charater form 
		lcd_cmd(0x01);		// clear display
		lcd_data(key);		// Display which key press 
	}
}
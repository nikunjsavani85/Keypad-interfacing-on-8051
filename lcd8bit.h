/*****************************************************************/
/* 								charater LCD 16x2( HD44780 )									 */
/* 					Here 8-Bit mode used for interfacing LCD 						 */
/*		And also possible to used 4-Bit mode for charcter LCD      */
/*****************************************************************/
#ifndef _LCD8BIT_H_
#define _LCD8BIT_H_

sfr LCD=0x80;		// Writing Data on LCD Data line 
sbit RS=P3^4;		// Data/Command Register port
sbit RW=P3^5;		// Read/Write operation port
sbit EN=P3^6;		// Enable

//------- LCD ready for performing Command --------------//

void lcd_cmd(unsigned char cmd)
{
	LCD=cmd;	// Send command on LCD_port
	RS=0;			// 0 ->Command mode ,1 ->Data mode
	RW=0;			// 0 ->Write operation ,1->Read operation
	EN=1;			// For operation high to low signal requried
		delay_ms(2);			// Requried 1.5 microsecond
	EN=0;
}

//--------- For Displaying charecter on LCD ------------//

void lcd_data(unsigned char ch)
{
	LCD=ch;	// Receive charactor and send on LCD
	RS=1;		//Data mode Register selected
	RW=0;		// write operation
	EN=1;
		delay_ms(2);
	EN=0;
}

//------------- LCD initial Mode -----------------//

void lcd_init()
{
	lcd_cmd(0x02);	// Set cursor to HOME position (R1xC1)
	lcd_cmd(0x38);	//(IMP) Intialise 5x8 dot matrix in "LCD 8-Bit Mode"
	lcd_cmd(0x0E);	// Display ON , Cursor ON
	lcd_cmd(0x06);	// Shift cursor to right side every time when new charter written on LCD
	lcd_cmd(0x01);	// Used to clear LCD screen or clear DDRAM
}

//---------- String displying on LCD -------------//

void lcd_string(char *s)	// Receving base addr of string
{
	while(*s)
	{
		lcd_data(*s++);				//one by one display
		delay_ms(10);
	}
}
#endif
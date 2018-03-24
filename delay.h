// Delay in milisecond lib

#ifndef __DELAY_H__
#define __DELAY_H__

void delay_ms(unsigned int ms)
{
	unsigned char i;
	for( ;ms>0;ms--)
	{
		for(i=250;i>0;i--);
		for(i=247;i>0;i--);
	}
}

#endif
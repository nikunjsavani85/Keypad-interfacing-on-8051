/************************************************************/
/*           4x4 keypad interfacing library                 */
/* 					Image attachment for 4x4 matrix 								*/
/*      Here port 2 used for 4x4 matrix interface						*/
/************************************************************/

#ifndef _KEYPAD4X4_H_
#define _KEYPAD4X4_H_

//------------- Row connection from 4x4 matrix -------------//
sbit R0=P2^0;		// 4 Row from 4 PIN of port2
sbit R1=P2^1;
sbit R2=P2^2;
sbit R3=P2^3;
//------------- column connection from 4x4 matrix -------------//
sbit C0=P2^4;		// 4 cloumn from 4 PIN of port2
sbit C1=P2^5;
sbit C2=P2^6;
sbit C3=P2^7;

code unsigned char keypad_lut[4][4]={7,8,9,'/',4,5,6,'*',1,2,3,'-','C',0,'=','+'};	// 4x4 Array for Switch selection
//code unsigned char keypad_lut[4][4]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};	// 4x4 Array for Switch selection

/*function developed for know the status of column*/
/* 								Return 1 or 0										*/
bit colscan()	
{
	return (C0&C1&C2&C3);
}

/* Function for which key press find */
char keyscan()
{
	char row,col;		// Using row & column finding key pressed from keypad_lut
	R0=R1=R2=R3=0;	// Port PIN status initialy low
	C0=C1=C2=C3=1;	// port PIN status initaly high means Rx & Cx no switch pressed
	
	while(colscan()==1);	//waiting for switch pressed
	
	//------------ FOR " ROW=0 " & COl=1,2,3,4 ---------------//
	
	R0=0;							//First check in 1st "R0" so make GND(Low)
	R1=R2=R3=1;				// other high
	
	if(colscan()==0)	//After "R0" select checking in that any key pressed or not
	{
		row=0;					//If any key pressed from 4 switch of "R0" make row=0
		goto colcheck;	//For finding witch column key pressed from "R0"
	}
	
	//------------ FOR " ROW=1 " & COl=1,2,3,4 ---------------//
	
	R1=0;							//First check in 1st "R1" so make GND(Low)
	R0=R2=R3=1;				// other high
	
	if(colscan()==0)	//After "R1" select checking in that any key pressed or not
	{
		row=1;					//If any key pressed from 4 switch of "R1" make row=1
		goto colcheck;	//For finding witch column key pressed from "R1"
	}
	
	//------------ FOR " ROW=2 " & COl=1,2,3,4 -----------------//
	
	R2=0;							//First check in 1st "R2" so make GND(Low)
	R0=R1=R3=1;				// other high
	
	if(colscan()==0)	//After "R2" select checking in that any key pressed or not
	{
		row=2;					//If any key pressed from 4 switch of "R2" make row=2
		goto colcheck;	//For finding witch column key pressed from "R2"
	}
	
	//------------ FOR " ROW=3 " & COl=1,2,3,4 -------------------//
	
	R3=0;								//First check in 1st "R3" so make GND(Low)
	R0=R1=R2=1;					// other high
	
	if(colscan()==0)		//After "R3" select checking in that any key pressed or not
	{
		row=3;						//If any key pressed from 4 switch of "R3" make row=3
		//goto colcheck;	//For finding witch column key pressed from "R3" NO NEED BECOZ AFTER THIS NEXT IS GOTO LOOP
	}
	
	colcheck:
	if(C0==0)
		col=0;
	else if(C1==0)
		col=1;
	else if(C2==0)
		col=2;
	else
		col=3;
	delay_ms(100);	//delay for displaying chareter
	
	while(colscan()==0);	//waiting for Switch release
	
	return(keypad_lut[row][col]);
}

#endif
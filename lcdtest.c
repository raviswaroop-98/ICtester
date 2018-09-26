#include<reg52.h>
#include<intrins.h>

#define lcdData P3

#define clearDisplay 0x01
#define rightToLeft  0x06
#define cursorBlink  0x0E
#define twoLines     0x38
#define G1           0x80
#define G2           0x88
#define G3           0xC0
#define G4           0xC8

sbit RS = P1^4;
sbit RW = P1^5;
sbit E  = P1^6;
sbit Busy = P3^0;

void lcdInit(void);
void lcdCmdWrite(unsigned char command);
void lcdDataWrite(unsigned char Data);
void lcdPrint(char *string);
void lcdBusy(void);

void main(void)
{
	lcdInit();
	
}

void lcdInit()
{
	lcdCmdWrite(clearDisplay);
	lcdCmdWrite(rightToLeft);
	lcdCmdWrite(cursorBlink);
	lcdCmdWrite(twoLines);
}

void lcdBusy()
{
	Busy = 1;
	RS = 0;
	RW = 1;
	while (Busy == 1)
	{
		E = 0;
		_nop_ ();
		E = 1;
	}
}

void lcdCmdWrite(unsigned char command)
{
	lcdBusy();
	RS = 0;
	RW = 0;
	lcdData = command;
	E = 1;
	_nop_ ();
	E = 0;
}

void lcdDataWrite(unsigned char Data)
{
	lcdBusy();
	RS = 1;
	RW = 0;
	lcdData = Data;
	E = 1;
	_nop_();
	E = 0;
}
	
void lcdPrint(char *string)
{
  while(*string)
	{
     lcdDataWrite(*string++);
	}
}	
	
	
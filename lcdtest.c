#include<reg52.h>

#define lcdData P3

#define clearDisplay 0x01
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
void lcdCmdWrite(unsigned char );
void lcdDataWrite(unsigned char );
void lcdPrint(char *string);
void MSdelay(unsigned int);

void main(void)
{
	lcdInit();
	lcdPrint("LCD WORKING");
	lcdCmdWrite(0xC0);
	MSdelay(10);
	lcdPrint("BITCHES...!!");
	while(1)
	{
	}
}

void MSdelay(unsigned int time)
{
	unsigned int i,j;
	for(i = 0; i < time; i++)
	{
		for(j=0; j<165; j++);
	}
}

void lcdInit()
{
	lcdCmdWrite(clearDisplay);
	lcdCmdWrite(cursorBlink);
	lcdCmdWrite(twoLines);
	lcdCmdWrite(G1);
}


void lcdCmdWrite(unsigned char command)
{
	RS = 0;
	RW = 0;
	lcdData = command;
	E = 1;
	MSdelay(5);
	E = 0;
	MSdelay(10);
}

void lcdDataWrite(unsigned char Data)
{
	RS = 1;
	RW = 0;
	lcdData = Data;
	E = 1;
	MSdelay(5);
	E = 0;
	MSdelay(10);s
}
	
void lcdPrint(char *string)
{
	while(*string > 0)
	{
		lcdDataWrite(*string++);
	}
	
}

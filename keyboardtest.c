#include<reg52.h>
#include<intrins.h>

#define lcdData P3
#define keyport P0

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

unsigned char inputkey(void);

void main()
{
	lcdInit();
	while(1){
		inputkey();
	  MSdelay(2000);
	}
}

unsigned char inputkey(void)
{
	unsigned char check;
	unsigned char pressed = 0;
	keyport = 0x0f;
	check = keyport;
	check &= 0x0f;
	while(check != 0x0f){
		lcdCmdWrite(clearDisplay);
		lcdPrint("Waiting to release");
		MSdelay(100);
		check = keyport;
		check &= 0x0f;
	}
	MSdelay(5);
	lcdCmdWrite(clearDisplay);
	lcdPrint("Press a key");
	while(pressed == 0){
		check = keyport;
		check &= 0x0f;
	  if(check != 0x0f){
		  MSdelay(5);
		  check = keyport;
			check &= 0xf;
		  if(check != 0x0f){
			  pressed = 1;
		  }
		  else{
			  pressed = 0;
			}
	  }
  }
	
/* checking col 1 */
	keyport = 0xef;
	check = keyport;
	check &= 0x0f;
	if(check != 0x0f){
		lcdCmdWrite(clearDisplay);
		if(check == 0x0e){
			lcdPrint("Key : 1");
			return;
		}
		if(check == 0x0d){
			lcdPrint("Key : 4");
			return;
		}
		if(check == 0x0b){
			lcdPrint("Key : 7");
			return;
		}
		if(check == 0x07){
			lcdPrint("Key : Enter");
			return;
		}
	}

/* checking col 2 */
	keyport = 0xdf;
	check = keyport;
	check &= 0x0f;
	if(check != 0x0f){
		lcdCmdWrite(clearDisplay);
		if(check == 0x0e){
			lcdPrint("Key : 2");
			return;
		}
		if(check == 0x0d){
			lcdPrint("Key : 5");
			return;
		}
		if(check == 0x0b){
			lcdPrint("Key : 8");
			return;
		}
		if(check == 0x07){
			lcdPrint("Key : 0");
			return;
		}
	}	
	
/* checking col 3 */
	keyport = 0xbf;
	check = keyport;
	check &= 0x0f;
	if(check != 0x0f){
		lcdCmdWrite(clearDisplay);
		if(check == 0x0e){
			lcdPrint("Key : 3");
			return;
		}
		if(check == 0x0d){
			lcdPrint("Key : 6");
			return;
		}
		if(check == 0x0b){
			lcdPrint("Key : 9");
			return;
		}
		if(check == 0x07){
			lcdPrint("Key : Return");
			return;
		}
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
	MSdelay(10);
}
	
void lcdPrint(char *string)
{
	while(*string > 0)
	{
		lcdDataWrite(*string++);
	}
	
}

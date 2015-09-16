#include "ebox.h"

#include "math.h"

#define TXPIN PA9
#define RXPIN PA10

USART uart1(USART1,TXPIN,RXPIN);

	
void setup()
{
	eBoxInit();

}

float x;
uint16_t y;
int main(void)
{

	setup();

	while(1)
	{		 	
		x = x + PI*0.01;
		if(x >= PI)x=0;
		y = 2000 - (sin(x)+1)*1000;
		
		analogWrite(PA7,y);
		delay_ms(50);
	}


}

#include "ebox.h"

#define TXPIN PA9
#define RXPIN PA10

USART uart1(USART1,TXPIN,RXPIN);

uint32_t xx;

EXTIx ex(PA7,EXTI_Trigger_Falling);

void exit()
{
	xx++;
	uart1.printf("\r\nxx = %d",xx);
}
void setup()
{
	eBoxInit();
	uart1.begin(9600);
	ex.attachInterrupt(exit);
}


int main(void)
{
	setup();
	while(1)
	{
		;
	}


}





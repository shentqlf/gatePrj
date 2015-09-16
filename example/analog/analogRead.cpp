
#include "ebox.h"

#define TXPIN PA9
#define RXPIN PA10

USART uart1(USART1,TXPIN,RXPIN);

void setup()
{
	eBoxInit();
	uart1.begin(9600);
	
	PA7->mode(AIN);
}


int16_t x;
int main(void)
{
	setup();
	while(1)
	{
		
		x = analogRead(PA7);
		uart1.printf("PA7:hex = %05d\r\n",x);
		x = analogReadToVoltage(PA7);
		uart1.printf("PA7:val = %04dmv\r\n",x);
		uart1.printf("==============\r\n",x);
		delay_ms(1000);
	}


}





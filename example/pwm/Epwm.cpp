
#include "ebox.h"

#define TXPIN PA9
#define RXPIN PA10

USART uart1(USART1,TXPIN,RXPIN);

PWM pwm1(PA7);

void setup()
{
	eBoxInit();
	uart1.begin(9600);

	pwm1.setDuty(500);

}

int main(void)
{
	setup();
	
	while(1)
	{
		uart1.printf("\r\nruning !");
		delay_ms(1000);
	}


}





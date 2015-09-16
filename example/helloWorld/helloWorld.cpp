
#include "ebox.h"


#define TXPIN PA9
#define RXPIN PA10

USART uart1(USART1,TXPIN,RXPIN);
//USART uart2(USART3,PA2,PA3);
//USART uart3(USART3,PB10,PB11);

void setup()
{
	eBoxInit();
	uart1.begin(9600);
	
}


int main(void)
{
	setup();
	while(1)
	{
		uart1.printf("hello World !\r\n");
		delay_ms(1000);
	}


}





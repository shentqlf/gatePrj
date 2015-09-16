
#include "ebox.h"
#include "ds3231.h"

#define TXPIN PA9
#define RXPIN PA10

#define SDAPIN PA5
#define SCLIN PA4


USART uart1(USART1,TXPIN,RXPIN);
DS3231 ds(SDAPIN,SCLIN);

DateTime t;
char time[9];
char date[9];

void setup()
{
	eBoxInit();
	uart3.begin(9600);
	ds.begin(100000);
	
	t.year = 15;
	t.month = 7;
	t.date = 3;
	t.hour = 23;
	t.min = 59;
	t.sec = 55;
}
int main(void)
{
	setup();
	ds.setTime(&t);
	while(1)
	{	
		ds.getDateTime(&t);
		ds.getTime(time);
		ds.getDate(date);
		uart1.printf("=======\r\n");
		uart1.printf("%02d-%02d-%02d %02d:%02d:%02d\r\n",t.year,t.month,t.date,t.hour,t.min,t.sec);

		uart1.printf(date);
		uart1.printf(" ");
		uart1.printf(time);
		uart1.printf("\r\n");
		delay_ms(1000);
	}


}





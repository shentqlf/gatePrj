#include "ioctr.h"

/******************
”≤º˛≈‰÷√¡–±Ì
*******************/
#define LED_PIN 			PA1
#define LED_TEST_PIN	PB8

#define BEEP_PIN 			PA2
#define BEEP_TEST_PIN PA3

#define JDQ1_PIN			PB4
#define JDQ1_TEST_PIN PB9

#define JDQ2_PIN			PB5
#define JDQ2_TEST_PIN PB10


PWM beep(&BEEP_PIN,2000);
PWM beep_test(&BEEP_TEST_PIN,2000);

void io_ctr_init()
{
	LED_PIN.mode(OUTPUT_PP);
	LED_TEST_PIN.mode(OUTPUT_PP);
	
	JDQ1_PIN.mode(OUTPUT_PP);
	JDQ2_PIN.mode(OUTPUT_PP);
	JDQ1_TEST_PIN.mode(OUTPUT_PP);
	JDQ2_TEST_PIN.mode(OUTPUT_PP);
	
	beep.set_duty(0);
	beep_test.set_duty(0);
}
void led_on()
{
	LED_PIN.set();
	LED_TEST_PIN.set();
}
void led_off()
{
	LED_PIN.reset();
	LED_TEST_PIN.reset();
}
void beep_on()
{
	beep.set_duty(500);
	beep_test.set_duty(50);
}
void beep_off()
{
	beep.set_duty(0);
	beep_test.set_duty(0);
}
void jdq1_on()
{
	JDQ1_PIN.set();
	JDQ1_TEST_PIN.set();
}
void jdq1_off()
{
	JDQ1_PIN.reset();
	JDQ1_TEST_PIN.reset();
}
void jdq2_on()
{
	JDQ2_PIN.set();
	JDQ2_TEST_PIN.set();
}
void jdq2_off()
{
	JDQ2_PIN.reset();
	JDQ2_TEST_PIN.reset();
}
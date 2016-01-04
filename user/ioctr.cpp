#include "ioctr.h"

/******************
硬件配置列表
*******************/
#define LED_PIN 			PA1
#define LED_TEST_PIN	PB8

#define BEEP_PIN 			PA2
#define BEEP_TEST_PIN PA3

#define JDQ1_PIN			PB4
#define JDQ1_TEST_PIN PB9

#define JDQ2_PIN			PB5
#define JDQ2_TEST_PIN PB10

#define HJS1_PIN            PB0
#define HJS2_PIN            PB1
#define HJS3_PIN            PB2
#define HJS4_PIN            PB3


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
    HJS1_PIN.mode(INPUT_PU);
    HJS2_PIN.mode(INPUT_PU);
    HJS3_PIN.mode(INPUT_PU);
    HJS4_PIN.mode(INPUT_PU);
    
    
	beep.set_duty(0);
	beep_test.set_duty(0);
    //默认状态
	led_off();
    beep_off();
	jdq1_off();
    jdq2_off();
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
int read_hjs1()
{
    return HJS1_PIN.read();
}
int read_hjs2()
{
    return HJS2_PIN.read();
}
int read_hjs3()
{
    return HJS3_PIN.read();
}
int read_hjs4()
{
    return HJS4_PIN.read();
}
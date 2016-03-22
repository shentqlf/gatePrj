
#include "ebox.h"

#include "includes.h"

void task_1();
void task_2();
void task_3();
void task_4();
void task_5();


 STACK_TypeDef TASK_1_STK[TASK_1_STK_SIZE];
 STACK_TypeDef TASK_2_STK[TASK_2_STK_SIZE];
 STACK_TypeDef TASK_3_STK[TASK_3_STK_SIZE];
 STACK_TypeDef TASK_4_STK[TASK_4_STK_SIZE];
 STACK_TypeDef TASK_5_STK[TASK_5_STK_SIZE];



////////////////////////////////////////////////////////////////////

  u8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};/*定义Mac变量*/
  u8 lip[4]={0};/*定义lp变量*/
  u8 sub[4]={255,255,255,0};/*定义subnet变量*/
  u8 gw[4]={192,168,0,1};/*定义gateway变量*/
	
//  u8 rip[4]={192,168,0,102};/*定义lp变量*/
  //u8 rip[4]={192,168,1,112};/*定义lp变量*/
  u8 buf[6];
///创建对象////////////////////////////////////////////////////
W5500 w5500(&PC13,&PC14,&PC15,&spi2);
UDP udp;
BUTTON	btn(&PA8,1);	

/////////全局变量///////////////////////////////////////////////////////////	
u8 connectState=0;//链接状态
u8 warningState = 0;
u8 warningTime = 10;
u8 jdq1State=0;
u8 jdq2State=0;
u8 recvBuf[256];//接收缓冲区
UDPMessage msg;//udp发送帧结构
  
uint8_t disp_mode = 0;
uint16_t num_of_enter = 0;
uint16_t num_of_out = 0;

	
void initUDPServer()
{
	w5500.begin(2,mac,lip,sub,gw);
	attach_eth_to_socket(&w5500);
  w5500.getMAC (buf);
	uart1.printf("======net config=======\r\n");
  uart1.printf("mac : %02x.%02x.%02x.%02x.%02x.%02x\r\n", buf[0],buf[1],buf[2],buf[3],buf[4],buf[5]);
  w5500.getIP (buf);
  uart1.printf("IP : %d.%d.%d.%d\r\n", buf[0],buf[1],buf[2],buf[3]);
  w5500.getSubnet(buf);
  uart1.printf("mask : %d.%d.%d.%d\r\n", buf[0],buf[1],buf[2],buf[3]);
  w5500.getGateway(buf);
  uart1.printf("GW : %d.%d.%d.%d\r\n", buf[0],buf[1],buf[2],buf[3]);
	
	udp.begin(SOCKET0,30000);
	uart1.printf("udp server is begin on localip:30000\r\n");
	uart1.printf("=======================\r\n");
}
void setup()
{

	ebox_init();
	OS_Init();
	
	uart1.begin(115200);
	uart1.printf("\r\nuart1 9600 ok!\r\n");
  
    
    dwin_init();
	io_ctr_init();
	uart1.printf("io control init ok!\r\n");

    
    load_ip(lip);
    if(lip[0] == 0xff && lip[1] == 0xff)
    {
        set_ip_as_default(lip);
        save_ip(lip);
    }
	initUDPServer();
	uart1.printf("net init ok!\r\n");
	
	flash.read(WARNING_TIME_FLASH_ADDR,&warningTime,1);
	
	if(warningTime == 0xff)
    {
		warningTime = 10;
		flash.write(WARNING_TIME_FLASH_ADDR,&warningTime,1);
    }
	uart1.printf("settings:\r\n");
	uart1.printf("warnning time =%d!\r\n",warningTime);
    
    
	flash.read(HOST_STATE_FLASH_ADDR,&host_state,1);
    if(host_state != 0 && host_state != 1)
    {
        host_state = 1;
		flash.write(HOST_STATE_FLASH_ADDR,&warningTime,1);
    }
    
	uart1.printf("host left or right=%d!\r\n",host_state);

    


    ring_start();
	
	OS_TaskCreate(task_1,&TASK_1_STK[TASK_1_STK_SIZE-1],TASK1_PRIO);
	OS_TaskCreate(task_2,&TASK_2_STK[TASK_2_STK_SIZE-1],TASK2_PRIO);
	OS_TaskCreate(task_3,&TASK_3_STK[TASK_3_STK_SIZE-1],TASK3_PRIO);
	OS_TaskCreate(task_4,&TASK_4_STK[TASK_4_STK_SIZE-1],TASK4_PRIO);
	OS_TaskCreate(task_5,&TASK_5_STK[TASK_5_STK_SIZE-1],TASK5_PRIO);
	OS_Start();
	
	
	
}



int main(void)
{
	setup();

	while(1)
	{

	}
}

void ring_start()
{
    for(int i = 0; i < 2; i++)
    {
        led_on();
        beep_on();	
        delay_ms(100);    
        led_off();
        beep_off();    
        delay_ms(100);    
    }
}
void ring_connect()
{
    for(int i = 0; i < 2; i++)
    {
        led_on();
        beep_on();	
        delay_ms(100);    
        led_off();
        beep_off();    
        delay_ms(100);    
    }
}
void ring_disconnect()
{
    led_on();
    beep_on();	
    delay_ms(500);       
    led_off();
    beep_off();    
}

void save_ip(u8 *ip)
{
    flash.write(FLASH_LOCAL_IP_ADDR,ip,4);
}
void load_ip(u8 *ip)
{
    flash.read(FLASH_LOCAL_IP_ADDR,ip,4);
}
void set_ip_as_default(u8 *ip)
{
    ip[0] = 192;
    ip[1] = 168;
    ip[2] = 1;
    ip[3] = 2;

}


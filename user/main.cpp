
#include "ebox.h"

#include "includes.h"

void task_1();
void task_2();
void task_3();


 STACK_TypeDef TASK_1_STK[TASK_1_STK_SIZE];
 STACK_TypeDef TASK_2_STK[TASK_2_STK_SIZE];
 STACK_TypeDef TASK_3_STK[TASK_3_STK_SIZE];
 STACK_TypeDef TASK_4_STK[TASK_4_STK_SIZE];



////////////////////////////////////////////////////////////////////

  u8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};/*����Mac����*/
  u8 lip[4]={192,168,0,211};/*����lp����*/
  u8 sub[4]={255,255,255,0};/*����subnet����*/
  u8 gw[4]={192,168,1,1};/*����gateway����*/
	
  u8 rip[4]={192,168,1,102};/*����lp����*/
  u8 ip[6];
///��������////////////////////////////////////////////////////
W5500 w5500(&PC13,&PC14,&PC15,&spi2);
UDP udp;
BUTTON	btn(&PA8,1);	

/////////ȫ�ֱ���///////////////////////////////////////////////////////////	
u8 connectState=0;//����״̬
u8 warningState = 0;
u8 warningTime = 10;
u8 jdq1State=0;
u8 jdq2State=0;
u8 recvBuf[100];//���ջ�����
UDPMessage msg;//udp����֡�ṹ

	
void initUDPServer()
{
	w5500.begin(2,mac,lip,sub,gw);
	attach_eth_to_socket(&w5500);
  w5500.getMAC (ip);
	uart1.printf("======net config=======\r\n");
  uart1.printf("mac : %02x.%02x.%02x.%02x.%02x.%02x\r\n", ip[0],ip[1],ip[2],ip[3],ip[4],ip[5]);
  w5500.getIP (ip);
  uart1.printf("IP : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  w5500.getSubnet(ip);
  uart1.printf("mask : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  w5500.getGateway(ip);
  uart1.printf("GW : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
	
	udp.begin(SOCKET0,30000);
	uart1.printf("udp server is begin on 192.168.1.111,30000\r\n");
	uart1.printf("=======================\r\n");
}
void setup()
{
	ebox_init();
	OS_Init();
	
	uart1.begin(9600);
	uart1.printf("\r\nuart1 9600 ok!\r\n");
	
	io_ctr_init();
	uart1.printf("io control init ok!\r\n");

	initUDPServer();
	uart1.printf("net init ok!\r\n");
	
	flash.read(0x10000,&warningTime,1);
	
	if(warningTime == 0xff)
		warningTime = 10;
		flash.write(0x10000,&warningTime,1);
	flash.read(0x10000,&warningTime,1);
	
	uart1.printf("setting:\r\n");
	uart1.printf("warnning time:%d!\r\n",warningTime);


	
	OS_TaskCreate(task_1,&TASK_1_STK[TASK_1_STK_SIZE-1],TASK1_PRIO);
	OS_TaskCreate(task_2,&TASK_2_STK[TASK_2_STK_SIZE-1],TASK2_PRIO);
	OS_TaskCreate(task_3,&TASK_3_STK[TASK_3_STK_SIZE-1],TASK3_PRIO);
	OS_Start();
	
	
	
}



int main(void)
{
	setup();

	while(1)
	{

	}

}





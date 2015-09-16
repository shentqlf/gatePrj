
#include "ebox.h"

#include "includes.h"

void task_1();
void task_2();
void task_3();


 STACK_TypeDef TASK_1_STK[TASK_1_STK_SIZE];
 STACK_TypeDef TASK_2_STK[TASK_2_STK_SIZE];
 STACK_TypeDef TASK_3_STK[TASK_3_STK_SIZE];
 STACK_TypeDef TASK_4_STK[TASK_4_STK_SIZE];


u8 recvBuf[100];
u8 sendBuf[100] = "jdq1:1\rjdq2:1\rbeep:1\rledx:1";

///创建对象////////////////////////////////////////////////////
USART 		uart1(USART1,PA9,PA10);
W5500 		w5500(PC13,SPI2,PB13,PB14,PB15,PC14,PC15);
TCPSERVER tcpServer;
Button btn(PA8,1);


  u8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};/*定义Mac变量*/
  u8 lip[4]={192,168,1,111};/*定义lp变量*/
  u8 sub[4]={255,255,255,0};/*定义subnet变量*/
  u8 gw[4]={192,168,1,1};/*定义gateway变量*/
	
  u8 rip[4]={192,168,1,102};/*定义lp变量*/
  u8 ip[6];
	
void initTCPServer()
{
	
	w5500.begin(mac,lip,sub,gw);
	attachEthToSocket(&w5500);
  w5500.getMAC (ip);
  uart1.printf("mac : %02x.%02x.%02x.%02x.%02x.%02x\r\n", ip[0],ip[1],ip[2],ip[3],ip[4],ip[5]);
  w5500.getIP (ip);
  uart1.printf("IP : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  w5500.getSubnet(ip);
  uart1.printf("mask : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  w5500.getGateway(ip);
  uart1.printf("GW : %d.%d.%d.%d\r\n", ip[0],ip[1],ip[2],ip[3]);
  uart1.printf("Network is ready.\r\n");
	
	tcpServer.begin(SOCKET0,30000);
}
void setup()
{
	eBoxInit();
	OS_Init();
	uart1.begin(9600);
	
	initTCPServer();
	uart1.printf("\r\nuart1 9600 ok!");
	
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





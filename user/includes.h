#ifndef __START_H
#define __START_H
#include "ebox.h"
#include "w5500.h"
#include "udp.h"
#include "button.h"
#include "ioctr.h"
#include "os.h"
#include "ctrpro.h"
#include "lcd_dwin.h"

#define WARNING_TIME_FLASH_ADDR 0x8010000
#define HOST_STATE_FLASH_ADDR   0x8010004
#define FLASH_LOCAL_IP_ADDR     0x8010008
#define FLASH_SERVER_IP_ADDR    0x801000C

#define TASK_1_STK_SIZE 512
#define TASK_2_STK_SIZE 256
#define TASK_3_STK_SIZE 512
#define TASK_4_STK_SIZE 128
#define TASK_5_STK_SIZE 128


#define TASK1_PRIO 1
#define TASK2_PRIO 0
#define TASK3_PRIO 2
#define TASK4_PRIO 3
#define TASK5_PRIO 4

extern STACK_TypeDef TASK_1_STK[TASK_1_STK_SIZE];
extern STACK_TypeDef TASK_2_STK[TASK_2_STK_SIZE];
extern STACK_TypeDef TASK_3_STK[TASK_3_STK_SIZE];
extern STACK_TypeDef TASK_4_STK[TASK_4_STK_SIZE];


//ȫ�ֶ���//////////////////////////////
extern W5500 w5500;
extern UDP udp;
extern BUTTON btn;
//ȫ�ֿ��ƶ���/////////////

//////ȫ�ֱ���/////////////////////////////
extern u8 connectState;
extern u8 warningState;
extern u8 warningTime;
extern u8 jdq1State;
extern u8 jdq2State;

extern u8 recvBuf[];
extern UDPMessage msg;

extern u8 host_state;//��������߻����ұ�

extern uint8_t disp_mode;
extern uint16_t num_of_enter;
extern uint16_t num_of_out;


extern u8 mac[];/*����Mac����*/
extern u8 lip[];/*����lp����*/
extern u8 sub[];/*����subnet����*/
extern u8 gw[];/*����gateway����*/

void save_ip(u8 *ip);
void load_ip(u8 *ip);
void set_ip_as_default(u8 *ip);


//����
void ring_start();
void ring_connect();
void ring_disconnect();
#endif

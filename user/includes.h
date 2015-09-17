#ifndef __START_H
#define __START_H
#include "ebox.h"
#include "w5500.h"
#include "udp.h"
#include "button.h"
#include "os.h"
#include "ctrpro.h"

#define TASK_1_STK_SIZE 512
#define TASK_2_STK_SIZE 256
#define TASK_3_STK_SIZE 512
#define TASK_4_STK_SIZE 128


#define TASK1_PRIO 1
#define TASK2_PRIO 0
#define TASK3_PRIO 2
#define TASK4_PRIO 3

extern STACK_TypeDef TASK_1_STK[TASK_1_STK_SIZE];
extern STACK_TypeDef TASK_2_STK[TASK_2_STK_SIZE];
extern STACK_TypeDef TASK_3_STK[TASK_3_STK_SIZE];
extern STACK_TypeDef TASK_4_STK[TASK_4_STK_SIZE];


//ȫ�ֶ���//////////////////////////////
extern W5500 w5500;
extern UDP udp;
extern Button btn;
//ȫ�ֿ��ƶ���/////////////
#define LED PA1
#define BEEP_PIN PA2

#define JDQ1 PB4
#define JDQ2 PB5

extern PWM beep;
//////ȫ�ֱ���/////////////////////////////
extern u8 connectState;
extern u8 warningState;
extern u8 warningTime;
extern u8 jdq1State;
extern u8 jdq2State;
extern u8 recvBuf[100];
extern UDPMessage msg;


#endif

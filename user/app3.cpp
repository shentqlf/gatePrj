


#include "ebox.h"
#include "includes.h"

float cpu;
INT16U mem;

void task_3()
{
  while(1)
	{
		cpu = OS_GetCPU();
		uart1.printf("cpu = %0.1f%%\r\n",cpu);
		
		
		mem = OS_GetStackMaxUsage(TASK_1_STK,TASK_1_STK_SIZE);
		uart1.printf("task1£ºmem = %02d%%\r\n",mem);
		mem = OS_GetStackMaxUsage(TASK_2_STK,TASK_2_STK_SIZE);
		uart1.printf("task2£ºmem = %02d%%\r\n",mem);
		mem = OS_GetStackMaxUsage(TASK_3_STK,TASK_3_STK_SIZE);
		uart1.printf("task3£ºmem = %02d%%\r\n",mem);
		OS_TimeDelay(1000);
	}

}


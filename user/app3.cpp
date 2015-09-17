


#include "ebox.h"
#include "includes.h"

float cpu;
INT16U mem;

u8 xintiaoBuf[] = "$,X,0,1,;";
	u8 turn = 0;
	u8 count1 = 0;
	u8 count2 = 0;
void task_3()
{
  while(1)
	{
		cpu = OS_GetCPU();
		if(connectState == 1)
		{
			count1++;
			count1=count1%2;
			if(count1 == 0)
			{
				msg.len = sizeof(xintiaoBuf);
				msg.buf = xintiaoBuf;
				udp.send(&msg);
			}
		}
		if(warningState  == 1)
		{ 

			if(turn == 0)
			{
				PB8->write(1);
				beep.setDuty(500);
			}
			else
			{
				PB8->write(0);
				beep.setDuty(0);
			
			}
			if(warningTime > 0)	
			{
				if((warningTime*2 - count2) == 0)
				{
					warningState = 0;
					PB8->write(0);
					beep.setDuty(0);
					count2 = 0;
					turn = 0;
				}
				count2++;
			
			}
			turn++;
			turn = turn%2;
		}
//		uart1.printf("cpu = %0.1f%%\r\n",cpu);
//		
//		
//		mem = OS_GetStackMaxUsage(TASK_1_STK,TASK_1_STK_SIZE);
//		uart1.printf("task1£ºmem = %02d%%\r\n",mem);
//		mem = OS_GetStackMaxUsage(TASK_2_STK,TASK_2_STK_SIZE);
//		uart1.printf("task2£ºmem = %02d%%\r\n",mem);
//		mem = OS_GetStackMaxUsage(TASK_3_STK,TASK_3_STK_SIZE);
//		uart1.printf("task3£ºmem = %02d%%\r\n",mem);
		OS_TimeDelay(500);
	}

}


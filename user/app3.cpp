

/***********************************
功能说明：
此任务完成报警任务的执行，心跳的维护
************************************/
#include "ebox.h"
#include "includes.h"

float cpu;
INT16U mem;

u8 xintiaoBuf[] = "$,X,0,0,;";
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
				led_on();
				beep_on();			
			}
			else
			{
				led_off();
				beep_off();

			}
			if(warningTime > 0)	
			{
				if((warningTime*2 - count2) == 0)
				{
					warningState = 0;
					
					led_off();
					beep_off();
	
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
//		uart1.printf("task1：mem = %02d%%\r\n",mem);
//		mem = OS_GetStackMaxUsage(TASK_2_STK,TASK_2_STK_SIZE);
//		uart1.printf("task2：mem = %02d%%\r\n",mem);
//		mem = OS_GetStackMaxUsage(TASK_3_STK,TASK_3_STK_SIZE);
//		uart1.printf("task3：mem = %02d%%\r\n",mem);
		OS_DelayTimes(500);
	}

}


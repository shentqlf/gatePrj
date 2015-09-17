
#include "ebox.h"
#include "includes.h"
u8 task2count = 0;

#define LED PA1
#define BEEP_PIN PA2

#define JDQ1 PB4
#define JDQ2 PB5

PWM beep(BEEP_PIN,36,1000);

void task_2()
{
	
	JDQ1->mode(OUTPUT_PP);
	JDQ2->mode(OUTPUT_PP);
	
	beep.setDuty(0);

	LED->mode(OUTPUT_PP);
	
  while(1)
	{
//		task2count++;
//		uart1.printf("Task 2 Running!!!,runtimes = %d\r\n",task2count);
		///////////继电器1////////////////////////////////////////////////
		if(recvBuf[9] == '1')
		{
				JDQ1->set();
			sendBuf[5] = '1';

		}
		else if(recvBuf[9] == '0')
		{
					JDQ1->reset();	
			sendBuf[5] = '0';
		}
		//////////继电器2///////////////////////////////////////////////////////////
		if(recvBuf[11] == '1')
		{
				JDQ2->set();
			sendBuf[5+7] = '1';
		}
		else if(recvBuf[11] == '0')
		{
					JDQ2->reset();	
			sendBuf[5+7] = '0';
		}		
			/////////蜂鸣器/////////////////////////////////////////////////////
			if(recvBuf[13] == '1')
			{
				beep.setDuty(500);
				sendBuf[5+7*2] = '1';
			}
			else if(recvBuf[13] == '0')
			{
				beep.setDuty(0);
				sendBuf[5+7*2] = '0';
			}
			/////////LED//////////////////////////////////////////////////////////////////////
			
			if(recvBuf[15] == '1')
			{
				sendBuf[5+7*3] = '1';
				LED->set();
			}
			else if(recvBuf[15] == '0')
			{
				sendBuf[5+7*3] = '0';
			LED->reset();
			}
			msg.buf = sendBuf;
			uart1.printf("\r\n0.flag = %c",ctr[0].flag);
			uart1.printf("\r\n0.cmd = %c",ctr[0].cmd);
			uart1.printf("\r\n0.type = %c",ctr[0].type);
			uart1.printf("\r\n0.type = %c%c%c%c%c\r\n",ctr[0].para[0],ctr[0].para[1],ctr[0].para[2],ctr[0].para[3],ctr[0].para[4]);
			if(count>=1)
			count--;
			uart1.printf("\r\n1.flag = %c",ctr[1].flag);
			uart1.printf("\r\n1.cmd = %c",ctr[1].cmd);
			uart1.printf("\r\n1.type = %c",ctr[1].type);
			uart1.printf("\r\n1.type = %c%c%c%c%c\r\n",ctr[1].para[1],ctr[1].para[1],ctr[1].para[2],ctr[1].para[3],ctr[1].para[4]);
			
			if(count>=1)
			count--;
			
		//udp.send(&msg);
		//任务执行完成，挂起
		OS_TaskSuspend(TASK2_PRIO);
	}

}

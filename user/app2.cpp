
#include "ebox.h"
#include "includes.h"
u8 task2count = 0;

#define LED PA1
#define BEEP_PIN PA2

#define JDQ1 PB4
#define JDQ2 PB5

PWM beep(BEEP_PIN,36,1000);
extern TCPSERVER tcpServer;

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
			
		tcpServer.send(sendBuf,sizeof(sendBuf));
		//任务执行完成，挂起
		OS_TaskSuspend(TASK2_PRIO);
	}

}

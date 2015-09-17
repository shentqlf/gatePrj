
#include "includes.h"

#define APPDEBUG




PRO* currentPro;

u8 ackBuf[] = "$,Z,0,0;";
////////////////////////////
void connect(PRO* p)
{
	if(p->para[0] == '0')
		connectState = 0;
	else
		connectState = 1;
	
}
//警告命令处理
//$,1,0,1,;////////////////////
void warning(PRO* p)
{
	if(p->para[0] == '0')
		warningState = 0;
	else
		warningState = 1;

}
///继电器1/////////////////////////////////
void jdq1(PRO* p)
{
		if(p->para[0] == '0')
			PB10->write(0);
		else
			PB10->write(1);
}
PRO* getCMD()
{
	for(int i =0; i < 10;i ++)
		{
			if(ctr[i].flag == 1)
				return  &ctr[i];
		}
	return &ctr[0];
}
void exec(PRO* pro)
{
	
		if(pro->flag == 1)
		{
			switch(pro->cmd)
			{
				case '0':
					connect(pro);
					break;
				case '1':
					warning(pro);
					break;
				case '2':

					break;
				case '3':

					break;
				default :
					
					break;
		
			}
			ackBuf[4] = pro->cmd;
			ackBuf[6] = '1';
			msg.len =sizeof(ackBuf);
			msg.buf = ackBuf;

			udp.send(&msg);
			pro->flag = 0;

		}
}
void task_2()
{
	
	JDQ1->mode(OUTPUT_PP);
	JDQ2->mode(OUTPUT_PP);
	
	beep.setDuty(0);

	LED->mode(OUTPUT_PP);
	
  while(1)
	{
		currentPro = getCMD();
		exec(currentPro);
		OS_TimeDelay(10);
	}

}

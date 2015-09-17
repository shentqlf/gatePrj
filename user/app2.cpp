
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
			PB9->write(0);
		else
			PB9->write(1);
}
///继电器2/////////////////////////////////
void jdq2(PRO* p)
{
		if(p->para[0] == '0')
			PB10->write(0);
		else
			PB10->write(1);
}
//设置时间//////////////////////////////////
#include "stdlib.h"
void setTime(PRO* p)
{
	u8 str[6];
	u8 i = 0;
	str[0] = p->para[0];
	str[1] = p->para[1];
	str[2] = p->para[2];
	str[3] = p->para[3];
	str[4] = p->para[4];
	str[5] = '\0';
	warningTime = atof((const char*)str);
	

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
					ackBuf[6] = '1';
					break;
				case '1':
					warning(pro);
					ackBuf[6] = '1';
					break;
				case '2':
					jdq1(pro);
					ackBuf[6] = '1';
					break;
				case '3':
					jdq2(pro);
					ackBuf[6] = '1';
					break;				
				case '4':
					setTime(pro);
					ackBuf[6] = '1';
					break;
				default :
					
					ackBuf[6] = '0';
					break;
		
			}
			ackBuf[4] = pro->cmd;
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

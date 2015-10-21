
#include "includes.h"


PRO* currentPro;

u8 ackBuf[] = "$,Z,0,0;";
////////////////////////////
int connect(PRO* p)
{
	int ret;
	if(p->para[0] == '0')
	{
		connectState = 0;
		ret = 0;
	}
	else if(p->para[0] == '1')
	{
		connectState = 1;
		ret = 0;
	}
	else
	{
		ret = -1;
	}
	return ret;
	
}
//警告命令处理
//$,1,0,1,;////////////////////
int warning(PRO* p)
{
	int ret;
	if(p->para[0] == '0')
	{
		warningState = 0;	
		ret = 0;
	}
	else if(p->para[0] == '1')
	{
		warningState = 1;
		ret = 0;
	}
	else
		ret = -1;
	return ret;
}
///继电器1/////////////////////////////////
int jdq1(PRO* p)
{
	int ret;
		if(p->para[0] == '0')
		{
			jdq1_off();
			ret = 0;
		}
		else if(p->para[0] == '1')
		{
			jdq1_on();
			ret = 0;
		}
		else
			ret = -1;
		return ret;
}
///继电器2/////////////////////////////////
int jdq2(PRO* p)
{
	int ret;
		if(p->para[0] == '0')
		{
			jdq2_off();
			ret = 0;
		}
		else if(p->para[0] == '1')
		{
			jdq2_on();
			ret = 0;
		}
		else
			ret = -1;
		return ret;
}

//设置时间//////////////////////////////////
#include "stdlib.h"
int setTime(PRO* p)
{
	int ret = 0;
	u8 str[6];
	u8 i = 0;
	str[0] = p->para[0];
	str[1] = p->para[1];
	str[2] = p->para[2];
	str[3] = p->para[3];
	str[4] = p->para[4];
	str[5] = '\0';
	warningTime = atof((const char*)str);
	
	flash.write(0x10000,&warningTime,1);
	flash.read(0x10000,&warningTime,1);
	uart1.printf("setting:\r\n");
	uart1.printf("warnning time:%d!\r\n",warningTime);
	
	return ret;
}
PRO* getCMD()
{
	for(int i =0; i < 10;i ++)
		{
			if(ctr[i].flag == 1)
				return  &ctr[i];
		}
	return 0;
}
void exec(PRO* pro)
{
	int ret;
		if(pro->flag == 1)
		{
			switch(pro->cmd)
			{
				case '0':
					ret = connect(pro);
					if(ret == 0)
						ackBuf[6] = '1';
					else if(ret == -1)
						ackBuf[6] = '0';
					break;
				case '1':
					ret = warning(pro);
					if(ret == 0)
						ackBuf[6] = '1';
					else if(ret == -1)
						ackBuf[6] = '0';
					break;
				case '2':
					ret = jdq1(pro);
					if(ret == 0)
						ackBuf[6] = '1';
					else if(ret == -1)
						ackBuf[6] = '0';
					break;
				case '3':
					ret = jdq2(pro);
					if(ret == 0)
						ackBuf[6] = '1';
					else if(ret == -1)
						ackBuf[6] = '0';
					break;				
				case '4':
					ret = setTime(pro);
					if(ret == 0)
						ackBuf[6] = '1';
					else if(ret == -1)
						ackBuf[6] = '0';
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
	
  while(1)
	{
		currentPro = getCMD();
		exec(currentPro);
		OS_DelayTimes(10);
	}

}

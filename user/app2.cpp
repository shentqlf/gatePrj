/*
此任务并行处理接收到的命令
*/
#include "includes.h"


PRO* currentPro;

u8 ackBuf[] = "$,Z,0,0;";
////////////////////////////
int connect(PRO* p)
{
	int ret = 0;
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
	int ret = 0;
	if(connectState == 1)
	{
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
	}
	else
		ret = -2;
	return ret;
}
///继电器1/////////////////////////////////
int jdq1(PRO* p)
{
	int ret = 0;
	if(connectState == 1)
	{
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
	}
	else
		ret = -2;
		return ret;
}
///继电器2/////////////////////////////////
int jdq2(PRO* p)
{
	int ret = 0;
	if(connectState == 1)
	{

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
	}
	else
		ret = -2;
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
int set_host_left_right(PRO* p)
{
	int ret = 0;
	if(connectState == 1)
	{

		if(p->para[0] == '0')
		{
			host_state = 0;
            flash.write(0x10010,&host_state,1);
            flash.read(0x10010,&host_state,1);
            uart1.printf("setting:\r\n");
            uart1.printf("host :%d!\r\n",host_state);

			ret = 0;
		}
		else if(p->para[0] == '1')
		{
			host_state = 1;
            flash.write(0x10010,&host_state,1);
            flash.read(0x10010,&host_state,1);
            uart1.printf("setting:\r\n");
            uart1.printf("host :%d!\r\n",host_state);
			ret = 0;
		}
		else
			ret = -1;
	}
	else
		ret = -2;
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
void ack(int ret)
{
	switch(ret)
	{
		case 0://参数正常
			ackBuf[6] = '0';
		break;
		case -1://参数异常
			ackBuf[6] = '1';
		break;
		case -2://未连接
			ackBuf[6] = '2';
		break;
		default ://未知错误
			ackBuf[6] = '9';
		break;
	}
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
					break;
				case '1':
					ret = warning(pro);
					break;
				case '2':
					ret = jdq1(pro);
					break;
				case '3':
					ret = jdq2(pro);
					break;				
				case '4':
					ret = setTime(pro);
					break;
                case '6':
                    ret = set_host_left_right(pro);
                    break;
				default :
					ret = 9;
					break;
			}
			ack(ret);
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
		if(currentPro != 0)
			exec(currentPro);
		OS_DelayTimes(10);
	}

}

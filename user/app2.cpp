/*
1、从命令队列中获取未执行的命令，并执行

2、执行完成后向主机回复执行的结果
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
        ring_disconnect();
		ret = 0;
	}
	else if(p->para[0] == '1')
	{
		connectState = 1;
        ring_connect();
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
    if(connectState == 1)
	{
        if(p->para[0] < '0' || p->para[0] > '9')
            return -1;
        for(int j = 0; j < 5; j++)
        {
            if(p->para[j] < '0' || p->para[j] > '9')
                p->para[j] = '\0';
        }
        u8 str[6];
        u8 i = 0;
        str[0] = p->para[0];
        str[1] = p->para[1];
        str[2] = p->para[2];
        str[3] = p->para[3];
        str[4] = p->para[4];
        str[5] = '\0';
        warningTime = atof((const char*)str);
        
        flash.write(WARNING_TIME_FLASH_ADDR,&warningTime,1);
        flash.read(WARNING_TIME_FLASH_ADDR,&warningTime,1);
        uart1.printf("setting:\r\n");
        uart1.printf("warnning time:%d!\r\n",warningTime);
    }
    else
        ret = -2;	
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
            flash.write(HOST_STATE_FLASH_ADDR,&host_state,1);
            flash.read(HOST_STATE_FLASH_ADDR,&host_state,1);
            uart1.printf("setting:\r\n");
            uart1.printf("host :%d!\r\n",host_state);

			ret = 0;
		}
		else if(p->para[0] == '1')
		{
			host_state = 1;
            flash.write(HOST_STATE_FLASH_ADDR,&host_state,1);
            flash.read(HOST_STATE_FLASH_ADDR,&host_state,1);
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

int set_disp_mode(PRO* p)
{
	int ret = 0;
	if(connectState == 1)
	{

		if(p->para[0] == '0')
		{
			disp_mode = 0;
            disp_item(PIC_0_START);
			ret = 0;
		}
		else if(p->para[0] == '1')
		{
			disp_mode = 1;
            disp_item(PIC_3_ENTER);
            OS_DelayTimes(1);
            set_var_u16(VAR_3_NUM_ENTER,num_of_enter);
            OS_DelayTimes(1);
            set_var_u16(VAR_5_NUM_ENTER,num_of_enter);
            OS_DelayTimes(1);
			ret = 0;
		}
		else if(p->para[0] == '2')
		{
			disp_mode = 2;
            disp_item(PIC_2_OUT);
            OS_DelayTimes(1);
            set_var_u16(VAR_2_NUM_OUT,num_of_out);
            OS_DelayTimes(1);
            set_var_u32(VAR_5_NUM_OUT,num_of_out);
            OS_DelayTimes(1);
			ret = 0;
		}
		else if(p->para[0] == '3')
		{
			disp_mode = 3;
            disp_item(PIC_5_ENTER_OUT);
            OS_DelayTimes(1);
            set_var_u16(VAR_3_NUM_ENTER,num_of_enter);
            OS_DelayTimes(1);
            set_var_u16(VAR_5_NUM_ENTER,num_of_enter);
            OS_DelayTimes(1);
            set_var_u16(VAR_2_NUM_OUT,num_of_out);
            OS_DelayTimes(1);
            set_var_u32(VAR_5_NUM_OUT,num_of_out);
            OS_DelayTimes(1);
			ret = 0;
		}
		else
			ret = -1;
	}
	else
		ret = -2;
	return ret;
}
int set_num_enter_mode(PRO* p)
{
	int ret = 0;
	if(connectState == 1)
	{
        u8 str[6];
        u8 i = 0;
        if(p->para[0] < '0' || p->para[0] > '9')
            return -1;
        for(int j = 0; j < 5; j++)
        {
            if(p->para[j] < '0' || p->para[j] > '9')
                str[j] = '\0';
        }
        str[0] = p->para[0];
        str[1] = p->para[1];
        str[2] = p->para[2];
        str[3] = p->para[3];
        str[4] = p->para[4];
        str[5] = '\0';
        num_of_enter = atof((const char*)str);
        
        set_var_u16(VAR_3_NUM_ENTER,num_of_enter);
        set_var_u16(VAR_5_NUM_ENTER,num_of_enter);
        uart1.printf("num of enter:%d!\r\n",num_of_enter);
        
        return ret;
	}
	else
		ret = -2;
	return ret;
}
int set_num_out_mode(PRO* p)
{
	int ret = 0;
	if(connectState == 1)
	{
        u8 str[6];
        u8 i = 0;
        if(p->para[0] < '0' || p->para[0] > '9')
            return -1;
        for(int j = 0; j < 5; j++)
        {
            if(p->para[j] < '0' || p->para[j] > '9')
                str[j] = '\0';
        }
        str[0] = p->para[0];
        str[1] = p->para[1];
        str[2] = p->para[2];
        str[3] = p->para[3];
        str[4] = p->para[4];
        str[5] = '\0';
        num_of_out = atof((const char*)str);
        
        set_var_u16(VAR_2_NUM_OUT,num_of_out);
        set_var_u32(VAR_5_NUM_OUT,num_of_out);
        uart1.printf("num of OUT:%d!\r\n",num_of_out);
        
        return ret;
	}
	else
		ret = -2;
	return ret;
}
int set_local_ip(PRO* p)
{
	int ret = 0;
	if(connectState == 1)
	{
        int i = 0,j = 0,k=0;
        u8 str[6]={0};
        while(1)
        {
            str[k] = p->para[i];
            if(p->para[i] == '.' || p->para[i] == '\0')
            {
                str[k] = '\0';
                lip[j] = atof((const char*)str);
                j++;
                k=0;
            }
            else
            {
                k++;
            }
            i++;
            
            if(j>=4 && i <= MAX_LENGTH)
            {
                save_ip(lip);
                ret = 0;
                break;
            }
            
            if(i > MAX_LENGTH)//参数错误
            {
                ret = -1;
                break;
            }
        }        
        uart1.printf("IP : %d.%d.%d.%d\r\n", lip[0],lip[1],lip[2],lip[3]);
        ret = 0;
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
                case '7':
                    ret = set_disp_mode(pro);
                    break;
                case '8':
                    ret = set_num_enter_mode(pro);
                    break;
                case '9':
                    ret = set_num_out_mode(pro);
                    break;
                case 'A':
                    ret = set_local_ip(pro);
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
            pro->cmd = 0;
            pro->type = 0;
            for(int i = 0; i < MAX_LENGTH; i++)
                pro->para[i] = 0;

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

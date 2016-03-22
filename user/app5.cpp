/*
�������Ǻ�����������������Ľ������ͨ�����緢�͵�������
*/
#include "includes.h"
#define UNKNOW 0
#define IN  1
#define OUT 2
#define FIRST_IN 3
#define FIRST_OUT 4
#define DEFAULT 5

#define TIMEOUT   5000
u8 inout_buf_2[] = "$,5,0,0,;";

void out_one_2()
{
    uart1.printf("��ȥһ����\r\n");
    if(connectState == 1)
    {
        inout_buf_2[6] = '0';
        msg.len = sizeof(inout_buf_2);
        msg.buf = inout_buf_2;
        udp.send(&msg);
    }
}
void in_one_2()
{
    uart1.printf("����һ����\r\n");
    if(connectState == 1)
    {
        inout_buf_2[6] = '1';
        msg.len = sizeof(inout_buf_2);
        msg.buf = inout_buf_2;
        udp.send(&msg);
    }
}


void task_5()//ͳ�ƽ�����
{
    int status = DEFAULT;
    int delay_times = 500;
    static uint64_t last_time = 0;
    while(1)
    {
        
        switch(status)
        {
            case DEFAULT:
                if(read_hjs3() == 1)
                    status = FIRST_IN;
                if(read_hjs4() == 1)
                    status = FIRST_OUT;
                break;
            case FIRST_IN:
                if(read_hjs4() == 1)
                {
                    OS_DelayTimes(1000);
                    status = OUT;
                    if(host_state == 1)
                        out_one_2();
                    else
                        in_one_2();
                    status = DEFAULT;
                }
                break;
            case FIRST_OUT:
                if(read_hjs3() == 1)
                {
                    OS_DelayTimes(1000);
                    status = IN;
                    if(host_state == 1)
                        in_one_2();
                    else
                        out_one_2();
                    status = DEFAULT;
                }
                break;
            default:
                    status = DEFAULT;
            break;
        }
        OS_DelayTimes(10);
        
    }

}
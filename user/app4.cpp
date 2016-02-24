/*
此任务是红外事务处理，并将处理的结果发送通过网络发送到服务器
*/
#include "includes.h"
#define UNKNOW 0
#define IN  1
#define OUT 2
#define FIRST_IN 3
#define FIRST_OUT 4
#define DEFAULT 5

#define TIMEOUT   5000
u8 inout_buf[] = "$,5,0,0,;";

u8 host_state;
void out_one()
{
    uart1.printf("出去一个人\r\n");
    if(connectState == 1)
    {
        inout_buf[6] = '0';
        msg.len = sizeof(inout_buf);
        msg.buf = inout_buf;
        udp.send(&msg);
    }
}
void in_one()
{
    uart1.printf("进入一个人\r\n");
    if(connectState == 1)
    {
        inout_buf[6] = '1';
        msg.len = sizeof(inout_buf);
        msg.buf = inout_buf;
        udp.send(&msg);
    }
}


void task_4()
{
    int status = DEFAULT;
    int delay_times = 500;
    static uint64_t last_time = 0;
    while(1)
    {
        
        switch(status)
        {
            case DEFAULT:
                if(read_hjs1() == 1)
                    status = FIRST_IN;
                if(read_hjs2() == 1)
                    status = FIRST_OUT;
                break;
            case FIRST_IN:
                if(read_hjs2() == 1)
                {
                    OS_DelayTimes(1000);
                    status = OUT;
                    if(host_state == 1)
                        out_one();
                    else
                        in_one();
                    status = DEFAULT;
                }
                break;
            case FIRST_OUT:
                if(read_hjs1() == 1)
                {
                    OS_DelayTimes(1000);
                    status = IN;
                    if(host_state == 1)
                        in_one();
                    else
                        out_one();
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
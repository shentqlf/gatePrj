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
void task_4()
{
    int status = DEFAULT;
    int delay_times = 500;
    u32 last_time = 0;
    while(1)
    {
        if(status == DEFAULT)
        {
           if(read_hjs1() == 1)
           {
               OS_DelayTimes(delay_times);
               while(read_hjs1());
               status = FIRST_IN;
               last_time = millis();
               uart1.printf("FIRST IN\r\n");
           }
           if(read_hjs2() == 1)
           {
               OS_DelayTimes(delay_times);
               while(read_hjs2());
               status = FIRST_OUT;
               last_time = millis();
               uart1.printf("FIRST out\r\n");
          }
        }
        if(status == FIRST_IN)
        {
           if(read_hjs2() == 1)
           {
               OS_DelayTimes(delay_times);
               while(read_hjs2());
               status = IN;
               if(host_state == 1)
               {
                    uart1.printf("进入一个人\r\n");
                    inout_buf[6] = '1';
               }
               else
               {
                    uart1.printf("出去一个人\r\n");
                    inout_buf[6] = '2';
               }
                if(connectState == 1)
                {
                    msg.len = sizeof(inout_buf);
                    msg.buf = inout_buf;
                    udp.send(&msg);
                }

               status = DEFAULT;
          }
           if(read_hjs1() == 1)
           {
               OS_DelayTimes(delay_times);
               while(read_hjs1());
               status = UNKNOW;
                uart1.printf("未知状态\r\n");
                inout_buf[6] = '0';
                if(connectState == 1)
                {
                    msg.len = sizeof(inout_buf);
                    msg.buf = inout_buf;
                    udp.send(&msg);
                }
               status = DEFAULT;
           }
           if(millis() - last_time > TIMEOUT)
           {
               uart1.printf("超时\r\n");
               status = DEFAULT;
           }
        }        
        if(status == FIRST_OUT)
        {
           if(read_hjs1() == 1)
           {
               OS_DelayTimes(delay_times);
               while(read_hjs1());
               status = IN;
               if(host_state == 1)
               {
                    uart1.printf("出去一个人\r\n");
                    inout_buf[6] = '2';
               }
               else
               {
                    uart1.printf("进入一个人\r\n");
                    inout_buf[6] = '1';
               }
               
                if(connectState == 1)
                {
                    msg.len = sizeof(inout_buf);
                    msg.buf = inout_buf;
                    udp.send(&msg);
                }
               status = DEFAULT;
           }
           if(read_hjs2() == 1)
           {
               OS_DelayTimes(delay_times);
               while(read_hjs2());
               status = UNKNOW;
               uart1.printf("未知状态\r\n");
                inout_buf[6] = '0';
                if(connectState == 1)
                {
                    msg.len = sizeof(inout_buf);
                    msg.buf = inout_buf;
                    udp.send(&msg);
                }
               status = DEFAULT;
           }
           if(millis() - last_time > TIMEOUT)
           {
               uart1.printf("超时\r\n");
               status = DEFAULT;
           }

        }
        
    }

}
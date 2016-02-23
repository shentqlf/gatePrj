/*
接收数据，并将接收的数据复制到命令队列中
*/

#include "includes.h"

u16 len;


void task_1()
{

	while(1)
	{

		len = udp.recv(recvBuf);
		if(len > 0)
		{
			if(len>80)break;//超出最大命令缓冲区
			msg.len =len;
			msg.rIP = udp.remoteIP;
			msg.rPort = udp.remotePort;
			msg.buf = recvBuf;		
			deal(recvBuf,len);
		}
        btn.loop();
        if(btn.pressed_for(2000,1))
        {
            PB8.set();
            set_ip_as_default(lip);
            save_ip(lip);
        }
		OS_DelayTimes(10);
	}
}



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
		OS_DelayTimes(10);
	}
}

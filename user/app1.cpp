/*
�������ݣ��������յ����ݸ��Ƶ����������
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
			if(len>80)break;//��������������
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

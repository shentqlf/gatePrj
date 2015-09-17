

#include "ebox.h"
#include "os.h"
#include "includes.h"



	
u8 start[] = "\r\n===============\r\n";
u16 len;

UDPMessage msg;

void task_1()
{

	while(1)
	{
		btn.read();
		if(btn.click())
		{
			uart1.printf("btn click \r\n");
		}
		if(btn.release())
		{
			uart1.printf("btn release \r\n");
		}		
		if(btn.pressedFor(1000,2))
		{
			uart1.printf("btn long \r\n");
		}
		len = udp.recv(recvBuf);
		if(len > 0)
		{
//			uart1.printf("\r\n==================");
//			uart1.printf("\r\n客户端:%d.%d.%d.%d:%d",udp.remoteIP[0],udp.remoteIP[1],udp.remoteIP[2],udp.remoteIP[3],udp.remotePort);
//			uart1.printf("\r\n数据长度：%d",len);
//			uart1.printf("\r\n数据内容：");
//			uart1.printf((const char*)recvBuf);

			msg.len =len;
			msg.rIP = udp.remoteIP;
			msg.rPort = udp.remotePort;
			msg.buf = recvBuf;
			
//			udp.send(&msg);
			deal(recvBuf,len);
			//tcpServer.send(recvBuf,len);
			//唤醒任务2开始执行相关动作
			OS_TaskResume(TASK2_PRIO);

		}

		OS_TimeDelay(1);
	}
}



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
//			uart1.printf("\r\n�ͻ���:%d.%d.%d.%d:%d",udp.remoteIP[0],udp.remoteIP[1],udp.remoteIP[2],udp.remoteIP[3],udp.remotePort);
//			uart1.printf("\r\n���ݳ��ȣ�%d",len);
//			uart1.printf("\r\n�������ݣ�");
//			uart1.printf((const char*)recvBuf);

			msg.len =len;
			msg.rIP = udp.remoteIP;
			msg.rPort = udp.remotePort;
			msg.buf = recvBuf;
			
//			udp.send(&msg);
			deal(recvBuf,len);
			//tcpServer.send(recvBuf,len);
			//��������2��ʼִ����ض���
			OS_TaskResume(TASK2_PRIO);

		}

		OS_TimeDelay(1);
	}
}

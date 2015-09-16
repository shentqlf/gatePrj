

#include "ebox.h"
#include "os.h"
#include "includes.h"

#include "w5500.h"
#include "tcp.h"


	
u8 start[] = "\r\n===============\r\n";
u16 len;


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
		len = tcpServer.recv(recvBuf);
		if(len > 0)
		{
			uart1.printf("\r\n==================");
			uart1.printf("\r\n�ͻ���:%d.%d.%d.%d:%d",tcpServer.remoteIP[0],tcpServer.remoteIP[1],tcpServer.remoteIP[2],tcpServer.remoteIP[3],tcpServer.remotePort);
			uart1.printf("\r\n���ݳ��ȣ�%d",len);
			uart1.printf("\r\n�������ݣ�");
			uart1.printf((const char*)recvBuf);

			tcpServer.send(start,sizeof(start));
			//tcpServer.send(recvBuf,len);
			//��������2��ʼִ����ض���
			OS_TaskResume(TASK2_PRIO);

		}

		OS_TimeDelay(1);
	}
}

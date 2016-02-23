#include "ctrpro.h"

#define HEAD '$'
#define DOT ','
#define END ';'

#define NEEDHEAD 0
#define NEEDDOT  1
#define NEEDPARA  2

#define MAX 10

u8 state = NEEDHEAD;

PRO ctr[MAX];//ʮ��������������ڶ������
u8 cmdBuf[256];



void copycmd(PRO* dec,u8* sour,u8 len);
	u8 count = 0;
	u8 j = 0;

void deal(u8 * buf,u8 len)
{
	u8 i = 0;
	for(int k = 0;k< 256;k++)
	cmdBuf[k] = 0;
	while(i<len)
	{
		
		switch(state)
		{
			case NEEDHEAD:
				if(buf[i] == HEAD)
				{
					i++;					
					state = NEEDDOT;
				}
				else
				{
						i++;			
				}
				break;
			case NEEDDOT:
				if(buf[i] == DOT)
				{
					i++;
					state = NEEDPARA;
				}
				else
				{
					state = NEEDHEAD;
					i++;
				}
				break;
			case NEEDPARA:
				if(buf[i] == END)//�����⵽";"�������������������ݸ��Ƶ������б�
				{
					i++;
					copycmd(&ctr[count],cmdBuf,j);//j��cmdbuf�����ݳ���
					count++;
					if(count == MAX)count = 0;
					j=0;
					state = NEEDHEAD;
				}
				else if(buf[i] != DOT)//�������",",���ַ����ݸ��Ƶ�������
				{
					if(j<MAX_LENGTH + 2)//������Ʋ���22�ֽ�
						cmdBuf[j] = buf[i];//��������
					else
					{
						//����֡��ֱ���������б��ν��ܵ�����
						state = NEEDHEAD;
						i = 0;
						j = 0;
						count = 0;
						return;
					}
					j++;
					i++;				
				}
				else if(buf[i] == DOT)
				{
					i++;
				}
				break;
		}
	}
}
void copycmd(PRO* dec,u8* sour,u8 len)
{
	u8 i=0;
	uart1.printf("cmd location = %d\r\n",count);//ʹ�õڼ���������
//	uart3.printf("cmd location = %d\r\n",count);//ʹ�õڼ���������
	dec->flag = 1;
	dec->cmd = sour[i++];
	dec->type = sour[i++];
    for(int j = 0; j < len - 2; j++)//���������ݲ��ǲ�������
    {
        dec->para[j] = sour[i++];	
//        if(i==len)return;
    }
//	dec->para[1] = sour[i++];	
//	if(i==len)return;
//	dec->para[2] = sour[i++];	
//	if(i==len)return;
//	dec->para[3] = sour[i++];
//	if(i==len)return;
//	dec->para[4] = sour[i++];
//	if(i==len)return;
//	return;
	


}
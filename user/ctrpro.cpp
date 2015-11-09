#include "ctrpro.h"

#define HEAD '$'
#define DOT ','
#define END ';'

#define NEEDHEAD 0
#define NEEDDOT  1
#define NEEDPARA  2

#define MAX 10

u8 state = NEEDHEAD;

PRO ctr[MAX];//十个命令缓冲区，用于多命令处理
u8 cmdBuf[100];



void copycmd(PRO* dec,u8* sour,u8 len);
	u8 count = 0;
	u8 j = 0;

void deal(u8 * buf,u8 len)
{
	u8 i = 0;
	for(int k = 0;k< 100;k++)
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
				if(buf[i] == END)
				{
					i++;
					copycmd(&ctr[count],cmdBuf,j);
					count++;
					if(count == MAX)count = 0;
					j=0;
					state = NEEDHEAD;
				}
				else if(buf[i] != DOT)
				{
					if(j<8)
						cmdBuf[j] = buf[i];
					else
					{
						//错误帧，直接抛弃所有本次接受的内容
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
	uart1.printf("c = %d\r\n",count);//使用第几个缓冲区
	dec->flag = 1;
	dec->cmd = sour[i++];
	dec->type = sour[i++];
	dec->para[0] = sour[i++];	
	if(i==len)return;
	dec->para[1] = sour[i++];	
	if(i==len)return;
	dec->para[2] = sour[i++];	
	if(i==len)return;
	dec->para[3] = sour[i++];
	if(i==len)return;
	dec->para[4] = sour[i++];
	if(i==len)return;
	return;
	


}
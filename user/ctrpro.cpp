#include "ctrpro.h"

#define HEAD '$'
#define DOT ','
#define END ';'


PRO ctr[10];
u8 cmdBuf[50];

#define NEEDHEAD 0
#define NEEDDOT  1
#define NEEDPARA  2

#define A
u8 state = NEEDHEAD;
void copycmd(PRO* dec,u8* sour,u8 len);
	u8 count = 0;
	u8 j = 0;

void deal(u8 * buf,u8 len)
{
	u8 i = 0;
	for(int i = 0;i< 8;i++)
	cmdBuf[i] = 0;
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
				break;
			case NEEDPARA:
				if(buf[i] == END)
				{
					i++;
					copycmd(&ctr[count],cmdBuf,j);
					count++;
					j=0;
					state = NEEDHEAD;
				}
				else if(buf[i] != DOT)
				{
					cmdBuf[j++] = buf[i];
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
	dec->flag = 1;
	dec->cmd = sour[i++];
	dec->type = sour[i++];
	dec->para[0] = sour[i++];	if(i==len)return;
	dec->para[1] = sour[i++];	if(i==len)return;
	dec->para[2] = sour[i++];	if(i==len)return;
	dec->para[3] = sour[i++];	if(i==len)return;
	dec->para[4] = sour[i++];	if(i==len)return;
	return;
	


}
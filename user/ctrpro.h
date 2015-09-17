#ifndef __CTRPRO_H
#define __CTRPRO_H

#include "includes.h"
typedef struct 
{
	u8 flag;
	u8 cmd;
	u8 type;
	u8 para[5];
}PRO;

extern PRO ctr[10];
extern 	u8 count;
void deal(u8 * buf,u8 len);

#endif
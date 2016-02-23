#ifndef __CTRPRO_H
#define __CTRPRO_H

#include "includes.h"
#define MAX_LENGTH 20
typedef struct 
{
	u8 flag;
	u8 cmd;
	u8 type;
	u8 para[MAX_LENGTH];
}PRO;

extern  PRO ctr[10];
void deal(u8 * buf,u8 len);

#endif

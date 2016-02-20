
#include "ebox.h"

#define W_REG 0X80
#define R_REG 0X81
#define W_VAR_REG 0X82
#define R_VAR_REG 0X83
#define W_BUF 0X84

#define VERSION     0X01
#define LED_SET     0X02
#define PIC_ID      0X03

#define HEAD1 0XA5
#define HEAD2 0X5A

//图片地址
#define PIC_0_START       0
#define PIC_1_IN          1
#define PIC_2_OUT         2
#define PIC_3_ENTER       3
#define PIC_4_IN_ENTER    4
#define PIC_5_ENTER_OUT   5

//变量地址
#define VAR_1_NUM_IN        0X11
#define VAR_2_NUM_OUT       0X21
#define VAR_3_NUM_ENTER     0X31
#define VAR_4_NUM_IN        0X41
#define VAR_4_NUM_ENTER     0X46
#define VAR_5_NUM_ENTER     0X51
#define VAR_5_NUM_OUT       0X56



void disp_item(uint16_t item);
void set_var_u16(uint16_t reg,uint16_t data);
void set_var_u32(uint16_t reg,uint32_t data);
void disp_test();
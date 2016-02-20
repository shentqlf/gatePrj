#include "lcd_dwin.h"


typedef union 
{
    u16 u16;
    u8  u8[2];
}data16_t;

typedef union 
{
    u32 u32;
    u8  u8[4];
}data32_t;


void dwin_init()
{
    uart3.begin(115200);
    uart3.printf("uart3 is ok\r\n");
    disp_item(0);
    delay_ms(100);
}
void disp_item(uint16_t item)
{
    char buf[10];
    uint8_t len;
    uint8_t cmd;
    uint8_t reg;
    data16_t data16;
    
    len = 4;
    cmd = W_REG;
    reg = PIC_ID;
    data16.u16 = item;
    
    buf[0] = HEAD1;
    buf[1] = HEAD2;
    buf[2] = len;
    buf[3] = cmd;
    buf[4] = reg;
    buf[5] = data16.u8[1];
    buf[6] = data16.u8[0];
    
    uart3.printf_length(buf,7);
}
void set_var_u16(uint16_t reg,uint16_t data)
{
    char buf[10];
    uint8_t len;
    uint8_t cmd;
    data16_t reg16;
    data16_t data16;
    
    len = 5;
    cmd = W_VAR_REG;
    reg16.u16 = reg;
    data16.u16 = data;
    
    buf[0] = HEAD1;
    buf[1] = HEAD2;
    
    buf[2] = len;
    buf[3] = cmd;
    buf[4] = reg16.u8[1];
    buf[5] = reg16.u8[0];
    buf[6] = data16.u8[1];
    buf[7] = data16.u8[0];
    uart3.printf_length(buf,8);
}
void set_var_u32(uint16_t reg,uint32_t data)
{
    char buf[10];
    uint8_t len;
    uint8_t cmd;
    data16_t reg16;
    data32_t data32;
    
    len = 7;
    cmd = W_VAR_REG;
    reg16.u16 = reg;
    data32.u32 = data;
    
    buf[0] = HEAD1;
    buf[1] = HEAD2;
    
    buf[2] = len;
    buf[3] = cmd;
    buf[4] = reg16.u8[1];
    buf[5] = reg16.u8[0];
    
    buf[6] = data32.u8[3];
    buf[7] = data32.u8[2];
    buf[8] = data32.u8[1];
    buf[9] = data32.u8[0];
    
    uart3.printf_length(buf,10);
}
void disp_test()
{
    disp_item(PIC_2_OUT);
    delay_ms(10);
    set_var_u16(VAR_2_NUM_OUT,65535);
    delay_ms(1000);
    
    disp_item(PIC_3_ENTER);
    delay_ms(10);
    set_var_u16(VAR_3_NUM_ENTER,345);
    delay_ms(1000);
    
    disp_item(PIC_5_ENTER_OUT);
    delay_ms(10);
    set_var_u32(VAR_5_NUM_OUT,0x00ff);
    delay_ms(10);
    set_var_u16(VAR_5_NUM_ENTER,65535);
    delay_ms(1000);
        
}
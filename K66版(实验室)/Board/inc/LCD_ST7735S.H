#ifndef _VCAN_LCD_ST7735S_H_
#define _VCAN_LCD_ST7735S_H_

#include "MK66_gpio.h"
#include "enter.h"


//用户配置
#define ST7735S_DIR_DEFAULT     0       //定义默认方向 (0~3)

/********************* ST7735S内部实现 ***********************/
//LCD 的管脚定义
#define     LCD_ST7735S_WR      PTC9
#define     LCD_ST7735S_RD      PTC10
#define     LCD_ST7735S_CS      PTC11
#define     LCD_ST7735S_RS      PTC12
#define     LCD_ST7735S_RST     PTC13

//此部分需要修改初始化里的代码
#define     LCD_ST7735S_P0              PTC_B0_OUT
#define     LCD_ST7735S_PIN             PTC_B0_IN
#define     LCD_ST7735S_PDDR_OUT()      (DDRC_B0 = 0xff)    //DDR[X]_B[N]_OUT   ,X取 A~E ,N取0~3 。例如  DDRD_B3_OUT  表示 PTD 的Byte 3 ，即 PTD24~31
#define     LCD_ST7735S_PDDR_IN()       (DDRC_B0 = 0)

#define ST7735S_DELAY()                         //do{asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");asm("nop");}while(0)
#define ST7735S_DELAY_MS(ms)    DELAY_MS(ms)

extern lcd_t   lcd_st7735s;

#endif 

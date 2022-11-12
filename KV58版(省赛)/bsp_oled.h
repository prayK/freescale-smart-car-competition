#ifndef _OLED_H
#define _OLED_H
#include "Camera.h"
#define byte unsigned char //自己加的
#define word unsigned int //自己加的
#define LED_IMAGE_WHITE 255

extern uint8_t bmp_buff[4800]; 
extern uint8_t compress_buff[60][80]; 
extern uint8_t ImageBuffer[60][80]; 
 
extern const byte F6x8[][6];
extern void Image_Show();
void LCD_WrDat(byte data);
void LCD_WrCmd(byte cmd);
void LCD_Set_Pos(byte x, byte y); 
void LCD_Init(void); 
void LCD_CLS(void); 
void LCD_P6x8Str(byte x,byte y,byte ch[]);
void LCD_P8x16Str(byte x,byte y,byte ch[]);
void LCD_P14x16Str(byte x,byte y,byte ch[]);
void LCD_Print(byte x, byte y, byte ch[]);
void LCD_PutPixel(byte x,byte y);
void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
void Draw_LQLogo(void);
void Draw_LibLogo(void);
void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
void LCD_Fill(byte dat);
void oled_print_short(uint8_t uc_posx, uint8_t uc_posy, int16_t s_data);
void LED_PrintImage(byte *pucTable, uint16_t usRowNum, uint16_t usColumnNum);
void Draw_CameraBMP(byte x0,byte y0,byte x1,byte y1,uint8_t bmp[]);
void Display_uint8(uint8_t i,uint8_t x,uint8_t y) ;
void My_LCD_PutPixel(unsigned char x,unsigned char y);

#endif


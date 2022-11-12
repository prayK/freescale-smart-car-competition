#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;


void BOARD_InitBootPins(void);
void BOARD_InitPins(void); //摄像头场，行，像素IO初始化
void BOARD_InitData(void); //摄像头数据口初始化
void BOARD_InitOled(void); //OLED初始化
void BOARD_InitLed(void);  //led和蜂鸣器IO口初始化
void BOARD_InitMotorFtm(void);//电机
void BOARD_InitServoFtm(void);//舵机
void BOARD_InitUart(void);//串口IO口初始化
void BOARD_InitI2c(void); //IIC初始化，这里IO口被SCCB用了，很奇怪
void BOARD_InintButtons(void); //八位拨码开关IO初始化
void BOARD_InitFtmquad(void);  //编码器IO口初始化


#if defined(__cplusplus)
}
#endif

#endif 

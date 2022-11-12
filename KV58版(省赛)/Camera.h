#ifndef _CAMERA_H
#define _CAMERA_H
#include <stdint.h>
#include "fsl_device_registers.h"

#define IMAGE_SIZE    4

#if (IMAGE_SIZE  ==  0) 
#define User_Size    H_60_W_80 
#define OV7620_W    (80) 
#define OV7620_H    (60) 
///////////////////////////////////////////////////////////////////////////////////////////////////
 
#elif (IMAGE_SIZE == 1) 
#define User_Size    H_120_W_160 
#define OV7620_W    (160) 
#define OV7620_H    (120) 
 
#elif (IMAGE_SIZE == 2) 
#define User_Size    H_180_W_240 
#define OV7620_W    (240) 
#define OV7620_H    (180) 
 
#elif (IMAGE_SIZE == 3) 
#define User_Size    H_240_W_320 
#define OV7620_W    (320) 
#define OV7620_H    (240) 
///////////////////////////////////////////////////////////////////////////////////////////////////

#elif (IMAGE_SIZE == 4) 
#define User_Size    H_240_W_80 
#define OV7620_W    (80) 
#define OV7620_H    (240) 

#elif (IMAGE_SIZE == 5) 
#define User_Size    H_180_W_80 
#define OV7620_W    (80) 
#define OV7620_H    (180) 

#elif (IMAGE_SIZE == 6)  
#define User_Size    H_120_W_80 
#define OV7620_W    (80) 
#define OV7620_H    (120) 
///////////////////////////////////////////////////////////////////////////////////////////////////

#else 
#error "Image Size Not Support!" 
#endif 
 
#define BOARD_OV7620_PCLK_PORT      GPIOC
#define BOARD_OV7620_PCLK_PIN       (5)
#define BOARD_OV7620_VSYNC_PORT     GPIOC
#define BOARD_OV7620_VSYNC_PIN      (6)
#define BOARD_OV7620_HREF_PORT      GPIOC
#define BOARD_OV7620_HREF_PIN       (7)
#define BOARD_OV7620_DATA_OFFSET    (0) 
#define CMD_IMG     1
#define WaveSize    4
#define CAMERA_SIZE    (OV7620_W * OV7620_H/8 )
#define CAMERA_DMA_NUM (OV7620_W /8 )    //DMA采集次数
 
typedef enum
{
    Idle,
    Complete,
    Start,		
} Image_Status;

void Camera_Init(void);
void Send_Grayscale(void);
void OV7725_Eagle_DMA(void);
void OV7725_ISR(uint32_t index);
int  SCCB_Init(uint32_t I2C_MAP);
void Send_Binary(uint8_t *Image);
void VCAN_SendWare(void *wareaddr, uint32_t waresize);
void Img_Extract(uint8_t *Dst, uint8_t *Src, uint32_t Srclen);
void UART_WriteBytes(UART_Type *instance,  uint8_t *Buff, uint32_t Length);

extern uint8_t *img_buff;
extern float Ware[WaveSize];
extern volatile Image_Status Image_Flag;
extern uint8_t ImageBuffer[60][80];
extern uint8_t gImageBuffer[OV7620_H * OV7620_W / 8];
extern uint8_t eImageBuffer[(OV7620_H)*((OV7620_W/8)+1)];
extern uint8_t pImageBuffer[(OV7620_H)*((OV7620_W/8)+1)];
extern uint8_t Image_Distortion[OV7620_H][OV7620_W];


#endif

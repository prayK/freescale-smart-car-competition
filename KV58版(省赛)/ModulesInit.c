#include "speed.h"
#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "board.h"
#include "Camera.h"
#include "fsl_pit.h"
#include "fsl_ftm.h"
#include "fsl_port.h"
#include "fsl_edma.h"
#include "fsl_lptmr.h"
#include "fsl_dmamux.h"
#include <stdlib.h>
#include "stdio.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "it.h"
#include "speed.h"
#include "key_group.h"
#include "i2c.h"
#include "bsp_my_oled.h"
#include "bsp_oled.h"
#include "mpu6050.h"
#include "ModulesInit.h"
#include  "ServoControl.h"
#include "ImageInformation.h"

extern   uint8_t   imgbuff[CAMERA_SIZE];
extern   uint8_t   assist2;
extern   uint8_t   assist1;
extern   uint8_t   assist3;

uint8_t     CNST_Value = 60;

void  PIT0_IRQHandler(void);
void  PIT1_IRQHandler(void);
char  User_Stop_Line_JianCe(void);

/***系统初始化***/
void System_Init()
{ 
        //camera_init(imgbuff);
        /* Define the init structure for the input LED pin */   
        gpio_pin_config_t LED_config = {
                kGPIO_DigitalOutput, 1, //输出 1高电平 0低电平
        };
            gpio_pin_config_t buzz_config = {
                kGPIO_DigitalOutput, 0, //输出 1高电平 0低电平
        };
        //设置中断优先级	
        NVIC_SetPriorityGrouping(2);//设置优先级分组,3bit抢占优先级
        NVIC_SetPriority(PORTD_IRQn,0);
        NVIC_SetPriority(DMA0_DMA16_IRQn, 1);
        //NVIC_SetPriority(PIT0_IRQn,2);
 
        /*The Following is Modules Pin_Mux Create By Pray. Date:2018.6.25*/
        BOARD_InitPins();     //Camera /pclk/vsy/hse Pin D11,D10,D13
        BOARD_InitData();     //Camera Data Pin /D0-D7 
        BOARD_InitUART();     //Uart1_RX Pin  C3/ uart1_TX Pin C4 
        //BOARD_InitSCCB();     //Eagle SCCB(I2C1)E0,E1
        BOARD_InitI2c();
        BOARD_InitOled();     //OLED DC RST SDA SCL Pin/  C16 C17 C18 C19 
        BOARD_InitLed();      //Led Pin/A17  C0 D15 E29
        BOARD_InintButtons(); //Boma Pin/ E6 E7 E8 E9 E10 E11 E12 E16 
        BOARD_InitFtmquad();  //Quadrature Decoder //Ftm1 A B Pin/,A12 A13
        BOARD_InitFtm3();     //Servo Pin Init//Ftm3 CH0 E5
        BOARD_InitFtm0();     //Motor Pin Init//FTM0_CH0 FTM0_CH1,PTC1 PTC2
        BOARD_BootClockRUN(); //System Clock
        BOARD_InitDebugConsole(); //Debug控制台
 
        /*Usefr Modules Init*/
        LCD_Init();                            //User OlED Init
        KEY_Init();                            //User Key Init
        Camera_Init();                         //User Camera Init 
        MotorInit();                           //User Motor Init 
        ServoInit();                           //User Servo Init                                                         
        EncoderInit();                         //User Encoder Init
        GPIO_PinInit(GPIOA, 17, &LED_config);  //Red LED
        GPIO_PinInit(GPIOC,  0, &LED_config);  //Yellow LED
        GPIO_PinInit(GPIOD, 15, &LED_config);  //Blue LED
        GPIO_PinInit(GPIOE, 29, &LED_config);  //Green LED
        GPIO_PinInit(GPIOE, 22, &buzz_config); //Buzz  
        LCD_CLS(); 
} 
 
uint8_t flag_stopcar = 0; 
//void PIT0_IRQHandler(void) 
//{
//      if(PIT_TFLG(PIT0) == 1 )        
//      { 
//            PIT_Flag_Clear(PIT0);
//            if(User_Stop_Line_JianCe() == 1)
//            { 
//                  flag_stopcar = 1; 
//            }  
//            if(flag_stopcar==0)  
//            { 
//                    EncoderRead();
//                    GoalSpeedSet();
//                    MotorControl();
//            } 
//            else 
//            {
//                    FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, 0); 
//                    FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, 0); 
//            } 
//      } 
//}

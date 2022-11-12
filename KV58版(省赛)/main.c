#include "include.h" 

uint8_t  bmp_buff[4800]; 
uint8_t  compress_buff[60][80]; 
uint8_t  flag_imgbuff=0U; 
uint8_t  StopFlag = 0U; 
int16_t  Gyro = 0U; 
uint32_t instance; 
int16_t  accel[3] = {0},gyro[3] = {0}; 
extern int32_t EncoderCount; 
extern volatile uint16_t GoalSpeed; 
extern uint8_t StartLineFind_Flag; 
uint8_t  BOMAControlStopFlag = 0U; 
extern uint8_t StartDelay;

int main(void) 
{ 
          BOARD_BootClockRUN(); 
 
          gpio_pin_config_t LED_config  = {kGPIO_DigitalOutput, 1,}; 
          gpio_pin_config_t buzz_config = {kGPIO_DigitalOutput, 1,}; 
 
          /*设置中断优先级*/ 
          NVIC_SetPriorityGrouping(2); 
          NVIC_SetPriority(PORTC_IRQn, 0); 
          NVIC_SetPriority(DMA0_DMA16_IRQn, 1); 
 
          /*内部资源IO配置初始化*/ 
          BOARD_InitPins(); 
          BOARD_InitData(); 
          BOARD_InitI2c(); 
          BOARD_InitUart(); 
          BOARD_InitOled(); 
          BOARD_InitLed(); 
          BOARD_InintButtons(); 
          BOARD_InitFtmquad(); 
          BOARD_InitDebugConsole(); 
 
          /*外设初始化*/ 
          LCD_Init(); 
          KEY_Init();
          MotorInit(); 
          ServoInit(); 
          Camera_Init(); 
          FTM_quad_decoder_init(); 
          GPIO_PinInit(GPIOA, 17U, &LED_config); 
          GPIO_PinInit(GPIOC,  0U, &LED_config); 
          GPIO_PinInit(GPIOD, 15U, &LED_config); 
          GPIO_PinInit(GPIOE, 29U, &LED_config); 
          GPIO_PinInit(GPIOE, 22U, &buzz_config); 
          LCD_CLS(); 
 
          while (1) 
          { 
                  Key_Scan(); 
                  Switch_KeyEvenManage(); ////按键控制
                  BOMA_KeyEvenManage();/////拨码控制
                  if(Image_Flag == Complete) 
                  { 
                          flag_imgbuff = !flag_imgbuff; 
                          Image_Flag = Idle; 
                          PORT_SetPinInterruptConfig(PORTC, 6, kPORT_InterruptRisingEdge); 
                          EnableIRQ(PORTC_IRQn); 
                  } 
                  ImageIdentification(); 
                  IncrementalServoControl(); 
                  if (StartDelay == 1)
                  {
                            GoalSpeedSet(); 
                            if(User_Stop_Line_JianCe() == 1U && StartLineFind_Flag == 1U)// && BOMAControlStopFlag == 1U) 
                            { 
                                    StopFlag=1U;   
                            } 
                            if(StopFlag == 0U) 
                            { 
                                    MotorControl(); 
                            } 
                            else 
                            { 
                                    if (EncoderCount > 10) 
                                    { 
                                           GoalSpeed = 0U; 
                                           MotorControl(); 
                                    } 
                                    else 
                                    { 
                                           FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, 0U); 
                                           FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, 0U); 
                                           FTM_SetSoftwareTrigger(FTM0, true); 
                                    } 
                            } 
                  }
         } 
} 
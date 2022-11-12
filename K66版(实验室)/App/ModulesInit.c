#include "common.h"
#include "include.h"

extern   uint8   imgbuff[CAMERA_SIZE];
extern   uint8   assist2;
extern   uint8   assist1;
extern   uint8   assist3;

uint8     CNST_Value = 60;

void PIT0_IRQHandler(void);
void PIT1_IRQHandler(void);
char User_Stop_Line_JianCe(void);

/***系统初始化***/
void System_Init()
{ 
      lcd_init(WHITE);
      led_init(LED_MAX);
      gpio_init (PTA15, GPO,0);
      camera_init(imgbuff);
      ftm_quad_init(FTM1, FTM_PS_1, FTM1_QDPHA_PIN, FTM1_QDPHB_PIN);//A12
      ftm_pwm_init(FTM3, FTM_CH0, ServoFrequency, ServoCenterValue, FTM3_CH0_PIN); //PTE5
      ftm_pwm_init(FTM0, FTM_CH2, MotorFrequency, MotorInitDuty, FTM0_CH2_PIN);//PTA5
      ftm_pwm_init(FTM0, FTM_CH3, MotorFrequency, MotorInitDuty, FTM0_CH3_PIN);//PTA6
      pit_init_ms(PIT0, 10); 
      set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler); 
      set_vector_handler(PORTA_VECTORn , PORTA_IRQHandler); 
      set_vector_handler(DMA0_DMA16_VECTORn , DMA0_IRQHandler); 
      enable_irq (PIT0_IRQn); 
      
//      pit_init_ms(PIT1, 500);/////0.5秒切换成环内模式
//      set_vector_handler(PIT1_VECTORn ,PIT1_IRQHandler);
//      enable_irq (PIT1_IRQn); 
    
      NVIC_SetPriorityGrouping(3); //设置优先级分组,4bit 抢占优先级,没有亚优先
      NVIC_SetPriority(PORTA_IRQn , 0); //配置优先级  图像场中断  PORTA
      NVIC_SetPriority(DMA0_DMA16_IRQn  , 1); //配置优先级  图像  DMA0
      NVIC_SetPriority(PIT0_IRQn  , 2); //配置优先级  编码器   PIT0 
      //NVIC_SetPriority(PIT1_IRQn  , 3); //配置优先级  编码器   PIT0 
} 
 
uint8 flag_stopcar = 0; 
void PIT0_IRQHandler(void) 
{
      if(PIT_TFLG(PIT0) == 1 )        
      {
            PIT_Flag_Clear(PIT0);
            if(User_Stop_Line_JianCe() == 1)
            { 
                  flag_stopcar = 1; 
            }  
            if(flag_stopcar==0)  
            { 
                    EncoderRead();
                    GoalSpeedSet();
                    MotorControl();
            } 
            else 
            {
                    ftm_pwm_duty(FTM0, FTM_CH2, 0);
                    ftm_pwm_duty(FTM0, FTM_CH3, 0);  
            } 
      } 
}

//void PIT1_IRQHandler(void)
//{
//     if(assist2 == 1)
//     { 
//          assist1 = 0; 
//            assist3 = 1; 
//     } 
//    PIT_Flag_Clear(PIT0);       //清中断标志位
//}

/***拨码开关以及按键初始化***/
void Boma_Key_Init(void) 
{
      //八位拨码开关 
      gpio_init (PTA14, GPI,0); 
      port_init_NoALT (PTA14, ALT1 | PULLUP );

      gpio_init (PTA10, GPI,0);
      port_init_NoALT (PTA10, ALT1 | PULLUP );

      gpio_init (PTA8, GPI,0);
      port_init_NoALT (PTA8, ALT1 | PULLUP );

      gpio_init (PTE28, GPI,0);
      port_init_NoALT (PTE28, ALT1 | PULLUP );

      gpio_init (PTE26, GPI,0);
      port_init_NoALT (PTE26, ALT1 | PULLUP );

      gpio_init (PTE24, GPI,0);
      port_init_NoALT (PTE24, ALT1 | PULLUP );

      gpio_init (PTE27, GPI,0);
      port_init_NoALT (PTE27, ALT1 | PULLUP );

//      gpio_init (PTE25, GPI,0); 
//      port_init_NoALT (PTE25, ALT1 | PULLUP );

      //LCD按键
      //key_init(KEY_MAX);
}


/***像素 场中断服务函数***/
void PORTA_IRQHandler(void) 
{ 
     uint8  n; 
     uint32 flag; 

     while(!PORTA_ISFR); 
     flag = PORTA_ISFR; 
      PORTA_ISFR  = ~0; 
 
     n = 29;
     if(flag & (1 << n)) 
     { 
         camera_vsync(); 
     } 
}

/***DMA中断服务函数***/
void DMA0_IRQHandler(void) 
{ 
    camera_dma(); 
} 


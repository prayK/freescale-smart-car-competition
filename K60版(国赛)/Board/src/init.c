#include "init.h"
#include "include.h"

float dir_center = 4555;
extern uint8 imgbuff[CAMERA_SIZE];

void gpio_Init(void);
void PORTD_IRQHandler(void);
void DMA0_IRQHandler(void);

void init(void) 
{ 
          LCD_init();          //Һ����ʼ�� 
          ftm_quad_init(FTM2); //��ʼ���������� 
          camera_init(imgbuff);//�����ʼ�� 
          gpio_Init();         //�����Լ�����IO�ڳ�ʼ�� 
          Board_Gyro_Init();   //�����ǳ�ʼ�� 
          gpio_init (PTC0, GPO, 1);
          ftm_pwm_init(FTM0, FTM_CH2,10*1000,0); //�����ʼ��
          ftm_pwm_init(FTM0, FTM_CH3,10*1000,0); //�����ʼ��
          ftm_pwm_init(FTM1, FTM_CH0,250,(uint16)dir_center); //�����ʼ��
          set_vector_handler(PORTD_VECTORn , PORTD_IRQHandler);
          set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);
} 

void gpio_Init(void)
{ 
          //4λ���뿪��
          gpio_init (PTA12, GPI,0);         
          port_init (PTA12, ALT1 | PULLUP ); 
          
          gpio_init (PTA13, GPI,0);         
          port_init (PTA13, ALT1 | PULLUP ); 
          
          gpio_init (PTA14, GPI,0);         
          port_init (PTA14, ALT1 | PULLUP ); 
          
          gpio_init (PTA15, GPI,0);         
          port_init (PTA15, ALT1 | PULLUP );

          //LCD����
          gpio_init (PTA29, GPI,0);         //��
          port_init (PTA29, ALT1 | PULLUP ); 
        
          gpio_init (PTE26, GPI,0);         //��
          port_init (PTE26, ALT1 | PULLUP ); 
        
          gpio_init (PTA17, GPI,0);         //�� 
          port_init (PTA17, ALT1 | PULLUP );
        
          gpio_init (PTA9, GPI,0);          //��
          port_init (PTA9, ALT1 | PULLUP );
        
          gpio_init (PTE27, GPI,0);         //��
          port_init (PTE27, ALT1 | PULLUP );
}

void PORTD_IRQHandler(void)
{
          uint8  n;
          uint32 flag;

          while(!PORTD_ISFR);
          flag = PORTD_ISFR;
          PORTD_ISFR  = ~0;

          n =4;
          if(flag & (1 << n))
          {
                  camera_vsync();
          }
}

void DMA0_IRQHandler(void)
{
          camera_dma();
}

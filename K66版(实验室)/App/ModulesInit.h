#ifndef __MODULESINIT_H__
#define __MODULESINIT_H__

#define   ServoFrequency      300 
#define   MotorFrequency      10 * 1000 
#define   MotorInitDuty       0 
#define   ServoCenterValue    54.01 //Ô½Ð¡Ô½Íù×óÆ«//31.11

extern void  PORTA_IRQHandler(void);   
extern void  DMA0_IRQHandler(void);
extern void  System_Init(void);
extern void  lptmr_hander(void);
extern void  Boma_Key_Init(void);

#endif
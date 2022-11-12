#ifndef __KEY_GROUP_H
#define __KEY_GROUP_H

#define statusS1  GPIO_ReadPinInput(GPIOA,24)  
#define statusS2  GPIO_ReadPinInput(GPIOA,25) 
#define statusS3  GPIO_ReadPinInput(GPIOA,27) 

#define statusS4  GPIO_ReadPinInput(GPIOA,29) 
#define statusS5  GPIO_ReadPinInput(GPIOA,28) 
#define statusS6  GPIO_ReadPinInput(GPIOB, 4) 
#define statusS7  GPIO_ReadPinInput(GPIOB, 7) 
#define statusS8  GPIO_ReadPinInput(GPIOB, 5) 
 
#define statusB1  GPIO_ReadPinInput(GPIOE, 16) 
#define statusB2  GPIO_ReadPinInput(GPIOE, 12) 
#define statusB3  GPIO_ReadPinInput(GPIOE, 17) 
#define statusB4  GPIO_ReadPinInput(GPIOE, 10) 
#define statusB5  GPIO_ReadPinInput(GPIOE,  9) 
#define statusB6  GPIO_ReadPinInput(GPIOE,  8) 
#define statusB7  GPIO_ReadPinInput(GPIOE,  7) 
#define statusB8  GPIO_ReadPinInput(GPIOE,  6) 




void LostFlagDisplay(void);
void KEY_Init(void); 
void Key_Scan(void); 
void MainShow(void);
void SecondShow(void);
void ThirdShow(void);
void ForthShow(void);
void FifthShow(void);
void BOMA_KeyEvenManage(void);
void Switch_KeyEvenManage(void);

#endif
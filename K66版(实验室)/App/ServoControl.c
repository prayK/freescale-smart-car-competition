#include "common.h"
#include "include.h"
#include "ServoControl.h"

extern float ServoPDValue[2];
extern float ServoPValue[2]; 
extern uint8  Ring_Find_Flag; 
extern uint8  LeftRing_Find_Flag;
extern uint8  RightRing_Find_Flag;
float    ServoPIDCalculate; 
float    ServoOutPut; 
extern   int8   CurrentError; 
extern   float CenterValue; 
int8      LastError; 

/*二次P，PID算法*/
void IncrementalServoControl(void) 
{ 
              UseLineValueChangePValue();
              //UseTwicePValue();//只使用二次P
  
              //UseSticPValue();//静态P算法

              ServoPIDCalculate = (CenterValue + ServoPDValue[0] * CurrentError + ServoPDValue[1] * (CurrentError - LastError)); 
              if(ServoPIDCalculate < 0)  ServoPIDCalculate = 0; 
              ServoOutPut = ServoPIDCalculate; 
 
              if(ServoOutPut > ServoOutPutMax) ServoOutPut = ServoOutPutMax; 
              if(ServoOutPut < ServoOutPutMin) ServoOutPut = ServoOutPutMin;   
 
              LastError = CurrentError; 
 
              ftm_pwm_duty(FTM3, FTM_CH0, ServoOutPut); 
              ServoOutPut = 0; 
} 

/*舵机控制函数*/
void ServoControl(void)
{ 
       //ServoPIDCalculate=(int)(kp1 * duojijiaodu / 10 - kd * (lastpiancha_4 - duojijiaodu));
       //舵机的pid算法公式，没有小数，所以kp1要写整数再除以10来实现小数
       if(ServoOutPut > ServoOutPutMax) ServoOutPut = ServoOutPutMax; 
       if(ServoOutPut < ServoOutPutMin) ServoOutPut = ServoOutPutMin;   
       ftm_pwm_duty(FTM3, FTM_CH0, ServoOutPut); 
} 
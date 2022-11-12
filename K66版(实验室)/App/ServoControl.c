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

/*����P��PID�㷨*/
void IncrementalServoControl(void) 
{ 
              UseLineValueChangePValue();
              //UseTwicePValue();//ֻʹ�ö���P
  
              //UseSticPValue();//��̬P�㷨

              ServoPIDCalculate = (CenterValue + ServoPDValue[0] * CurrentError + ServoPDValue[1] * (CurrentError - LastError)); 
              if(ServoPIDCalculate < 0)  ServoPIDCalculate = 0; 
              ServoOutPut = ServoPIDCalculate; 
 
              if(ServoOutPut > ServoOutPutMax) ServoOutPut = ServoOutPutMax; 
              if(ServoOutPut < ServoOutPutMin) ServoOutPut = ServoOutPutMin;   
 
              LastError = CurrentError; 
 
              ftm_pwm_duty(FTM3, FTM_CH0, ServoOutPut); 
              ServoOutPut = 0; 
} 

/*������ƺ���*/
void ServoControl(void)
{ 
       //ServoPIDCalculate=(int)(kp1 * duojijiaodu / 10 - kd * (lastpiancha_4 - duojijiaodu));
       //�����pid�㷨��ʽ��û��С��������kp1Ҫд�����ٳ���10��ʵ��С��
       if(ServoOutPut > ServoOutPutMax) ServoOutPut = ServoOutPutMax; 
       if(ServoOutPut < ServoOutPutMin) ServoOutPut = ServoOutPutMin;   
       ftm_pwm_duty(FTM3, FTM_CH0, ServoOutPut); 
} 
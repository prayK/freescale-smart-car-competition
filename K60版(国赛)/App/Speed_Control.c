#include "include.h"
#include "Speed_Control.h"
#include <math.h>

extern uint8 ave_center; 
float SpeedP = 6, SpeedD = 15; 
 
//float Speed_Kp = 42, Speed_Ki = 6, Speed_Kd = 3.5;
float Speed_Kp = 50,Speed_Ki = 10,Speed_Kd = 0; 


int16 FTM_count = 0;
int32 AllFtmCount = 0;  
int16_t SpeedOutPut = 0,Speed_Ek0 = 0, Speed_Ek1 = 0, Speed_Ek2 = 0; 
int16_t SpeedCurrentError, SpeedLastError; 

uint16_t CalculateResult; 
uint16_t DutyGo = 0,DutyBack = 0; 
uint16_t speed_line[2]; 
volatile uint16_t GoalSpeed = 270U; 

extern uint8_t LeftRing_Find_Flag; 
extern uint8_t RightRing_Find_Flag; 
extern uint8_t LeftRingReadyIn;
extern uint8_t RightRingReadyIn;
extern uint8_t assist4, assistr4; 
extern uint8_t ReduceLeftRingSpeed;
extern uint8_t ReduceRightRingSpeed;
extern uint8_t za_flag, zhangai;


void Encoder_Read(void) 
{
         FTM_count = ftm_quad_get(FTM2); 
         AllFtmCount = FTM_count + AllFtmCount;
         if(FTM_count<0) FTM_count=0; 
         ftm_quad_clean(FTM2); 
} 

int16 S_Error;
float a,b;
float Speed_S = 160,Speed_M = 210,Speed_H = 280; 

float RingSpeed = 165;         //Ĭ�ϻ����ٶ�
float InRingSpeed = 165;       //Ĭ�Ͻ������ٶ�
float OutRingSpeed = 150;      //Ĭ�ϳ������ٶ�
float PassObstructSpeed = 190; //Ĭ��ͨ���ϰ����ٶ�
float TheMostSlowSpeed = 130;  //Ĭ�������ٶ�

//ĥ��̥�ĳ�
//float Speed_S = 120,Speed_M = 160,Speed_H = 180;
//float RingSpeed = 180;      //Ĭ�ϻ����ٶ�
//float InRingSpeed = 160;    //Ĭ�Ͻ������ٶ�
//float OutRingSpeed = 140;   //Ĭ�ϳ������ٶ�
//float PassObstructSpeed = 150;   //Ĭ��ͨ���ϰ����ٶ�

extern uint8 ave_center_s;
extern float bian_bi,bian_ca;
extern uint8_t assistr5, assist5; 

void Speed_Set(void) //���ݲ�ͬ����������������ٶ�
{         
  if (BM3 == 1)
  {
         S_Error = ave_center_s - 40; 
         if(S_Error<0) S_Error = -S_Error; 
         if(S_Error>20) S_Error = 20; 
         
         a = (Speed_H - Speed_S)/20;
         b = Speed_H;
         GoalSpeed = (uint16)(-a * S_Error + b);
 
         if((GoalSpeed-(uint16)Speed_S)>(uint16)((Speed_H-Speed_S)*bian_bi))//�����ٶ�ʱ ��ֹ�������ȼ���  ����ɨ�赽��������ȷ���ٶ� 
         { 
                GoalSpeed = (uint16)((Speed_H-Speed_S) * bian_bi+Speed_S);//��������޷�
         } 

         if((GoalSpeed-(uint16)Speed_S)>(uint16)((Speed_H-Speed_S)*bian_ca))//��������޷�
         { 
                GoalSpeed = (uint16)((Speed_H-Speed_S) * bian_ca+Speed_S); 
         } 
         
         if (LeftRing_Find_Flag || RightRing_Find_Flag) //�����ٶ�
                  GoalSpeed = (uint16_t)RingSpeed;
         if (RightRingReadyIn || LeftRingReadyIn)         //�������ٶ�
                  GoalSpeed = (uint16_t)InRingSpeed;
         if (assist4 || assistr4)                         //�������ٶ�
                  GoalSpeed = (uint16_t)OutRingSpeed;
         if (za_flag)
                  GoalSpeed = (uint16_t)PassObstructSpeed;  //ͨ���ϰ����ٶ�
  }
  if(BM3 == 0)
  {
        GoalSpeed = (uint16_t)TheMostSlowSpeed;//���������£��㶨�����ٶ�����
  }
} 

void SpeedControl(void) //pid�㷨�ó�������ֵ����
{
          Speed_Ek0 = GoalSpeed - FTM_count; 
 
          SpeedOutPut= (int16_t)( SpeedOutPut 
                                   + (int16_t)(Speed_Kp * (Speed_Ek0 - Speed_Ek1)) 
                                   + (int16_t)(Speed_Ki * (Speed_Ek0)) 
                                   + (int16_t)(Speed_Kd * (Speed_Ek0 - 2 * Speed_Ek1 + Speed_Ek2)) 
                                 ); 
          Speed_Ek2 = Speed_Ek1; 
          Speed_Ek1 = Speed_Ek0; 
 
          if ( SpeedOutPut > 8000 ) SpeedOutPut  = 8000; 
          else if ( SpeedOutPut < (int16_t) -8000 ) SpeedOutPut = -8000; 
 
          if(SpeedOutPut > 0) 
          { 
                  DutyGo = (uint16_t)SpeedOutPut; 
                  DutyBack = 0; 
          } 
          else 
          { 
                  DutyGo = 0; 
                  DutyBack = (uint16_t)(-SpeedOutPut); 
          } 
          ftm_pwm_duty(FTM0, FTM_CH2, (uint16)DutyGo); 
          ftm_pwm_duty(FTM0, FTM_CH3, (uint16)DutyBack); 
          
          speed_line[0]=(uint16)FTM_count;
          speed_line[1]=(uint16)GoalSpeed;
          vcan_sendware(speed_line,sizeof(speed_line));
}



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

float RingSpeed = 165;         //默认环岛速度
float InRingSpeed = 165;       //默认进环岛速度
float OutRingSpeed = 150;      //默认出环岛速度
float PassObstructSpeed = 190; //默认通过障碍物速度
float TheMostSlowSpeed = 130;  //默认最慢速度

//磨轮胎的车
//float Speed_S = 120,Speed_M = 160,Speed_H = 180;
//float RingSpeed = 180;      //默认环岛速度
//float InRingSpeed = 160;    //默认进环岛速度
//float OutRingSpeed = 140;   //默认出环岛速度
//float PassObstructSpeed = 150;   //默认通过障碍物速度

extern uint8 ave_center_s;
extern float bian_bi,bian_ca;
extern uint8_t assistr5, assist5; 

void Speed_Set(void) //根据不同赛道情况建立基本速度
{         
  if (BM3 == 1)
  {
         S_Error = ave_center_s - 40; 
         if(S_Error<0) S_Error = -S_Error; 
         if(S_Error>20) S_Error = 20; 
         
         a = (Speed_H - Speed_S)/20;
         b = Speed_H;
         GoalSpeed = (uint16)(-a * S_Error + b);
 
         if((GoalSpeed-(uint16)Speed_S)>(uint16)((Speed_H-Speed_S)*bian_bi))//计算速度时 防止弯道大幅度加速  根据扫描到的行数来确定速度 
         { 
                GoalSpeed = (uint16)((Speed_H-Speed_S) * bian_bi+Speed_S);//纵向弯道限幅
         } 

         if((GoalSpeed-(uint16)Speed_S)>(uint16)((Speed_H-Speed_S)*bian_ca))//横向弯道限幅
         { 
                GoalSpeed = (uint16)((Speed_H-Speed_S) * bian_ca+Speed_S); 
         } 
         
         if (LeftRing_Find_Flag || RightRing_Find_Flag) //环岛速度
                  GoalSpeed = (uint16_t)RingSpeed;
         if (RightRingReadyIn || LeftRingReadyIn)         //进环岛速度
                  GoalSpeed = (uint16_t)InRingSpeed;
         if (assist4 || assistr4)                         //出环岛速度
                  GoalSpeed = (uint16_t)OutRingSpeed;
         if (za_flag)
                  GoalSpeed = (uint16_t)PassObstructSpeed;  //通过障碍物速度
  }
  if(BM3 == 0)
  {
        GoalSpeed = (uint16_t)TheMostSlowSpeed;//拨码三拨下，恒定最慢速度跑完
  }
} 

void SpeedControl(void) //pid算法得出电机输出值驱动
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



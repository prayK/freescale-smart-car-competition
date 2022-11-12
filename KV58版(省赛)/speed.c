#include "include.h" 

extern uint8_t Ring_Find_Flag, LeftRing_Find_Flag ; 
extern uint8_t RightRing_Find_Flag;

uint32_t speed_line[2]; 
volatile uint16_t GoalSpeed = 40U; 
int32_t EncoderCount = 0U;
float Speed_Kp = 44,Speed_Ki = 10,Speed_Kd = 13;
int16_t SpeedOutPut = 0,Speed_Ek0 = 0, Speed_Ek1 = 0, Speed_Ek2 = 0; 
uint16_t DutyGo = 0,DutyBack = 0; 

//电机初始化  
void MotorInit(void) 
{ 
        ftm_config_t ftm0Info;
        ftm_chnl_pwm_signal_param_t ftmParam[2];
 
        ftmParam[0].chnlNumber = kFTM_Chnl_0;    //PWM通道
        ftmParam[0].level = kFTM_HighTrue;       //PWM有效信号(高电平有效)
        ftmParam[0].dutyCyclePercent = 0U;       //PWM初始化duty(0)
        ftmParam[0].firstEdgeDelayPercent = 0U;  //PWM第一时钟沿延时(0)
 
        ftmParam[1].chnlNumber = kFTM_Chnl_1; 
        ftmParam[1].level = kFTM_HighTrue; 
        ftmParam[1].dutyCyclePercent = 0U; 
        ftmParam[1].firstEdgeDelayPercent = 0U; 
 
        BOARD_InitMotorFtm(); ///电机FTMIO口初始化
        FTM_GetDefaultConfig(&ftm0Info);//获取IO口配置
        ftm0Info.chnlPolarity = 0; 
        FTM_Init(FTM0, &ftm0Info); 
        /////////////////////////////2路/////////////////////10KHZ/////////////////////
        FTM_SetupPwm(FTM0, ftmParam, 2U, kFTM_EdgeAlignedPwm, 10000U, FTM1_SOURCE_CLOCK);
        FTM_StartTimer(FTM0, kFTM_SystemClock); 
        FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, 0);
        FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, 0);
        FTM_SetSoftwareTrigger(FTM0, true); 
} 
 
//编码器初始化FTM1_QDPHA B0，FTM1_QDPHB B1 
void FTM_quad_decoder_init(void) 
{ 
        ftm_phase_params_t phAparams,phBparams;
 
        phAparams.enablePhaseFilter = false; 
        phAparams.phaseFilterVal = 0x00U; 
        phAparams.phasePolarity = kFTM_QuadPhaseNormal; 
        phBparams.enablePhaseFilter = false;  
        phBparams.phaseFilterVal = 0x00U; 
        phBparams.phasePolarity = kFTM_QuadPhaseNormal;
 
        CLOCK_EnableClock(kCLOCK_Ftm1);
        FTM_SetupQuadDecode(FTM1, &phAparams, &phBparams, kFTM_QuadCountAndDir);
        FTM_ClearQuadDecoderCounterValue(FTM1);
} 

//获取编码器的脉冲 
void CalSpeedError(void) 
{ 
        EncoderCount = FTM_GetQuadDecoderCounterValue(FTM1);//获取脉冲数
        if(EncoderCount<0)  EncoderCount=0;
        FTM_ClearQuadDecoderCounterValue(FTM1);//清空计数
} 
 
extern uint8_t ave_center;
float SpeedP = 5, SpeedD = 10; 
int16_t SpeedCurrentError, SpeedLastError;
uint16_t CalculateResult;
extern uint8_t QFlag; 
extern uint8_t assist4, assistr4; 
uint8_t HighSpeed = 74;////默认全局速度
uint8_t RingSpeed = 37;////默认环岛速度
extern uint8_t za_flag_r, za_flag_l, za_flag, zhangai, shi_flag; 
extern float D_P1, D_P, D_D;
uint8_t speed_low = 40, speed_high = 80;
float a,b; 

//目标速度设定 
void GoalSpeedSet(void) 
{ 
         SpeedCurrentError = ave_center - 40; 
 
         if (SpeedCurrentError < 0) SpeedCurrentError = -SpeedCurrentError; 
 
         CalculateResult = (uint16_t)(SpeedP * SpeedCurrentError 
                                      + SpeedD * (SpeedCurrentError - SpeedLastError)); 
 
         if (CalculateResult > 35) CalculateResult = 35; 
         GoalSpeed = HighSpeed - CalculateResult; 
 
         SpeedLastError = SpeedCurrentError; 
         if (SpeedLastError < 0) SpeedLastError = -SpeedLastError; 
 
//         if (LeftRing_Find_Flag == 1 || RightRing_Find_Flag == 1) 
//         { 
//               GoalSpeed = RingSpeed; 
//         } 
//         
//        a = sqrt((speed_high - speed_low) / 400);
//        b = speed_low;
//        GoalSpeed = (uint16_t)((a * (SpeedCurrentError - 20)) * (a * (SpeedCurrentError - 20)) + b); 
// 
//        a = (speed_high - speed_low) / 20;
//        b = speed_high;
//        GoalSpeed = (uint16_t)(-a * SpeedCurrentError + b); 
} 

//电机pid输出速度 
void MotorControl(void) 
{ 
          CalSpeedError();           
          Speed_Ek0 = GoalSpeed - EncoderCount; 
 
          SpeedOutPut= (int16_t)( SpeedOutPut
                                   + (int16_t)(Speed_Kp * (Speed_Ek0 - Speed_Ek1)) 
                                   + (int16_t)(Speed_Ki * (Speed_Ek0)) 
                                   + (int16_t)(Speed_Kd * (Speed_Ek0 - 2 * Speed_Ek1 + Speed_Ek2)) 
                                 ); 
          Speed_Ek2 = Speed_Ek1; 
          Speed_Ek1 = Speed_Ek0; 
 
          if ( SpeedOutPut > 600 ) SpeedOutPut  = 600; 
          else if ( SpeedOutPut < (int16_t) -600 ) SpeedOutPut = -600; 
 
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
          FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_0, kFTM_EdgeAlignedPwm, (uint16_t)DutyGo); 
          FTM_UpdatePwmDutycycle(FTM0, kFTM_Chnl_1, kFTM_EdgeAlignedPwm, (uint16_t)DutyBack);
          FTM_SetSoftwareTrigger(FTM0, true); 
} 

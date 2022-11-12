#include "include.h" 
 
extern uint8_t ave_center;
uint16_t CenterValue; 
uint16_t ServoOutPut;
int16_t ServoPIDCalculate; 
int16_t CurrentError; 
int16_t LastError; 
float ServoPValue[2] = {2.5, 48}; 
float ServoPDValue[2] = {5.7, 14}; 
extern uint8_t LeftRing_Find_Flag,RightRing_Find_Flag; 
float D_P1=3.8, D_P=3.8, D_D=100;
extern int16_t CurrentError; 
extern uint8_t assist3; 
extern uint8_t assistr3; 
extern uint8_t TempError; 
extern uint8_t assist4, assistr4; 
float RingP = 3.6;

/*舵机初始化FTM3_CH6 PTE11*/ 
void ServoInit(void) 
{ 
        ftm_config_t ftm3Info;
        ftm_chnl_pwm_signal_param_t ftmParam[1];

        /* Configures the FTM parameters with frequency 300 HZ */
        ftmParam[0].chnlNumber = kFTM_Chnl_6; 
        ftmParam[0].level = kFTM_HighTrue; 
        ftmParam[0].dutyCyclePercent = 540U; 
        ftmParam[0].firstEdgeDelayPercent = 0U; 
 
        BOARD_InitServoFtm();//舵机IO口初始化
        FTM_GetDefaultConfig(&ftm3Info); 
        ftm3Info.reloadPoints = kFTM_CntMax;
        ftm3Info.chnlPolarity = 0; 
        FTM_Init(FTM3, &ftm3Info); 
 
        /////////////////////////////1路/////////////////////300HZ/////////////////////
        FTM_SetupPwm(FTM3, ftmParam, 1U, kFTM_EdgeAlignedPwm, 300U, SystemMCGFFClock);  
        FTM_StartTimer(FTM3, kFTM_FixedClock); 
        FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_6, kFTM_EdgeAlignedPwm, ServoCenterValue);
        FTM_SetSoftwareTrigger(FTM3, true); 
} 
 
/*二次P，PID算法*/ 
void IncrementalServoControl(void) 
{ 
             CenterValue = (uint16_t)ServoCenterValue; 
             CurrentError = ave_center - 40; 
 
             if (LeftRing_Find_Flag == 1 || RightRing_Find_Flag == 1) 
             { 
                    D_P=RingP;
                    D_D=0;
             } 
             if (assist4 == 1 || assistr4 == 1)
             { 
                    D_P=4.9;
                    D_D=0;
             } 

             ServoPIDCalculate = (uint16_t)(CenterValue 
                                            + (D_P1 * CurrentError * CurrentError / 1000 + D_P) * CurrentError
                                            + D_D * (CurrentError - LastError));
             
             if(ServoPIDCalculate < 0)  ServoPIDCalculate = 0; 
             ServoOutPut = ServoPIDCalculate; 
 
             if(ServoOutPut > ServoOutPutMax) ServoOutPut = ServoOutPutMax; 
             if(ServoOutPut < ServoOutPutMin) ServoOutPut = ServoOutPutMin; 
 
             FTM_UpdatePwmDutycycle(FTM3, kFTM_Chnl_6, kFTM_EdgeAlignedPwm, (uint16_t)ServoOutPut);
             FTM_SetSoftwareTrigger(FTM3, true); 
             LastError = CurrentError; 
} 

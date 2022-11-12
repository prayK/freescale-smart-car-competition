#ifndef __CAR_CONCTROL_H__
#define __CAR_CONCTROL_H__
#include "include.h"

extern volatile uint16_t GoalSpeed;
extern float dir_center;
extern float dir_zhongzhi;
extern uint32 sizetmp;
extern uint32 img_MAX;
extern int16  FTM_count;
extern uint8_t assist4,assistr4; 
extern uint8_t LeftRingReadyIn;
extern uint8_t RightRingReadyIn;
extern uint8_t assist3,assistr3; 
extern float Speed_S, Speed_M, Speed_H;
extern float PassObstructSpeed;   //默认通过障碍物速度
extern float RingSpeed;     //默认环岛期望速度 
extern float InRingSpeed;   //默认进环岛期望速度
extern float OutRingSpeed;  //默认出环岛期望速度
extern float TheMostSlowSpeed; 
extern float Speed_Kp, Speed_Ki, Speed_Kd;
extern float InLeftRingV;   //进左环岛转向偏置
extern float InRightRingV;  //进右环岛转向偏置
extern float OutLeftRingV;  //出左环岛转向偏置
extern float OutRightRingV; //出右环岛转向偏置
extern uint8_t StreetCalWdith;  //第20行有黑点右边
extern uint8_t StreetCalWdith0; //第20行有黑点左边
extern uint8_t StreetCalWdith1; //第50行有黑点右边
extern uint8_t StreetCalWdith2; //第35行有黑点右边
extern uint8_t StreetCalWdith3; //第50行有黑点左边
extern uint8_t StreetCalWdith4; //第35行有黑点左边
extern uint8_t StreetCalWdith5; //第30行有黑点右边
extern uint8_t StreetCalWdith6; //第53行有黑点左边
extern uint8_t StreetCalWdith7; //第30行有黑点左边
extern uint8_t StreetCalWdith8; //第53行有黑点右边
extern uint8_t StreetCalWdith9; //第45行有黑点左边
extern uint8_t bian_line[120]; 

extern uint8_t StreetCalWdith16;////消除左环岛误判
extern uint8_t StreetCalWdith12;
extern uint8_t StreetCalWdith10;////消除左环岛误判
extern uint8_t StreetCalWdith6;

extern uint8_t StreetCalWdithL16;////消除右环岛误判
extern uint8_t StreetCalWdithL12;
extern uint8_t StreetCalWdithL10;////消除右环岛误判
extern uint8_t StreetCalWdithL6;

extern uint8_t StreetCalLong30; 
extern uint8_t StreetCalLong50; 
extern float QZ_End;
extern float QZ_Top;
extern float Param;//定距离为几米
extern float QZ_End;
extern float QZ_Top;
extern uint8_t bian_line[120]; 
extern uint8_t assistr3;  
extern uint8_t ave_center;
extern uint8_t StreetCalLong;
extern uint8_t bian_line[120]; 
extern uint8_t Ring_Find_Flag;
extern uint8_t StreetCalWdith6; 
extern uint8_t img[60][CAMERA_W];
extern uint8_t LeftRing_Find_Flag; 
extern uint8_t RightRing_Find_Flag; 
extern uint8_t imgbuff[CAMERA_SIZE];
extern uint16_t DutyGo; 
extern Site_t sit_R[60]; 
extern Site_t sit_L[60]; 
extern Site_t center_line[60];
extern volatile uint16_t GoalSpeed; 
extern uint8_t za_flag, zhangai;

extern float L_Cur_K; //左圆环补线斜率
extern float R_Cur_K; //右圆环补线斜率
extern uint8_t assistr4, assist4; 
extern uint8_t assistr5, assist5; 
//extern Coord Angle;
extern char Start_Gyro_Z_Flag;
extern char Start_Gyro_X_Flag;
extern char Start_Gyro_Y_Flag;


void image_watch_fun(void);
void speed_change_fun();
void ring_set_fun();
void ParameterWatching_fun(void);
void dir_change_fun();

extern void run(void);
extern void speed_control(void);
extern void speed_changeSet(void);

#endif
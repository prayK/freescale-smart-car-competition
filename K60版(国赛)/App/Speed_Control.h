#ifndef __SPEED_CONCTROL_H__
#define __SPEED_CONCTROL_H__
#include "include.h"

void  SpeedControl(void) ;
void  Encoder_Read(void);
void Speed_Set(void);
void User_Moto_ChaSu(int16 *left_speed, int16 *right_speed, int16 bash_speed, uint16 angle_pwm);

#endif
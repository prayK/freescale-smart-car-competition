#ifndef __SERVOCONTROL_H__
#define __SERVOCONTROL_H__
#include "fsl_clock.h"
 
#define ServoOutPutMax    670
#define ServoOutPutMin    430
#define ServoCenterValue  526 //ԽСԽ����ƫ 
 
extern void ServoInit(void);
extern void IncrementalServoControl(void);

#endif 

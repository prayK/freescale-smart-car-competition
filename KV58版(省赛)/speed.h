#ifndef __SPEED_H__
#define __SPEED_H__

#include "fsl_ftm.h"
#include "stdint.h"

#define FTM1_SOURCE_CLOCK     CLOCK_GetFreq(kCLOCK_FastPeriphClk)

void MotorInit(void);
void FTM_quad_decoder_init(void);
void CalSpeedError(void);
void GoalSpeedSet(void);
void MotorControl(void);

#endif
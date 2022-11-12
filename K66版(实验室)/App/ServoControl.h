#ifndef __SERVOCONTROL_H__
#define __SERVOCONTROL_H__

#define      ServoOutPutMax      66.01
#define      ServoOutPutMin      32.01

extern void Judge(void);
extern void IncrementalServoControl(void);
extern void ServoControl(void);

#endif 

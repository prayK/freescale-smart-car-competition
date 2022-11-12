#ifndef __SMARTCARCONTROL_H__
#define __SMARTCARCONTROL_H__

extern int16 GoalSpeedSet(void);
extern void EncoderRead(void);
extern void ImageWatching(void);
extern void MotorControl(void);
extern void ImageIdentification(void); 
extern void ImageGet(void); 
extern void vcan_sendware();

#endif

#ifndef __BOARD_GYRO_H__
#define __BOARD_GYRO_H__

#include "include.h"

#define GYRO_CS PTB22
#define GYRO_SDO PTB23

typedef struct Coord{int16 x,y,z;}Coord;

unsigned char Board_Gyro_Init(void);;

int Gyro_Read_X(void);

void Gyro_Angle_IRQ(void);

extern Coord Angle;

#endif

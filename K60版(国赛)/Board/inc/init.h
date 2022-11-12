#ifndef __INIT_H__
#define __INIT_H__
#include "include.h"

void init(void);
void   PORTD_IRQHandler();
void   DMA0_IRQHandler();
void   sendimg(void *imgaddr, uint32 imgsize);
void   PIT0_IRQHandler(void);


#endif
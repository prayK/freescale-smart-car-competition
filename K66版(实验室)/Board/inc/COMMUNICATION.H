#ifndef _VCAN_COMPUTER_H_
#define _VCAN_COMPUTER_H_

#include "common.h"
#include "MK66_uart.h"

extern void vcan_sendimg(void *imgaddr, uint32_t imgsize);
extern void vcan_sendccd(void *ccdaddr, uint32_t ccdsize);
extern void vcan_sendware(void *wareaddr, uint32_t waresize);

#endif  
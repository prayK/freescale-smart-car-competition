#ifndef _OV7725_H_
#define _OV7725_H_

#include <stdint.h>
#include "fsl_i2c.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x)	(sizeof(x) / sizeof((x)[0]))
#endif

typedef enum
{
    H_60_W_80, 
    H_120_W_160, 
    H_180_W_240, 
    H_240_W_320, 
    H_240_W_80, 
    H_180_W_80,
    H_120_W_80,
}ov7725_size; 

int ov7725_probe(uint32_t i2c_instance);
int ov7725_set_image_size(ov7725_size size);

#endif


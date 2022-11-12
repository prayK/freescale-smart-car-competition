#ifndef _CAMERA_H_
#define _CAMERA_H_


#define CAMERA_OV7725_EAGLE         2       //山外鹰眼
#define CAMERA_OV7725_WOLF          3       //山外狼眼


#define USE_CAMERA      CAMERA_OV7725_EAGLE   //选择使用的 摄像头

typedef struct
{
    uint8 addr;                 /*寄存器地址*/
    uint8 val;                   /*寄存器值*/
} reg_s;

//定义图像采集状态
typedef enum
{
    IMG_NOTINIT = 0,
    IMG_FINISH,             //图像采集完毕
    IMG_FAIL,               //图像采集失败(采集行数少了)
    IMG_GATHER,             //图像采集中
    IMG_START,              //开始采集图像
    IMG_STOP,               //禁止图像采集
} IMG_STATUS_e;



#include  "SCCB.H"
#include  "OV7725_EAGLE.H"

extern void img_extract(void *dst, void *src, uint32_t srclen);

#endif



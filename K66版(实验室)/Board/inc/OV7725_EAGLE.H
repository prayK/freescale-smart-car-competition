#ifndef _OV7725_EAGLE_H_
#define _OV7725_EAGLE_H_

#include  "OV7725_REG.H"


//配置摄像头顶层接口
#define camera_init(imgaddr)    ov7725_eagle_init(imgaddr)
#define camera_get_img()        ov7725_eagle_get_img()

#define camera_vsync()          ov7725_eagle_vsync()
#define camera_href()
#define camera_dma()            ov7725_eagle_dma()

//配置 摄像头 参数
#define CAMERA_DMA_CH       OV7725_EAGLE_DMA_CH         //定义摄像头的DMA采集通道
#define CAMERA_W            OV7725_EAGLE_W              //定义摄像头图像宽度
#define CAMERA_H            OV7725_EAGLE_H              //定义摄像头图像高度

#define CAMERA_SIZE         OV7725_EAGLE_SIZE           //图像占用空间大小
#define CAMERA_DMA_NUM      OV7725_EAGLE_DMA_NUM        //DMA采集次数


//配置摄像头 属性
#define OV7725_EAGLE_DMA_CH       DMA_CH0 //定义摄像头的DMA采集通道
#define OV7725_EAGLE_W            80 //定义摄像头图像宽度
#define OV7725_EAGLE_H            240 //定义摄像头图像高度
#define OV7725_EAGLE_SIZE         (OV7725_EAGLE_W * OV7725_EAGLE_H/8 )  //图像占用空间大小
#define OV7725_EAGLE_DMA_NUM      (OV7725_EAGLE_SIZE ) //DMA采集次数

extern  uint8   ov7725_eagle_init(uint8 *imgaddr);
extern  void    ov7725_eagle_get_img(void);
extern  void    ov7725_eagle_vsync(void);
extern  void    ov7725_eagle_dma(void);

#endif 



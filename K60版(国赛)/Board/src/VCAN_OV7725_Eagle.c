#include "common.h"
#include "MK60_gpio.h"
#include "MK60_port.h"
#include "MK60_dma.h"
#include "VCAN_camera.h"

extern float CNST_Value;

#define OV7725_EAGLE_Delay_ms(time)  DELAY_MS(time)

uint8   *ov7725_eagle_img_buff;

volatile IMG_STATUS_e      ov7725_eagle_img_flag = IMG_FINISH;   //图像状态

//内部函数声明
static uint8 ov7725_eagle_reg_init(void);
static void ov7725_eagle_port_init();


/*鹰眼ov7725初始化 */
uint8 ov7725_eagle_init(uint8 *imgaddr)
{
    ov7725_eagle_img_buff = imgaddr;
    while(ov7725_eagle_reg_init() == 0);
    ov7725_eagle_port_init();
    return 0;
}

/*鹰眼ov7725管脚初始化(内部调用)*/
void ov7725_eagle_port_init()
{
    dma_portx2buff_init(CAMERA_DMA_CH, (void *)&PTD_B1_IN, (void *)ov7725_eagle_img_buff, PTD5, DMA_BYTE1, CAMERA_DMA_NUM, DADDR_KEEPON);
    DMA_DIS(CAMERA_DMA_CH);
    disable_irq(PORTD_IRQn);
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);
    DMA_IRQ_EN(CAMERA_DMA_CH);

    port_init(PTD5, ALT1 | DMA_FALLING | PULLDOWN ); 
    port_init(PTD4, ALT1 | IRQ_RISING  | PULLDOWN | PF); 

}

/*鹰眼ov7725场中断服务函数*/
void ov7725_eagle_vsync(void)
{
          //场中断需要判断是场结束还是场开始
          if(ov7725_eagle_img_flag == IMG_START)
          {
                    ov7725_eagle_img_flag = IMG_GATHER;
                    disable_irq(PORTD_IRQn);
                    PORTD_ISFR = 1 <<  PT5;
                    DMA_EN(CAMERA_DMA_CH);
                    PORTD_ISFR = 1 <<  PT5;
                    DMA_DADDR(CAMERA_DMA_CH) = (uint32)ov7725_eagle_img_buff;
          }
          else
          {
                    disable_irq(PORTD_IRQn);
                    ov7725_eagle_img_flag = IMG_FAIL;
          }
}

/*鹰眼ov7725 DMA中断服务函数*/
void ov7725_eagle_dma()
{
          ov7725_eagle_img_flag = IMG_FINISH ;
          DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //清除通道传输中断标志位
}

/*鹰眼ov7725采集图像(采集到的数据存储在 初始化时配置的地址上)*/
void ov7725_eagle_get_img()
{
          ov7725_eagle_img_flag = IMG_START;
          PORTD_ISFR = ~0;              //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
          enable_irq(PORTD_IRQn);
          while(ov7725_eagle_img_flag != IMG_FINISH)
          {
                if(ov7725_eagle_img_flag == IMG_FAIL)
                {
                      ov7725_eagle_img_flag = IMG_START;
                      PORTD_ISFR = ~0;   //写1清中断标志位(必须的，不然回导致一开中断就马上触发中断)
                      enable_irq(PORTD_IRQn);
                }
          }
}


/*OV7725初始化配置表*/
reg_s ov7725_eagle_reg[] =
{
//    //寄存器，寄存器值次                 // 50fps    75fps   112fps  150fps
//    {OV7725_COM4         , 0xC1},       // 0xC1     0x41    0x81    0xC1
//    {OV7725_CLKRC        , 0x02},       // 0x02     0x00    0x00    0x00
  
    {OV7725_COM4         , 0xC1}, 
    {OV7725_CLKRC        , 0x00}, 
    {OV7725_COM2         , 0x03},
    {OV7725_COM3         , 0xD0},
    {OV7725_COM7         , 0x40},
    {OV7725_HSTART       , 0x3F},
    {OV7725_HSIZE        , 0x50},
    {OV7725_VSTRT        , 0x03},
    {OV7725_VSIZE        , 0x78},
    {OV7725_HREF         , 0x00},
    {OV7725_SCAL0        , 0x0A},
    {OV7725_AWB_Ctrl0    , 0xE0},
    {OV7725_DSPAuto      , 0xff},
    {OV7725_DSP_Ctrl2    , 0x0C},
    {OV7725_DSP_Ctrl3    , 0x00},
    {OV7725_DSP_Ctrl4    , 0x00},

#if (CAMERA_W == 80)
    {OV7725_HOutSize     , 0x14},
#elif (CAMERA_W == 160)
    {OV7725_HOutSize     , 0x28},
#elif (CAMERA_W == 240)
    {OV7725_HOutSize     , 0x3c},
#elif (CAMERA_W == 320)
    {OV7725_HOutSize     , 0x50},
#else

#endif

#if (CAMERA_H == 60 )
    {OV7725_VOutSize     , 0x1E},
#elif (CAMERA_H == 120 )
    {OV7725_VOutSize     , 0x3c},
#elif (CAMERA_H == 180 )
    {OV7725_VOutSize     , 0x5a},
#elif (CAMERA_H == 240 )
    {OV7725_VOutSize     , 0x78},
#else

#endif

    {OV7725_EXHCH        , 0x00},
    {OV7725_GAM1         , 0x0c},
    {OV7725_GAM2         , 0x16},
    {OV7725_GAM3         , 0x2a},
    {OV7725_GAM4         , 0x4e},
    {OV7725_GAM5         , 0x61},
    {OV7725_GAM6         , 0x6f},
    {OV7725_GAM7         , 0x7b},
    {OV7725_GAM8         , 0x86},
    {OV7725_GAM9         , 0x8e},
    {OV7725_GAM10        , 0x97},
    {OV7725_GAM11        , 0xa4},
    {OV7725_GAM12        , 0xaf},
    {OV7725_GAM13        , 0xc5},
    {OV7725_GAM14        , 0xd7},
    {OV7725_GAM15        , 0xe8},
    {OV7725_SLOP         , 0x20},
    {OV7725_LC_RADI      , 0x00},
    {OV7725_LC_COEF      , 0x13},
    {OV7725_LC_XC        , 0x08},
    {OV7725_LC_COEFB     , 0x14},
    {OV7725_LC_COEFR     , 0x17},
    {OV7725_LC_CTR       , 0x05},
    {OV7725_BDBase       , 0x99},
    {OV7725_BDMStep      , 0x03},
    {OV7725_SDE          , 0x04},
    {OV7725_BRIGHT       , 0x00},
    {OV7725_CNST         , 0x49},  //阈值
    {OV7725_SIGN         , 0x06},
    {OV7725_UVADJ0       , 0x11},
    {OV7725_UVADJ1       , 0x02},

};

uint8 ov7725_eagle_cfgnum = ARR_SIZE( ov7725_eagle_reg ) ; /*结构体数组成员数目*/


/*鹰眼ov7725寄存器 初始化,初始化结果(0表示失败，1表示成功)*/
uint8 ov7725_eagle_reg_init(void)
{
          uint16 i = 0;
          uint8 Sensor_IDCode = 0;
          SCCB_GPIO_init();
          
          if( 0 == SCCB_WriteByte ( OV7725_COM7, 0x80))
          {
                  return 0 ;
          }

          OV7725_EAGLE_Delay_ms(50);

          if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, OV7725_VER))
          {
                  return 0;
          }
          DEBUG_PRINTF("\nGet ID success，SENSOR ID is 0x%x", Sensor_IDCode);
          DEBUG_PRINTF("\nConfig Register Number is %d ", ov7725_eagle_cfgnum);
          if(Sensor_IDCode == OV7725_ID)
          {
                  for( i = 0 ; i < ov7725_eagle_cfgnum ; i++ )
                  {
                          if( 0 == SCCB_WriteByte(ov7725_eagle_reg[i].addr, ov7725_eagle_reg[i].val) )
                          {
                                  return 0;
                          }
                  }
          }
          else
          {
                  return 0;
          }
          return 1;
}

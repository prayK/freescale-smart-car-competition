#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include "common.h"

#include "MK60_wdog.h"
#include "MK60_gpio.h"     //IO�ڲ���
#include "MK60_uart.h"     //����
#include "MK60_SysTick.h"
#include "MK60_lptmr.h"    //�͹��Ķ�ʱ��(��ʱ)
#include "MK60_i2c.h"      //I2C
#include "MK60_spi.h"      //SPI
#include "MK60_ftm.h"      //FTM
#include "MK60_pit.h"      //PIT
#include "MK60_dma.h"      //DMA
#include "MK60_FLASH.h"    //FLASH

#include "VCAN_LED.H"          //LED
#include "VCAN_KEY.H"          //KEY
#include "VCAN_camera.h"       //����ͷ��ͷ�ļ�
#include "VCAN_LCD.h"          //Һ����ͷ�ļ�
#include "VCAN_key_event.h"    //������Ϣ����
#include "Speed_Control.h"
#include "VCAN_computer.h"     //�๦�ܵ�������
#include "init.h"
#include "common.h"
#include "main_menu.h"
#include "VCAN_menu.h"
#include "car_control.h"
#include "VCAN_UI_VAR.h"
#include "imag.h"
#include "Board_Gyro.h"

#define BM1 gpio_get(PTA14) 
#define BM2 gpio_get(PTA15)
#define BM3 gpio_get(PTA13) 
#define BM4 gpio_get(PTA12)
   
#endif  
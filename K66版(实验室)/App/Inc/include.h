#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

#include  "MK66_wdog.h"
#include  "MK66_gpio.h"     //IO¿Ú²Ù×÷
#include  "MK66_uart.h"     //´®¿Ú
#include  "MK66_i2c.h"      //I2C
#include  "MK66_spi.h"      //SPI
#include  "MK66_rtc.h"      //RTC
#include  "MK66_adc.h"      //ADC
#include  "MK66_dma.h"      //DMA
#include  "MK66_sdhc.h"     //SDHC

#include  "LED.H" 
#include  "KEY.H" 
#include  "SCCB.H"
#include  "LCD_ST7735S.H"
#include  "COMMUNICATION.H"
#include  "OV7725_EAGLE.H"
#include  "OLED.H"  
#include  "enter.h"

#include  "ImageInformation.h"
#include  "SmartCarControl.h"
//#include  "UserInterface.h"
#include  "ServoControl.h"
#include  "ModulesInit.h"
#include  "ImageDeal.h"
#include  "MyLibrary.h"


#define   BM1    gpio_get(PTA14) 

#endif 

#ifndef _BOARD_H_
#define _BOARD_H_

#include "clock_config.h" 
#include "fsl_gpio.h" 

#define BOARD_DEBUG_UART_CLK_FREQ     CLOCK_GetFastPeriphClkFreq()
#define BOARD_DEBUG_UART_BASEADDR     (uint32_t) UART0
#define BOARD_DEBUG_UART_BAUDRATE     115200
#define BOARD_DEBUG_UART_TYPE         DEBUG_CONSOLE_DEVICE_TYPE_UART

#define bus_clk_khz                   SIM_CLKDIV1_OUTDIV4(1) 
#define PIT_Flag_Clear                PIT->CHANNEL->TFLG|=PIT_TFLG_TIF_MASK   //清中断标志（写1 清空标志位）
#define pit_delay_ms(ms)              pit_delay(ms * bus_clk_khz);            //PIT延时 ms
#define pit_delay_us(us)              pit_delay(us * bus_clk_khz/1000);       //PIT延时 us
#define pit_delay_ns(ns)              pit_delay(ns * bus_clk_khz/1000000);    //PIT延时 ns
#define DelayMs(ms)                   pit_delay_ms(ms)
#define DelayUs(us)                   pit_delay_us(us)
#define DelayNs(ns)                   pit_delay_ns(ns)

void pit_delay(uint32_t cnt);  
void BOARD_InitDebugConsole(void);


typedef struct
{ 
    uint16_t x; 
    uint16_t y; 
} Site_t;

typedef struct
{ 
    uint16_t W; 
    uint16_t H; 
} Size_t;

#endif 
#include <stdint.h>
#include "include.h" 

/*Initialize debug console*/
void BOARD_InitDebugConsole(void)
{ 
      uint32_t uartClkSrcFreq = BOARD_DEBUG_UART_CLK_FREQ;
      DbgConsole_Init(BOARD_DEBUG_UART_BASEADDR, BOARD_DEBUG_UART_BAUDRATE,
                      BOARD_DEBUG_UART_TYPE, uartClkSrcFreq);
} 

void pit_delay(uint32_t cnt)
{ 
    SIM->SCGC6       |= SIM_SCGC6_PIT_MASK;//使能PIT时钟
    PIT->MCR         &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK );//使能PIT定时器时钟 ，调试模式下继续运行
    PIT->CHANNEL->TCTRL &= ~( PIT_TCTRL_TEN_MASK );//禁用PIT ，以便设置加载值生效
    PIT->CHANNEL->LDVAL  = cnt - 1;//设置溢出中断时间
    PIT_Flag_Clear;//清中断标志位
    PIT->CHANNEL->TCTRL &= ~ PIT_TCTRL_TEN_MASK;//禁止PITn定时器（用于清空计数值）
    PIT->CHANNEL->TCTRL  = ( 0 
                         | PIT_TCTRL_TEN_MASK//使能 PITn定时器 
                       ); 
    while( !(PIT->CHANNEL->TFLG& PIT_TFLG_TIF_MASK));
    PIT_Flag_Clear;//清中断标志位
} 


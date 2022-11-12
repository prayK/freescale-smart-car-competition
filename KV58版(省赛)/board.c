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
    SIM->SCGC6       |= SIM_SCGC6_PIT_MASK;//ʹ��PITʱ��
    PIT->MCR         &= ~(PIT_MCR_MDIS_MASK | PIT_MCR_FRZ_MASK );//ʹ��PIT��ʱ��ʱ�� ������ģʽ�¼�������
    PIT->CHANNEL->TCTRL &= ~( PIT_TCTRL_TEN_MASK );//����PIT ���Ա����ü���ֵ��Ч
    PIT->CHANNEL->LDVAL  = cnt - 1;//��������ж�ʱ��
    PIT_Flag_Clear;//���жϱ�־λ
    PIT->CHANNEL->TCTRL &= ~ PIT_TCTRL_TEN_MASK;//��ֹPITn��ʱ����������ռ���ֵ��
    PIT->CHANNEL->TCTRL  = ( 0 
                         | PIT_TCTRL_TEN_MASK//ʹ�� PITn��ʱ�� 
                       ); 
    while( !(PIT->CHANNEL->TFLG& PIT_TFLG_TIF_MASK));
    PIT_Flag_Clear;//���жϱ�־λ
} 


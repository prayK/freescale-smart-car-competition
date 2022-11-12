#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"


void BOARD_InitBootPins(void) 
{
    BOARD_InitPins();
}


/*****************摄像头场，行，像素IO口初始化*********************/
#define PCR_PS_DOWN                   0x00u   /*!< Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
void BOARD_InitPins(void) 
{
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTC, PIN5_IDX, kPORT_MuxAsGpio);          /* PORTC5 (pin 77) is configured as PTC5 */
  PORTC->PCR[5] = ((PORTC->PCR[5] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_ISF_MASK)))               /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_DOWN)                             /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
    );
  PORT_SetPinMux(PORTC, PIN6_IDX, kPORT_MuxAsGpio);          /* PORTC6 (pin 78) is configured as PTC6 */
  PORTC->PCR[6] = ((PORTC->PCR[6] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_ISF_MASK)))               /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_DOWN)                             /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
    );
  PORT_SetPinMux(PORTC, PIN7_IDX, kPORT_MuxAsGpio);          /* PORTC7 (pin 79) is configured as PTC7 */
  PORTC->PCR[7] = ((PORTC->PCR[7] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_ISF_MASK)))               /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_DOWN)                             /* Pull Select: Internal pulldown resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
    );
}



/*******************摄像头八个数据口初始化**********************/
#define PIN0_IDX                         0u   /*!< Pin number for pin 0 in a port */
#define PIN1_IDX                         1u   /*!< Pin number for pin 1 in a port */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN4_IDX                         4u   /*!< Pin number for pin 4 in a port */
#define PIN5_IDX                         5u   /*!< Pin number for pin 5 in a port */
#define PIN6_IDX                         6u   /*!< Pin number for pin 6 in a port */
#define PIN7_IDX                         7u   /*!< Pin number for pin 7 in a port */
void BOARD_InitData(void) 
{
  CLOCK_EnableClock(kCLOCK_PortD);                           /* Port D Clock Gate Control: Clock enabled */
  PORT_SetPinMux(PORTD, PIN0_IDX, kPORT_MuxAsGpio);          /* PORTD0 (pin 127) is configured as PTD0 */
  PORT_SetPinMux(PORTD, PIN1_IDX, kPORT_MuxAsGpio);          /* PORTD1 (pin 128) is configured as PTD1 */
  PORT_SetPinMux(PORTD, PIN2_IDX, kPORT_MuxAsGpio);          /* PORTD2 (pin 129) is configured as PTD2 */
  PORT_SetPinMux(PORTD, PIN3_IDX, kPORT_MuxAsGpio);          /* PORTD3 (pin 130) is configured as PTD3 */
  PORT_SetPinMux(PORTD, PIN4_IDX, kPORT_MuxAsGpio);          /* PORTD4 (pin 131) is configured as PTD4 */
  PORT_SetPinMux(PORTD, PIN5_IDX, kPORT_MuxAsGpio);          /* PORTD5 (pin 132) is configured as PTD5 */
  PORT_SetPinMux(PORTD, PIN6_IDX, kPORT_MuxAsGpio);          /* PORTD6 (pin 133) is configured as PTD6 */
  PORT_SetPinMux(PORTD, PIN7_IDX, kPORT_MuxAsGpio);          /* PORTD7 (pin 136) is configured as PTD7 */
}



/***************************OLED初始化**********************/
#define PIN12_IDX                       12u   /*!< Pin number for pin 12 in a port */
#define PIN13_IDX                       13u   /*!< Pin number for pin 13 in a port */
#define PIN14_IDX                       14u   /*!< Pin number for pin 14 in a port */
#define PIN15_IDX                       15u   /*!< Pin number for pin 15 in a port */
void BOARD_InitOled(void) 
{
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */
  PORT_SetPinMux(PORTC, PIN12_IDX, kPORT_MuxAsGpio);         /* PORTC12 (pin 117) is configured as PTC12 */
  PORT_SetPinMux(PORTC, PIN13_IDX, kPORT_MuxAsGpio);         /* PORTC13 (pin 118) is configured as PTC13 */
  PORT_SetPinMux(PORTC, PIN14_IDX, kPORT_MuxAsGpio);         /* PORTC14 (pin 119) is configured as PTC14 */
  PORT_SetPinMux(PORTC, PIN15_IDX, kPORT_MuxAsGpio);         /* PORTC15 (pin 120) is configured as PTC15 */
}




/***************************蜂鸣器和LED灯IO口初始化**************/
#define PCR_PS_DOWN                   0x00u 
#define PIN14_IDX                       14u 
#define PIN17_IDX                       17u 
#define PIN0_IDX                         0u 
#define PIN15_IDX                       15u 
#define PIN29_IDX                       29u 
void BOARD_InitLed(void) 
{
        CLOCK_EnableClock(kCLOCK_PortA); //A17  //开启时钟
        CLOCK_EnableClock(kCLOCK_PortC); //C0   //开启时钟
        CLOCK_EnableClock(kCLOCK_PortD); //D15  //开启时钟
        CLOCK_EnableClock(kCLOCK_PortE); //E29  //开启时钟
        //CLOCK_EnableClock(kCLOCK_PortD); ///蜂鸣器初始化D14  //开启时钟
        PORT_SetPinMux(PORTD, PIN14_IDX, kPORT_MuxAsGpio);///蜂鸣器初始化D14 

        PORT_SetPinMux(PORTA, PIN17_IDX, kPORT_MuxAsGpio); //PTA17
        PORTA->PCR[17] = ((PORTA->PCR[17] &
           (~(PORT_PCR_PS_MASK 
            | PORT_PCR_ISF_MASK))) 
            | PORT_PCR_PS(PCR_PS_DOWN) 
           );
        PORT_SetPinMux(PORTC, PIN0_IDX, kPORT_MuxAsGpio);  //PTC0
        PORTC->PCR[0] = ((PORTC->PCR[0] &
           (~(PORT_PCR_PS_MASK 
            | PORT_PCR_ISF_MASK))) 
            | PORT_PCR_PS(PCR_PS_DOWN) 
           );
        PORT_SetPinMux(PORTD, PIN15_IDX, kPORT_MuxAsGpio); //PTD15
        PORTD->PCR[15] = ((PORTD->PCR[15] &
           (~(PORT_PCR_PS_MASK 
            | PORT_PCR_ISF_MASK))) 
            | PORT_PCR_PS(PCR_PS_DOWN)   
           );
        PORT_SetPinMux(PORTE, PIN29_IDX, kPORT_MuxAsGpio); //PTE29
        PORTE->PCR[29] = ((PORTE->PCR[29] &
           (~(PORT_PCR_PS_MASK 
            | PORT_PCR_ISF_MASK))) 
            | PORT_PCR_PS(PCR_PS_DOWN) 
           );
}


/*******************IIC初始化*******************/
#define PCR_ODE_DISABLED              0x00u   /*!< Open Drain Enable: Open drain output is disabled on the corresponding pin. */
#define PCR_ODE_ENABLED               0x01u   /*!< Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
#define PCR_PS_UP                     0x01u   /*!< Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
#define PIN2_IDX                         2u   /*!< Pin number for pin 2 in a port */
#define PIN3_IDX                         3u   /*!< Pin number for pin 3 in a port */
#define PIN10_IDX                       10u   /*!< Pin number for pin 10 in a port */
#define PIN11_IDX                       11u   /*!< Pin number for pin 11 in a port */
void BOARD_InitI2c(void)
{ 
  CLOCK_EnableClock(kCLOCK_PortC);                           /* Port C Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTC, PIN10_IDX, kPORT_MuxAlt2);           /* PORTC10 (pin 82) is configured as I2C1_SCL */
  PORTC->PCR[10] = ((PORTC->PCR[10] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_ODE(PCR_ODE_ENABLED)                        /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
    );
  PORT_SetPinMux(PORTC, PIN11_IDX, kPORT_MuxAlt2);           /* PORTC11 (pin 83) is configured as I2C1_SDA */
  PORTC->PCR[11] = ((PORTC->PCR[11] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_ODE_MASK | PORT_PCR_ISF_MASK))) /* Mask bits to zero which are setting */
      | PORT_PCR_PS(PCR_PS_UP)                               /* Pull Select: Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set. */
      | PORT_PCR_ODE(PCR_ODE_ENABLED)                        /* Open Drain Enable: Open drain output is enabled on the corresponding pin, if the pin is configured as a digital output. */
    );
}

/*******************串口初始化*******************/
#define PIN16_IDX                       16u   /*!< Pin number for pin 16 in a port */
#define PIN17_IDX                       17u   /*!< Pin number for pin 17 in a port */
#define SOPT5_UART0RXSRC_UART_RX      0x00u   /*!< UART 0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX      0x00u   /*!< UART 0 transmit data source select: UART0_TX pin */
void BOARD_InitUart(void) 
{
  CLOCK_EnableClock(kCLOCK_PortB);                           /* Port B Clock Gate Control: Clock enabled */

  PORT_SetPinMux(PORTB, PIN16_IDX, kPORT_MuxAlt3);           /* PORTB16 (pin 62) is configured as UART0_RX */
  PORT_SetPinMux(PORTB, PIN17_IDX, kPORT_MuxAlt3);           /* PORTB17 (pin 63) is configured as UART0_TX */
  SIM->SOPT5 = ((SIM->SOPT5 &
    (~(SIM_SOPT5_UART0TXSRC_MASK | SIM_SOPT5_UART0RXSRC_MASK))) /* Mask bits to zero which are setting */
      | SIM_SOPT5_UART0TXSRC(SOPT5_UART0TXSRC_UART_TX)       /* UART 0 transmit data source select: UART0_TX pin */
      | SIM_SOPT5_UART0RXSRC(SOPT5_UART0RXSRC_UART_RX)       /* UART 0 receive data source select: UART0_RX pin */
    );
} 


/*******************八位拨码开关IO口初始化*******************/
#define PCR_PE_ENABLED                0x01u
#define PCR_PFE_DISABLED              0x00u
#define PCR_PS_UP                     0x01u

#define PIN24_IDX                       24u   //第一个
#define PIN25_IDX                       25u   //第二个
#define PIN27_IDX                       27u   //第三个
#define PIN29_IDX                       29u   //五向上
#define PIN28_IDX                       28u   //五向下
#define PIN4_IDX                         4u   //五向左
#define PIN7_IDX                         7u   //五向右
#define PIN5_IDX                         5u   //五向中

#define PIN6_IDX                         6u   //第一个
#define PIN7_IDX                         7u   //第二个
#define PIN8_IDX                         8u   //第三个
#define PIN9_IDX                         9u   //第四个

#define PIN10_IDX                       10u   //第五个
#define PIN17_IDX                       17u   //第六个

#define PIN16_IDX                       16u   //第七第
#define PIN12_IDX                       12u   //第八个

void BOARD_InintButtons(void) 
{ 
  CLOCK_EnableClock(kCLOCK_PortA); //开A时钟
  CLOCK_EnableClock(kCLOCK_PortB); //开B时钟
  CLOCK_EnableClock(kCLOCK_PortE); //开E时钟  

  PORT_SetPinMux(PORTA, PIN24_IDX, kPORT_MuxAsGpio);
  PORTA->PCR[24] = ((PORTA->PCR[24] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) 
      | PORT_PCR_PS(PCR_PS_UP) 
      | PORT_PCR_PE(PCR_PE_ENABLED) 
    );
  PORT_SetPinMux(PORTA, PIN25_IDX, kPORT_MuxAsGpio);
  PORTA->PCR[25] = ((PORTA->PCR[25] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))  
      | PORT_PCR_PS(PCR_PS_UP) 
      | PORT_PCR_PE(PCR_PE_ENABLED) 
    );
  PORT_SetPinMux(PORTA, PIN27_IDX, kPORT_MuxAsGpio);
  PORTA->PCR[27] = ((PORTA->PCR[27] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) 
      | PORT_PCR_PS(PCR_PS_UP)  
      | PORT_PCR_PE(PCR_PE_ENABLED) 
    );
  PORT_SetPinMux(PORTA, PIN29_IDX, kPORT_MuxAsGpio);
  PORTA->PCR[29] = ((PORTA->PCR[29] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))  
      | PORT_PCR_PS(PCR_PS_UP)
      | PORT_PCR_PE(PCR_PE_ENABLED) 
    );
  PORT_SetPinMux(PORTA, PIN28_IDX, kPORT_MuxAsGpio);
  PORTA->PCR[28] = ((PORTA->PCR[28] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))  
      | PORT_PCR_PS(PCR_PS_UP)
      | PORT_PCR_PE(PCR_PE_ENABLED)
    );
  PORT_SetPinMux(PORTB, PIN4_IDX, kPORT_MuxAsGpio);
  PORTB->PCR[4] = ((PORTB->PCR[4] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))  
      | PORT_PCR_PS(PCR_PS_UP)
      | PORT_PCR_PE(PCR_PE_ENABLED)
    );
  PORT_SetPinMux(PORTB, PIN7_IDX, kPORT_MuxAsGpio);
  PORTB->PCR[7] = ((PORTB->PCR[7] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_PFE_MASK | PORT_PCR_ISF_MASK)))
      | PORT_PCR_PS(PCR_PS_UP) 
      | PORT_PCR_PE(PCR_PE_ENABLED)
      | PORT_PCR_PFE(PCR_PFE_DISABLED)
    );
  PORT_SetPinMux(PORTB, PIN5_IDX, kPORT_MuxAsGpio);
  PORTB->PCR[5] = ((PORTB->PCR[5] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) 
      | PORT_PCR_PS(PCR_PS_UP)
      | PORT_PCR_PE(PCR_PE_ENABLED)
    );

 
  PORT_SetPinMux(PORTE, PIN6_IDX, kPORT_MuxAsGpio);
  PORTE->PCR[6] = ((PORTE->PCR[6] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) 
      | PORT_PCR_PS(PCR_PS_UP) 
      | PORT_PCR_PE(PCR_PE_ENABLED) 
    );
  PORT_SetPinMux(PORTE, PIN7_IDX, kPORT_MuxAsGpio);
  PORTE->PCR[7] = ((PORTE->PCR[7] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))  
      | PORT_PCR_PS(PCR_PS_UP) 
      | PORT_PCR_PE(PCR_PE_ENABLED) 
    );
  PORT_SetPinMux(PORTE, PIN8_IDX, kPORT_MuxAsGpio);
  PORTE->PCR[8] = ((PORTE->PCR[8] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) 
      | PORT_PCR_PS(PCR_PS_UP)  
      | PORT_PCR_PE(PCR_PE_ENABLED) 
    );
  PORT_SetPinMux(PORTE, PIN9_IDX, kPORT_MuxAsGpio);
  PORTE->PCR[9] = ((PORTE->PCR[9] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))  
      | PORT_PCR_PS(PCR_PS_UP)
      | PORT_PCR_PE(PCR_PE_ENABLED) 
    );
  PORT_SetPinMux(PORTE, PIN10_IDX, kPORT_MuxAsGpio);
  PORTE->PCR[10] = ((PORTE->PCR[10] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))  
      | PORT_PCR_PS(PCR_PS_UP)
      | PORT_PCR_PE(PCR_PE_ENABLED)
    );
  PORT_SetPinMux(PORTE, PIN17_IDX, kPORT_MuxAsGpio);
  PORTE->PCR[17] = ((PORTE->PCR[17] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))  
      | PORT_PCR_PS(PCR_PS_UP)
      | PORT_PCR_PE(PCR_PE_ENABLED)
    );
  PORT_SetPinMux(PORTE, PIN16_IDX, kPORT_MuxAsGpio);
  PORTE->PCR[16] = ((PORTE->PCR[16] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_PFE_MASK | PORT_PCR_ISF_MASK)))
      | PORT_PCR_PS(PCR_PS_UP) 
      | PORT_PCR_PE(PCR_PE_ENABLED)
      | PORT_PCR_PFE(PCR_PFE_DISABLED)
    );
  PORT_SetPinMux(PORTE, PIN12_IDX, kPORT_MuxAsGpio);
  PORTE->PCR[12] = ((PORTE->PCR[12] &
    (~(PORT_PCR_PS_MASK | PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK))) 
      | PORT_PCR_PS(PCR_PS_UP)
      | PORT_PCR_PE(PCR_PE_ENABLED)
    );

}





/************************编码器IO口初始化******************/
#define PIN0_IDX                         0u 
#define PIN1_IDX                         1u 
void BOARD_InitFtmquad(void) 
{
  CLOCK_EnableClock(kCLOCK_PortB); 
  PORT_SetPinMux(PORTB, PIN0_IDX, kPORT_MuxAlt6);
  PORT_SetPinMux(PORTB, PIN1_IDX, kPORT_MuxAlt6); 
}


/*************************电机IO初始化配置(C1,C2)***************/
#define PIN1_IDX                         1u  
#define PIN2_IDX                         2u  
#define SOPT8_FTM0OCH0SRC_FTM         0x00u  
#define SOPT8_FTM0OCH1SRC_FTM         0x00u  
void BOARD_InitMotorFtm(void)
{ 
        CLOCK_EnableClock(kCLOCK_PortC); 

        PORT_SetPinMux(PORTC, PIN1_IDX, kPORT_MuxAlt4); 
        PORT_SetPinMux(PORTC, PIN2_IDX, kPORT_MuxAlt4); 
        SIM->SOPT8 = ((SIM->SOPT8 &
          (~(SIM_SOPT8_FTM0OCH0SRC_MASK 
           | SIM_SOPT8_FTM0OCH1SRC_MASK)))
           | SIM_SOPT8_FTM0OCH0SRC(SOPT8_FTM0OCH0SRC_FTM) 
           | SIM_SOPT8_FTM0OCH1SRC(SOPT8_FTM0OCH1SRC_FTM)
          );
} 


//////////////////////////////////舵机IO口初始化已完成(FTM3_CH6 PTE11)2018.6.27  
#define PIN11_IDX                       11u 
#define SOPT8_FTM3OCH6SRC_FTM         0x00u 
void BOARD_InitServoFtm(void) 
{
        CLOCK_EnableClock(kCLOCK_PortE);  
        PORT_SetPinMux(PORTE, PIN11_IDX, kPORT_MuxAlt6);  
        SIM->SOPT8 = ((SIM->SOPT8 &
          (~(SIM_SOPT8_FTM3OCH6SRC_MASK))) 
            | SIM_SOPT8_FTM3OCH6SRC(SOPT8_FTM3OCH6SRC_FTM) 
          );
}
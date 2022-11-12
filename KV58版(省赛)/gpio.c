#include "gpio.h"
#include "fsl_device_registers.h"
#include "ov7725.h"
/* leagacy support for Kineis Z version(inital version) */
#if (!defined(GPIO_BASES))

#ifdef PORTF
#define GPIO_BASES {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF}
#define PORT_BASES {PORTA, PORTB, PORTC, PORTD, PORTE, PORTF}
#else
#define GPIO_BASES {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE}
#define PORT_BASES {PORTA, PORTB, PORTC, PORTD, PORTE}
#endif

#endif
#undef NULL  /* others (e.g. <stdio.h>) also define */
#define NULL 0
#undef DISABLE  /* others (e.g. <stdio.h>) also define */
#define DISABLE 0
#undef ENABLE  /* others (e.g. <stdio.h>) also define */
#define ENABLE 0
/* gloabl vars */
static GPIO_Type * const GPIO_InstanceTable[] = GPIO_BASES;
static PORT_Type * const PORT_InstanceTable[] = PORT_BASES;
static GPIO_CallBackType GPIO_CallBackTable[ARRAY_SIZE(PORT_InstanceTable)] = {NULL};
static const uint32_t SIM_GPIOClockGateTable[] =
{
    SIM_SCGC5_PORTA_MASK,
    SIM_SCGC5_PORTB_MASK,
    SIM_SCGC5_PORTC_MASK,
    SIM_SCGC5_PORTD_MASK,
    SIM_SCGC5_PORTE_MASK,
};
static const IRQn_Type GPIO_IRQnTable[] = 
{
    PORTA_IRQn,
    PORTB_IRQn,
    PORTC_IRQn,
    PORTD_IRQn,
    PORTE_IRQn,
};


 /**
 * @brief  set GPIO pin mux
 * @note   enable PORT clock before set pinmux number
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOx  GPIOx moudle
 * @param[in]  pin pin index number 0-31
 * @param[in]  pinMux pinmux function
 *              @arg kPinAltx  Pinmux function x
 * @retval None
 */
void PORT_PinMuxConfig(uint32_t instance, uint8_t pin, PORT_PinMux_Type pinMux)
{
    SIM->SCGC5 |= SIM_GPIOClockGateTable[instance];
    PORT_InstanceTable[instance]->PCR[pin] &= ~(PORT_PCR_MUX_MASK);
    PORT_InstanceTable[instance]->PCR[pin] |=  PORT_PCR_MUX(pinMux);
}

 /**
 * @brief  set pin internal pullup/down resistors
 * @note   pull resistor value is about 20K
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOx  GPIOx moudle
 * @param[in]  pin  pin index number 0-31
 * @param[in]  pull pull select
 *              @arg kPullDisabled  disable pull resistor
 *              @arg kPullUp        pull up
 *              @arg kPullDown      pull down
 * @retval None
 */
void PORT_PinPullConfig(uint32_t instance, uint8_t pin, PORT_Pull_Type pull)
{
    SIM->SCGC5 |= SIM_GPIOClockGateTable[instance];
    switch(pull)
    {
        case kPullDisabled:
            PORT_InstanceTable[instance]->PCR[pin] &= ~PORT_PCR_PE_MASK;
            break;
        case kPullUp:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_PE_MASK;
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_PS_MASK;
            break;
        case kPullDown:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_PE_MASK;
            PORT_InstanceTable[instance]->PCR[pin] &= ~PORT_PCR_PS_MASK;
            break;
        default:
            break;
    }
}
/**
 * @brief  �˿����ŵĿ�©״̬���� �û�һ�㲻�ص���
 * @code
 *      // ��PORTA�˿ڵ�3��������Ϊ��©״̬ 
 *      PORT_PinOpenDrainConfig(HW_GPIOA, 3, ENABLE);
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin  �˿��ϵ����ź� 0~31
 * @param[in]  status  ���ܿ��ؿ���
 *              @arg ENABLE   �������� 
 *              @arg DISABLE  �رչ���
 * @retval None
 */
void PORT_PinOpenDrainConfig(uint32_t instance, uint8_t pin, bool status)
{
    SIM->SCGC5 |= SIM_GPIOClockGateTable[instance];
    (status) ? (PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_ODE_MASK):(PORT_InstanceTable[instance]->PCR[pin] &= ~PORT_PCR_ODE_MASK);
}

/**
 * @brief  �˿����ŵĿ�����Դ�˲��� ��Ϊ����ʱ��Ч
 * @code
 *      // ��PORTA�˿ڵ�3��������Ϊ��©״̬ 
 *      PORT_PinPassiveFilterConfig(HW_GPIOA, 3, ENABLE);
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin  �˿��ϵ����ź� 0~31
 * @param[in]  status  ���ܿ��ؿ���
 *              @arg ENABLE   ��������
 *              @arg DISABLE  �رչ���
 * @retval None
 */
void PORT_PinPassiveFilterConfig(uint32_t instance, uint8_t pin, bool status)
{
    SIM->SCGC5 |= SIM_GPIOClockGateTable[instance];
    (status) ? (PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_PFE_MASK):(PORT_InstanceTable[instance]->PCR[pin] &= ~PORT_PCR_PFE_MASK);
}

 /**
 * @brief  ��������Ϊ���뻹���������  �û�һ�㲻�ص���
 * @note   ֻ�е�������ΪGPIOʱ��������
 * @code
 *      // ��PORTB�˿ڵ�3����������������
 *      GPIO_PinConfig(HW_GPIOB, 3, kInpput);
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin  �˿��ϵ����ź� 0~31
 * @param[in]  mode ��������������
 *              @arg kInpput  ���빦��ѡ��
 *              @arg kOutput  �������ѡ��
 * @retval None
 */
void GPIO_PinConfig(uint32_t instance, uint8_t pin, GPIO_PinConfig_Type mode)
{
    SIM->SCGC5 |= SIM_GPIOClockGateTable[instance];
    (mode == kOutput) ? (GPIO_InstanceTable[instance]->PDDR |= (1 << pin)):(GPIO_InstanceTable[instance]->PDDR &= ~(1 << pin));
}

 /**
 * @brief  GPIO��ʼ������
 * @code
 *    //��ʼ������PORTB�˿ڵ�10����Ϊ�����������
 *    GPIO_InitTypeDef GPIO_InitStruct1;      //����һ���ṹ����
 *    GPIO_InitStruct1.instance = HW_GPIOB;   //ѡ��PORTB�˿�
 *    GPIO_InitStruct1.mode = kGPIO_Mode_OPP; //�������
 *    GPIO_InitStruct1.pinx = 10;             //ѡ��10����
 *    //���ó�ʼ��GPIO���� 
 *    GPIO_Init(&GPIO_InitStruct1);
 * @endcode
 * @param[in]  GPIO_InitStruct GPIO��ʼ���ṹ�壬����������״̬����  
 * @see GPIO��ʼ����������
 * @retval None
 */
void GPIO_Init(GPIO_InitTypeDef * GPIO_InitStruct)
{
    /* config state */
    switch(GPIO_InitStruct->mode)
    {
        case kGPIO_Mode_IFT:
            PORT_PinPullConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kPullDisabled);
            PORT_PinOpenDrainConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, DISABLE);
            GPIO_PinConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kInput);
            break;
        case kGPIO_Mode_IPD:
            PORT_PinPullConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kPullDown);
            PORT_PinOpenDrainConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, DISABLE);
            GPIO_PinConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kInput);
            break;
        case kGPIO_Mode_IPU:
            PORT_PinPullConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kPullUp);
            PORT_PinOpenDrainConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, DISABLE);
            GPIO_PinConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kInput);
            break;
        case kGPIO_Mode_OOD:
            PORT_PinPullConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kPullUp);
            PORT_PinOpenDrainConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, ENABLE);
            GPIO_PinConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kOutput);
            break;
        case kGPIO_Mode_OPP:
            PORT_PinPullConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kPullDisabled);
            PORT_PinOpenDrainConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, DISABLE);
            GPIO_PinConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kOutput);
            break;
        default:
            break;					
    }
    /* config pinMux */
    PORT_PinMuxConfig(GPIO_InitStruct->instance, GPIO_InitStruct->pinx, kPinAlt1);
}

 /**
 * @brief  ���ٳ�ʼ��һ��GPIO���� ʵ������GPIO_Init���������
 * @code
 *      //��ʼ������PORTB�˿ڵ�10����Ϊ�����������
 *      GPIO_QuickInit(HW_GPIOB, 10, kGPIO_Mode_OPP);
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pinx �˿��ϵ����ź� 0~31
 * @param[in]  mode ���Ź���ģʽ
 *              @arg kGPIO_Mode_IFT ��������
 *              @arg kGPIO_Mode_IPD ��������
 *              @arg kGPIO_Mode_IPU ��������
 *              @arg kGPIO_Mode_OOD ��©���
 *              @arg kGPIO_Mode_OPP �������
 * @retval instance GPIOģ���
 */
uint8_t GPIO_QuickInit(uint32_t instance, uint32_t pinx, GPIO_Mode_Type mode)
{
    GPIO_InitTypeDef GPIO_InitStruct1;
    GPIO_InitStruct1.instance = instance;
    GPIO_InitStruct1.mode = mode;
    GPIO_InitStruct1.pinx = pinx;
    GPIO_Init(&GPIO_InitStruct1);
    return  instance;
}

 /**
 * @brief  ����ָ����������ߵ�ƽ���ߵ͵�ƽ
 * @note   �������������ó��������
 * @code
 *      //����PORTB�˿ڵ�10��������ߵ�ƽ
 *      GPIO_WriteBit(HW_GPIOB, 10, 1);
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin  �˿��ϵ����ź� 0~31
 * @param[in]  data ���ŵĵ�ƽ״̬  
 *              @arg 0  �͵�ƽ 
 *              @arg 1  �ߵ�ƽ
 * @retval None
 */
void GPIO_WriteBit(uint32_t instance, uint8_t pin, uint8_t data)
{
    SIM->SCGC5 |= SIM_GPIOClockGateTable[instance];
    (data) ? (GPIO_InstanceTable[instance]->PSOR |= (1 << pin)):(GPIO_InstanceTable[instance]->PCOR |= (1 << pin));
}

 /**
 * @brief  ��λָ�����ŵĵ�ƽ״̬����Ϊ�ߵ�ƽ��
 * @note   �������������ó��������
 * @code
 *      //��λPORTB�˿ڵ�10����
 *      GPIO_SetBit(HW_GPIOB, 10);
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin  �˿��ϵ����ź� 0~31
 * @retval None
 */
void GPIO_SetBit(uint32_t instance, uint32_t pin)
{
    GPIO_InstanceTable[instance]->PSOR |= (1 << pin);
}

 /**
 * @brief  ��λָ�����ŵĵ�ƽ״̬����Ϊ�͵�ƽ��
 * @note   �������������ó��������
 * @code
 *      //��λPORTB�˿ڵ�10����
 *      GPIO_ResetBit(HW_GPIOB, 10);
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin  �˿��ϵ����ź� 0~31
 * @retval None
 */
void GPIO_ResetBit(uint32_t instance, uint32_t pin)
{
    GPIO_InstanceTable[instance]->PCOR |= (1 << pin);
}

 /**
 * @brief  ��ȡһ�������ϵĵ�ƽ״̬
 * @code
 *      //��ȡPORTB�˿ڵ�10���ŵĵ�ƽ״̬
 *      uint8_t status ; //���ڴ洢���ŵ�״̬
 *      status = GPIO_ReadBit(HW_GPIOB, 10); //��ȡ���ŵ�״̬���洢��status��
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin  �˿��ϵ����ź� 0~31
 * @retval 0 �͵�ƽ
 * @retval 1 �ߵ�ƽ
 */
uint8_t GPIO_ReadBit(uint32_t instance, uint8_t pin)
{
    /* input or output */
    if(((GPIO_InstanceTable[instance]->PDDR) >> pin) & 0x01)
    {
        return ((GPIO_InstanceTable[instance]->PDOR >> pin) & 0x01);
    }
    else
    {
        return ((GPIO_InstanceTable[instance]->PDIR >> pin) & 0x01);
    }
}

 /**
 * @brief  ��תһ�����ŵĵ�ƽ״̬
 * @code
 *      //��תPORTB�˿ڵ�10���ŵĵ�ƽ״̬
 *      GPIO_ToggleBit(HW_GPIOB, 10); 
 * @endcode
 * @param[in]  instance: GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin  �˿��ϵ����ź� 0~31
 * @retval None
 */
void GPIO_ToggleBit(uint32_t instance, uint8_t pin)
{
    GPIO_InstanceTable[instance]->PTOR |= (1 << pin);
}

/**
 * @brief  ��ȡһ���˿�32λ������
 * @code
 *      //��ȡPORTB�˿ڵ��������ŵĵ�ƽ״̬
 *      uint32_t status ; //���ڴ洢���ŵ�״̬
 *      status = GPIO_ReadPort(HW_GPIOB); //��ȡ���ŵ�״̬���洢��status��
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @retval �˿ڵ�32λ����
 */
uint32_t GPIO_ReadPort(uint32_t instance)
{
    return (GPIO_InstanceTable[instance]->PDIR);
}
/**
 * @brief  ��һ���˿�д��32λ����
 * @code
 *      //��PORTB�˿�д��0xFFFFFFFF
 *      GPIO_WriteByte(HW_GPIOB, 0xFFFFFFFF); 
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  data  32λ����
 * @retval None
 */
void GPIO_WritePort(uint32_t instance, uint32_t data)
{
    GPIO_InstanceTable[instance]->PDOR = data;
}


/**
 * @brief  ����GPIO�����ж����ͻ���DMA����
 * @code
 *      //����PORTB�˿ڵ�10����Ϊ�½��ش����ж�
 *      GPIO_ITDMAConfig(HW_GPIOB, 10, kGPIO_IT_FallingEdge, true); 
 * @endcode
 * @param[in]  instance GPIOģ���
 *              @arg HW_GPIOA оƬ��PORTA�˿�
 *              @arg HW_GPIOB оƬ��PORTB�˿�
 *              @arg HW_GPIOC оƬ��PORTC�˿�
 *              @arg HW_GPIOD оƬ��PORTD�˿�
 *              @arg HW_GPIOE оƬ��PORTE�˿�
 * @param[in]  pin �˿��ϵ����ź� 0~31
 * @param[in]  config ����ģʽ
 *              @arg kGPIO_DMA_RisingEdge DMA�����ش���
 *              @arg kGPIO_DMA_FallingEdge DMA�½��ش���
 *              @arg kGPIO_DMA_RisingFallingEdge DMA�������½��ض�����
 *              @arg kGPIO_IT_Low �͵�ƽ�����ж�
 *              @arg kGPIO_IT_RisingEdge �����ش����ж�
 *              @arg kGPIO_IT_FallingEdge �½��ش����ж�
 *              @arg kGPIO_IT_RisingFallingEdge �������½��ض������ж�
 *              @arg kGPIO_IT_High �ߵ�ƽ�����ж�
 * @param[in]  status �Ƿ�ʹ��
 *              @arg 0 disable
 *              @arg 1 enable
 * @retval None
 */
void GPIO_ITDMAConfig(uint32_t instance, uint8_t pin, GPIO_ITDMAConfig_Type config, bool status)
{
    /* init moudle */
    SIM->SCGC5 |= SIM_GPIOClockGateTable[instance];
    PORT_InstanceTable[instance]->PCR[pin] &= ~PORT_PCR_IRQC_MASK;
    if(!status)
    {
        NVIC_DisableIRQ(GPIO_IRQnTable[instance]);
        return;
    }
    
    switch(config)
    {
        case kGPIO_DMA_RisingEdge:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_IRQC(1);
            break;
        case kGPIO_DMA_FallingEdge:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_IRQC(2);
            break;
        case kGPIO_DMA_RisingFallingEdge:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_IRQC(3);
            break;
        case kGPIO_IT_Low:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_IRQC(8);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        case kGPIO_IT_RisingEdge:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_IRQC(9);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        case kGPIO_IT_FallingEdge:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_IRQC(10);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        case kGPIO_IT_RisingFallingEdge:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_IRQC(11);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        case kGPIO_IT_High:
            PORT_InstanceTable[instance]->PCR[pin] |= PORT_PCR_IRQC(12);
            NVIC_EnableIRQ(GPIO_IRQnTable[instance]);
            break;
        default:
            break;
    }
}
/**
 * @brief  ע���жϻص�����
 * @code
 *      //ע��PTB10��EXTI�жϻص�����
 *      void PTB10_EXTI_ISR(uint32_t pinxArray)
 *      {
 *          if(pinxArray & (1u << 10))
 *              ;//�û��Զ��庯������
 *      }
 *      GPIO_CallbackInstall(instance,PTB10_EXTI_ISR);
 * @endcode
 * @attention  �ûص����������βε�
 * @param[in]  instance GPIOģ���ж���ں�
 *              @arg HW_GPIOA оƬ��PORTA�˿��ж����
 *              @arg HW_GPIOB оƬ��PORTB�˿��ж����
 *              @arg HW_GPIOC оƬ��PORTC�˿��ж����
 *              @arg HW_GPIOD оƬ��PORTD�˿��ж����
 *              @arg HW_GPIOE оƬ��PORTE�˿��ж����
 * @param[in]  AppCBFun �ص�����ָ�����
 * @retval None
 * @see ���ڴ˺����ľ���Ӧ�������Ӧ��ʵ��
 */
void GPIO_CallbackInstall(uint32_t instance, GPIO_CallBackType AppCBFun)
{
    /* init moudle */
//    SIM->SCGC5 |= SIM_GPIOClockGateTable[instance];
    if(AppCBFun != NULL)
    {
        GPIO_CallBackTable[instance] = AppCBFun;
    }
}


/**
 * @brief  GPIO�ж��ܴ��������û�һ������ʹ�ú��޸�
 * @param[in]  instance GPIOģ���ж���ں�
 *              @arg HW_GPIOA оƬ��PORTA�˿��ж����
 *              @arg HW_GPIOB оƬ��PORTB�˿��ж����
 *              @arg HW_GPIOC оƬ��PORTC�˿��ж����
 *              @arg HW_GPIOD оƬ��PORTD�˿��ж����
 *              @arg HW_GPIOE оƬ��PORTE�˿��ж����
 * @attention ��̬�����������ļ��ɼ�
 * @retval None
 */
static void PORT_IRQHandler(uint32_t instance)
{
    uint32_t ISFR;
    /* safe copy */
    ISFR = PORT_InstanceTable[instance]->ISFR;
    /* clear IT pending bit */
    PORT_InstanceTable[instance]->ISFR = 0xFFFFFFFF;
    if(GPIO_CallBackTable[instance])
    {
        GPIO_CallBackTable[instance](ISFR);
    }
}

/**
 * @brief  ϵͳGPIO�жϺ������û�����ʹ��
 */
void PORTA_IRQHandler(void)
{
    PORT_IRQHandler(HW_GPIOA);
}

/**
 * @brief  ϵͳGPIO�жϺ������û�����ʹ��
 */
void PORTB_IRQHandler(void)
{
    PORT_IRQHandler(HW_GPIOB);
}

///**
// * @brief  ϵͳGPIO�жϺ������û�����ʹ��
// */
//void PORTC_IRQHandler(void)
//{
//    PORT_IRQHandler(HW_GPIOC);
//}

/**
 * @brief  ϵͳGPIO�жϺ������û�����ʹ��
 */
void PORTD_IRQHandler(void)
{
    PORT_IRQHandler(HW_GPIOD);
}

/**
 * @brief  ϵͳGPIO�жϺ������û�����ʹ��
 */
void PORTE_IRQHandler(void)
{
    PORT_IRQHandler(HW_GPIOE);
}

#if (defined(MK70F12))
/**
 * @brief  ϵͳGPIO�жϺ������û�����ʹ��
 */
void PORTF_IRQHandler(void)
{
    PORT_IRQHandler(HW_GPIOF);
}
#endif



#include "include.h" 
 
extern int16_t accel[3],gyro[3];   
extern uint32_t I2C_GetInstance(I2C_Type *base);
 
uint8_t *img_buff; 
uint8_t ImageBuffer[60][80]; 
uint8_t gImageBuffer[OV7620_H * OV7620_W / 8]; 
uint8_t eImageBuffer[(OV7620_H)*((OV7620_W/8)+1)]; 
uint8_t pImageBuffer[(OV7620_H)*((OV7620_W/8)+1)]; 
uint8_t hImageBuffer[OV7620_H*OV7620_W]; 
uint8_t Image_Distortion[OV7620_H][OV7620_W]; 
float Ware[WaveSize];
volatile Image_Status Image_Flag = Idle;

/* Define the init structure for the input VSY pin */ 
gpio_pin_config_t VSY_config = { 
        kGPIO_DigitalInput, 0,    
}; 
/* Define the init structure for the input PCLK pin */ 
gpio_pin_config_t PCLK_config = { 
        kGPIO_DigitalInput, 0, 
};
/* Define the init structure for the input DATA pin */ 
gpio_pin_config_t Data_config = { 
        kGPIO_DigitalInput, 0, 
};
/////////////////////////////////////////////////////
void PORTC_IRQHandler(void) 
{ 
    OV7725_ISR(PORTC->ISFR);
}
void DMA0_DMA16_IRQHandler(void) 
{ 
    OV7725_Eagle_DMA();
}  
DMA_InitTypeDef DMA_InitStructure = {0};

void Camera_Init(void)
{
        uint32_t i;		

        if(SCCB_Init(I2C1_SCL_PC10_SDA_PC11))
        { 
            printf("no ov7725device found!\r\n");
            while(1);
        } 
        printf("OV7725 setup complete\r\n");    
        
        img_buff = gImageBuffer;

        /* Init input VSY GPIO. */
        PORT_SetPinInterruptConfig(PORTC, BOARD_OV7620_VSYNC_PIN, kPORT_InterruptRisingEdge);//kPORT_InterruptFallingEdge);
        EnableIRQ(PORTC_IRQn);//61  true  enable
        GPIO_PinInit(GPIOC, BOARD_OV7620_VSYNC_PIN, &VSY_config);
        /* Init input PCLK GPIO. */
        PORT_SetPinInterruptConfig(PORTC, BOARD_OV7620_PCLK_PIN, kPORT_DMAFallingEdge);
        EnableIRQ(DMA0_DMA16_IRQn);//0  true  enable
        GPIO_PinInit(GPIOC, BOARD_OV7620_PCLK_PIN, &PCLK_config); 

        /* Init input DATA GPIO. */
        for(i=0;i<8;i++)
        { 
              GPIO_PinInit(GPIOD, BOARD_OV7620_DATA_OFFSET+i, &Data_config);
        } 
        DMA_InitStructure.chl = HW_DMA_CH0;
        DMA_InitStructure.chlTriggerSource = PORTC_DMAREQ;
        DMA_InitStructure.triggerSourceMode = kDMA_TriggerSource_Normal;
        DMA_InitStructure.minorLoopByteCnt = 1;
        DMA_InitStructure.majorLoopCnt = ((OV7620_W/8) +1);

        DMA_InitStructure.sAddr = (uint32_t)&GPIOD->PDIR + BOARD_OV7620_DATA_OFFSET/8;
        DMA_InitStructure.sLastAddrAdj = 0;
        DMA_InitStructure.sAddrOffset = 0;
        DMA_InitStructure.sDataWidth = kDMA_DataWidthBit_8;
        DMA_InitStructure.sMod = kDMA_ModuloDisable;

        DMA_InitStructure.dAddr = (uint32_t)img_buff;
        DMA_InitStructure.dLastAddrAdj = 0;
        DMA_InitStructure.dAddrOffset = 1;
        DMA_InitStructure.dDataWidth = kDMA_DataWidthBit_8;
        DMA_InitStructure.dMod = kDMA_ModuloDisable;
     
        DMA_Init(&DMA_InitStructure);
}

int SCCB_Init(uint32_t I2C_MAP)
{
        int r;
        uint32_t instance;
        instance = I2C_QuickInit(I2C_MAP, 50*1000);
        r = ov7725_probe(instance);
        if(r) 
        { 
            return 1;
        } 
        r = ov7725_set_image_size(User_Size);

        if(r) 
        { 
            printf("OV7725 set image error\r\n");
            return 1;
        } 
        return 0;
}

void OV7725_ISR(uint32_t index)
{
        if(index & (1 << BOARD_OV7620_VSYNC_PIN))
        { 
                      DMA_EnableRequest(HW_DMA_CH0);    
                      DMA_SetDestAddress(HW_DMA_CH0 ,(uint32_t)img_buff);
                      DMA_SetMajorLoopCounter(HW_DMA_CH0 ,(OV7620_W/8)*OV7620_H);
                      PORT_SetPinInterruptConfig(PORTC, BOARD_OV7620_VSYNC_PIN, kPORT_InterruptRisingEdge);//kPORT_InterruptFallingEdge);
                      DisableIRQ(PORTC_IRQn);
                      PORTC->ISFR = 0xFFFFFFFF;
                      Image_Flag = Complete; 
        } 
}

void OV7725_Eagle_DMA(void)
{								
  	DMA_DisableRequest(HW_DMA_CH0);	
	Image_Flag = Complete; 		
}

void Img_Extract(uint8_t *Dst, uint8_t *Src, uint32_t Srclen)
{
        uint8_t Colour[2] = {1, 0};
        uint8_t Tmpsrc;
        while(Srclen --)
        {
            Tmpsrc = *Src++;
            *Dst++ = Colour[ (Tmpsrc >> 7 ) & 0x01 ];
            *Dst++ = Colour[ (Tmpsrc >> 6 ) & 0x01 ];
            *Dst++ = Colour[ (Tmpsrc >> 5 ) & 0x01 ];
            *Dst++ = Colour[ (Tmpsrc >> 4 ) & 0x01 ];
            *Dst++ = Colour[ (Tmpsrc >> 3 ) & 0x01 ];
            *Dst++ = Colour[ (Tmpsrc >> 2 ) & 0x01 ];
            *Dst++ = Colour[ (Tmpsrc >> 1 ) & 0x01 ];
            *Dst++ = Colour[ (Tmpsrc >> 0 ) & 0x01 ];
        }
}

void Send_Grayscale(void)
{
	Img_Extract(hImageBuffer ,gImageBuffer, (OV7620_H)*((OV7620_W/8)));
	UART_WriteByte(UART0,0x01);
	UART_WriteByte(UART0,0xFE);
	UART_WriteBytes(UART0, hImageBuffer, OV7620_H*OV7620_W);
	UART_WriteByte(UART0,0XFE);
	UART_WriteByte(UART0,0X01);
}

void Send_Binary(uint8_t *Image)
{
	UART_WriteByte(UART0,0x01);
	UART_WriteByte(UART0,0xFE);
	UART_WriteBytes(UART0, Image, (OV7620_H)*((OV7620_W/8)));
	UART_WriteByte(UART0,0XFE);
	UART_WriteByte(UART0,0X01);
}

void UART_WriteBytes(UART_Type *instance,  uint8_t *Buff, uint32_t Length) 
{ 
        while(Length--) 
        { 
            UART_WriteByte(instance, *Buff);
            Buff++;
        } 
} 
 
void VCAN_SendWare(void *wareaddr, uint32_t waresize)
{ 
        #define CMD_WARE     1
        uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};
        uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};
        UART_WriteBytes(UART0, cmdf, sizeof(cmdf));
        UART_WriteBytes(UART0, (uint8_t *)wareaddr, waresize);
        UART_WriteBytes(UART0, cmdr, sizeof(cmdr));
} 
#include "Board_Gyro.h"

void L3G4_spi_init(void);
static void L3G4_writereg(uint8 reg, uint8 dat);
static uint8 L3G4_readreg(uint8 reg);

char Start_Gyro_X_Flag = 0;   //陀螺仪X
char Start_Gyro_Y_Flag = 0;   //陀螺仪Y
char Start_Gyro_Z_Flag = 0;   //陀螺仪Z

int16 L3G4_Read_X();
int16 L3G4_Read_Y();
int16 L3G4_Read_Z();
Coord Angle = {0,0,0};

unsigned char Board_Gyro_Init(void)
{
  L3G4_spi_init();
  
  L3G4_writereg(0x20, 0x0F);
  L3G4_writereg(0x22, 0x08);
  L3G4_writereg(0x23, 0x30);
  
  L3G4_writereg(0x20, 0x0F);
  L3G4_writereg(0x22, 0x08);
  L3G4_writereg(0x23, 0x30);
  
  return 1;
}

/*------------------------------------------------------------------------------
L3G4+向寄存器里面写数据
参数：
    reg：寄存器
    dat：所要写的值
备注：
 -----------------------------------------------------------------------------*/
static void L3G4_writereg(uint8 reg, uint8 dat)
{
    uint8 buff[2];

    buff[0] = reg;

    buff[1] = dat;

    spi_mosi(SPI2, SPI_PCS0, buff, NULL, 2); //发送buff里数据,并采集到 buff里
}

void L3G4_spi_init(void)
{

//使能SPI模块时钟，配置SPI引脚功能
	SIM_SCGC3 |= SIM_SCGC3_SPI2_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	PORTB_ISFR = 1<<21;
	PORTB_PCR21 |= PORT_PCR_MUX(2);
	
	PORTB_ISFR = 1<<22;
	PORTB_PCR22 |= PORT_PCR_MUX(2);
	
	PORTB_ISFR = 1<<23;
	PORTB_PCR23 |= PORT_PCR_MUX(2);

	PORTB_ISFR = 1<<20;
	PORTB_PCR20 |= PORT_PCR_MUX(2);

	SPI2_MCR = ( 0
			| SPI_MCR_CLR_TXF_MASK     //清空 Tx FIFO 计数器
			| SPI_MCR_CLR_RXF_MASK     //清空 Rx FIFO 计数器
			| SPI_MCR_HALT_MASK        //停止SPI传输
			|  SPI_MCR_MSTR_MASK        //Master,主机模式
			|  SPI_MCR_PCSIS(1)
			|  SPI_MCR_PCSIS_MASK
		      );

//清标志位
	SPI2_SR = (0
		      | SPI_SR_EOQF_MASK    //发送队列空了，发送完毕
		      | SPI_SR_TFUF_MASK    //传输FIFO下溢标志位，SPI为从机模式，Tx FIFO为空，而外部SPI主机模式启动传输，标志位就会置1，写1清0
		      | SPI_SR_TFFF_MASK    //传输FIFO满标志位。 写1或者DMA控制器发现传输FIFO满了就会清0。 0表示Tx FIFO满了
		      | SPI_SR_RFOF_MASK    //接收FIFO溢出标志位。
		      | SPI_SR_RFDF_MASK    //接收FIFO损耗标志位，写1或者DMA控制器发现传输FIFO空了就会清0。0表示Rx FIFO空
		     );
        SPI2_CTAR0 = (0
                                       //| SPI_CTAR_DBR_MASK    //双波特率 ，假设 DBR=1，CPHA=1，PBR=00，得SCK Duty Cycle 为 50/50
                                       | SPI_CTAR_CPHA_MASK   //······数据在SCK上升沿改变（输出），在下降沿被捕捉（输入读取）。如果是0，则反之。  w25x16在上升沿读取数据；NRF24L01在上升沿读取数据
                                       | SPI_CTAR_PBR(0)       //我选择0 //波特率分频器 ，0~3 对应的分频值Prescaler为 2、3、5、7

                                       | SPI_CTAR_PDT(0x00)     //延时因子为 PDT*2+1 ，这里PDT为3，即延时因子为7。PDT为2bit
                                       | SPI_CTAR_BR(0)         //我选择0 //波特率计数器值 ,当BR<=3,分频Scaler 为 2*（BR+1） ，当BR>=3，分频Scaler 为 2^BR  。BR为4bit
                                       //SCK 波特率 = (Bus clk/Prescaler) x [(1+DBR)/Scaler ]          fSYS 为 Bus clock
                                       //              50M / 2         x [ 1  /  2  ] = 25M   这里以最大的来算

                                       | SPI_CTAR_CPOL_MASK   //时钟极性，1表示 SCK 不活跃状态为高电平,   NRF24L01 不活跃为低电平······
                                       | SPI_CTAR_FMSZ(0x07)    //每帧传输 7bit+1 ，即8bit （FMSZ默认就是8）
                                       // | SPI_CTAR_LSBFE_MASK //1为低位在前。
                                       //| SPI_CTAR_CSSCK(1)    //
                                       //|SPI_CTAR_PCSSCK(2)    //设置片选信号有效到时钟第一个边沿出现的延时的预分频值。tcsc延时预分频 2*x+1；
                                      );

	SPI2_MCR &= ~SPI_MCR_HALT_MASK;     //启动SPI传输。1为暂停，0为启动

}

int16 L3G4_Read_X()
{
    uint8 X_L,X_H;

    int16 XHL;

    X_L = (uint8)(L3G4_readreg(0xA8));//0X28|0X80 = 0XA8

    X_H = (uint8)(L3G4_readreg(0xA9));

    XHL = (int16)((X_H<<8)|X_L);

    return (XHL);
}

int16 L3G4_Read_Y()
{
    uint8 Y_L,Y_H;

    int16 YHL;

    Y_L = (uint8)(L3G4_readreg(0xAA));//0X2A|0X80 = 0xAA

    Y_H = (uint8)(L3G4_readreg(0xAB));

    YHL = (int16)((Y_H<<8)|Y_L);

    return (YHL);
}

int16 L3G4_Read_Z()
{
    uint8 Z_L,Z_H;

    int16 ZHL;

    Z_L = (uint8)(L3G4_readreg(0xAC));//0X2C|0X80 = 0XAC

    Z_H = (uint8)(L3G4_readreg(0xAD));

    ZHL = (int16)((Z_H<<8)|Z_L);

    return (ZHL);
}

/*------------------------------------------------------------------------------
L3G4+读寄存器
参数：
    reg：寄存器
    dat：需要读取的数据的存放地址
    return:读到的值
返回：读到的数值
个人小理解：野火的spi_mosi(SPI2, SPIn_PCS0, buff, buff, 2);这个函数里面的buff
            还是作为临时参数比较合适
 -----------------------------------------------------------------------------*/
static uint8 L3G4_readreg(uint8 reg)
{

    uint8 buff[2];

    buff[0] = reg;//先发送寄存器

    spi_mosi(SPI2, SPI_PCS0, buff, buff, 2); //发送buff数据，并保存到buff里

    return buff[1];//提取第二个数据
}

int Gyro_Read_X(void)
{
  int16 dis_data = 0;
  
  float temp = 0;
  
  dis_data = L3G4_Read_X();
  
  if((dis_data&0x8000) == 0x8000)     //补码转原码
  {
      dis_data = (~dis_data);
      dis_data &=0x7fff;
      temp=(float)dis_data*0.07;               // 数据手册 第9页，2000度/秒量程
      
      Angle.x -= (int)(temp);
  }
  else
  {
      temp=(float)dis_data*0.07;               // 数据手册 第9页，2000度/秒量程
      
      Angle.x += (int)(temp);
  }    
  return Angle.x;
}

int Gyro_Read_Y(void)
{
  int16 dis_data = 0;
  
  float temp = 0;
  
  dis_data = L3G4_Read_Y();
  
  if((dis_data&0x8000) == 0x8000)     //补码转原码
  {
      dis_data = (~dis_data);
      dis_data &=0x7fff;
      temp=(float)dis_data*0.07;               // 数据手册 第9页，2000度/秒量程
      
      Angle.y -= (int)(temp);
  }
  else
  {
      temp=(float)dis_data*0.07;               // 数据手册 第9页，2000度/秒量程
      
      Angle.y += (int)(temp);
  }    
  return Angle.y;
}

int Gyro_Read_Z(void)
{
  int16 dis_data = 0;
  
  float temp = 0;
  
  dis_data = L3G4_Read_Z();
  
  if((dis_data&0x8000) == 0x8000)     //补码转原码
  {
      dis_data = (~dis_data);
      dis_data &=0x7fff;
      temp=(float)dis_data*0.07;               // 数据手册 第9页，2000度/秒量程
      
      Angle.z -= (int16)(temp);
  }
  else
  {
      temp=(float)dis_data*0.07;               // 数据手册 第9页，2000度/秒量程
      
      Angle.z += (int16)(temp);
  }    
  return Angle.z;
}


void Gyro_Angle_IRQ(void)
{
  if(Start_Gyro_X_Flag)
  {
    Gyro_Read_X();
  }
  
  if(Start_Gyro_Y_Flag)
  {
    Gyro_Read_Y();
  }
  
  if(Start_Gyro_Z_Flag)
  {
    Gyro_Read_Z();
  }
}



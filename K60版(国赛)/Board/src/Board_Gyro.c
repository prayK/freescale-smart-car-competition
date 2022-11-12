#include "Board_Gyro.h"

void L3G4_spi_init(void);
static void L3G4_writereg(uint8 reg, uint8 dat);
static uint8 L3G4_readreg(uint8 reg);

char Start_Gyro_X_Flag = 0;   //������X
char Start_Gyro_Y_Flag = 0;   //������Y
char Start_Gyro_Z_Flag = 0;   //������Z

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
L3G4+��Ĵ�������д����
������
    reg���Ĵ���
    dat����Ҫд��ֵ
��ע��
 -----------------------------------------------------------------------------*/
static void L3G4_writereg(uint8 reg, uint8 dat)
{
    uint8 buff[2];

    buff[0] = reg;

    buff[1] = dat;

    spi_mosi(SPI2, SPI_PCS0, buff, NULL, 2); //����buff������,���ɼ��� buff��
}

void L3G4_spi_init(void)
{

//ʹ��SPIģ��ʱ�ӣ�����SPI���Ź���
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
			| SPI_MCR_CLR_TXF_MASK     //��� Tx FIFO ������
			| SPI_MCR_CLR_RXF_MASK     //��� Rx FIFO ������
			| SPI_MCR_HALT_MASK        //ֹͣSPI����
			|  SPI_MCR_MSTR_MASK        //Master,����ģʽ
			|  SPI_MCR_PCSIS(1)
			|  SPI_MCR_PCSIS_MASK
		      );

//���־λ
	SPI2_SR = (0
		      | SPI_SR_EOQF_MASK    //���Ͷ��п��ˣ��������
		      | SPI_SR_TFUF_MASK    //����FIFO�����־λ��SPIΪ�ӻ�ģʽ��Tx FIFOΪ�գ����ⲿSPI����ģʽ�������䣬��־λ�ͻ���1��д1��0
		      | SPI_SR_TFFF_MASK    //����FIFO����־λ�� д1����DMA���������ִ���FIFO���˾ͻ���0�� 0��ʾTx FIFO����
		      | SPI_SR_RFOF_MASK    //����FIFO�����־λ��
		      | SPI_SR_RFDF_MASK    //����FIFO��ı�־λ��д1����DMA���������ִ���FIFO���˾ͻ���0��0��ʾRx FIFO��
		     );
        SPI2_CTAR0 = (0
                                       //| SPI_CTAR_DBR_MASK    //˫������ ������ DBR=1��CPHA=1��PBR=00����SCK Duty Cycle Ϊ 50/50
                                       | SPI_CTAR_CPHA_MASK   //������������������SCK�����ظı䣨����������½��ر���׽�������ȡ���������0����֮��  w25x16�������ض�ȡ���ݣ�NRF24L01�������ض�ȡ����
                                       | SPI_CTAR_PBR(0)       //��ѡ��0 //�����ʷ�Ƶ�� ��0~3 ��Ӧ�ķ�ƵֵPrescalerΪ 2��3��5��7

                                       | SPI_CTAR_PDT(0x00)     //��ʱ����Ϊ PDT*2+1 ������PDTΪ3������ʱ����Ϊ7��PDTΪ2bit
                                       | SPI_CTAR_BR(0)         //��ѡ��0 //�����ʼ�����ֵ ,��BR<=3,��ƵScaler Ϊ 2*��BR+1�� ����BR>=3����ƵScaler Ϊ 2^BR  ��BRΪ4bit
                                       //SCK ������ = (Bus clk/Prescaler) x [(1+DBR)/Scaler ]          fSYS Ϊ Bus clock
                                       //              50M / 2         x [ 1  /  2  ] = 25M   ��������������

                                       | SPI_CTAR_CPOL_MASK   //ʱ�Ӽ��ԣ�1��ʾ SCK ����Ծ״̬Ϊ�ߵ�ƽ,   NRF24L01 ����ԾΪ�͵�ƽ������������
                                       | SPI_CTAR_FMSZ(0x07)    //ÿ֡���� 7bit+1 ����8bit ��FMSZĬ�Ͼ���8��
                                       // | SPI_CTAR_LSBFE_MASK //1Ϊ��λ��ǰ��
                                       //| SPI_CTAR_CSSCK(1)    //
                                       //|SPI_CTAR_PCSSCK(2)    //����Ƭѡ�ź���Ч��ʱ�ӵ�һ�����س��ֵ���ʱ��Ԥ��Ƶֵ��tcsc��ʱԤ��Ƶ 2*x+1��
                                      );

	SPI2_MCR &= ~SPI_MCR_HALT_MASK;     //����SPI���䡣1Ϊ��ͣ��0Ϊ����

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
L3G4+���Ĵ���
������
    reg���Ĵ���
    dat����Ҫ��ȡ�����ݵĴ�ŵ�ַ
    return:������ֵ
���أ���������ֵ
����С��⣺Ұ���spi_mosi(SPI2, SPIn_PCS0, buff, buff, 2);������������buff
            ������Ϊ��ʱ�����ȽϺ���
 -----------------------------------------------------------------------------*/
static uint8 L3G4_readreg(uint8 reg)
{

    uint8 buff[2];

    buff[0] = reg;//�ȷ��ͼĴ���

    spi_mosi(SPI2, SPI_PCS0, buff, buff, 2); //����buff���ݣ������浽buff��

    return buff[1];//��ȡ�ڶ�������
}

int Gyro_Read_X(void)
{
  int16 dis_data = 0;
  
  float temp = 0;
  
  dis_data = L3G4_Read_X();
  
  if((dis_data&0x8000) == 0x8000)     //����תԭ��
  {
      dis_data = (~dis_data);
      dis_data &=0x7fff;
      temp=(float)dis_data*0.07;               // �����ֲ� ��9ҳ��2000��/������
      
      Angle.x -= (int)(temp);
  }
  else
  {
      temp=(float)dis_data*0.07;               // �����ֲ� ��9ҳ��2000��/������
      
      Angle.x += (int)(temp);
  }    
  return Angle.x;
}

int Gyro_Read_Y(void)
{
  int16 dis_data = 0;
  
  float temp = 0;
  
  dis_data = L3G4_Read_Y();
  
  if((dis_data&0x8000) == 0x8000)     //����תԭ��
  {
      dis_data = (~dis_data);
      dis_data &=0x7fff;
      temp=(float)dis_data*0.07;               // �����ֲ� ��9ҳ��2000��/������
      
      Angle.y -= (int)(temp);
  }
  else
  {
      temp=(float)dis_data*0.07;               // �����ֲ� ��9ҳ��2000��/������
      
      Angle.y += (int)(temp);
  }    
  return Angle.y;
}

int Gyro_Read_Z(void)
{
  int16 dis_data = 0;
  
  float temp = 0;
  
  dis_data = L3G4_Read_Z();
  
  if((dis_data&0x8000) == 0x8000)     //����תԭ��
  {
      dis_data = (~dis_data);
      dis_data &=0x7fff;
      temp=(float)dis_data*0.07;               // �����ֲ� ��9ҳ��2000��/������
      
      Angle.z -= (int16)(temp);
  }
  else
  {
      temp=(float)dis_data*0.07;               // �����ֲ� ��9ҳ��2000��/������
      
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



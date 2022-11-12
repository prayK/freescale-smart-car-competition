#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum _pin_mux_direction
{
  kPIN_MUX_DirectionInput = 0U,         /* Input direction */
  kPIN_MUX_DirectionOutput = 1U,        /* Output direction */
  kPIN_MUX_DirectionInputOrOutput = 2U  /* Input or output direction */
} pin_mux_direction_t;


void BOARD_InitBootPins(void);
void BOARD_InitPins(void); //����ͷ�����У�����IO��ʼ��
void BOARD_InitData(void); //����ͷ���ݿڳ�ʼ��
void BOARD_InitOled(void); //OLED��ʼ��
void BOARD_InitLed(void);  //led�ͷ�����IO�ڳ�ʼ��
void BOARD_InitMotorFtm(void);//���
void BOARD_InitServoFtm(void);//���
void BOARD_InitUart(void);//����IO�ڳ�ʼ��
void BOARD_InitI2c(void); //IIC��ʼ��������IO�ڱ�SCCB���ˣ������
void BOARD_InintButtons(void); //��λ���뿪��IO��ʼ��
void BOARD_InitFtmquad(void);  //������IO�ڳ�ʼ��


#if defined(__cplusplus)
}
#endif

#endif 

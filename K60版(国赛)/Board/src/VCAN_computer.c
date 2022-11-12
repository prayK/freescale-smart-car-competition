#include "common.h"
#include "MK60_uart.h"
#include "VCAN_computer.h"


void vcan_sendimg(void *imgaddr, uint32_t imgsize)
{
#define CMD_IMG     1
    uint8_t cmdf[2] = {CMD_IMG, ~CMD_IMG};    //ɽ����λ�� ʹ�õ�����
    uint8_t cmdr[2] = {~CMD_IMG, CMD_IMG};    //ɽ����λ�� ʹ�õ�����

    uart_putbuff(VCAN_PORT, cmdf, sizeof(cmdf));    //�ȷ�������
    uart_putbuff(VCAN_PORT, (uint8_t *)imgaddr, imgsize); //�ٷ���ͼ��
    uart_putbuff(VCAN_PORT, cmdr, sizeof(cmdr));    //�ȷ�������
}


void vcan_sendware(void *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //���ڵ��� ʹ�õ�ǰ����
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //���ڵ��� ʹ�õĺ�����

    uart_putbuff(VCAN_PORT, cmdf, sizeof(cmdf));    //�ȷ���ǰ����
    uart_putbuff(VCAN_PORT, (uint8_t *)wareaddr, waresize);    //��������
    uart_putbuff(VCAN_PORT, cmdr, sizeof(cmdr));    //���ͺ�����

}
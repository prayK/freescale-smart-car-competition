#include "common.h"
#include "MK66_uart.h"
#include "COMMUNICATION.H"

//中南黄竞辉上位机发送图像数据 //下位机通信协议还没写好
//void SendPicData(UARTn_e uartn, uint8 *data, uint16 size, uint16 width, uint16 hight)
//{
//        uint8 psize[2] = {0};
//        uart_putbuff(VCAN_PORT, SendHead, 4);
//        uart_putchar(VCAN_PORT, 250);
//        TransToU16(psize, size + 4);
//        uart_putbuff(VCAN_PORT, psize, sizeof(psize));
//        
//        TransToU16(psize, width);
//        uart_putbuff(VCAN_PORT, psize, sizeof(psize));
//        TransToU16(psize, hight);
//        uart_putbuff(VCAN_PORT, psize, sizeof(psize));
//        uart_putchar(VCAN_PORT, data, size);
//        uart_putchar(VCAN_PORT, 0x0A);///最后一位校验
//}

//逐飞上位机图像
void seekfree_sendimg_7725(void *imgaddr, uint32_t imgsize)
{
        uart_putchar(VCAN_PORT, 0x00);
        uart_putchar(VCAN_PORT, 0xff);
        uart_putchar(VCAN_PORT, 0x01);
        uart_putchar(VCAN_PORT, 0x01); 
        uart_putbuff(VCAN_PORT, (uint8_t *)imgaddr, imgsize);   
}

//山外上位机图像
void vcan_sendimg(void *imgaddr, uint32_t imgsize)
{
    #define CMD_IMG     1
        uint8_t cmdf[2] = {CMD_IMG, ~CMD_IMG};    
        uint8_t cmdr[2] = {~CMD_IMG, CMD_IMG};    
        uart_putbuff(VCAN_PORT, cmdf, sizeof(cmdf));    
        uart_putbuff(VCAN_PORT, (uint8_t *)imgaddr, imgsize); 
        uart_putbuff(VCAN_PORT, cmdr, sizeof(cmdr));
}

//山外上位机虚拟示波器
void vcan_sendware(void *wareaddr, uint32_t waresize)
{
    #define CMD_WARE     3
        uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};
        uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};
        uart_putbuff(VCAN_PORT, cmdf, sizeof(cmdf));
        uart_putbuff(VCAN_PORT, (uint8_t *)wareaddr, waresize);
        uart_putbuff(VCAN_PORT, cmdr, sizeof(cmdr));
}
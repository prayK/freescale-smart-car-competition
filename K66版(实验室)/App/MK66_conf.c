#include    "common.h"
#include    "include.h"

#if (USE_LCD == LCD_ILI9341)
extern lcd_t   lcd_ili9341;
lcd_t *  glcd =  &lcd_ili9341;

#elif  (USE_LCD == LCD_ST7735S)
extern lcd_t   lcd_st7735s;
lcd_t *  glcd =  &lcd_st7735s;

#elif  (USE_LCD == LCD_ST7735R)
extern lcd_t   lcd_st7735r;
lcd_t *  glcd =  &lcd_st7735r;

#elif  (USE_LCD == LCD_ILI9325)
extern lcd_t   lcd_ili9325;
lcd_t *  glcd =  &lcd_ili9325;
#endif

void soft_delay_us(uint32_t us)
{
        volatile  uint32_t i=us,j;
        while(i--)
        {
                j=0x1000;
                while(j--);
        }
}

void soft_delay_ms(uint32_t ms)
{
        volatile  uint32_t i=ms;
        while(i--)
        {
                soft_delay_us(1000);
        }
}

const char ASSERT_FAILED_STR[] = "Assertion failed in %s at line %d\n";

void assert_failed(char *file, int line)
{
    led_init(LED0);
    while (1)
    {
        DEBUG_PRINTF(ASSERT_FAILED_STR, file, line);      //通过串口提示断言失败
        //死循环等待程序员检测为何断言失败
        led_turn(LED0);
        soft_delay_ms(1000);
    }
}

/*!
 *  @brief      重定义printf 到串口
 *  @param      ch      需要打印的字节
 *  @param      stream  数据流
 *  @since      v5.0
 *  @note       此函数由山外库FWD里的printf所调用
 */
int enter_fputc(char ch)
{
    uart_putchar(VCAN_PORT, (char)ch);
    return(ch);
}


/*!
 *  @brief      默认中断服务函数
 *  @since      v5.0
 *  @note       此函数写入中断向量表里，不需要用户执行
 */
void default_isr(void)
{
#ifdef  DEBUG_MODE
#define VECTORNUM    ((SCB_ICSR & SCB_ICSR_VECTACTIVE_MASK)>>SCB_ICSR_VECTACTIVE_SHIFT)
                            //等效于 (*(volatile uint8_t*)(0xE000ED04))
    uint8 vtr = VECTORNUM;
    char  str[100];
    get_isr_info(str);       //获取中断信息
    led_init(LED1);
    while(1)
    {
        led_turn(LED1);
        DEBUG_PRINTF("\nvector=%d\n", vtr);
        DEBUG_PRINTF(str);      //把中断信息发送出去
        soft_delay_ms(1000);
    }
#else
    return;
#endif
}

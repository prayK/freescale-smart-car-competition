#ifndef __MK66_CONF_H__
#define __MK66_CONF_H__


#define LCD_ST7735S     1 
#define USE_LCD         LCD_ST7735S  

#define DEBUG_PRINT

#define EXTAL_IN_MHz            (16)

#define CORE_CLK                PLL180      // 从 PLL_e 里选择 已提供的 配置方案
                                            // bus 、 flex bus 、 flash 频率 都是 core 整数倍分频而来
#define MAX_BUS_CLK             100         // bus      (bus        >= core/16  )
#define MAX_FLEXBUS_CLK         25          // flex bus (flex bus   >= core/16  )
#define MAX_FLASH_CLK           28          // flash    (flash      >= core/16  )

#define VCAN_PORT           UART3
#define VCAN_BAUD           115200

#define DELAY()         systick_delay_ms(500)
#define DELAY_MS(ms)    systick_delay_ms(ms)
#define DELAY_US(us)    systick_delay_us(us)

extern void soft_delay_ms(uint32_t ms);
extern void soft_delay_us(uint32_t us);

void assert_failed(char *, int);


#if defined( DEBUG_MODE )
#define ASSERT(expr) \
    if (!(expr)) \
        assert_failed(__FILE__, __LINE__)
#else
#define ASSERT(expr)
#endif
          
#if( defined(DEBUG_MODE) && defined(DEBUG_PRINT))
#define DEBUG_PRINTF(FORMAT,...)        do{printf(FORMAT,##__VA_ARGS__);}while(0)
#else
#define DEBUG_PRINTF(FORMAT,...)
#endif


#endif

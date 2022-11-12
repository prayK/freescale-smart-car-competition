#ifndef _LED_H_
#define _LED_H_

typedef enum
{
      LED0,
      LED1,
      LED2,
      LED3,
      LED_MAX,
}LED_e;
 
typedef enum LED_status
{
      LED_ON  =   0, 
      LED_OFF =   1 
}LED_status; 

extern void    led_init(LED_e);            
extern void    led(LED_e,LED_status);
extern void    led_turn(LED_e);

#endif  
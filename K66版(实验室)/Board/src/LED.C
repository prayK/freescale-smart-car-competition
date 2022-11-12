#include "common.h"
#include "MK66_port.h"
#include "MK66_gpio.h"
#include "LED.H"

PTXn_e LED_PTxn[LED_MAX] = {PTB20,PTB21,PTB22,PTB23};

void    led_init(LED_e ledn)
{
        if(ledn < LED_MAX)
        {
                gpio_init(LED_PTxn[ledn],GPO,LED_OFF);
        }
        else
        {
                ledn = LED_MAX;
                while(ledn--)
                {
                        gpio_init(LED_PTxn[ledn],GPO,LED_OFF);
                }

        }
}

void   led(LED_e ledn,LED_status status)
{
        if(ledn < LED_MAX)
        {
                gpio_set(LED_PTxn[ledn],status);
        }
        else
        {
                ledn = LED_MAX;
                while(ledn--)
                {
                        gpio_set(LED_PTxn[ledn],status);
                }
        }
}

void led_turn(LED_e ledn)
{
        if(ledn < LED_MAX)
        {
                gpio_turn(LED_PTxn[ledn]);
        }
        else
        {
                ledn = LED_MAX;
                while(ledn--)
                {
                        gpio_turn(LED_PTxn[ledn]);
                }
        }
}

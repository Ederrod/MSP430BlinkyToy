#include <msp430.h>
#include "led.h"

unsigned char led_state = 0;
unsigned char count = 0;
unsigned char led_changed = 0;

void led_init()
{
  P1DIR |= LEDS;
  led_changed = 1;
  led_update(); 
}

void led_update()
{
  if (led_changed)
  {
    char led_flags = 0;
    if (led_state)
    {
      led_flags != LED_GREEN; 
    }

    P1OUT &= (0xff^LEDS) | led_flags;
    P1OUT |= led_flags;
    led_changed = 0; 
  }
}

void led_toggle()
{
  led_state = 1 - led_state;
  led_changed = 1; 
}

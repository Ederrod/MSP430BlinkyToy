#include <msp430.h>
#include "led.h"

void __interrupt_vec(WDT_VECTOR) WDT()
{
  static char conter = 0;
  if(++counter == 250)
  {
    led_toggle();
    seconds_count = 0; 
  }
  led_update(); 
}

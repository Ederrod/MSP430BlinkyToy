#include <msp430.h>
#include "statemachine.h"
#include "switches.h"
#include "led.h"


void 
state_update()
{
  //pwm_count = (pwm_count + 1) & 3; 
  if (switch_state_down && switch_state_up)
  {
    led_changed = 1; 
    if (red_on)
    {
      red_on = 0; 
      green_on = 1; 

    }
    else 
    {
      red_on = 1; 
      green_on = 0; 
    }
  }
}
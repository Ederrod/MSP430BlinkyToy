#include <msp430.h>
#include "statemachine.h"
#include "switches.h"
#include "led.h"

static enum {off=0, dim=1, bright=2} led_mode;
static char pwm_count = 0; 

void 
state_update()
{
  pwm_count = (pwm_count + 1) & 3; 
  if (switch_state_down && switch_state_up)
  {
    char new_red_on;
    switch (led_mode) {
    case off:
      new_red_on = 0; break;
    case bright:
      new_red_on = 1; 
      led_change = 1; 
      break;
    case dim:
      new_red_on = (pwm_count < 1); break; /* 25% duty cycle */
    }
    if (red_on != new_red_on) {
      red_on = new_red_on;
      led_changed = 1;
      switch_state_down = 0; 
      switch_state_up = 0; 
    }
  }
}
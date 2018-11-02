#include <msp430.h>
#include "statemachine.h"
#include "led.h"


// state variables 
static enum {off=0, dim=1, bright=2} led_mode;
static char pwm_count = 0;		

void
led_dim_slow_clock()		/* slowly cycle through {off, dim, bright} */
{
  led_mode = (ledMode + 1) % 3;
}

void
led_dim_fast_clock()	/* quickly cycle through 0...3 */
{
  pwm_count = (pwm_count + 1) & 3; 
}

void 
led_dim_state_update()
{
  char new_red_on;
  switch (ledMode) {
  case off:
    new_red_on = 0; break;
  case bright:
    new_red_on = 1; break;
  case dim:
    new_red_on = (pwm_count < 1); break; /* 25% duty cycle */
  }
  if (red_on != new_red_on) {
    red_on = new_red_on;
    led_changed = 1;
  }
}




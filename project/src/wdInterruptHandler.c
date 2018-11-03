#include <msp430.h>
#include "led.h"
#include "switches.h"
#include "led_dim_statemachine.h"


/**
 * We only want this interrupt to have affect when 
 * in our system we are at State 2 and State 4, meaning that
 * both Switch 2 and Switch 4 were pressed. 
 */
void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  if(switch_btn == SW2 || switch_btn == SW4){
    static char blink_count = 0;
    if (++blink_count == 125) {
      led_dim_slow_clock(); 
      blink_count = 0;
    }
    led_dim_fast_clock(); 
    led_state_update(); 
  }
}

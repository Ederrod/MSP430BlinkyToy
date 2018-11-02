#include <msp430.h>
#include "led.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if(switch_btn == SW2){
    if (++blink_count == 125) {
      led_dim_slow_clock(); 
      blink_count = 0;
    }
    led_dim_fast_clock(); 
    led_state_update(); 
  }
}

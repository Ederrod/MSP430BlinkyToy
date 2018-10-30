#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"
#include "led_statemachine.h"

void main(void) 
{  
  configureClocks();
  buzzer_init(); 
  led_state_init(); 
  switch_init();
  led_init();


  or_sr(0x18);  // CPU off, GIE on
} 

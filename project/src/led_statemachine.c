#include <msp430.h>
#include "led_statemachine.h"
#include "buzzer.h"
#include "switches.h"
#include "led.h"

static enum {dim=0, bright=1} led_mode; 


void led_state_init()
{
    led_mode = bright; 
}

void 
led_state_update()
{ 
    if (switch_down_btn == switch_up_btn)
    {
        //buzzer_advance_frequency();
        //state_led_mode(); 
        led_update(); 
    }
}
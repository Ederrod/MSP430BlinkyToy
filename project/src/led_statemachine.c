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
    if (switch_state_down && switch_state_up)
    {
        //buzzer_advance_frequency();
        //state_led_mode(); 
        if (red_on)
        {
            led_changed = 1; 
            green_on = 1; 
            red_on = 0; 
            led_update();
        } 
        else 
        {
            led_changed = 1; 
            green_on = 0; 
            red_on = 1; 
            led_update();
        }

    }
    switch_state_down = 0; 
    switch_state_up = 0; 
}
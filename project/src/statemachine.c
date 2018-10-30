#include <msp430.h>
#include "statemachine.h"
#include "switches.h"
#include "led.h"

static enum {dim=0, bright=1} led_mode; 


void state_init()
{
    led_mode = bright; 
}

void state_led_mode()
{
    led_mode = (led_mode + 1) % 2; 
}

void 
state_update()
{ 
    if (switch_state_down && switch_state_up)
    {
        state_led_mode(); 
        if (red_on) /* RED_LED */
        {
            buzzer_set_period(100); 
            led_changed = 1; 
            red_on = 0; 
            green_on = 1;
        }
        else /* GREEN_LED */
        {
            buzzer_set_period(1000); 
            led_changed = 1; 
            green_on = 0; 
            red_on = 1; 
        }
    }
}
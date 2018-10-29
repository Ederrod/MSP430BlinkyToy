#include <msp430.h>
#include "statemachine.h"
#include "switches.h"
#include "led.h"

static enum {dim=0, bright=1} led_mode; 

void state_init()
{
    led_mode = bright; 
}

void 
state_update()
{
    //pwm_count = (pwm_count + 1) & 3; 
    if (switch_state_down && switch_state_up)
    {
        led_changed = 1; 
        if (red_on) /* RED_LED */
        {
            // TODO: if led is dim, do a led change
            //else dim the led
            if (led_mode == dim)
            {
                led_mode = bright; 
                led_changed = 1; 
                red_on = 0; 
                green_on = 1; 
            }
            else 
            {
                led_mode = dim; 
                if (red_on != new_red_on) {
                    red_on = new_red_on;
                    led_changed = 1;
                }
            }
        }
        else /* GREEN_LED */
        {
            // TODO: if led is dim, do a led change
            // else dim the led
            red_on = 1; 
            green_on = 0; 
        }
    }
}
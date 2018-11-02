#include <msp430.h>
#include "led_statemachine.h"
#include "switches.h"
#include "led.h"

static enum {off=0, dim=1} led_mode; 
static char pwm_count = 0; 

void 
led_slow_clock()
{
    led_mode = (led_mode + 1) % 2; 
}

void 
led_fast_clock()
{
    pwm_count = (pwm_count + 1) & 2; 
}

/**
 * Based on the button that initiated the interrup make the led change
 * to the state of that button
 */
void 
led_state_update()
{
    switch (switch_btn)
    {
    case SW1: /*BRIGHT_RED*/
        if (green_on)
        {
            led_changed = 1;
            green_on = 0; 
            red_on = 1; 
        }

        /*Do check if dim or bright*/
        // if dim then set led to bright
        //buzzer_advance_frequency(); 
        break; 
    case SW2: /*DIM_RED*/
        if (green_on)
        {
            led_changed = 1;
            green_on = 0; 
            red_on = 1; 
        }
        char new_red_on; 
        if (led_mode == off)
        {
            new_red_on = 0; 
        }
        if (led_mode == dim)
        {
            new_red_on = (pwm_count < 1); 
        }
        if (red_on != new_red_on) {
            red_on = new_red_on;
            led_changed = 1;
        }
        //buzzer_advance_frequency(); 
        break; 
    case SW3: /*BRIGHT_GREEN*/
        if (red_on)
        {
            led_changed = 1;
            green_on = 1; 
            red_on = 0; 
        }
        //buzzer_advance_frequency();
        break; 
    case SW4: /*DIM_GREEN*/
        if (red_on)
        {
            led_changed = 1;
            green_on = 1; 
            red_on = 0; 
        }
        //buzzer_advance_frequency();
        break; 
    }
    // reset switch states
    switch_state_down = 0;
    switch_state_up = 0; 
    led_update();
}

// void 
// led_state_update()
// { 
//     if (switch_state_down && switch_state_up)
//     {
//         //buzzer_advance_frequency();
//         //state_led_mode(); 
//         if (red_on)
//         {
//             led_changed = 1; 
//             green_on = 1; 
//             red_on = 0; 
//         } 
//         else 
//         {
//             led_changed = 1; 
//             green_on = 0; 
//             red_on = 1; 
//         }

//     }
//     switch_state_down = 0; 
//     switch_state_up = 0; 
//     led_update();
// }

#include <msp430.h>
#include "led_statemachine.h"
#include "switches.h"
#include "led.h"


/**
 * Based on the button that initiated the interrup make the led change
 * to the state of that button
 */
void 
led_state_update()
{
    switch (switch_btn)
    {
    case SW1: 
        red_on = 1; 
        green_on = 0; 
        break; 
    case SW2: 
        led_changed = 1; 
        green_on = 1; 
        red_on = 0; 
        break; 
    case SW3: 
        break; 
    case SW4: 
        break; 
    }
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
#include <msp430.h>
#include "led_statemachine.h"
#include "switches.h"
#include "led.h"

enum {btn1 = 1, btn2 = 2, btn3 = 3, btn4 = 4} btn_state; 

/**
 * Based on the button that initiated the interrup make the led change
 * to the state of that button
 */
void 
led_state_update()
{
    switch (btn_state)
    {
    case btn1: 
        led_changed = 1; 
        red_on = 1; 
        green_on = 0; 
        break; 
    case btn2: 
        led_changed = 1; 
        red_on = 0; 
        green_on = 1; 
        break; 
    case btn3: 
        break; 
    case btn4: 
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
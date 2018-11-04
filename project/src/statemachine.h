#ifndef led_statemachine_included
#define led_statemachine_included

#include <msp430.h>
#include "statemachine.h"
#include "led_dim_statemachine.h"
#include "switches.h"
#include "led.h"
#include "buzzer.h"

void led_state_update();

#endif
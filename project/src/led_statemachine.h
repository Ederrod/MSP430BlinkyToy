#ifndef led_statemachine_included
#define led_statemachine_included

extern enum {btn1 = 1, btn2 = 2, btn3 = 3, btn4 = 4} btn_state; 

void led_state_init();
void led_state_update();

#endif
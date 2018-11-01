#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "led_statemachine.h"

char switch_state_down, switch_state_up, switch_state, switch_btn; 

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE = SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void 
get_switch(char p2val)
{
  // Check if our down, has been set off
  if (switch_state_down)
  {
    // check if the switch that casued the down state is no longer in down state.
    if (p2val & switch_btn)
    {
      switch_state_up = 1; 
    }
  }
  else 
  {
    // find who caused down state
    switch_state_down = 1; 
    if (!(p2val & SW1))
    {
      switch_btn = SW1; 
    }
    if (!(p2val & SW2))
    {
      switch_btn = SW2; 
    }
    if (!(p2val & SW3))
    {
      switch_btn = SW3; 
    }
    if (!(p2val & SW4))
    {
      switch_btn = SW4; 
    }
  }

}

/**
 * Find out when up and down event is caused by the same button.  
 */

void 
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense(); 
  get_switch(p2val);
  if (switch_state_down && switch_state_up)
  {
    led_state_update(); 
  }
}

// void
// switch_interrupt_handler()
// {
//   char p2val = switch_update_interrupt_sense();
//   switch_state = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
//   if (switch_state)
//   {
//     switch_state_down = 1; 
//   }
//   else 
//   {
//     if (switch_state_down)
//     {
//       switch_state_up = 1; 
//       led_state_update(); 
//     }
//   }
// }

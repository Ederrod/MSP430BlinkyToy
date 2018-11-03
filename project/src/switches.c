#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "statemachine.h"

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

/**
 * Function to check that the up interrupt was caused by the same Switch. 
 */
void 
switch_up_interrupt(char p2val)
{
  if (p2val & switch_btn)
  {
    switch_state_up = 1; 
  }
}

/**
 * Function to check which Switch casued the down interrupt.
 */
void 
switch_down_interrupt(char p2val)
{
  if ((p2val & SW1) == 0)
  {
    switch_btn = SW1; 
  }
  if ((p2val & SW2) == 0)
  {
    switch_btn = SW2; 
  }
  if ((p2val & SW3) == 0)
  {
    switch_btn = SW3; 
  }
  if ((p2val & SW4) == 0)
  {
    switch_btn = SW4; 
  }

  if (switch_btn)
  {
    switch_state_down = 1; 
  }
}

/**
 * Interrupt handler, will only make state changes when 
 * we get a down and up action, meaning a button press.
 */

void 
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense(); 
  // If our down event has already been triggered check that
  // the current interrupt was and up event and casued by the same switch
  if (switch_state_down)
  {
    switch_up_interrupt(p2val); 
    led_state_update(); 
  }
  else 
  {
    switch_down_interrupt(p2val); 
  }
}
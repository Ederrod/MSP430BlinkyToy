#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "led_statemachine.h"

char switch_state_down, switch_state_up, switch_down_btn, switch_up_btn; /* effectively boolean */
static enum {btn1 = 1, btn2 = 2, btn3 = 3, btn4 = 4} switch_state;

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
void switch_state(char p2val)
{
  if (p2val & SW1)
  {
    switch_state = btn1; 
  }
  if (p2val & SW2)
  {
    switch_state = btn2; 
  }
  if (p2val & SW3)
  {
    switch_state = btn3; 
  }
  if (p2val & SW4)
  {
    switch_state = btn4; 
  }
}

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switch_state(p2val); 
  // switch_state = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  // if (switch_state)
  // {
  //   switch_state_down = 1; 
  // }
  // else 
  // {
  //   if (switch_state_down)
  //   {
  //     switch_state_up = 1; 
  //     led_state_update(); 
  //   }
  // }

  switch(switch_state)
  {
  case btn1:
    /*turn red on bright*/
    if (switch_down_btn == 0) /* if our down is 0, no one has had a down yet*/
    {
      switch_down_btn = btn1; 
    }
    else
    {
      if (switch_down_btn == btn1)
      {
        switch_up_btn = btn1; 
        red_on = 1; 
        green_on = 0; 
        led_state_update(); 
      }
    }

    break; 
  case btn2:
    /*turn red on dim*/
    break;  
  case btn3:
    /*turn green on bright*/
    if (switch_down_btn == 0) /* if our down is 0, no one has had a down yet*/
    {
      switch_down_btn = btn3; 
    }
    else
    {
      if (switch_down_btn == btn3)
      {
        switch_up_btn = btn3; 
        green_on = 1; 
        red_on = 0; 
        led_state_update(); 
      }
    }
    break;  
  case btn4:
    /*turn green on dim*/
    break;  
  }
}

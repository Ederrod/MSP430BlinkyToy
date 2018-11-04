#include <msp430.h>
#include "libTimer.h"
#include "buzzer.h"

static unsigned int period = 1000;
static signed int rate = 200;	

#define MIN_PERIOD 1000
#define MAX_PERIOD 4000

// void delay_ms(unsigned int ms )
// {
//     unsigned int i;
//     for (i = 0; i<= ms; i++)
//        __delay_cycles(500); //Built-in function that suspends the execution for 500 cicles
// }

// void delay_us(unsigned int us )
// {
//     unsigned int i;
//     for (i = 0; i<= us/2; i++)
//        __delay_cycles(1);
// }

// void beep(unsigned short note)
// {
//     int i;
//     long delay = (long)(10000/note);  //This is the semiperiod of each note.
//     //long time = (long)((duration*100)/(delay*2));  //This is how much time we need to spend on the note.
//     buzzer_set_period(note);
//     delay_us(delay);  
//     delay_ms(20); //Add a little delay to separate the single notes
// }

void buzzer_init()
{
    /* 
       Direct timer A output "TA0.1" to P2.6.  
        According to table 21 from data sheet:
          P2SEL2.6, P2SEL2.7, anmd P2SEL.7 must be zero
          P2SEL.6 must be 1
        Also: P2.6 direction must be output
    */
    timerAUpmode();		/* used to drive speaker */
    P2SEL2 &= ~(BIT6 | BIT7);
    P2SEL &= ~BIT7; 
    P2SEL |= BIT6;
    P2DIR = BIT6;		/* enable output to speaker (P2.6) */

    buzzer_advance_frequency();	/* start buzzing!!! */
}

void buzzer_advance_frequency() 
{
  period += rate;
  if ((rate > 0 && (period > MAX_PERIOD)) || 
      (rate < 0 && (period < MIN_PERIOD))) {
    rate = -rate;
    period += (rate << 1);
  }
  buzzer_set_period(period);
    // beep(A3);
    // beep(A3);
    // beep(A3);
    // beep(F3);
    // beep(CS3);
    // beep(A3);
    // beep(F3);
    // beep(CS3);
    // beep(A3);
 
    // delay_ms(150);
    // //end of first bit
 
    // beep(E4);
    // beep(E4);
    // beep(E4);
    // beep(FS3);
    // beep(CS3);
    // beep(GS3);
    // beep(F3);
    // beep(CS3);
    // beep(A3);
 
    // delay_ms(150);
    // //end of second bit...
 
    // beep(A5);
    // beep(A3);
    // beep(A3);
    // beep(A5);
    // beep(GS5);
    // beep(G5);
    // beep(FS5);
    // beep(F5);
    // beep(FS5);
 
    // delay_ms(250);
 
    // beep(AS3);
    // beep(DS5);
    // beep(D5);
    // beep(CS5);
    // beep(CS3);
    // beep(B3);
    // beep(CS3);
 
    // delay_ms(250);
 
    // beep(F3);
    // beep(GS3);
    // beep(F3);
    // beep(A3);
    // beep(CS3);
    // beep(A3);
    // beep(CS3);
    // beep(E4);
 
    // //end of third bit... (ThouG5 it doesn't play well)
    // //let's repeat it
 
    // beep(A5);
    // beep(A3);
    // beep(A3);
    // beep(A5);
    // beep(GS5);
    // beep(G5);
    // beep(FS5);
    // beep(F5);
    // beep(FS5);
 
    // delay_ms(250);
 
    // beep(AS3);
    // beep(DS5);
    // beep(D5);
    // beep(CS5);
    // beep(CS3);
    // beep(B3);
    // beep(CS3);
 
    // delay_ms(250);
 
    // beep(F3);
    // beep(GS3);
    // beep(F3);
    // beep(CS3);
    // beep(A3);
    // beep(F3);
    // beep(CS3);
    // beep(A3);
}

void buzzer_set_period(short cycles)
{
  CCR0 = cycles; 
  CCR1 = cycles >> 1;		/* one half cycle */
}

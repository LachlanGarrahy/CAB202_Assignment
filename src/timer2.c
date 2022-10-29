#include <avr/io.h>
#include <avr/interrupt.h>

#include "io.h"

volatile uint8_t sequence_counter;

void timer2_init() {
    cli();
    TCB1.CTRLB = TCB_CNTMODE_INT_gc;    // Configure TCB0 in periodic interrupt mode
    TCB1.CCMP = 4367;                   // Set interval for 13.1ms (4367 clocks @ 3.3 MHz)
    TCB1.INTCTRL = TCB_CAPT_bm;         // CAPT interrupt enable
    TCB1.CTRLA = TCB_ENABLE_bm;         // Enable
    sei(); 
}

// synchronises the value of sequence counter in main with this value
void decrease_sequence_counter(uint8_t value){
    sequence_counter = value;
}

// if the value can be decreased it decreases it according to the timer
ISR(TCB1_INT_vect) {
    if (sequence_counter > 0)
    {
        sequence_counter--;
    }    

    TCB1.INTFLAGS = TCB_CAPT_bm;        // Acknowledge interrupt
}
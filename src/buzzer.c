#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include "io.h"


void buzz_init(){
    // sets port b pin 0 as off
    PORTB.OUTSET = PIN0_bm;
    // sets portb b pin 0 as an output
    PORTB.DIRSET = PIN0_bm;
    
    cli(); // Disable interrupts globally
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0_bm;
    TCA0.SINGLE.CTRLB = TCA_SPLIT_LCMP0_bm;
    TCA0.SINGLE.CMP0 = 786;
    sei(); // Enable interrupts globally
}

void sound_duty_cycle_adjust(uint16_t input){

    TCA0.SINGLE.CMP0 = input;
}

ISR(TCA0_CMP0_vect) {
    printf("fuck");

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm;
}
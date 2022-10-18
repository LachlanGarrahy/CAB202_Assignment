#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "spi.h"
#include "io.h"

uint8_t left_digit;
uint8_t right_digit;

void timer_init() {
    cli();
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;    // Configure TCB0 in periodic interrupt mode
    TCB0.CCMP = 33333;                   // Set interval for 1ms (3333 clocks @ 3.3 MHz)
    TCB0.INTCTRL = TCB_CAPT_bm;         // CAPT interrupt enable
    TCB0.CTRLA = TCB_ENABLE_bm;         // Enable
    sei(); 
}

void set_digits(uint8_t left, uint8_t right){
    left_digit = left;
    right_digit = right;
}

ISR(TCB0_INT_vect) {
    static uint8_t digit = 0;

    if (digit){
        spi_write(left_digit);
    }else{
        spi_write(right_digit);
    }

    digit = !digit;

    TCB0.INTFLAGS = TCB_CAPT_bm;         // Acknowledge interrupt
}
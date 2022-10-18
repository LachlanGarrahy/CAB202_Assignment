#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "spi.h"
#include "io.h"

uint8_t left_digit;
uint8_t right_digit;

void timer_init() {
    cli();
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0_bm;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
    TCA0.SINGLE.PER = 33333;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
    sei(); 
}

void set_digits(uint8_t left, uint8_t right){
    left_digit = left;
    right_digit = right;
}

ISR(TCA0_CMP0_vect) {
    static uint8_t digit = 0;

    if (digit){
        spi_write(left_digit);
    }else{
        spi_write(right_digit);
    }

    digit = !digit;

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm;        // Acknowledge interrupt
}
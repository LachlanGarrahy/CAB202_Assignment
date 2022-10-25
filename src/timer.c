#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "spi.h"
#include "io.h"

uint8_t left_digit = 0b10000000;
uint8_t right_digit = 0b00000000;

volatile uint8_t pb_state = 0xFF;
volatile uint8_t pb_debounced = 0xFF;

void timer_init() {
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;

    cli();
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;    // Configure TCB0 in periodic interrupt mode
    TCB0.CCMP = 3333;                   // Set interval for 1ms (3333 clocks @ 3.3 MHz)
    TCB0.INTCTRL = TCB_CAPT_bm;         // CAPT interrupt enable
    TCB0.CTRLA = TCB_ENABLE_bm;         // Enable
    sei(); 
}

void set_digits(uint8_t left, uint8_t right){
    left_digit = left;
    right_digit = right;
}

void flip_screens(){
    static uint8_t digit = 0;

    if (digit){
        spi_write(right_digit);
    }else{
        spi_write(left_digit);
    }

    digit = !digit;
}

void check_buttons(){
    static uint8_t count0 = 0;
    static uint8_t count1 = 0;

    pb_state = PORTA.IN;
    uint8_t pb_changed = pb_state ^ pb_debounced;

    count1 = (count1 ^ count0) & pb_changed;
    count0 = ~count0 & pb_changed;

    pb_debounced ^= (count0 & count1);
    pb_state = pb_debounced;
}

ISR(TCB0_INT_vect) {
    flip_screens();
    check_buttons();

    TCB0.INTFLAGS = TCB_CAPT_bm;        // Acknowledge interrupt
}
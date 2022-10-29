#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

// method to initialise pwm
void pwm_pwm_init(){
    PORTB.DIRSET = PIN1_bm;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc;
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP1_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
    TCA0.SINGLE.PER = 3333;
    TCA0.SINGLE.CMP1 = 1666;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

// method to adjust the brightness of the display
void brightness_adjust(uint8_t input){
    TCA0.SINGLE.PER = 255;
    TCA0.SINGLE.CMP1 = input;
}


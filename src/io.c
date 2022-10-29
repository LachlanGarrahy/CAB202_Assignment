#include <stdio.h>
#include "uart.h"
#include "spi.h"
#include "timer.h"
#include "digit_finder.h"
#include "adc.h"
#include "pwm.h"
#include "buzzer.h"

// methods to setup standard io
static int stdio_putchar(char c, FILE *stream);
static int stdio_getchar(FILE *stream);

static FILE stdio = FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar, _FDEV_SETUP_RW);

// method to display to the terminal
static int stdio_putchar(char c, FILE *stream) {
    uart_putc(c);
    return c; //the putchar function must return the character written to the stream
}

// method to read from the terminal
static int stdio_getchar(FILE *stream) {
    return uart_getc();
}

// method to initalise stdio
void stdio_init(void) {
    // Assumes serial interface is initialised elsewhere
    uart_init();
    stdout = &stdio;
    stdin = &stdio;
}

// method to initialise the display
void display_init(void){
    spi_init();
}

// method to initialise the adc interrupts
void adc_init(void){
    adc_adc_init();
}

// method to initialise the buzzer
void buzzer_init(void){
    sound_duty_cycle_adjust(0);
    buzz_init();
}

// method to adjust the noise of the buzzer
void adjust_buzzer(uint8_t value){
    buzzer_frequency_finder(value);
}

// method to initialise the pwm
void pwm_init(void){
    pwm_pwm_init();
}

// method to adjust the displays brightness
void display_brightness(uint8_t value){
    brightness_adjust(value);
}

// method to display a hex digit across the 7 segment display
void display_hex(uint8_t digit){
    timer_init();
    display_hex_finder(digit);
    brightness_adjust(255);
}

// method to display 2 bytes directly to the display
void display_raw(uint8_t left, uint8_t right){
    set_digits(left, right);
}

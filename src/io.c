#include <stdio.h>
#include "uart.h"
#include "spi.h"
#include "timer.h"

static int stdio_putchar(char c, FILE *stream);
static int stdio_getchar(FILE *stream);

static FILE stdio = FDEV_SETUP_STREAM(stdio_putchar, stdio_getchar, _FDEV_SETUP_RW);

static int stdio_putchar(char c, FILE *stream) {
    uart_putc(c);
    return c; //the putchar function must return the character written to the stream
}

static int stdio_getchar(FILE *stream) {
    return uart_getc();
}

void stdio_init(void) {
    // Assumes serial interface is initialised elsewhere
    uart_init();
    stdout = &stdio;
    stdin = &stdio;
}

void display_init(void){
    spi_init();
}

void display_on(void){
    spi_on();
}

void display_off(void){
    spi_off();
}

void display_hex(uint8_t digit){
    display_hex_finder(digit);
}

void display_raw(uint8_t left, uint8_t right){
    timer_init();
    set_digits(left, right);
}
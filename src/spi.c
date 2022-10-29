#include <avr/io.h>
#include <avr/interrupt.h>

#include "io.h"

// method to initialise spi interrupts
void spi_init(void){
    PORTMUX.SPIROUTEA = PORTMUX_SPI0_ALT1_gc;

    PORTA.DIRSET = PIN1_bm;
    PORTC.DIRSET = PIN0_bm | PIN2_bm;

    cli();
    SPI0.CTRLB = SPI_SSD_bm;
    SPI0.CTRLA = SPI_MASTER_bm | SPI_ENABLE_bm;
    SPI0.INTCTRL = SPI_IE_bm;
    sei();
}

// method to write to the spi data bit
void spi_write(uint8_t b){
    SPI0.DATA = b;
}

// acknoledge the spi interrupt
ISR(SPI0_INT_vect){
    PORTA.OUTCLR = PIN1_bm;
    PORTA.OUTSET = PIN1_bm;
    SPI0.INTFLAGS = SPI_IF_bm;
}
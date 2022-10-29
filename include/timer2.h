#include <avr/io.h>
#include <avr/interrupt.h>

//declares the variable as volatile to be accessed from main
extern volatile uint8_t sequence_counter;

//initialises second timer
void timer2_init();

//method to decrease the counter
void decrease_sequence_counter(uint8_t value);
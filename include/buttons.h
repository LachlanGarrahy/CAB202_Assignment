#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint8_t sequence_counter;

void buttons_init();

void decrease_sequence_counter(uint8_t value);
#include <stdint.h>
#include <avr/interrupt.h>

extern volatile uint8_t pb_state;

void timer_init();
void set_digits(uint8_t left, uint8_t right);
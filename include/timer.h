#include <stdint.h>
#include <avr/interrupt.h>
//allows main to access the state
extern volatile uint8_t pb_state;
//intiiliases timer
void timer_init();
//sets the display digits
void set_digits(uint8_t left, uint8_t right);
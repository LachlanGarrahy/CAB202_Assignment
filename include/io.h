#include <stdint.h>

void stdio_init();

void pwm_init();
void adc_init();

void display_init();                            // Initialise display
void display_on();                              // Turn on display
void display_off();                             // Turn off display
void display_hex(uint8_t digit);                // Display uint8 as hex digits
void display_raw(uint8_t left, uint8_t right);  // Set segment states for left and right digits
void display_brightness(uint8_t value);         // Set display brightness

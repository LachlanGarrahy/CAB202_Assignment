#include <stdint.h>
// method to initlaise stdio
void stdio_init();

//method to initilaise pwm
void pwm_init();
//method to initialise adc
void adc_init();
//method to inistialise the buzzer
void buzzer_init();
//method to adjust the buzzer tone
void adjust_buzzer(uint8_t value);
//method to turn the buzzer off
void buzzer_off();

void display_init();                            // Initialise display
void display_hex(uint8_t digit);                // Display uint8 as hex digits
void display_raw(uint8_t left, uint8_t right);  // Set segment states for left and right digits
void display_brightness(uint8_t value);         // Set display brightness

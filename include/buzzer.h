#include <stdint.h>

//method to initialise the buzzer
void buzz_init();
// method to adjust the sound
void sound_duty_cycle_adjust(uint32_t input);
// method to adjust the frequency
void buzzer_frequency_finder(uint8_t value);
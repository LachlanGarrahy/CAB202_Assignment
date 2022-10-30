#include <stdio.h>

extern volatile uint32_t STATE_LFSR;

//method to decode and decrypt by parsing pointers
uint8_t* decode_decrypt(uint8_t* ENCODED, uint8_t* RESULT);

//method to decode from base 64 by parsing pointers
uint8_t* decode(uint8_t* ENCODED, uint8_t* DECRYPTED);

//method to descramble by parsing pointers
uint8_t* decrypt(uint8_t* DECRYPTED, uint8_t* RESULT);

uint8_t lsbit(uint8_t byte);
#include <stdio.h>
#include "io.h"

uint8_t lsbyte(uint32_t);
uint8_t lsbit(uint8_t);
uint8_t DecodeToBinary(uint8_t);
void decode(uint8_t*, uint8_t*);
void descamble(uint8_t*, uint8_t*);


void decode_decrypt(uint8_t* ENCODED, uint8_t* RESULT){
    uint8_t DECRYPTED[3];
    decode(ENCODED, DECRYPTED);
    descamble(DECRYPTED, RESULT);
}

void decode(uint8_t* ENCODED, uint8_t* DECRYPTED){
    uint8_t high_byte;
    uint8_t low_byte;
    uint8_t byte;

    high_byte = DecodeToBinary(ENCODED[0]);
    low_byte = DecodeToBinary(ENCODED[1]);
    byte = (high_byte << 2)|(low_byte >> 4);
    DECRYPTED[0] = byte;

    high_byte = DecodeToBinary(ENCODED[1]);
    low_byte = DecodeToBinary(ENCODED[2]);
    byte = (high_byte << 4)|(low_byte >> 2);
    DECRYPTED[1] = byte;

    high_byte = DecodeToBinary(ENCODED[2]);
    low_byte = DecodeToBinary(ENCODED[3]);
    byte = (high_byte << 6)|(low_byte);
    DECRYPTED[2] = byte;
}

void descamble(uint8_t* DECRYPTED, uint8_t* RESULT){
    uint32_t STATE_LFSR = 0x11244682;
    uint32_t MASK = 0xB4BCD35C;

    uint8_t BIT;

    for (uint32_t i = 0; i < 3; i++)
    {
        RESULT[i] = lsbyte(STATE_LFSR) ^ DECRYPTED[i];
        BIT = lsbit(STATE_LFSR);
        STATE_LFSR >>= 1;
        if (BIT)
        {
            STATE_LFSR ^= MASK;
        }
    }
}

uint8_t lsbyte(uint32_t bytes){
    bytes <<= 3;
    bytes >>= 3;
    return bytes;
}

uint8_t lsbit(uint8_t byte){
    byte &= 0b00000001;
    return byte;
}

uint8_t DecodeToBinary(uint8_t byte){
    uint8_t number;
    if (byte >= 'a' && byte <= 'z'){
        number = byte - 'a' + 26;
    }else if (byte >= 'A' && byte <= 'Z'){
        number = byte - 'A' + 0;
    }else if (byte >= '0' && byte <= '9'){
        number =  byte - '0' + 52;
    }
    return number;
}
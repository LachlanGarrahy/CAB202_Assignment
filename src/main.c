#include <stdio.h>
#include "io.h"
#include "buttons.h"
#include "sequence.h"

uint8_t lsbyte(uint32_t);
uint8_t lsbit(uint8_t);
uint8_t DecodeToBinary(uint8_t);


uint8_t counter = 0;

uint8_t pb = 0xFF;
uint8_t pb_r = 0xFF;
uint8_t pb_changed, pb_falling;

int main(void) {
    stdio_init();
    //buzzer_init();
    display_init();
    buttons_init();
    pwm_init();
    adc_init();

    uint8_t DECODED[3];
    
    // for (uint8_t i = 0; i < 3; i++)
    // {
    //     uint8_t high_byte = DecodeToBinary(TEST_BASE64[i]);
    //     uint8_t low_byte = DecodeToBinary(TEST_BASE64[i+1]);

    //     printf("%d\n%d\n",high_byte, low_byte);

    //     uint8_t byte = (high_byte << 2)|(low_byte >> 4);
    //     DECODED[i] = byte;
    // }

    uint8_t high_byte;
    uint8_t low_byte;
    uint8_t byte;

    high_byte = DecodeToBinary(TEST_BASE64[0]);
    low_byte = DecodeToBinary(TEST_BASE64[1]);
    byte = (high_byte << 2)|(low_byte >> 4);
    DECODED[0] = byte;

    high_byte = DecodeToBinary(TEST_BASE64[1]);
    low_byte = DecodeToBinary(TEST_BASE64[2]);
    byte = (high_byte << 4)|(low_byte >> 2);
    DECODED[1] = byte;

    high_byte = DecodeToBinary(TEST_BASE64[2]);
    low_byte = DecodeToBinary(TEST_BASE64[3]);
    byte = (high_byte << 6)|(low_byte);
    DECODED[2] = byte;


    printf("%X\n", DECODED[0]);
    printf("%X\n", DECODED[1]);
    printf("%X\n", DECODED[2]);
    



   
    uint32_t STATE_LFSR = 0x11244682;
    uint32_t MASK = 0xB4BCD35C;

    uint8_t DESCRAMBLED[3];
    uint8_t BIT;

    for (uint32_t i = 0; i < 3; i++)
    {
        DESCRAMBLED[i] = lsbyte(STATE_LFSR) ^ DECODED[i];
        BIT = lsbit(STATE_LFSR);
        STATE_LFSR >>= 1;
        if (BIT)
        {
            STATE_LFSR ^= MASK;
        }
    }

    // printf("%d\n", DESCRAMBLED[0]);
    // printf("%d\n", DESCRAMBLED[1]);
    // printf("%d\n", DESCRAMBLED[2]);

    while(1){

        pb_r = pb;
        pb = pb_state;

        pb_changed = pb ^ pb_r;
        pb_falling = pb_changed & pb_r;

        if((pb_falling & PIN6_bm)){
            if (counter < 255){
                counter += 1;
            }
        }else if(pb_falling & PIN5_bm){
            if (counter > 0){
                counter -= 1;
            }
        }

        //sound_duty_cycle_adjust(1667);

        display_hex(counter);
    }
}

uint8_t msbyte(uint32_t bytes){
    bytes >>= 3;
    return bytes;
}

uint8_t mbyte(uint32_t bytes){
    bytes <<= 3;
    bytes >>= 3;
    return bytes;
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
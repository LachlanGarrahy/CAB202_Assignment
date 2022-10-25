#include <stdio.h>
#include "io.h"
#include "buttons.h"
#include "sequence.h"
#include "decoder.h"

// uint8_t lsbyte(uint32_t);
// uint8_t lsbit(uint8_t);
// uint8_t DecodeToBinary(uint8_t);


uint8_t counter = 0;

uint8_t pb = 0xFF;
uint8_t pb_r = 0xFF;
uint8_t pb_changed, pb_falling;

int main(void) {
    stdio_init();
    //buzzer_init();
    display_init();
    //buttons_init();
    pwm_init();
    adc_init();

    uint16_t sequence_counter = 0;

    printf("%X, %X, %X, %X\n", SEQUENCE[sequence_counter], SEQUENCE[sequence_counter+1], SEQUENCE[sequence_counter+2], SEQUENCE[sequence_counter+3]); 
    sequence_counter += 4;    
    printf("%X, %X, %X, %X\n", SEQUENCE[sequence_counter], SEQUENCE[sequence_counter+1], SEQUENCE[sequence_counter+2], SEQUENCE[sequence_counter+3]); 
    

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

// uint8_t lsbyte(uint32_t bytes){
//     bytes <<= 3;
//     bytes >>= 3;
//     return bytes;
// }

// uint8_t lsbit(uint8_t byte){
//     byte &= 0b00000001;
//     return byte;
// }

// uint8_t DecodeToBinary(uint8_t byte){
//     uint8_t number;
//     if (byte >= 'a' && byte <= 'z'){
//         number = byte - 'a' + 26;
//     }else if (byte >= 'A' && byte <= 'Z'){
//         number = byte - 'A' + 0;
//     }else if (byte >= '0' && byte <= '9'){
//         number =  byte - '0' + 52;
//     }
//     return number;
// }
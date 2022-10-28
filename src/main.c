#include <stdio.h>
#include <avr/pgmspace.h>
#include "io.h"
#include "buttons.h"
#include "timer.h"
#include "sequence.h"
#include "decoder.h"

uint8_t pb = 0xFF;
uint8_t pb_r = 0xFF;
uint8_t pb_changed, pb_falling;

typedef enum {
    SEQUENCE_SELECT,
    BUTTON_INCREASE,
    BUTTON_DECREASE,
    SEQUENCE_START,
    DECODE,
    PROCESS
} STATE;

STATE current_state = SEQUENCE_SELECT;

int main(void) {
    stdio_init();
    //buzzer_init();
    display_init();
    buttons_init();
    pwm_init();
    adc_init();

    uint8_t ENCODED[4];
    uint8_t RESULT[3];

    static uint8_t counter;
    static uint16_t offset;

    while(1){
        switch(current_state){
            case SEQUENCE_SELECT:
                pb_r = pb;
                pb = pb_state;

                pb_changed = pb ^ pb_r;
                pb_falling = pb_changed & pb_r;

                if(pb_falling & PIN6_bm){
                    current_state = BUTTON_INCREASE;
                }else if(pb_falling & PIN5_bm){
                    current_state = BUTTON_DECREASE;
                }else if(pb_falling & PIN7_bm){
                    current_state = SEQUENCE_START;
                }

                display_hex(counter);

                break;
            case BUTTON_INCREASE:
                if (counter < 255){
                        counter += 1;
                }
                current_state = SEQUENCE_SELECT;
                break;
            case BUTTON_DECREASE:
                if (counter > 0){
                        counter -= 1;
                }
                current_state = SEQUENCE_SELECT;
                break;
            case SEQUENCE_START:
                offset = counter << 5;
                current_state = DECODE;
                break;
            case DECODE:
                
                ENCODED[0] = pgm_read_byte(SEQUENCE+offset);
                offset ++;
                ENCODED[1] = pgm_read_byte(SEQUENCE+offset);
                offset ++;
                ENCODED[2] = pgm_read_byte(SEQUENCE+offset);
                offset ++;
                ENCODED[3] = pgm_read_byte(SEQUENCE+offset);
                offset ++;              

                decode_decrypt(ENCODED, RESULT);
                sequence_counter = RESULT[0];
                current_state = PROCESS;
                break;
            case PROCESS:
                if (RESULT[0] == 0)
                {
                    current_state = SEQUENCE_SELECT;
                    printf("end\n");
                    break;
                }
                
                printf("Step: %X, %X, %X\n", RESULT[0], RESULT[1], RESULT[2]);
                
                if(sequence_counter == 0){
                    current_state = DECODE;
                }

                break;
        }
    }
}
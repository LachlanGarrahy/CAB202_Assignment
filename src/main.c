#include <stdio.h>
#include <avr/pgmspace.h>
#include "io.h"
#include "timer2.h"
#include "timer.h"
#include "sequence.h"
#include "decoder.h"

// variables to check button state
uint8_t pb = 0xFF;
uint8_t pb_r = 0xFF;
uint8_t pb_changed, pb_falling;

// variables to mask left and right digits
uint8_t left_on = 0b10000000;
uint8_t right_off = 0b01111111;

// method to get the encoded values
uint16_t get_encoded_values(uint8_t* ENCODED, uint16_t offset);

// initialise state machine
typedef enum {
    SEQUENCE_SELECT,
    BUTTON_INCREASE,
    BUTTON_DECREASE,
    SEQUENCE_START,
    DECODE,
    PROCESS
} STATE;

// set the initial state of the state machine
STATE current_state = SEQUENCE_SELECT;

// main
int main(void) {
    // initialise all the stuff 
    stdio_init();
    buzzer_init();
    display_init();
    timer2_init();
    pwm_init();
    adc_init();

    // lists for encoded and result
    uint8_t ENCODED[4];
    uint8_t RESULT[3];

    // variables to set the counter and the offset
    static uint8_t counter;
    static uint16_t offset;
    
    // state machine
    while(1){
        switch(current_state){
            // initial state
            case SEQUENCE_SELECT:

                // debounces the buttons
                pb_r = pb;
                pb = pb_state;

                pb_changed = pb ^ pb_r;
                pb_falling = pb_changed & pb_r;

                // swaps to the corresponding state
                if(pb_falling & PIN6_bm){
                    current_state = BUTTON_INCREASE;
                }else if(pb_falling & PIN5_bm){
                    current_state = BUTTON_DECREASE;
                }else if(pb_falling & PIN7_bm){
                    current_state = SEQUENCE_START;
                }

                //displays current value of counter on the display
                display_hex(counter);

                break;
            case BUTTON_INCREASE:
                //if the counter is less than 255 
                //increase the counter by 1 and
                //swap back to sequence select
                if (counter < 255){
                        counter += 1;
                }
                current_state = SEQUENCE_SELECT;
                break;
            case BUTTON_DECREASE:
                //if the counter is more than 0 
                //decrese the counter by 1 and
                //swap back to sequence select
                if (counter > 0){
                        counter -= 1;
                }
                current_state = SEQUENCE_SELECT;
                break;
            case SEQUENCE_START:
                //set offset to counter * 32
                offset = counter << 5;
                current_state = DECODE;
                break;
            case DECODE:
                
                // gets the encoded values from the list
                offset = get_encoded_values(ENCODED, offset);          

                //decodes the encoded values and puts them in result
                decode_decrypt(ENCODED, RESULT);
                //sets the sequence counter to result
                sequence_counter = RESULT[0];

                current_state = PROCESS;
                break;
            case PROCESS:
                //if result[0] is 0 return to sequence select
                if (RESULT[0] == 0)
                {
                    current_state = SEQUENCE_SELECT;
                    break;
                }

                //sets the display brightness
                display_brightness(RESULT[1]);
                display_raw(left_on, right_off);
                
                //adjusts the buzzer output
                adjust_buzzer(RESULT[2]);
                
                //if sequence counter is 0 go to the next step
                if(sequence_counter == 0){
                    current_state = DECODE;
                }

                break;
        }
    }
}

//method to get the encoded values
uint16_t get_encoded_values(uint8_t* ENCODED, uint16_t offset){

    ENCODED[0] = pgm_read_byte(SEQUENCE+offset);
    offset ++;
    ENCODED[1] = pgm_read_byte(SEQUENCE+offset);
    offset ++;
    ENCODED[2] = pgm_read_byte(SEQUENCE+offset);
    offset ++;
    ENCODED[3] = pgm_read_byte(SEQUENCE+offset);
    offset ++;  

    return offset;
}
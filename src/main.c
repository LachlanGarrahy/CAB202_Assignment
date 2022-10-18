#include <stdio.h>
#include "io.h"
#include "buttons.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uint8_t counter = 0;

uint8_t pb = 0xFF;
uint8_t pb_r = 0xFF;
uint8_t pb_changed, pb_falling;

int main(void) {
    stdio_init();
    display_init();
    buttons_init();

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
        display_hex(counter);
    }
}

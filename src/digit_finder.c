#include <stdio.h>
#include "io.h"

// variables to hold values for the display
#define DISP_0 0x08
#define DISP_1 0x6B
#define DISP_2 0x44
#define DISP_3 0x41
#define DISP_4 0x23
#define DISP_5 0x11
#define DISP_6 0x10
#define DISP_7 0x4B
#define DISP_8 0x00
#define DISP_9 0x01
#define DISP_A 0x02
#define DISP_B 0x30
#define DISP_C 0x1C
#define DISP_D 0x60
#define DISP_E 0x14
#define DISP_F 0x16
#define DISP_DASH 0x77
#define DISP_BLANK 0x7F

uint8_t find_hex_digit(uint8_t);

// method to call the display function with the values parsed from display hex
void display_hex_finder(uint8_t digit){
    uint8_t left = 0b10000000;
    uint8_t right = 0;

    // shifts the 8 bit byte to get only the high nibble and check the digit
    uint8_t left_digit = find_hex_digit(digit >> 4) | left;

    // shifts the 8 bit byte to get only the low nibble and check the digit
    uint8_t right_digit = digit << 4;
    right_digit = find_hex_digit(right_digit >> 4) | right;

    // calls the method to diplay to the 7 segment displays
    display_raw(left_digit, right_digit);
}

// method to return the value to be parsed to the display method
uint8_t find_hex_digit(uint8_t digit){
    if (digit == 0){
        return DISP_0;
    }else if (digit == 1){
        return DISP_1;
    }else if (digit == 2){
        return DISP_2;
    }else if (digit == 3){
        return DISP_3;
    }else if (digit == 4){
        return DISP_4;
    }else if (digit == 5){
        return DISP_5;
    }else if (digit == 6){
        return DISP_6;
    }else if (digit == 7){
        return DISP_7;
    }else if (digit == 8){
        return DISP_8;
    }else if (digit == 9){
        return DISP_9;
    }else if (digit == 10){
        return DISP_A;
    }else if (digit == 11){
        return DISP_B;
    }else if (digit == 12){
        return DISP_C;
    }else if (digit == 13){
        return DISP_D;
    }else if (digit == 14){
        return DISP_E;
    }else{
        return DISP_F;
    }
}
#include <stdio.h>
#include "io.h"

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
        return 0b00001000;
    }else if (digit == 1){
        return 0b01101011;
    }else if (digit == 2){
        return 0b01000100;
    }else if (digit == 3){
        return 0b01000001;
    }else if (digit == 4){
        return 0b00100011;
    }else if (digit == 5){
        return 0b00010001;
    }else if (digit == 6){
        return 0b00010000;
    }else if (digit == 7){
        return 0b01001011;
    }else if (digit == 8){
        return 0b00000000;
    }else if (digit == 9){
        return 0b00000011;
    }else if (digit == 10){
        return 0b00000010;
    }else if (digit == 11){
        return 0b00110000;
    }else if (digit == 12){
        return 0b00011100;
    }else if (digit == 13){
        return 0b01100000;
    }else if (digit == 14){
        return 0b00010100;
    }else{
        return 0b00010110;
    }
}
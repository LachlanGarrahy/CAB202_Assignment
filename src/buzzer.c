#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

// methods to find the note and the octave
uint32_t find_note(uint8_t digit);
uint32_t find_octave(uint8_t digit);

// methods to find the frequency
uint32_t find_note_55(uint8_t digit);
uint32_t find_note_110(uint8_t digit);
uint32_t find_note_220(uint8_t digit);
uint32_t find_note_440(uint8_t digit);
uint32_t find_note_880(uint8_t digit);
uint32_t find_note_1760(uint8_t digit);
uint32_t find_note_3520(uint8_t digit);
uint32_t find_note_7040(uint8_t digit);
uint32_t find_note_14080(uint8_t digit);
uint32_t find_note_28160(uint8_t digit);
uint32_t find_note_56320(uint8_t digit);
uint32_t find_note_112640(uint8_t digit);
uint32_t find_note_225280(uint8_t digit);
uint32_t find_note_450560(uint8_t digit);
uint32_t find_note_901120(uint8_t digit);
uint32_t find_note_1802240(uint8_t digit);

//method to inistialise the buzzer and TCA0 CMP0 timer
void buzz_init(){
    // sets port b pin 0 as off
    PORTB.OUTSET = PIN0_bm;
    // sets portb b pin 0 as an output
    PORTB.DIRSET = PIN0_bm;
    
    cli(); // Disable interrupts globally
    TCA0.SINGLE.INTCTRL = TCA_SINGLE_CMP0_bm;
    TCA0.SINGLE.CTRLB = TCA_SPLIT_LCMP0_bm;
    TCA0.SINGLE.CMP0 = 1666;
    sei(); // Enable interrupts globally
}

// method to adjust the period and CMP0
void sound_duty_cycle_adjust(uint32_t input){

    TCA0.SINGLE.PER = input;

    TCA0.SINGLE.CMP0 = input>>1;
}

// method to find the note and run the function to adjust the noise
void buzzer_frequency_finder(uint8_t value){

    sound_duty_cycle_adjust(find_note(value));

}

// acknowledges the interrupt and toggles the bit to make the buzzer play
ISR(TCA0_CMP0_vect) {
    PORTB.OUTTGL = PIN0_bm;

    TCA0.SINGLE.INTFLAGS = TCA_SINGLE_CMP0_bm;
}


uint32_t find_note(uint8_t digit){
    uint32_t octave = digit<<4;
    octave = find_octave(digit>>4);

    if (octave == 55){
        return find_note_55(digit>>4) + octave;
    }else if (octave == 110){
        return find_note_110(digit>>4) + octave;
    }else if (octave == 220){
        return find_note_220(digit>>4) + octave;
    }else if (octave == 440){
        return find_note_440(digit>>4) + octave;
    }else if (octave == 880){
        return find_note_880(digit>>4) + octave;
    }else if (octave == 1760){
        return find_note_1760(digit>>4) + octave;
    }else if (octave == 3520){
        return find_note_3520(digit>>4) + octave;
    }else if (octave == 7040){
        return find_note_7040(digit>>4) + octave;
    }else if (octave == 14080){
        return find_note_14080(digit>>4) + octave;
    }else if (octave == 28160){
        return find_note_28160(digit>>4) + octave;
    }else if (octave == 56320){
        return find_note_56320(digit>>4) + octave;
    }else if (octave == 112640){
        return find_note_112640(digit>>4) + octave;
    }else if (octave == 225280){
        return find_note_225280(digit>>4) + octave;
    }else if (octave == 450560){
        return find_note_450560(digit>>4) + octave;
    }else if (octave == 901120){
        return find_note_901120(digit>>4) + octave;
    }else{
        return find_note_1802240(digit>>4) + octave;
    }
}

uint32_t find_note_55(uint8_t digit){
    if (digit == 0){
        return 4;
    }else if (digit == 1){
        return 8;
    }else if (digit == 2){
        return 12;
    }else if (digit == 3){
        return 16;
    }else if (digit == 4){
        return 20;
    }else if (digit == 5){
        return 24;
    }else if (digit == 6){
        return 28;
    }else if (digit == 7){
        return 32;
    }else if (digit == 8){
        return 36;
    }else if (digit == 9){
        return 40;
    }else if (digit == 10){
        return 44;
    }else{
        return 48;
    }
}
uint32_t find_note_110(uint8_t digit){
    if (digit == 0){
        return 8;
    }else if (digit == 1){
        return 16;
    }else if (digit == 2){
        return 24;
    }else if (digit == 3){
        return 32;
    }else if (digit == 4){
        return 40;
    }else if (digit == 5){
        return 48;
    }else if (digit == 6){
        return 56;
    }else if (digit == 7){
        return 64;
    }else if (digit == 8){
        return 72;
    }else if (digit == 9){
        return 80;
    }else if (digit == 10){
        return 88;
    }else{
        return 96;
    }
}
uint32_t find_note_220(uint8_t digit){
    if (digit == 0){
        return 17;
    }else if (digit == 1){
        return 34;
    }else if (digit == 2){
        return 51;
    }else if (digit == 3){
        return 68;
    }else if (digit == 4){
        return 85;
    }else if (digit == 5){
        return 102;
    }else if (digit == 6){
        return 119;
    }else if (digit == 7){
        return 136;
    }else if (digit == 8){
        return 153;
    }else if (digit == 9){
        return 170;
    }else if (digit == 10){
        return 187;
    }else{
        return 204;
    }
}
uint32_t find_note_440(uint8_t digit){
    if (digit == 0){
        return 34;
    }else if (digit == 1){
        return 68;
    }else if (digit == 2){
        return 102;
    }else if (digit == 3){
        return 136;
    }else if (digit == 4){
        return 170;
    }else if (digit == 5){
        return 204;
    }else if (digit == 6){
        return 238;
    }else if (digit == 7){
        return 272;
    }else if (digit == 8){
        return 306;
    }else if (digit == 9){
        return 340;
    }else if (digit == 10){
        return 374;
    }else{
        return 408;
    }
}
uint32_t find_note_880(uint8_t digit){
    if (digit == 0){
        return 68;
    }else if (digit == 1){
        return 136;
    }else if (digit == 2){
        return 204;
    }else if (digit == 3){
        return 272;
    }else if (digit == 4){
        return 340;
    }else if (digit == 5){
        return 408;
    }else if (digit == 6){
        return 476;
    }else if (digit == 7){
        return 544;
    }else if (digit == 8){
        return 612;
    }else if (digit == 9){
        return 680;
    }else if (digit == 10){
        return 748;
    }else{
        return 816;
    }
}
uint32_t find_note_1760(uint8_t digit){
    if (digit == 0){
        return 135;
    }else if (digit == 1){
        return 270;
    }else if (digit == 2){
        return 405;
    }else if (digit == 3){
        return 540;
    }else if (digit == 4){
        return 675;
    }else if (digit == 5){
        return 810;
    }else if (digit == 6){
        return 945;
    }else if (digit == 7){
        return 1080;
    }else if (digit == 8){
        return 1215;
    }else if (digit == 9){
        return 1350;
    }else if (digit == 10){
        return 1485;
    }else{
        return 1620;
    }
}
uint32_t find_note_3520(uint8_t digit){
    if (digit == 0){
        return 270;
    }else if (digit == 1){
        return 540;
    }else if (digit == 2){
        return 810;
    }else if (digit == 3){
        return 1080;
    }else if (digit == 4){
        return 1350;
    }else if (digit == 5){
        return 1620;
    }else if (digit == 6){
        return 1890;
    }else if (digit == 7){
        return 2160;
    }else if (digit == 8){
        return 2430;
    }else if (digit == 9){
        return 2700;
    }else if (digit == 10){
        return 2970;
    }else{
        return 3240;
    }
}
uint32_t find_note_7040(uint8_t digit){
    if (digit == 0){
        return 542;
    }else if (digit == 1){
        return 1084;
    }else if (digit == 2){
        return 1626;
    }else if (digit == 3){
        return 2168;
    }else if (digit == 4){
        return 2710;
    }else if (digit == 5){
        return 3252;
    }else if (digit == 6){
        return 1794;
    }else if (digit == 7){
        return 4336;
    }else if (digit == 8){
        return 4878;
    }else if (digit == 9){
        return 5420;
    }else if (digit == 10){
        return 5962;
    }else{
        return 6504;
    }
}
uint32_t find_note_14080(uint8_t digit){
    if (digit == 0){
        return 1083;
    }else if (digit == 1){
        return 2166;
    }else if (digit == 2){
        return 3249;
    }else if (digit == 3){
        return 4332;
    }else if (digit == 4){
        return 5415;
    }else if (digit == 5){
        return 6498;
    }else if (digit == 6){
        return 7581;
    }else if (digit == 7){
        return 8664;
    }else if (digit == 8){
        return 9747;
    }else if (digit == 9){
        return 10830;
    }else if (digit == 10){
        return 11913;
    }else{
        return 12996;
    }
}
uint32_t find_note_28160(uint8_t digit){
    if (digit == 0){
        return 2166;
    }else if (digit == 1){
        return 4332;
    }else if (digit == 2){
        return 6498;
    }else if (digit == 3){
        return 8664;
    }else if (digit == 4){
        return 10830;
    }else if (digit == 5){
        return 12996;
    }else if (digit == 6){
        return 15162;
    }else if (digit == 7){
        return 17328;
    }else if (digit == 8){
        return 19494;
    }else if (digit == 9){
        return 21660;
    }else if (digit == 10){
        return 23826;
    }else{
        return 25992;
    }
}
uint32_t find_note_56320(uint8_t digit){
    if (digit == 0){
        return 4332;
    }else if (digit == 1){
        return 8664;
    }else if (digit == 2){
        return 12996;
    }else if (digit == 3){
        return 17328;
    }else if (digit == 4){
        return 21660;
    }else if (digit == 5){
        return 25992;
    }else if (digit == 6){
        return 30324;
    }else if (digit == 7){
        return 34656;
    }else if (digit == 8){
        return 38988;
    }else if (digit == 9){
        return 43320;
    }else if (digit == 10){
        return 47652;
    }else{
        return 51984;
    }
}
uint32_t find_note_112640(uint8_t digit){
    if (digit == 0){
        return 8665;
    }else if (digit == 1){
        return 17330;
    }else if (digit == 2){
        return 25995;
    }else if (digit == 3){
        return 34660;
    }else if (digit == 4){
        return 43325;
    }else if (digit == 5){
        return 51990;
    }else if (digit == 6){
        return 60655;
    }else if (digit == 7){
        return 69320;
    }else if (digit == 8){
        return 77985;
    }else if (digit == 9){
        return 86650;
    }else if (digit == 10){
        return 95315;
    }else{
        return 103980;
    }
}
uint32_t find_note_225280(uint8_t digit){
    if (digit == 0){
        return 17329;
    }else if (digit == 1){
        return 34658;
    }else if (digit == 2){
        return 51987;
    }else if (digit == 3){
        return 69316;
    }else if (digit == 4){
        return 86645;
    }else if (digit == 5){
        return 103974;
    }else if (digit == 6){
        return 121303;
    }else if (digit == 7){
        return 138632;
    }else if (digit == 8){
        return 155961;
    }else if (digit == 9){
        return 173290;
    }else if (digit == 10){
        return 190619;
    }else{
        return 207948;
    }
}
uint32_t find_note_450560(uint8_t digit){
    if (digit == 0){
        return 34658;
    }else if (digit == 1){
        return 69316;
    }else if (digit == 2){
        return 103974;
    }else if (digit == 3){
        return 138632;
    }else if (digit == 4){
        return 173290;
    }else if (digit == 5){
        return 207948;
    }else if (digit == 6){
        return 242606;
    }else if (digit == 7){
        return 277264;
    }else if (digit == 8){
        return 311922;
    }else if (digit == 9){
        return 346580;
    }else if (digit == 10){
        return 381238;
    }else{
        return 415896;
    }
}
uint32_t find_note_901120(uint8_t digit){
    if (digit == 0){
        return 69317;
    }else if (digit == 1){
        return 138634;
    }else if (digit == 2){
        return 207951;
    }else if (digit == 3){
        return 277268;
    }else if (digit == 4){
        return 346585;
    }else if (digit == 5){
        return 415902;
    }else if (digit == 6){
        return 485219;
    }else if (digit == 7){
        return 554536;
    }else if (digit == 8){
        return 623853;
    }else if (digit == 9){
        return 693170;
    }else if (digit == 10){
        return 762487;
    }else{
        return 831804;
    }
}
uint32_t find_note_1802240(uint8_t digit){
    if (digit == 0){
        return 138634;
    }else if (digit == 1){
        return 277268;
    }else if (digit == 2){
        return 415902;
    }else if (digit == 3){
        return 554536;
    }else if (digit == 4){
        return 693170;
    }else if (digit == 5){
        return 831804;
    }else if (digit == 6){
        return 970438;
    }else if (digit == 7){
        return 1109072;
    }else if (digit == 8){
        return 1247706;
    }else if (digit == 9){
        return 1386340;
    }else if (digit == 10){
        return 1524974;
    }else{
        return 1663608;
    }
}

uint32_t find_octave(uint8_t digit){
    if(digit == 0){
        return 0;
    }
    return 55 << digit;
}
// #include <avr/io.h>
// #include <avr/interrupt.h>

// #include "io.h"

// volatile uint8_t pb_state = 0xFF;
// volatile uint8_t pb_debounced = 0xFF;

// void buttons_init() {
//     // Enable pull-up resistors for PBs
//     PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
//     PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
//     PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
//     PORTA.PIN7CTRL = PORT_PULLUPEN_bm;

//     // Configure timer for PB sampling
//     cli();
//     TCB1.CTRLB = TCB_CNTMODE_INT_gc;    // Configure TCB0 in periodic interrupt mode
//     TCB1.CCMP = 3333;                   // Set interval for 1ms (3333 clocks @ 3.3 MHz)
//     TCB1.INTCTRL = TCB_CAPT_bm;         // CAPT interrupt enable
//     TCB1.CTRLA = TCB_ENABLE_bm;         // Enable
//     sei(); 
// }

// // Timer ISR; samples pushbuttons
// ISR(TCB1_INT_vect) {
//     static uint8_t count0 = 0;
//     static uint8_t count1 = 0;

//     pb_state = PORTA.IN;
//     uint8_t pb_changed = pb_state ^ pb_debounced;

//     count1 = (count1 ^ count0) & pb_changed;
//     count0 = ~count0 & pb_changed;

//     pb_debounced ^= (count0 & count1);
//     pb_state = pb_debounced;

//     TCB1.INTFLAGS = TCB_CAPT_bm;        // Acknowledge interrupt
// }
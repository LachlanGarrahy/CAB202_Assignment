#include <stdint.h>
//method to initiliase uart
void uart_init();
//method to get user input in terminal
uint8_t uart_getc();
//method to display to terminal
void uart_putc(uint8_t c);
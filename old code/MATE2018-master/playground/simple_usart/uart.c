#include <avr/io.h>
#include <stdio.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUD
#define BAUD 115200
#endif
#include <util/setbaud.h>

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */

void uart_init(void) {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
    UBRR1H = UBRRH_VALUE;
    UBRR1L = UBRRL_VALUE;
    
#if USE_2X
    UCSR0A |= _BV(U2X0);
    UCSR1A |= _BV(U2X1);
#else
    UCSR0A &= ~(_BV(U2X0));
    UCSR1A &= ~(_BV(U2X1));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */ 
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */   
    
    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); /* 8-bit data */ 
    UCSR1B = _BV(RXEN1) | _BV(TXEN1);   /* Enable RX and TX */ 
}


void uart_putchar_0(char c) {
    if (c == '\n') {
        uart_putchar_0('\r');
    }
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

char uart_getchar_0() {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void uart_putchar_1(char c) {
    if (c == '\n') {
        uart_putchar_1('\r');
    }
    loop_until_bit_is_set(UCSR1A, UDRE1);
    UDR1 = c;
}

char uart_getchar_1() {
    loop_until_bit_is_set(UCSR1A, RXC1);
    return UDR1;
}

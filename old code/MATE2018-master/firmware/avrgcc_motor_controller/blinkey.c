/* ledblink.c, an LED blinking program */
#include<avr/io.h>
#include<util/delay.h>

#define BAUD 115200

#include <util/setbaud.h>

void uart_init(void) {
    UBRR1H = UBRRH_VALUE;
    UBRR1L = UBRRL_VALUE;

#if USE_2X
    UCSR1A |= _BV(U2X0);
#else
    UCSR1A &= ~(_BV(U2X0));
#endif

    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); /* 8-bit data */
    UCSR1B = _BV(RXEN1) | _BV(TXEN1);   /* Enable RX and TX */
}


void uart_putchar(char c) {
    UDR1 = c;
    loop_until_bit_is_set(UCSR1A, TXC1); /* Wait until transmission ready. */
}

// speed should be a number from -3200 to 3200
void setMotorSpeed(int id, int speed)
{
  uart_putchar(0xAA);
  uart_putchar(id);
  if (speed < 0)
  {
    uart_putchar(0x06);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    uart_putchar(0x05);  // motor forward command
  }
  uart_putchar(speed & 0x1F);
  uart_putchar(speed >> 5);
}

void clearErrors()
{
  uart_putchar(0x83);
}

main()
{
        uart_init();
        clearErrors();
        _delay_ms(100);
        setMotorSpeed(1, 1000);
}

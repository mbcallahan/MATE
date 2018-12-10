/*
 * Demonstration on how to redirect stdio to UART. 
 *
 * http://appelsiini.net/2011/simple-usart-with-avr-libc
 *
 * To compile and upload run: make clean; make; make program;
 * Connect to serial with: screen /dev/tty.usbserial-*
 *
 * Copyright 2011 Mika Tuupola
 *
 * Licensed under the MIT license:
 *   http://www.opensource.org/licenses/mit-license.php
 *
 */
 
#include<util/delay.h>
 
#include "main.h"
#include "uart.h"

// speed should be a number from -3200 to 3200
void setMotorSpeed(int id, int speed)
{
  uart_putchar_1(0xAA);
  uart_putchar_1(id);
  if (speed < 0)
  {
    uart_putchar_1(0x06);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    uart_putchar_1(0x05);  // motor forward command
  }
  uart_putchar_1(speed & 0x1F);
  uart_putchar_1(speed >> 5);
}

void clearErrors()
{
  uart_putchar_1(0x83);
}


int main(void) {    

    uart_init();
    clearErrors();
    _delay_ms(100);
    while(1){
       setMotorSpeed(1, -3200);
       _delay_ms(1000);
       setMotorSpeed(1, 3200);
       _delay_ms(1000);
    }
    
        
    return 0;
}

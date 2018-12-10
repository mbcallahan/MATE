#include "settings.h"
//#include "debug.h"
#include "messenger.h"
#include <avr/io.h>
#include <util/delay.h>

long last_toggle;
int last_value;

void m_uart_init(void) {
    UBRR1H = UBRRH_VALUE;
    UBRR1L = UBRRL_VALUE;

#if USE_2X
    UCSR1A |= _BV(U2X1);
#else
    UCSR1A &= ~(_BV(U2X1));
#endif

    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); /* 8-bit data */
    UCSR1B = _BV(RXEN1) | _BV(TXEN1);   /* Enable RX and TX */
}

void m_uart_putchar(char c) {
    UDR1 = c;
    loop_until_bit_is_set(UCSR1A, UDRE1); /* Wait until transmission ready. */
}

// required to allow motors to move
// must be called when controller restarts and after any error
void clearErrors()
{
  m_uart_putchar(0x83);
}

// speed should be a number from -3200 to 3200
void setMotorSpeed(int id, int speed)
{
  m_uart_putchar(0xAA);
  m_uart_putchar(id);
  if (speed < 0)
  {
    m_uart_putchar(0x06);  // motor reverse command
    speed = -speed;  // make speed positive
  }
  else
  {
    m_uart_putchar(0x05);  // motor forward command
  }
  m_uart_putchar(speed & 0x1F);
  m_uart_putchar(speed >> 5);
}


void setLowSides(char value) {
  PORTD = (PORTD & 7) | (value & 128) | (value & 1)<<6 | (value & 2) << 4 | (value & 4) << 2 | (value & 8);
  PORTB = (PORTB & ~7) | (value & 16) >> 2 | (value & 32) >> 4 | (value & 64) >> 6;
}


int main() {
  m_uart_init();
  initializeBusses();
  DDRD |= ~7;
  DDRB |= 7;
  PORTD &= 7;
  PORTB &= ~7;
 
  // the Simple Motor Controller must be running for at least 1 ms
  // before we try to send serial data, so we delay here for 5 ms
  _delay_ms(5);
  clearErrors();
  
  setMotorSpeed(1, 0);
  setMotorSpeed(2, 0);
  setMotorSpeed(3, 0);
  setMotorSpeed(4, 0);
  setMotorSpeed(5, 0);
  setMotorSpeed(6, 0); 

  _delay_ms(100);

  
  char data[255];
  char key[255];
  struct Message message;
  message.key = key;
  message.data = data;

  while (1) {
    if (receiveMessage(&message, 0)){
    
      if (message.key[0] == 'a' && message.key[1] == '1') {
        
        data[0] = 0xFF;
        struct Message response = {'r', message.key, message.keyLen, data, 1};
        _delay_us(200);
        sendMessage(&response, 0);
      } else if (message.key[0] == 't') {
        int mc_id = message.key[1] - '0';
        setMotorSpeed(mc_id, *(int *)message.data);
      }
      else if (message.key[0] == 's') {
        setLowSides(message.data[0]);
        //setLowSide(s_id, *(int *)message.data);
        //logInfo("Set the low side switch!!");
      }
      else if (message.key[0] == 'r') {
        clearErrors();
      }
      else {
        //logInfo("No idea what we have here...");
        //reportMessage(&message);
      }
    }   
  }
}

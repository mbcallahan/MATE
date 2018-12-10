#include "settings.h"
//#include "debug.h"
#include "messenger.h"
#include <avr/io.h>
#include <util/delay.h>

/*
void reportMessage(struct Message * message) {
  logDebug("Reporting message:");
  logDebug("prefix: " + String(message->prefix));
  logDebug("key len: " + String((int) message->keyLen));
  logDebug("message->key[0]: " + String(message->key[0]));
  logDebug("data len: " + String((int) message->dataLen));
}*/

void initializeBusses() {
  #ifdef MC_Board
    DDRD |= (1<<2);
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
  #endif
}

void configureBus(int mode, int busId) { // mode is 1 for transmit, 0 for receive
  #ifdef CTL_Board
  if (busId == 0){
    digitalWrite(70, mode);
    digitalWrite(5, mode);
  }
  else if (busId == 1){
    digitalWrite(71, mode);
    digitalWrite(72, mode);
  }
  else if (busId == 2){
    digitalWrite(73, mode);
    digitalWrite(6, mode);
  }
  #endif
  #ifdef MC_Board
  if (busId == 0){
    if (mode) {
      PORTD |= (1<<2);
    }
    else {
      PORTD &= ~(1<<2);
    }
  }
  #endif
}

void flushToBus(int busId) {
  if (busId == 0)
    while (!( UCSR0A & (1<<TXC0)));

  #ifdef CTL_Board
  
  else if (busId == 1)
    Serial1.flush();
  else if (busId == 2)
    Serial2.flush();
  else if (busId == 3)
    Serial3.flush();

  #endif
}

void writeToBus(char * buff, int len, int busId) {
  if (busId == 0)
    for (int i = 0; i < len; i++) {
      /* Wait for empty transmit buffer */
      while ( !( UCSR0A & (1<<UDRE0)) );
      /* Put data into buffer, sends the data */
      UDR0 = buff[i];    
    }

  #ifdef CTL_Board
  
  else if (busId == 1)
    Serial1.write(buff, len);
  else if (busId == 2)
    Serial2.write(buff, len);
  else if (busId == 3)
    Serial3.write(buff, len);

  #endif
}

int availableFromBus(int busId) {
  if (busId == 0)
    return !!(UCSR0A & (1<<RXC0));

  #ifdef CTL_Board
  else if (busId == 1)
    return Serial1.available();
  else if (busId == 2)
    return Serial2.available();
  else if (busId == 3)
    return Serial3.available();

  #endif
}

int readBytesFromBus(char * buff, int len, int busId){
  // Read bytes with timeout!
  int bytes_read = 0;
  char next_byte;
  int iterations = 0;
  while (bytes_read < len){
    if (iterations > 100){
      //logWarn("Warning: Message receive timeout.");
      #ifdef CTL_Board
      digitalWrite(62, HIGH);
      #endif
      return 0;
    }
    if (!availableFromBus(busId)){
      continue;
    }
    if (busId == 0) {
      next_byte = UDR0;
    }
      
    #ifdef CTL_Board

    else if (busId == 1)
      Serial1.readBytes(&next_byte, 1);
    else if (busId == 2)
      Serial2.readBytes(&next_byte, 1);
    else if (busId == 3)
      Serial3.readBytes(&next_byte, 1);
    #endif
    
    buff[bytes_read] = next_byte;
    bytes_read++;
  }
  return 1;
}


void sendMessage(struct Message * message, int busId) {
  configureBus(1, busId);

  writeToBus(&(message->prefix), 1, busId); // Write preface ('s' for set, 'g' for get, 'r' for return value, 'd' for debug message)
  
  writeToBus(&(message->keyLen), 1, busId); // Write key length (1 byte)
  writeToBus(message->key, message->keyLen, busId); // Write key

  writeToBus(&(message->dataLen), 1, busId); // Write data length (1 byte)
  writeToBus(message->data, message->dataLen, busId); // Write data

  flushToBus(busId);

  configureBus(0, busId);
  //delay(1);
}

int receiveMessage(struct Message * message, int busId) {
  if (!availableFromBus(busId))
    return 0;

  int result;
  
  result = readBytesFromBus(&(message->prefix), 1, busId);
  if (!result)
    return result;

  if (message->prefix != 'g' && message->prefix != 's' && message->prefix != 'r' && message->prefix != 'd')
    return 0; // Bogus message!
  
  result = readBytesFromBus( &(message->keyLen), 1, busId);
  if (!result)
    return result;
  
  result = readBytesFromBus(message->key, message->keyLen, busId);
  if (!result)
    return 0;

  message->dataLen = 0;
  if (message->prefix == 's' || message->prefix == 'd' || message->prefix == 'r') {
    
    result = readBytesFromBus( &(message->dataLen), 1, busId);
    if (!result)
      return 0;

    result = readBytesFromBus(message->data, message->dataLen, busId);
    if (!result)
      return 0;

  }
  return 1;
}



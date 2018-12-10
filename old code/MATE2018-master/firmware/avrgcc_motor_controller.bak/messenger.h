#ifndef Messenger
#define Messenger

#define BAUD 115200
#include <util/setbaud.h>

struct Message {
  char prefix;
  char * key;
  char keyLen;
  char * data;
  char dataLen;
};

void initializeBusses();
void flushToBus(int);
void reportMessage(struct Message *);
void configureBus(int, int);
void writeToBus(char *, int, int);
int availableFromBus(int);
int readBytesFromBus(char *, int, int);
void sendMessage(struct Message *, int busId);
int receiveMessage(struct Message *, int busId);

#endif


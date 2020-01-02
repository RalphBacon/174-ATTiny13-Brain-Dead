#include "BasicSerial.h"

//Private - used locally only
void sendhex( uint8_t nibble) {
  if ( nibble > 9 )
    nibble += ('A' - '0' - 10);
  TxByte(nibble += '0');
}

// Splits an integer into two nibbles
void sendHexByte(uint8_t value) {
  sendhex((value & 0xF0) >> 4);
  sendhex((value & 0x0F));
}

// Main serial function
void serOut( const char* str)
{
  while (*str) TxByte (*str++);
}

void printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    char c = n % base;
    n /= base;

    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  while (*str) TxByte (*str++);
}

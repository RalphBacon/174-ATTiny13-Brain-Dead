/* Optimized AVR305 half-duplex serial uart implementation
 * timing for 81N, 115.2kbps @8Mhz = 69.4 cycles/bit
 * and @16Mhz = 138.9 cycles/bit
 * @author: Ralph Doncaster
 * @version: $Id$
 * 
 * Amended January 2020 Ralph Bacon to cater for 1.2MHz
 */
#include "Arduino.h"

#ifdef F_CPU
//	#ifdef BAUD_RATE
//	#undef BAUD_RATE
//	#endif

	#if F_CPU==1200000
		#define BAUD_RATE 19200
		#warning Using 19200 Baud Rate for 1.2MHz clock
	#else
		#define BAUD_RATE 115200
	#endif
#endif

#ifdef F_CPU
  #define TXDELAY (((F_CPU/BAUD_RATE)-9)/3)
#else
  #error CPU frequency F_CPU undefined
#endif

#if TXDELAY > 255
  #error low baud rates unsupported - use higher BAUD_RATE
#endif

extern "C" {
  void TxTimedByte(char, char);
}

#define TxByte(C) TxTimedByte(C , TXDELAY)

void sendHexByte(uint8_t value);

void serOut(const char* str);

void printNumber(unsigned long n, uint8_t base=10);


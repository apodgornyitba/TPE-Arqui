#ifndef LIB_H
#define LIB_H

#include <stdint.h>
#include <rtc.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

unsigned char RTC(unsigned int mode);

uint64_t getReg(uint64_t reg);
int getKey(int n);
unsigned char getMem(uint64_t address);

#endif
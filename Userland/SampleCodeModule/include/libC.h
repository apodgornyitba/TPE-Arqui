#ifndef LIB_C_H
#define LIB_C_H

#include <stdint.h>

int printf(char * str, ...);
int scanf(char * str, ...);
int strcmp(const char * str1, const char * str2);
char *numtostr(unsigned int num, int base);
int putChar(char c);
void puts(char * str);
int getChar();
uint32_t hex2int(char *hex);

#endif
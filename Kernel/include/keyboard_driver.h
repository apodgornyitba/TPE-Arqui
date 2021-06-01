#ifndef _KEYBOARD_DRIVER_H
#define _KEYBOARD_DRIVER_H

#include <defs.h>
#include <stdint.h>

#define INPUT_BUFFER 255 //Cant max de caracteres en buffer de input

void initKb();
void keyboard_handler();
void loadKey(char c);
int readChar(); 
int readBuffer(char *destination, int size);

#endif
#include <keyboard_driver.h>
#include <lib.h>

static char keyboardBuffer[INPUT_BUFFER];
static unsigned int bufferSize = 0;

static int shifted = 0;
static int caps = 0;
static int rdIdx = 0;
static int wrIdx = 0;

void initKb() {
    shifted = caps = 0;
    rdIdx = wrIdx = bufferSize = 0;
}

void keyboard_handler() {
    
    if(getKey(0x64) != 0){

        unsigned char keyScanned = getKey(0x60);

        if(keyScanned == LSHIFT_PRESSED || keyScanned == RSHIFT_PRESSED){
            shifted = 1;
            return;
        }
        if (keyScanned==LSHIFT_RELEASED || keyScanned == RSHIFT_RELEASED){
            shifted = 0;
            return;
        }
        if(keyScanned == CAPSLOCK){
            caps = 1 - caps;
            return;
        }
        if ( keyScanned >= 58 || keyScanned & 0x80)
            return;
        int shiftState = shifted == caps? 0:1;
        char c = scanToAscii[keyScanned][shiftState];

        loadKey(c); 
    }
}

void loadKey(char c){
    if(c == '\r')
        c = '\n';

    if(c != 0) {
        keyboardBuffer[wrIdx] = c;
        wrIdx = (wrIdx + 1) % INPUT_BUFFER;

        if(bufferSize < INPUT_BUFFER)
            bufferSize++;
        else
            rdIdx = (rdIdx + 1) % INPUT_BUFFER;
    }
}

int dumpChar()
{
    if (bufferSize <= 0) 
        return -1;

    int c = keyboardBuffer[rdIdx];
    rdIdx = (rdIdx + 1) % INPUT_BUFFER;
    bufferSize--;
    return c;
}

int dumpBuffer(char* destination, int size){
    //Se dumpea la cantidad de elementos posibles!
    //Si la destinacion es muy pequeña el buffer NO se vacia, solo lee los elementos pertinentes

    // Si el tamaño es 0 ni si quiera es posible devolver un string legible!
    if (size<=0 || bufferSize<=0)
        return -1;

    int idx=0;
    while (idx<size-1 && bufferSize){
        destination[idx] = dumpChar();
        idx++;
    }
    destination[idx]=0;
    return idx;
}


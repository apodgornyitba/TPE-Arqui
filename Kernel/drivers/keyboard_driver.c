#include <keyboard_driver.h>
#include <lib.h>

static char keyboardBuffer[INPUT_BUFFER];
static unsigned int bufferSize = 0;

static int shifted = 0;
static int caps = 0;
static int rdIdx = 0;
static int wrIdx = 0;

#define ESC 27 /* ASCII escape */

/* Scancodes for shift and capslock keys: */

#define LSHIFT_PRESSED 0x2A  /* Scan codes for shift press, */
#define LSHIFT_RELEASED 0xAA /* shift release and capslock  */
#define RSHIFT_PRESSED 0x36  /* keys.                       */
#define RSHIFT_RELEASED 0xB6
#define CAPSLOCK 0x3A
#define CAPSLOCK_RELEASED 0xBA
#define CTRL 0x1D
#define BACKSPACE 8 /* Ascii codes for Backspace, Tab and enter */
#define TAB 9       /* keys.                                    */
#define ENTER_KEY 13

char scanToAscii[58][2] = /* Array containing ascii codes for appropriate scan codes */
    {
        {0, 0},
        {ESC, ESC},
        {'1', '!'},
        {'2', '@'},
        {'3', '#'},
        {'4', '$'},
        {'5', '%'},
        {'6', '^'},
        {'7', '&'},
        {'8', '*'},
        {'9', '('},
        {'0', ')'},
        {'-', '_'},
        {'=', '+'},
        {8, 8},
        {9, 9},
        {'q', 'Q'},
        {'w', 'W'},
        {'e', 'E'},
        {'r', 'R'},
        {'t', 'T'},
        {'y', 'Y'},
        {'u', 'U'},
        {'i', 'I'},
        {'o', 'O'},
        {'p', 'P'},
        {'[', '{'},
        {']', '}'},
        {13, 13},
        {0, 0},
        {'a', 'A'},
        {'s', 'S'},
        {'d', 'D'},
        {'f', 'F'},
        {'g', 'G'},
        {'h', 'H'},
        {'j', 'J'},
        {'k', 'K'},
        {'l', 'L'},
        {';', ':'},
        {39, 34},
        {'`', '~'},
        {0, 0},
        {'\\', '|'},
        {'z', 'Z'},
        {'x', 'X'},
        {'c', 'C'},
        {'v', 'V'},
        {'b', 'B'},
        {'n', 'N'},
        {'m', 'M'},
        {',', '<'},
        {'.', '>'},
        {'/', '?'},
        {0, 0},
        {0, 0},
        {0, 0},
        {' ', ' '},
};

void initKb() {
    shifted = caps = 0;
    rdIdx = wrIdx = bufferSize = 0;
}

void keyboard_handler() {
    
    if(getKey(0x64) != 0)
    {

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

int readChar()
{
    if (bufferSize <= 0) 
        return -1;

    int c = keyboardBuffer[rdIdx];
    rdIdx = (rdIdx + 1) % INPUT_BUFFER;
    bufferSize--;
    return c;
}

int readBuffer(char* destination, int size){
    //Se dumpea la cantidad de elementos posibles.
    //Si la destinacion es muy pequeña el buffer no se vacia.
    // Si el tamaño es 0 no se puede devolver un string legible.
    if (size<=0 || bufferSize<=0)
        return -1;

    int idx=0;
    while (idx<size-1 && bufferSize){
        destination[idx] = readChar();
        idx++;
    }
    destination[idx]=0;
    return idx;
}
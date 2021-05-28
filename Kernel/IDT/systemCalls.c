#include <systemCalls.h>
#include <keyboard_driver.h>
#include <naiveConsole.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

uint64_t sysRead(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9)
{
    //para que solo lea del teclado
    if (fd != STDIN) {
        return -1;
    }

    char* buff = (char *) buffer;
    return readBuffer(buff,length);

}

uint64_t sysDateTime(uint64_t selector, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    return DateTime(selector);
}

uint64_t sysGetReg(uint64_t buffer, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    long long *array = (long long *)buffer;
    for (int i = 0; i < 15; i++) {
        //empiezo en RAX, termino en R15
        array[i] = getReg(i);
    }
    return 0;
}

uint64_t sysWrite(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9)
{
    char* buff = (char*) buffer;
    int inserted = 0;
    while (length > 0)
    {
        if (*buff == '\0' || *buff==-1)
            break;
        if (fd==STDIN)
            loadKey(*buff);
        else
            ncPrintChar(*buff);
        buff++;
        inserted++;
        length--;
    }

    return inserted;
}

uint64_t sysGetMem(uint64_t buffer, uint64_t address, uint64_t bytes, uint64_t r8, uint64_t r9)
{
    unsigned char *array = (unsigned char *)buffer;
    for (unsigned char i = 0; i < bytes; i++) {
        array[i] = (unsigned char) getMem(address+i);
    }
    return 0;
}

uint64_t sysClear(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) {
    ncClear();
    return 0;
}
#include <systemCalls.h>
#include <keyboard_driver.h>
#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

static uint64_t regs[17] = {0};

uint64_t sysRead(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9)
{
    if (fd != STDIN) {
        return -1;
    }
    char* buff = (char *) buffer;
    return dumpBuffer(buff,length);

}

uint64_t sysDateTime(uint64_t selector, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    return DateTime(selector);
}

uint64_t* getRegs(){
    return regs;
}
uint64_t sysGetReg(uint64_t buffer, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    long long *array = (long long *)buffer;
    for (int i = 0; i < 15; i++) {
        array[i] = regs[i];
    }
    return 0;
}

uint64_t sysWrite(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9)
{
    char* buff = (char*) buffer;
    unsigned int color;

    switch (fd)
    {
    case STDOUT:
        color= fontColour;
        break;
    case STDERR:
        color = STDERR_COL;
        break;
    case STDIN:
        break;
    default:
        return-1;
    }

    int inserted = 0;
    while (length > 0)
    {
        if (*buff == '\0' || *buff==-1)
            break;
        if (fd==STDIN)
            loadChar(*buff);
        else
            putChar(*buff, color);
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
        array[i] = (unsigned char) _getMem(address+i);
    }
    return 0;
}
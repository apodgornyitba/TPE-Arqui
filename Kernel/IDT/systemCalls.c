#include <systemCalls.h>
#include <keyboard_driver.h>
#include <stdint.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

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

//write

//getMem
//getReg
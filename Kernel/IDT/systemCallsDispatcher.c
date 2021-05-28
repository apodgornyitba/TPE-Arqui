#include <stdint.h>
#include <systemCalls.h>
#include <systemCallsDispatcher.h>

static uint64_t (*systemCalls[])(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9) = {
    sysRead,       //0
    sysWrite,      //1
    sysDateTime,   //2
    sysGetMem,     //3
    sysGetReg,     //4
    sysClear       //5
    };

uint64_t syscallDispatcher(uint64_t rdi, uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9)
{
    return (*systemCalls[rdi])(rsi, rdx, rcx, r8, r9);
}
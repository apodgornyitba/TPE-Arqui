#ifndef _SYSTEM_CALLS_H
#define _SYSTEM_CALLS_H

#include <stdint.h>
#include <lib.h>

uint64_t sysRead(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9);
uint64_t sysDateTime(uint64_t selector, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t sysGetReg(uint64_t buffer, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);
uint64_t sysWrite(uint64_t fd, uint64_t buffer, uint64_t length, uint64_t r8, uint64_t r9);
uint64_t sysGetMem(uint64_t buffer, uint64_t address, uint64_t bytes, uint64_t r8, uint64_t r9);
uint64_t sysClear(uint64_t rsi, uint64_t rdx, uint64_t rcx, uint64_t r8, uint64_t r9);

#endif
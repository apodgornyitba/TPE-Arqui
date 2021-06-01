#include <naiveConsole.h>
#include <lib.h>

#define ZERO_EXCEPTION_ID 0
#define INVALID_OP_CODE_ID 6

static void zero_division();
static void invalid_op_code();

static const char *registers[] = {"RAX:", "RBX:", "RCX:", "RDX:", "RBP:", "RDI:", "RSI:", "R8 :", "R9 :", "R10:", "R11:", "R12:", "R13:", "R14:", "R15:"};

void printRegisters(uint64_t rsp);

void exceptionDispatcher(int exception, uint64_t rsp) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if (exception ==  INVALID_OP_CODE_ID)
        invalid_op_code();
    printRegisters(rsp);
    return;
}

static void zero_division() {
	ncPrint("Exception 0: zero_division. \n");
}

static void invalid_op_code() {
	ncPrint("Exception 6: invalid_op_code. \n");
}

void printRegisters(uint64_t rsp){
    ncPrint("RSP: ");
    ncPrintHex(rsp+3*8);
    ncNewline();
    ncPrint("RIP: ");
    ncPrintHex(rsp);
    ncNewline();
    for (int i = 0; i <= 14; i++){
        ncPrint(registers[i]);
        ncPrintHex(getReg(i));
        ncNewline();
    }
    ncNewline();  
}
#include <libC.h>
#include <shellCommands.h>

#define SEC   0
#define MIN   1
#define HOUR  2
#define DAY   3
#define MONTH 4
#define YEAR  5

static const char *registers[] = {"RAX:", "RBX:", "RCX:", "RDX:", "RBP:", "RDI:", "RSI:", "R8 :", "R9 :", "R10:", "R11:", "R12:", "R13:", "R14:", "R15:"};
void divExc();
void getHelp();
void printRegisters(uint64_t rsp);
void printMem(char* hexa);
void printDateTime(unsigned int selector);

void shellMainLoop(){
    char command[120] = {0};
    char param[120] = {0};
    while (runningState){
        print("$ > ");
        command[0]=0;
        param[0]=0;
        scan("!%s %s",command,param);
        if (strcmp(command,"HELP") == 0)
            getHelp();
        else if (strcmp(command,"DATE_TIME")==0)
            printDateTime();
        else if(strcmp(command,"CLEAR")==0)
            Clear();
        else if (strcmp(command, "PRINT_MEM") == 0){
            if (param[0]=='0'&& param[1]=='x')
                printMem(param);
            else print("ingrese un parametro valido en hexa.\n");
        }
        else if (strcmp(command, "INFO_REG") == 0)
            printRegisters();
        else if (strcmp(command,"DIVEX") == 0)
            divExc();
        else if(strcmp(command,"OPEX")==0)
            opCodeExc();
        else if (strcmp(command, "EXIT") == 0)
            return;
        else{
            print("Comando inválido.\n Escriba HELP para más información.\n");           
        }
    }
    return;
}

void getHelp() {
    print("HELP: Informacion de comandos.\n");
    print("TIME: Se imprime el tiempo y la fecha actual.\n");
    print("CLEAR: Se limpia la pantalla.\n");
    print("PRINT_MEM: Volcado de memoria de 32 bytes desde la direccion dada.\n");
    print("INFO_REG: Se imprimen los valores de los registros.\n");
    print("DIVEX: Para lanzar una excepcion por división por cero.\n");
    print("OPEX: Para lanzar una excepción por operador de codigo inválido.\n");
    print("EXIT: Abortar la ejecución.\n");
    print("\n");
}

void divExc(){
    int a = 1, b = 0;
    a = a/b;
}

void printMem(char* hexa){
    long long address = hexaToInt(hexa);
    unsigned char buff[33];
    char byte[10];
    getMem(buff,address,32);
    print("\n");
    print("Memoria en address %s :\n",hexa);
    for (int i=0;i<32;i++){
        if (i==16)
            print("\n");
        intToHexa((char)buff[i], byte, 1);
        print("%s ", byte);
    }
    print("\n");
}

void printRegisters(uint64_t rsp) {
    print("RSP: %s\n", rsp+3*8);
    print("RIP: %s\n", rsp);
    for (int i = 0; i <= 14; i++){
        print("%s: %s\n", registers[i], getReg(i));
    }
}

void printDateTime(unsigned int selector) {
    print("%s:%s:%s\n%s\\%s\\%s", DateTime(2), DateTime(1), DateTime(3),DateTime(3),DateTime(4),DateTime(5));
}
#include <libC.h>
#include <lib.h>
#include <stdint.h>
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
void printRegisters();
void printMem(char* hexa);
void printDateTime();

void shellMain(){
    char command[120] = {0};
    char param[120] = {0};
    while (1)
    {
        printf("$ > ");
        command[0]=0;
        param[0]=0;
        scanf("!%s %s",command,param);
        if (strcmp(command,"HELP") == 0)
            getHelp();
        else if (strcmp(command,"DATE_TIME")==0)
            printDateTime();
        else if(strcmp(command,"CLEAR")==0)
            Clear();
        else if (strcmp(command, "printf_MEM") == 0)
        {
            if (param[0]=='0'&& param[1]=='x')
                printMem(param);
            else printf("Ingrese un parametro valido en hexa.\n");
        }
        else if (strcmp(command, "INFO_REG") == 0)
            printRegisters();
        else if (strcmp(command,"DIVEX") == 0)
            divExc();
        else if(strcmp(command,"OPEX")==0)
            opCodeExc();
        else if (strcmp(command, "EXIT") == 0)
            return;
        else printf("Comando invalido.\n Escriba HELP para mas informacion.\n");           
    }
    return;
}

void getHelp() {
    printf("HELP: Informacion de comandos.\n");
    printf("TIME: Se imprime el tiempo y la fecha actual.\n");
    printf("CLEAR: Se limpia la pantalla.\n");
    printf("printf_MEM: Volcado de memoria de 32 bytes desde la direccion dada.\n");
    printf("INFO_REG: Se imprimen los valores de los registros.\n");
    printf("DIVEX: Para lanzar una excepcion por division por cero.\n");
    printf("OPEX: Para lanzar una excepción por operador de codigo invalido.\n");
    printf("EXIT: Abortar la ejecucion.\n");
    printf("\n");
}

void divExc(){
    int a = 1, b = 0;
    a = a/b;
}

void printMem(char* hexa){
    long long address = hex2int(hexa);
    unsigned char buff[33];
    //char byte[10];
    getMem(buff, address, 32);
    printf('\n');
    printf("Memoria en address %s :\n", hexa);
    for (int i = 0; i < 32; i++){
        if (i == 16)
            printf("\n");
        // intToHexa((char)buff[i], byte, 1);
        printf("%x ", (char)buff[i]);
    }
    printf("\n");
}

void printRegisters() {
    unsigned long long buff[15]={0};
    getReg(buff);
    for (int i = 0; i <= 14; i++)
    {
        printf("%s: %d\n", registers[i], buff[i]);
    }
}

void printDateTime() {
    printf("%d:%d:%d\n%d\\%d\\%d", DateTime(2), DateTime(1), DateTime(0),DateTime(3),DateTime(4),DateTime(5));
}
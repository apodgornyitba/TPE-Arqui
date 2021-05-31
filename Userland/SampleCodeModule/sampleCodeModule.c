/* sampleCodeModule.c */
#include <libC.h>
#include <lib.h>
#include <shellCommands.h>

int main() {
	Clear();
    printf("BIENVENIDOS\n");
    printf("Que modulo desea correr?\n");
    printf("Para conocer los comandos habilitados escriba HELP\n");
	shellMain();
	Clear();
	return 0;
}
/* sampleCodeModule.c */
#include <libC.h>
#include <shellCommands.h>

int main() {
	Clear();
    print("BIENVENIDOS\n");
    print("¿Qué módulo desea correr?\n");
    print("Para conocer los comandos habilitados escriba HELP\n");
	shellMain();
	scClear();
	return 0;
}
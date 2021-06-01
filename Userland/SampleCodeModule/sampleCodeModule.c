/* sampleCodeModule.c */
// #include <libC.h>
// #include <lib.h>
// #include <shellCommands.h>

// int main() {
// 	Clear();
//     printf("BIENVENIDOS");
// 	// printf("\n");
//     // printf("Que modulo desea correr?\n");
//     // printf("Para conocer los comandos habilitados escriba HELP\n");
// 	// shellMain();
// 	// Clear();
// 	return 0;
// }

char * v = (char*)0xB8000 + 79 * 2;

static int var1 = 0;
static int var2 = 0;


int main() {
	//All the following code may be removed 
	*v = 'X';
	*(v+1) = 0x74;

	//Test if BSS is properly set up
	if (var1 == 0 && var2 == 0)
		return 0xDEADC0DE;

	return 0xDEADBEEF;
}
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void pruebas_composicion_funciones(void);

int main(int argc, char *argv[]) {
	printf("~~~ PRUEBAS ALUMNO ~~~\n");
	pruebas_composicion_funciones();
	
	return failure_count() > 0;
}

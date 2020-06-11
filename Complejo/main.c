#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void pruebas_numero_complejo(void);

int main(int argc, char *argv[]) {
	printf("~~~ PRUEBAS ALUMNO ~~~\n");
	pruebas_numero_complejo();
	
	return failure_count() > 0;
}

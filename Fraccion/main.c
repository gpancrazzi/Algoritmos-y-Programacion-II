#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void pruebas_fraccion_alumno(void);

int main(int argc, char *argv[]) {
	printf("~~~ PRUEBAS ALUMNO ~~~\n");
	pruebas_fraccion_alumno();
	
	return failure_count() > 0;
}

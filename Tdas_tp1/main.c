#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void pruebas_tdas_tp1(void);

int main(int argc, char *argv[]) {
	printf("~~~ PRUEBAS ALUMNO ~~~\n");
	pruebas_tdas_tp1();
	
	return failure_count() > 0;
}

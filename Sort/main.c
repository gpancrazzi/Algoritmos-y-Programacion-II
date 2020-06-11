#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

void pruebas_sort_alumno(void);

int main(int argc, char *argv[]) {
	printf("~~~ PRUEBAS ALUMNO ~~~\n");
	pruebas_sort_alumno();
	
	return failure_count() > 0;
}

#include "testing.h"
#include "guia_sort.h"
#include <stdlib.h>
#include <stdio.h>

void prueba_ejercicio_propuesto(void) {
	char* arreglo1[] = {"19890308", "19901011", "19950927", "19880130", "19911228", "19890309", "19890308", "19900707", "19900717", "19900508", "19890309", "19890304"};
	size_t n1 = 12;
	
	char** arreglo_ordenado = radix_sort(arreglo1, n1);
	for (size_t i = 0; i < n1; i++) {
		printf("%s\n", arreglo_ordenado[i]);
	}
	
	free(arreglo_ordenado);
}

void pruebas_sort_guia_alumno() {
	prueba_ejercicio_propuesto();
}

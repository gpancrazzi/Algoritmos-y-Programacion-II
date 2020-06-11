#include "vector.h"
#include "testing.h"
#include <stdlib.h>

#define CONSTANTE_VOLUMEN 10000

//Ejercicio 4 de la Guia
/*
Mismo a lo anterior, pero que el arreglo sea de int (no de int*), utilizando los TDAs tal cual se los implementa en clase.
*/
vector_t* invertir_orden_enteros(vector_t* vector1) {
	if ((vector1 == NULL) || (vector_largo(vector1) == 0)) {
		return NULL;
	}
	
	vector_t* vector2 = vector_crear(vector_largo(vector1));
	if (vector2 == NULL) {
		return NULL;
	}
	
	int entero_auxiliar = 0;
	for (size_t i = 0, j = vector_largo(vector1) - 1; i < vector_largo(vector1); i++, j--) {
		vector_obtener(vector1, j, &entero_auxiliar);
		vector_guardar(vector2, i, entero_auxiliar);
	}
	
	return vector2;
}
/*
La complejidad temporal del algoritmo es O(n).
*/

void prueba_invertir_orden_enteros_nulo(void) {
	vector_t* arreglo1 = vector_crear(0);
	
	print_test("Prueba invertir orden enteros arreglo nulo retorna null", invertir_orden_enteros(NULL) == NULL);
	print_test("Prueba invertir orden enteros n igual a cero retorna null", invertir_orden_enteros(arreglo1) == NULL);
	vector_destruir(arreglo1);
}

void guardar_valores_enteros(vector_t* vector1) {
	for (size_t i = 0; i < vector_largo(vector1); i++) {
		vector_guardar(vector1, i, rand() % 10007);
	}
}

void verificar_orden_invertido(vector_t* arreglo1, vector_t* arreglo2, bool* ok) {
	int entero1 = 0, entero2 = 0;
	
	for (size_t i = 0, j = vector_largo(arreglo2) - 1; i < vector_largo(arreglo2); i++, j--) {
		vector_obtener(arreglo1, j, &entero1);
		vector_obtener(arreglo2, i, &entero2);
		if (entero1 != entero2) {
			*ok = false;
			return;
		}
	}
}

void prueba_invertir_orden_enteros_algunos_elementos(void) {
	vector_t* arreglo1 = vector_crear(15);
	
	guardar_valores_enteros(arreglo1);
	vector_t* arreglo_invertido = invertir_orden_enteros(arreglo1);
	bool ok = true;
	verificar_orden_invertido(arreglo_invertido, arreglo1, &ok);
	print_test("Prueba invertir orden enteros arreglo con varios elementos retorna el orden correcto", ok == true);
	vector_destruir(arreglo1);
	vector_destruir(arreglo_invertido);
}

void prueba_invertir_orden_enteros_volumen(void) {
	vector_t* arreglo1 = vector_crear(CONSTANTE_VOLUMEN);
	
	guardar_valores_enteros(arreglo1);
	vector_t* arreglo_invertido = invertir_orden_enteros(arreglo1);
	bool ok = true;
	verificar_orden_invertido(arreglo_invertido, arreglo1, &ok);
	print_test("Prueba invertir orden enteros arreglo en volumen retorna el orden correcto", ok == true);
	vector_destruir(arreglo1);
	vector_destruir(arreglo_invertido);
}

void pruebas_invertir_orden_enteros(void) {
	prueba_invertir_orden_enteros_nulo();
	prueba_invertir_orden_enteros_algunos_elementos();
	prueba_invertir_orden_enteros_volumen();
}

int main(int argc, char *argv[]) {
	pruebas_invertir_orden_enteros();
	return failure_count() > 0;
}

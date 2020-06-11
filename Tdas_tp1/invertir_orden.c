#include "pila.h"
#include "testing.h"
#include <stdlib.h>

#define CONSTANTE_VOLUMEN 10000

//Ejercicio 3 de la Guia
/*
Implementar una función que reciba un arreglo de void* e invierta su orden, utilizando los TDAs vistos. 
Indicar y justificar el orden de ejecución.
*/
void** invertir_orden(void** arreglo1, size_t n) {
	if ((arreglo1 == NULL) || (n == 0)) {
		return NULL;
	}
	
	pila_t* pila1 = pila_crear();
	if (pila1 == NULL) {
		return NULL;
	}
	
	void** arreglo2 = malloc(sizeof(void*) * n);
	if (arreglo2 == NULL) {
		return NULL;
	}
	
	for (size_t i = 0; i < n; i++) {
		pila_apilar(pila1, arreglo1[i]);
	}
	
	for (size_t i = 0; i < n; i++) {
		arreglo2[i] = pila_desapilar(pila1);
	}
	
	pila_destruir(pila1);
	return arreglo2;
}
/*
La complejidad temporal del algoritmo es O(n).
*/

void prueba_invertir_orden_nulo(void) {
	int arreglo1[2] = {1, 2};
	void* arreglo2[2] = {&arreglo1[0], &arreglo1[1]};
	
	print_test("Prueba invertir orden arreglo nulo retorna null", invertir_orden(NULL, 2) == NULL);
	print_test("Prueba invertir orden n igual a cero retorna null", invertir_orden(arreglo2, 0) == NULL);
}

void insertar_valores_enteros(int arreglo[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo[i] = rand() % 10007;
	}
}

void insertar_punteros(void** arreglo1, int arreglo2[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo1[i] = &arreglo2[i];
	}
}

void verificar_arreglo_invertido(void** arreglo1, void** arreglo2, int n, bool* ok) {
	for (int i = 0, j = n - 1; i < n; i++, j--) {
		if (arreglo1[i] != arreglo2[j]) {
			*ok = false;
			return;
		}
	}
}

void prueba_invertir_orden_algunos_elementos(void) {
	int arreglo1[15];
	void* arreglo2[15];
	
	insertar_valores_enteros(arreglo1, 15);
	insertar_punteros(arreglo2, arreglo1, 15);
	void** arreglo_invertido = invertir_orden(arreglo2, 15);
	bool ok = true;
	verificar_arreglo_invertido(arreglo_invertido, arreglo2, 15, &ok);
	print_test("Prueba invertir orden arreglo con varios elementos retorna el orden correcto", ok == true);
	free(arreglo_invertido);
}

void prueba_invertir_orden_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	void* arreglo2[CONSTANTE_VOLUMEN];
	
	insertar_valores_enteros(arreglo1, CONSTANTE_VOLUMEN);
	insertar_punteros(arreglo2, arreglo1, CONSTANTE_VOLUMEN);
	void** arreglo_invertido = invertir_orden(arreglo2, CONSTANTE_VOLUMEN);
	bool ok = true;
	verificar_arreglo_invertido(arreglo_invertido, arreglo2, CONSTANTE_VOLUMEN, &ok);
	print_test("Prueba invertir orden arreglo en volumen retorna el orden correcto", ok == true);
	free(arreglo_invertido);
}

void pruebas_invertir_orden(void) {
	prueba_invertir_orden_nulo();
	prueba_invertir_orden_algunos_elementos();
	prueba_invertir_orden_volumen();
}

int main(int argc, char *argv[]) {
	pruebas_invertir_orden();
	return failure_count() > 0;
}

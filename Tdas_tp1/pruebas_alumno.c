#include "tdas_tp1.h"
#include "testing.h"
#include <stdlib.h>

#define CONSTANTE_VOLUMEN 10000

void prueba_pila_multitop_null(void) {
	void** arreglo1 = pila_multitop(NULL, 4);
	pila_t* pila1 = pila_crear();
	void** arreglo2 = pila_multitop(pila1, 0);
	
	print_test("Prueba multitop con pila nula retorna arreglo null", arreglo1 == NULL);
	print_test("Prueba multitop con n vacio retorna arreglo null", arreglo2 == NULL);
	pila_destruir(pila1);
}

void apilar_elementos(pila_t* pila, int** vector, int n) {
	for (int i = 0; i < n; i++) {
		pila_apilar(pila, vector[i]);
	}
}

void verificar_arreglo(void** arreglo, pila_t* pila, int n, bool* ok) {
	for (int i = 0; i < n; i++) {
		if (pila_esta_vacia(pila)) {
			if (arreglo[i] != NULL) {
				*ok = false;
				return;
			}
		} else {
			if (arreglo[i] != pila_desapilar(pila)) {
				*ok = false;
				return;
			}
		}
	}
}

void prueba_pila_multitop_algunos_elementos(void) {
	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_t* pila3 = pila_crear();
	int num[] = {5, 8, 79, 7, 6, -2, 45};
	int* val[] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6]};
	
	apilar_elementos(pila1, val, 7);
	bool ok = true;
	void** arreglo1 = pila_multitop(pila1, 7);
	verificar_arreglo(arreglo1, pila1, 7, &ok);
	print_test("Prueba multitop con varios elementos retorna arreglo en orden correcto (se iteran todos los elementos apilados)", ok);
	apilar_elementos(pila2, val, 7);
	ok = true;
	void** arreglo2 = pila_multitop(pila2, 4);
	verificar_arreglo(arreglo2, pila2, 4, &ok);
	print_test("Prueba multitop con varios elementos retorna arreglo en orden correcto (se iteran algunos elementos apilados)", ok);
	apilar_elementos(pila3, val, 12);
	ok = true;
	void** arreglo3 = pila_multitop(pila3, 12);
	verificar_arreglo(arreglo3, pila3, 12, &ok);
	print_test("Prueba multitop con varios elementos retorna arreglo en orden correcto (se iteran mas elementos que los apilados)", ok);
	// Destruccion de los elementos en memoria dinamica.
	pila_destruir(pila1);
	free(arreglo1);
	pila_destruir(pila2);
	free(arreglo2);
	pila_destruir(pila3);
	free(arreglo3);
}

void determinar_valores_aleatorios(int arreglo[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo[i] = rand() % 10007;
	}
}

void determinar_valores_punteros(int** arreglo1, int arreglo2[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo1[i] = &arreglo2[i];
	}
}

void prueba_pila_multitop_volumen(void) {
	pila_t* pila1 = pila_crear();
	int num[CONSTANTE_VOLUMEN];
	int* val[CONSTANTE_VOLUMEN];
	
	determinar_valores_aleatorios(num, CONSTANTE_VOLUMEN);
	determinar_valores_punteros(val, num, CONSTANTE_VOLUMEN);
	apilar_elementos(pila1, val, CONSTANTE_VOLUMEN);
	bool ok = true;
	void** arreglo1 = pila_multitop(pila1, CONSTANTE_VOLUMEN);
	verificar_arreglo(arreglo1, pila1, CONSTANTE_VOLUMEN, &ok);
	print_test("Prueba multitop en volumen retorna arreglo en orden correcto", ok);
	// Destruccion de los elementos en memoria dinamica.
	pila_destruir(pila1);
	free(arreglo1);
}

void pruebas_tdas_tp1() {
	prueba_pila_multitop_null();
	prueba_pila_multitop_algunos_elementos();
	prueba_pila_multitop_volumen();
}

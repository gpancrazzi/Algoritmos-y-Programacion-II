#include "tp0.h"

void swap (int* x, int* y) {
	int aux;
	
	aux = *y;
	*y = *x;
	*x = aux;
}

int maximo (int vector[], int n) {
	if (n <= 0) {
		return -1;
	}
	
	int pos = 0;
	for (int i = 0; i < n; i++) {
		if (vector[i] > vector[pos]) {
			pos = i;
		}
	}
	
	return pos;
}

int comparar_enteros (int x, int y) {
	if (x > y) {
		return 1;
	}
		
	if (x < y) {
		return -1;
	}
	
	return 0;
}

int comparar (int vector1[], int n1, int vector2[], int n2) {
	int resultado = 0;
	
	for (int i = 0; (i < n1) && (i < n2); i++) {
		resultado = comparar_enteros(vector1[i], vector2[i]);
		if (resultado != 0) {
			return resultado;
		}
	}
	
	return comparar_enteros(n1, n2);
}

void seleccion (int vector[], int n) {
	if (n <= 1) {
		return;
	}
		
	int pos = maximo(vector, n);
	swap(&vector[n - 1], &vector[pos]);
	seleccion(vector, n - 1);
}

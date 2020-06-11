#include "sort.h"
#include "testing.h"
#include <stdio.h>

#define CONSTANTE_VOLUMEN 10000

void prueba_mergesort_unico_elemento(void) {
	int arreglo1[1] = {2};
	
	merge_sort(arreglo1, 1);
	print_test("Prueba mergesort con un unico elemento funciona correctamente", arreglo1[0] == 2);
}

void comparar_orden(int arreglo1[], int arreglo2[], int n, bool* ok) {
	if (n < 0) {
		return;
	}
	
	if (arreglo1[n] == arreglo2[n]) {
		*ok = true;
		return comparar_orden(arreglo1, arreglo2, n - 1, ok);
	}
	
	*ok = false;
	return;
}

void prueba_mergesort_algunos_elementos(void) {
	int arreglo1[8] = {6, 8, 7, 2, 1, 5, 9, 6};
	int arreglo2[8] = {6, 8, 7, 2, 1, 5, 9, 6};
	int arreglo3[11] = {61, 82, 74, 22, 10, 57, 998, 6897, 34, 3, 1};
	int arreglo4[11] = {61, 82, 74, 22, 10, 57, 998, 6897, 34, 3, 1};
	int arreglo5[12] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
	int arreglo6[12] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7};
	
	merge_sort(arreglo1, 8);
	seleccion_sort(arreglo2, 8);
	bool ok = true;
	comparar_orden(arreglo1, arreglo2, 7, &ok);
	print_test("Prueba mergesort con algunos elementos ordena correctamente (cantidad par)", ok);
	merge_sort(arreglo3, 11);
	seleccion_sort(arreglo4, 11);
	ok = true;
	comparar_orden(arreglo3, arreglo4, 10, &ok);
	print_test("Prueba mergesort con algunos elementos ordena correctamente (cantidad impar)", ok);
	merge_sort(arreglo5, 12);
	seleccion_sort(arreglo6, 12);
	ok = true;
	comparar_orden(arreglo5, arreglo6, 11, &ok);
	print_test("Prueba mergesort con elementos iguales ordena correctamente", ok);
}

void determinar_valores_aleatorios(int arreglo[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo[i] = rand() % 10007;
	}
}

void copiar_arreglo(int arreglo1[], int arreglo2[], int n) {
	for (int i = 0; i < n; i++) {
		arreglo2[i] = arreglo1[i];
	}
}

void prueba_mergesort_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN];
	int arreglo3[CONSTANTE_VOLUMEN + 1];
	int arreglo4[CONSTANTE_VOLUMEN + 1];
	
	determinar_valores_aleatorios(arreglo1, CONSTANTE_VOLUMEN);
	copiar_arreglo(arreglo1, arreglo2, CONSTANTE_VOLUMEN);
	merge_sort(arreglo1, CONSTANTE_VOLUMEN);
	seleccion_sort(arreglo2, CONSTANTE_VOLUMEN);
	bool ok = true;
	comparar_orden(arreglo1, arreglo2, CONSTANTE_VOLUMEN - 1, &ok);
	print_test("Prueba mergesort en volumen ordena correctamente (cantidad de elementos par)", ok);
	determinar_valores_aleatorios(arreglo3, CONSTANTE_VOLUMEN + 1);
	copiar_arreglo(arreglo3, arreglo4, CONSTANTE_VOLUMEN + 1);
	merge_sort(arreglo3, CONSTANTE_VOLUMEN + 1);
	seleccion_sort(arreglo4, CONSTANTE_VOLUMEN + 1);
	ok = true;
	comparar_orden(arreglo3, arreglo4, CONSTANTE_VOLUMEN, &ok);
	print_test("Prueba mergesort en volumen ordena correctamente (cantidad de elementos impar)", ok);
}

void prueba_countingsort_algunos_elementos(void) {
	int arreglo1[] = {8, 7, 3, 8, 7, 1, 7, 3, 11, 2, 1, 2, 8, 10};
	int arreglo_ordenado1[] = {1, 1, 2, 2, 3, 3, 7, 7, 7, 8, 8, 8, 10, 11};
	int arreglo2[] = {7, 11, 12, 10, 4, 3, 2, 1, 5, 7, 8, 9, 9, 12, 2, 1, 1, 6, 9};
	int arreglo_ordenado2[] = {1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 9, 10, 11, 12, 12};
	int arreglo3[] = {7, 11, 12, 10, 0, 4, 3, 2, 1, 5, 7, 8, 9, 9, 0, 12, 2, 1, 1, 6, 9};
	int arreglo_ordenado3[] = {0, 0, 1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 7, 8, 9, 9, 9, 10, 11, 12, 12};
	int arreglo4[] = {7};
	int arreglo_ordenado4[] = {7};
	size_t n1 = 14, n2 = 19, n3 = 21, n4 = 1;
	size_t minimo1 = 1, minimo2 = 0;
	size_t maximo1 = 12;
	
	int* arreglo9 = counting_sort(arreglo4, n4, minimo1, maximo1, NULL);
	bool ok = true;
	comparar_orden(arreglo9, arreglo_ordenado4, (int)n4 - 1, &ok);
	print_test("Prueba countingsort ordena correctamente arreglo con un solo elemento", ok);
	free(arreglo9);
	int* arreglo5 = counting_sort(arreglo1, n1, minimo1, maximo1, NULL);
	ok = true;
	comparar_orden(arreglo5, arreglo_ordenado1, (int)n1 - 1, &ok);
	print_test("Prueba countingsort ordena correctamente (cantidad par y rango minimo distinto de 0)", ok);
	free(arreglo5);
	int* arreglo6 = counting_sort(arreglo2, n2, minimo1, maximo1, NULL);
	ok = true;
	comparar_orden(arreglo6, arreglo_ordenado2, (int)n2 - 1, &ok);
	print_test("Prueba countingsort ordena correctamente (cantidad impar y rango minimo distinto de 0)", ok);
	free(arreglo6);
	int* arreglo7 = counting_sort(arreglo1, n1, minimo2, maximo1, NULL);
	ok = true;
	comparar_orden(arreglo7, arreglo_ordenado1, (int)n1 - 1, &ok);
	print_test("Prueba countingsort ordena correctamente (cantidad par y rango minimo igual a 0)", ok);
	free(arreglo7);
	int* arreglo8 = counting_sort(arreglo3, n3, minimo2, maximo1, NULL);
	ok = true;
	comparar_orden(arreglo8, arreglo_ordenado3, (int)n3 - 1, &ok);
	print_test("Prueba countingsort ordena correctamente (cantidad impar y rango minimo igual a 0)", ok);
	free(arreglo8);
}

void determinar_enteros_aleatorios_en_rango(int arreglo[], size_t n, size_t minimo, size_t maximo) {
	for (size_t i = 0; i < n; i++) {
		arreglo[i] = rand() % (int)maximo;
		if (arreglo[i] < (int)minimo) {
			arreglo[i] = (int)minimo;
		}
	}
}

void prueba_countingsort_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo_ordenado1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN + 1];
	int arreglo_ordenado2[CONSTANTE_VOLUMEN + 1];
	size_t minimo1 = 1, maximo1 = 12;
	
	determinar_enteros_aleatorios_en_rango(arreglo1, CONSTANTE_VOLUMEN, minimo1, maximo1);
	copiar_arreglo(arreglo1, arreglo_ordenado1, CONSTANTE_VOLUMEN);
	seleccion_sort(arreglo_ordenado1, CONSTANTE_VOLUMEN);
	int* arreglo3 = counting_sort(arreglo1, CONSTANTE_VOLUMEN, minimo1, maximo1, NULL);
	bool ok = true;
	comparar_orden(arreglo3, arreglo_ordenado1, CONSTANTE_VOLUMEN - 1, &ok);
	print_test("Prueba countingsort en volumen ordena correctamente (cantidad par)", ok);
	free(arreglo3);
	determinar_enteros_aleatorios_en_rango(arreglo2, CONSTANTE_VOLUMEN + 1, minimo1, maximo1);
	copiar_arreglo(arreglo2, arreglo_ordenado2, CONSTANTE_VOLUMEN + 1);
	seleccion_sort(arreglo_ordenado2, CONSTANTE_VOLUMEN + 1);
	int* arreglo4 = counting_sort(arreglo2, CONSTANTE_VOLUMEN + 1, minimo1, maximo1, NULL);
	ok = true;
	comparar_orden(arreglo4, arreglo_ordenado2, (CONSTANTE_VOLUMEN + 1) - 1, &ok);
	print_test("Prueba countingsort en volumen ordena correctamente (cantidad impar)", ok);
	free(arreglo4);
}

void prueba_radixsort(void) {
	int arreglo1[] = {34, 71, 14, 6, 58, 91, 14, 73, 14, 15};
	int arreglo2[] = {4, 1, 44, 56, 18, 41, 74, 3, 89, 60, 35};
	int n1 = 10, n2 = 11;
	
	bool ok = true;
	int* arreglo3 = radix_sort(arreglo1, n1);
	merge_sort(arreglo1, n1);
	comparar_orden(arreglo1, arreglo3, n1 - 1, &ok);
	print_test("Prueba radixsort ordena correctamente (cantidad par)", ok);
	free(arreglo3);
	
	ok = true;
	int* arreglo4 = radix_sort(arreglo2, n2);
	merge_sort(arreglo2, n2);
	comparar_orden(arreglo2, arreglo4, n2 - 1, &ok);
	print_test("Prueba radixsort ordena correctamente (cantidad impar)", ok);
	free(arreglo4);
}

void valores_rand_radix(int arreglo[], size_t n) {
	for (size_t i = 0; i < n; i++) {
		arreglo[i] = rand() % 99;
		if (arreglo[i] < 0) {
			arreglo[i] = arreglo[i] * (-1);
		}
	}
}

void prueba_radixsort_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN + 1];
	
	bool ok = true;
	valores_rand_radix(arreglo1, CONSTANTE_VOLUMEN);
	int* arreglo3 = radix_sort(arreglo1, CONSTANTE_VOLUMEN);
	merge_sort(arreglo1, CONSTANTE_VOLUMEN);
	comparar_orden(arreglo1, arreglo3, CONSTANTE_VOLUMEN - 1, &ok);
	print_test("Prueba radixsort en volumen ordena correctamente (cantidad par)", ok);
	free(arreglo3);
	
	ok = true;
	valores_rand_radix(arreglo2, CONSTANTE_VOLUMEN + 1);
	int* arreglo4 = radix_sort(arreglo2, CONSTANTE_VOLUMEN + 1);
	merge_sort(arreglo2, CONSTANTE_VOLUMEN + 1);
	comparar_orden(arreglo2, arreglo4, CONSTANTE_VOLUMEN, &ok);
	print_test("Prueba radixsort en volumen ordena correctamente (cantidad impar)", ok);
	free(arreglo4);
}

void comparar_sort(int arreglo1[], int arreglo2[], int n, bool* ok) {
	for (size_t i = 0; i < n; i++) {
		if (arreglo1[i] != arreglo2[i]) {
			*ok = false;
			return;
		}
	}
}

void prueba_quicksort(void) {
	int arreglo1[] = {34};
	int arreglo2[] = {34};
	int arreglo3[] = {1, 3, 8, 1, 9, 14};
	int arreglo4[] = {1, 1, 3, 8, 9, 14};
	int arreglo5[] = {567, 45, 3, 23, 567, 56, 11, 90, 12, -12, 78};
	int arreglo6[] = {-12, 3, 11, 12, 23, 45, 56, 78, 90, 567, 567};
	int arreglo7[] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
	int arreglo8[] = {3, 3, 3, 3, 3, 3, 3, 3, 3};
	int n1 = 1, n2 = 6, n3 = 11, n4 = 9;
	
	bool ok = true;
	quick_sort(arreglo1, 0, n1);
	comparar_sort(arreglo1, arreglo2, n1, &ok);
	print_test("Prueba quicksort ordena correctamente con un solo elemento", ok);
	
	ok = true;
	quick_sort(arreglo3, 0, n2);
	comparar_sort(arreglo3, arreglo4, n2, &ok);
	print_test("Prueba quicksort ordena correctamente (cantidad par)", ok);
	
	ok = true;
	quick_sort(arreglo5, 0, n3);
	comparar_sort(arreglo5, arreglo6, n3, &ok);
	print_test("Prueba quicksort ordena correctamente (cantidad impar)", ok);
	
	ok = true;
	quick_sort(arreglo7, 0, n4);
	comparar_sort(arreglo7, arreglo8, n4, &ok);
	print_test("Prueba quicksort ordena correctamente (todos elementos iguales)", ok);
}

void prueba_quicksort_volumen(void) {
	int arreglo1[CONSTANTE_VOLUMEN];
	int arreglo2[CONSTANTE_VOLUMEN];
	int arreglo3[CONSTANTE_VOLUMEN + 1];
	int arreglo4[CONSTANTE_VOLUMEN + 1];
	
	bool ok = true;
	determinar_valores_aleatorios(arreglo1, CONSTANTE_VOLUMEN);
	copiar_arreglo(arreglo1, arreglo2, CONSTANTE_VOLUMEN);
	quick_sort(arreglo1, 0, CONSTANTE_VOLUMEN);
	merge_sort(arreglo2, CONSTANTE_VOLUMEN);
	comparar_sort(arreglo1, arreglo2, CONSTANTE_VOLUMEN, &ok);
	print_test("Prueba quicksort en volumen ordena correctamente (cantidad par)", ok);
	
	ok = true;
	determinar_valores_aleatorios(arreglo3, CONSTANTE_VOLUMEN + 1);
	copiar_arreglo(arreglo3, arreglo4, CONSTANTE_VOLUMEN + 1);
	quick_sort(arreglo3, 0, CONSTANTE_VOLUMEN + 1);
	merge_sort(arreglo4, CONSTANTE_VOLUMEN + 1);
	comparar_sort(arreglo3, arreglo4, CONSTANTE_VOLUMEN + 1, &ok);
	print_test("Prueba quicksort en volumen ordena correctamente (cantidad impar)", ok);
}

void prueba_bucketsort(void) {
	double arreglo1[] = {0.04, 0.07, 0.03, 0.05, 0.1, 0.06, 0.04, 0, 0.03, 0.11, 0.09, 0.18, 0.18, 0.14, 0.08, 0.11, 0, 0, 0.17, 0.91, 0.42, 0.25, 0.39, 0.4, 0.23, 0.1};
	double arreglo2[] = {0, 0, 0, 0.03, 0.03, 0.04, 0.04, 0.05, 0.06, 0.07, 0.08, 0.09, 0.1, 0.1, 0.11, 0.11, 0.14, 0.17, 0.18, 0.18, 0.23, 0.25, 0.39, 0.4, 0.42, 0.91};
	int n1 = 26;
	
	bucket_sort(arreglo1, n1);
	bool ok = true;
	for (size_t i = 0; i < n1; i++) {
		ok &= arreglo1[i] == arreglo2[i];
	}
	
	print_test("Prueba bucketsort funciona correctamente", ok);
}

void pruebas_sort_alumno() {
	prueba_mergesort_unico_elemento();
	prueba_mergesort_algunos_elementos();
	prueba_mergesort_volumen();
	prueba_countingsort_algunos_elementos();
	prueba_countingsort_volumen();
	prueba_radixsort();
	prueba_radixsort_volumen();
	prueba_quicksort();
	prueba_quicksort_volumen();
	prueba_bucketsort();
}

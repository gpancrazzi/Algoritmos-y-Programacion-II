#include "sort.h"
#include <stdlib.h>

/* ******************************************************************
 *                        ALGORITMO MERGESORT
 * *****************************************************************/

void copiar_arreglo_aux(int arreglo1[], int arreglo2[], int inicio, int fin) {
	for (int i = inicio, j = 0; i <= fin; i++, j++) {
		arreglo1[i] = arreglo2[j]; 
	}
}

void cargar_datos_faltantes(int arreglo1[], int arreglo2[], int* posicion1, int* posicion2) {
	arreglo1[*posicion1] = arreglo2[*posicion2];
	*posicion1 = *posicion1 + 1;
	*posicion2 = *posicion2 + 1;
}

void merge(int arreglo[], int inicio, int mitad, int fin) {
	int arreglo_aux[(fin - inicio) + 1];
	int i = 0, inicio_aux = inicio, mitad_aux = mitad;
	
	while ((inicio_aux < mitad) && (mitad_aux <= fin)) {
		if (arreglo[inicio_aux] <= arreglo[mitad_aux]) {
			arreglo_aux[i] = arreglo[inicio_aux];
			inicio_aux++;
		} else {
			arreglo_aux[i] = arreglo[mitad_aux];
			mitad_aux++;
		}
		i++;
	}
	
	while (inicio_aux < mitad) {
		cargar_datos_faltantes(arreglo_aux, arreglo, &i, &inicio_aux);
	}
	
	while (mitad_aux <= fin) {
		cargar_datos_faltantes(arreglo_aux, arreglo, &i, &mitad_aux);
	}
	
	copiar_arreglo_aux(arreglo, arreglo_aux, inicio, fin);
}

void mergesort(int arreglo[], int inicio, int fin) {
	if (fin == inicio) {
		return;
	}
	
	int mitad = (inicio + fin) / 2;
	mergesort(arreglo, inicio, mitad);
	mergesort(arreglo, mitad + 1, fin);
	merge(arreglo, inicio, mitad + 1, fin);
}

void merge_sort(int arreglo[], int n) {
	if (n <= 1) {
		return;
	}
	
	mergesort(arreglo, 0, n - 1);
}

/* Teorema Maestro:
T(n) = A * T(n / B) + O(n ^ C)
A = 2
B = 2
C = 1
T(n) = 2T(n / 2) + O(n)
Como log_B(A) = C => log_2(2) = 1 entonces el orden del algoritmo es O(n * log(n))
*/

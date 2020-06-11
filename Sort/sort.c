#include "sort.h"
#include "lista.h"

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

/* ******************************************************************
 *                        ALGORITMO COUNTINGSORT 
 * *****************************************************************/

void inicializar_arreglo(int arreglo[], size_t n) {
	for (size_t i = 0; i < n; i++) {
		arreglo[i] = 0;
	}
}

int* counting_sort(int arreglo[], size_t n, size_t minimo, size_t maximo, int cifra_significativa(int dato)) {
	int frecuencias[maximo + 1];
	
	inicializar_arreglo(frecuencias, maximo + 1); //complejidad temporal O(k) siendo k el valor de maximo.
	for (size_t i = 0; i < n; i++) {
		if (cifra_significativa) {
			frecuencias[cifra_significativa(arreglo[i])] = frecuencias[cifra_significativa(arreglo[i])] + 1;
		} else {
			frecuencias[arreglo[i]] = frecuencias[arreglo[i]] + 1;
		}                                                           //complejidad temporal O(n) siendo n la cantidad de elementos del arreglo.
	}
	
	int frecuencias_acumuladas[maximo + 1];
	frecuencias_acumuladas[minimo] = 0;
	for (size_t i = minimo + 1; i < maximo + 1; i++) {
		frecuencias_acumuladas[i] = frecuencias_acumuladas[i - 1] + frecuencias[i - 1];  //O(k).
	}
	
	int* arreglo_auxiliar = malloc(sizeof(int) * n);
	if (arreglo_auxiliar == NULL) {
		return NULL;
	}
	
	for (size_t i = 0; i < n; i++) {
		if (cifra_significativa) {
			arreglo_auxiliar[frecuencias_acumuladas[cifra_significativa(arreglo[i])]] = arreglo[i];            
		    frecuencias_acumuladas[cifra_significativa(arreglo[i])] = frecuencias_acumuladas[cifra_significativa(arreglo[i])] + 1;
		} else {
			arreglo_auxiliar[frecuencias_acumuladas[arreglo[i]]] = arreglo[i];              //O(n).
		    frecuencias_acumuladas[arreglo[i]] = frecuencias_acumuladas[arreglo[i]] + 1; 
		} 
	}
	
	return arreglo_auxiliar;
}
/*
La complejidad temporal del algoritmo es 0(2n + 2k), quito las constantes, queda finalmente O(n + k).
Si el rango k es conocido, acotado y, a lo sumo, similar a n, entonces puedo utilizar counting_sort,
ya que la complejidad temporal va a ser O(n) (considero k como una constante). En caso contrario,
no conviene utilizar este algoritmo.
*/

/* ******************************************************************
 *                        ALGORITMO SELECTIONSORT
 * *****************************************************************/
 
void swap(int* x, int* y) {
	int aux;
	
	aux = *y;
	*y = *x;
	*x = aux;
}

int maximo(int vector[], int n) {
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

void seleccion_sort(int vector[], int n) {
	if (n <= 1) {
		return;
	}
		
	int pos = maximo(vector, n);
	swap(&vector[n - 1], &vector[pos]);
	seleccion_sort(vector, n - 1);
}

/* ******************************************************************
 *                        ALGORITMO RADIXSORT
 * *****************************************************************/
int calcular_primer_cifra(int dato) {
	return dato % 10;
}

int calcular_segunda_cifra(int dato) {
	return dato / 10;
}

int* radix_sort(int arreglo[], size_t n) {
	int* arreglo_ordenado1 = NULL;
	int* arreglo_ordenado2 = NULL;
	
	arreglo_ordenado1 = counting_sort(arreglo, n, 0, 9, calcular_primer_cifra);
	if (!arreglo_ordenado1) {
		return NULL;
	}
	
	arreglo_ordenado2 = counting_sort(arreglo_ordenado1, n, 0, 9, calcular_segunda_cifra);
	free(arreglo_ordenado1);
	if (!arreglo_ordenado2) {
		return NULL;
	}
	
	return arreglo_ordenado2;
}

/* ******************************************************************
 *                        ALGORITMO BUCKETSORT
 * *****************************************************************/

void swap_arreglof(double vector[], int pos_1, int pos_2) {
	double aux = vector[pos_1];
	vector[pos_1] = vector[pos_2];
	vector[pos_2] = aux;
}

void quick_sortf(double vector[], int inicio, int fin) {
	if ((fin - inicio) < 2) {
		return;
	}
	
	int izq = inicio + 1;
	int der = fin - 1;
	int pivote = inicio;
	int medio = (izq + der) / 2;                    
	swap_arreglof(vector, pivote, medio);           

	while (izq <= der) {
		while ((izq <= der) && (vector[der] >= vector[pivote])) {
			der--;
		}
		while ((izq <= der) && (vector[izq] < vector[pivote])) {
			izq++;
		}
		if (izq < der) {
			swap_arreglof(vector, izq, der);
		}
	}

	swap_arreglof(vector, pivote, der);              
	quick_sortf(vector, inicio, der);                
	quick_sortf(vector, der+1, fin);
}

void bucket_sort(double arreglo[], int n) {
	double arreglo_auxiliar[n];
	int cantidad_por_balde[6];
	lista_t* listas[5];
	
	cantidad_por_balde[5] = n;
	for (size_t i = 0; i < 5; i++) {
		listas[i] = lista_crear();
		cantidad_por_balde[i] = 0;
	}
	
	for (size_t i = 0; i < n; i++) {
		if (arreglo[i] <= 0.05) {
			lista_insertar_ultimo(listas[0], &arreglo[i]); 
		} else if ((arreglo[i] > 0.05) && (arreglo[i] <= 0.08)) {
			lista_insertar_ultimo(listas[1], &arreglo[i]);
			cantidad_por_balde[0] = cantidad_por_balde[0] + 1;
		} else if ((arreglo[i] > 0.08) && (arreglo[i] <= 0.15)) {
			lista_insertar_ultimo(listas[2], &arreglo[i]);
			cantidad_por_balde[1] = cantidad_por_balde[1] + 1;
		} else if ((arreglo[i] > 0.15) && (arreglo[i] <= 0.3)) {
			lista_insertar_ultimo(listas[3], &arreglo[i]);
			cantidad_por_balde[2] = cantidad_por_balde[2] + 1;
		} else {
			lista_insertar_ultimo(listas[4], &arreglo[i]);
			cantidad_por_balde[3] = cantidad_por_balde[3] + 1;
		}
	}
	
	size_t j = 0;
	for (size_t i = 0; i < 5; i++) {
		while (!lista_esta_vacia(listas[i])) {
			arreglo_auxiliar[j] = *(double*)lista_borrar_primero(listas[i]);
			j++;
		}
		lista_destruir(listas[i], NULL);
		quick_sortf(arreglo_auxiliar, cantidad_por_balde[i], cantidad_por_balde[i + 1]);
	}
	
	for (size_t i = 0; i < n; i++) {
		arreglo[i] = arreglo_auxiliar[i];
	}
}
 /* ******************************************************************
 *                        ALGORITMO QUICKSORT
 * *****************************************************************/

void swap_arreglo(int vector[], int pos_1, int pos_2) {
	int aux = vector[pos_1];
	vector[pos_1] = vector[pos_2];
	vector[pos_2] = aux;
}

void quick_sort(int vector[], int inicio, int fin) {
	if ((fin - inicio) < 2) {
		return;
	}
	
	int izq = inicio + 1;
	int der = fin - 1;
	int pivote = inicio;
	int medio = (izq + der) / 2;                    // Cambia el del medio con el primero. 
	swap_arreglo(vector, pivote, medio);           // (optimización para vectores ordenados).swap_arreglo(vector, pivote, medio);

	while (izq <= der) {
		while ((izq <= der) && (vector[der] >= vector[pivote])) {
			der--;
		}
		while ((izq <= der) && (vector[izq] < vector[pivote])) {
			izq++;
		}
		if (izq < der) {
			swap_arreglo(vector, izq, der);
		}
	}

	swap_arreglo(vector, pivote, der);              // Coloca el pivote al final de los menores y el último
	quick_sort(vector, inicio, der);                // menor en el primer lugar.
	quick_sort(vector, der+1, fin);
}

#include "guia_sort.h"

//Ejercicio propuesto de la Guia
/*
Se tiene un arreglo de cadenas que representan fechas de la forma YYYYMMDD (ej: 20110626 representa el 26/06/2011). 
Implementar un algoritmo lineal que las ordene de forma creciente.
*/
void inicializar_arreglo(int arreglo[], size_t n) {
	for (size_t i = 0; i < n; i++) {
		arreglo[i] = 0;
	}
}

char** counting_sort(char** arreglo, size_t n, size_t minimo, size_t maximo, size_t cifra_significativa(char* dato, int posicion), int posicion) {
	int frecuencias[maximo + 1];
	
	inicializar_arreglo(frecuencias, maximo + 1);
	for (size_t i = 0; i < n; i++) {
		frecuencias[cifra_significativa(arreglo[i], posicion)] = frecuencias[cifra_significativa(arreglo[i], posicion)] + 1;
	}
	
	int frecuencias_acumuladas[maximo + 1];
	frecuencias_acumuladas[minimo] = 0;
	for (size_t i = minimo + 1; i < maximo + 1; i++) {
		frecuencias_acumuladas[i] = frecuencias_acumuladas[i - 1] + frecuencias[i - 1];
	}
	
	char** arreglo_auxiliar = malloc(sizeof(char*) * n);
	if (!arreglo_auxiliar) {
		return NULL;
	}
	
	for (size_t i = 0; i < n; i++) {
		arreglo_auxiliar[frecuencias_acumuladas[cifra_significativa(arreglo[i], posicion)]] = arreglo[i];            
		frecuencias_acumuladas[cifra_significativa(arreglo[i], posicion)] = frecuencias_acumuladas[cifra_significativa(arreglo[i], posicion)] + 1;
	}
	
	return arreglo_auxiliar;
}

size_t calcular_cifra(char* dato, int posicion) {
	size_t numero = (size_t)atoi(dato);
	size_t cifra_significativa = 0;
	
	for (int i = posicion; i < 8; i++) {
		cifra_significativa = numero % 10;
		numero = numero / 10;
	}
	
	return cifra_significativa;
}

char** radix_sort(char** arreglo, size_t n) {
	char** arreglo_ordenado = counting_sort(arreglo, n, 0, 9, calcular_cifra, 7);
	
	if (!arreglo_ordenado) {
		return NULL;
	}
	char** arreglo_auxiliar = arreglo_ordenado;
	
	for (int i = 6; i >= 0; i--) {
		arreglo_ordenado = counting_sort(arreglo_auxiliar, n, 0, 9, calcular_cifra, i);
		if (!arreglo_ordenado) {
			free(arreglo_auxiliar);
			return NULL;
		}
		free(arreglo_auxiliar);
		arreglo_auxiliar = arreglo_ordenado;
	}
	
	return arreglo_ordenado;
}

//Ejercicio 1 de la Guia
/*
Realizar un seguimiento de ordenar el siguiente arreglo utilizando Inserción, Selección, MergeSort, QuickSort y HeapSort. 
Contar la cantidad de operaciones (aproximadamente) 
para validar empíricamente la diferencia en el orden de cada uno, y poder comparar aquellos que sean iguales: [1, 7, 5, 8, 2, 4, 9, 6, 5].
*/

//Ejercicio 2 de la Guia
/*
Implementar un algoritmo que permita ordenar de menor a mayor en O(n) un arreglo casi ordenado de mayor a menor.
*/
void swap(int arreglo[], size_t x, size_t y) {
	int aux = arreglo[x];
	arreglo[x] = arreglo[y];
	arreglo[y] = aux;
}

void ordenar_arreglo(int arreglo[], size_t n) {
    for (size_t i = 0, j = n - 1; i < n; i++, j--) {
		swap(arreglo, i, j);
	}
	
	for (size_t i = 0; i < (n - 1); i++) {
		if (arreglo[i] > arreglo[i + 1]) {
			swap(arreglo, i, i + 1);
		}
	}
}

//Ejercicio 3 de la Guia
/*
Se tiene un arreglo de números, como el del primer ejercicio (no necesariamente ese). 
Indicar cuál sería un algoritmo eficiente para ordenar dicho arreglo.
*/
//Cualquier algoritmo comparativo que sea O(n * log(n)), es decir, Quicksort, Mergesort o Heapsort.

//Ejercicio 4 de la Guia
/*
Se tiene un arreglo de estructuras de la forma struct {long anio, char* evento}, que indica el año y evento de un hecho definido a lo largo de la historia 
de la Tierra. Indicar y justificar cuál sería un algoritmo de ordenamiento apropiado para utilizar para ordenar dicho arreglo por año. 
Indicar también, si en vez de ordenar por año se decide ordenar por evento (lexicográficamente). 
Si se quiere ordenar por año y dentro de cada año, por evento: ¿Deben utilizarse para ambos campos el mismo algoritmo de ordenamiento? 
¿Que característica/s deben cumplir dicho o dichos algoritmos para que quede ordenado como se desea? ¿En qué orden deben aplicarse los ordenamientos?
*/
/*
Con los datos suministrados, para ordenar por año, podria utilizar un algoritmo como Mergesort, Quicksort o Heapsort.
Para ordenar por evento podria utilizar Radixsort o Countingsort.
No, no debe usarse el mismo algoritmo de ordenamiento para ambos. Los algoritmos tienen que ser estables. Primero ordenar por eventos y luego por años.
*/

//Ejercicio 5 de la Guia
/*
Hacer el seguimiento de counting sort para ordenar por año las siguientes obras:
    1988 - Crónicas del Ángel Gris
    2000 - Los Días del Venado
    1995 - Alta Fidelidad
    1987 - Tokio Blues
    2005 - En Picada
    1995 - Crónica del Pájaro que Da Cuerda al Mundo
    1995 - Ensayo Sobre la Ceguera
    2005 - Los Hombres que No Amaban a las Mujeres
¿Cuál es el orden del algoritmo? ¿Qué sucede con el orden de los elementos de un mismo año, respecto al orden inicial, luego de finalizado el algoritmo? 
Justificar brevemente.
*/
/*
El orden de Countingsort es O(n + k). Como el algoritmo es estable, el orden relativo de los elementos del mismo año se mantiene al final con respecto al
arreglo inicial.
*/

//Ejercicio 6 de la Guia
/*
Realizar el seguimiento de ordenar por Radix Sort el siguiente arreglo de cadenas que representan versiones. 
Cada versión tiene el formato a.b.c, donde cada valor a, b y c puede tener un valor entre 0 y 99. 
Considerar que se quiere que quede ordenado primero por la primera componente (a), luego por la segunda (b) y finalmente por la tercera (c). 
Tener en cuenta que, por ejemplo 1.1.3 < 1.1.20, 2.20.8 < 3.0.0.
["4.3.2", "5.1.2", "10.1.4", "2.1.20", "2.2.1", "4.2.3",
"2.1.5", "8.1.2", "5.30.1", "10.0.23"]
*/

//Ejercicio 7 de la Guia
/*
Indicar Verdadero o Falso, justificando de forma concisa en cualquier caso.

a. Podríamos mejorar el orden de complejidad de QuickSort si contaramos con más información sobre cómo son los datos a ordenar.
F: no podríamos mejorar el orden de complejidad de O(n * log(n)).

b. No siempre conviene utilizar Counting Sort para ordenar un arreglo de números enteros.
V: Counting es eficiente si el rango de valores es acotado y conocido (o de facil obtención).

c. Que un algoritmo de ordenamientos sea estable implica que el algoritmo ordena sobre el arreglo original (sin utilizar otro adicional). 
Por ejemplo, Counting Sort no es estable.
F: Un algoritmo de ordenamiento estable es aquel que respeta el orden de aparicion relativo de los elementos de igual valor.
*/

//Ejercicio 8 de la Guia
/*
Se quiere ordenar un arreglo de películas por su género. No se conoce cuántos, ni cuáles son estos géneros, 
pero se sabe que son muy pocos comparando con la cantidad de películas a ordenar. 
Diseñar un algoritmo que permita ordenar las películas en tiempo lineal de la cantidad de películas y explique como funcionaría sobre las siguientes películas:

    Donnie Darko (2001): Thriller psicológico
    Juno (2007): Coming of age
    The Shining (1980): Thriller psicológico
    Labyrinth (1986): Fantasía
    Ferris Bueller’s Day Off (1986): Coming of age
*/

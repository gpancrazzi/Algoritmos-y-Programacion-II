#include "heap.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 3
#define CONSTANTE_REDIMENSION 2
#define CANTIDAD_MINIMA_REDIMENSION 4

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/
 
struct heap {
    void** datos;
    size_t cantidad;
    size_t capacidad;
    cmp_func_t cmp;
};

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

size_t calcular_posicion_del_padre(size_t pos_elem) {
	return (pos_elem - 1) / 2;
}

size_t calcular_posicion_hijo_izquierdo(size_t pos_elem) {
	return (pos_elem * 2) + 1;
}

void swap(void** datos, size_t pos1, size_t pos2) {
	void* dato_aux = datos[pos1];
	datos[pos1] = datos[pos2];
	datos[pos2] = dato_aux;
}

bool redimensionar_heap(heap_t* heap, size_t capacidad) {
	void** temp_datos = realloc(heap->datos, sizeof(void*) * capacidad);
	
	if (!temp_datos) {
		return false;
	}
	
	heap->capacidad = capacidad;
	heap->datos = temp_datos;
	return true;
}

void upheap(void** datos, cmp_func_t cmp, size_t pos_elem) {
	if (pos_elem == 0) {
		return;
	}
	
	size_t pos_padre = calcular_posicion_del_padre(pos_elem);
	if (cmp(datos[pos_elem], datos[pos_padre]) <= 0) {
		return;
	}
	
	swap(datos, pos_elem, pos_padre);
	upheap(datos, cmp, pos_padre);
}

void downheap(void** datos, cmp_func_t cmp, size_t n, size_t pos_elem) {
	size_t pos_hijo = calcular_posicion_hijo_izquierdo(pos_elem);
	
	if (pos_hijo >= n) {
		return;
	}
	
	if (((pos_hijo + 1) < n) && (cmp(datos[pos_hijo + 1], datos[pos_hijo]) > 0)) {
		pos_hijo++;
	}
	
	if (cmp(datos[pos_elem], datos[pos_hijo]) >= 0) {
		return;
	}
	
	swap(datos, pos_elem, pos_hijo);
	downheap(datos, cmp, n, pos_hijo);
}

void heapify(void** datos, cmp_func_t cmp, size_t n) {
    size_t i = calcular_posicion_del_padre(n - 1);
	
	while (i != -1) {
		downheap(datos, cmp, n, i);
		i--;
	}
}

/* ******************************************************************
 *                        FUNCION HEAPSORT
 * *****************************************************************/

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	if (cant <= 1) {
		return;
	}
	
	heapify(elementos, cmp, cant);
	for (size_t i = cant - 1; i > 0; i--) {
		swap(elementos, 0, i);
		downheap(elementos, cmp, i, 0);
	}
}
 
/* ******************************************************************
 *                        PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
	
	if (!heap) {
		return NULL;
	}
	
	void** datos = malloc(sizeof(void*) * CAPACIDAD_INICIAL);
	if (!datos) {
		free(heap);
		return NULL;
	}
	
	heap->datos = datos;
	heap->cmp = cmp;
	heap->capacidad = CAPACIDAD_INICIAL;
	heap->cantidad = 0;
	return heap;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
	if (n <= 0) {
		return NULL;
	}
	
	heap_t* heap = heap_crear(cmp);
	if (!heap) {
		return NULL;
	}
	
	while (heap->capacidad < n) {
		heap->capacidad *= CONSTANTE_REDIMENSION;
	}
	
	void** arreglo_copia = malloc(sizeof(void*) * heap->capacidad);
	if (!arreglo_copia) {
		heap_destruir(heap, NULL);
		return NULL;
	}
	
	for (size_t i = 0; i < n; i++) {
		arreglo_copia[i] = arreglo[i];
	}
	
	heapify(arreglo_copia, cmp, n);
	heap->cantidad = n;
	free(heap->datos);
	heap->datos = arreglo_copia;
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
	if (destruir_elemento) {
		for (size_t i = 0; i < heap->cantidad; i++) {
			destruir_elemento(heap->datos[i]);
		}
	}
	
	free(heap->datos);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap) {
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
	return heap->cantidad == 0;
}

bool heap_encolar(heap_t *heap, void *elem) {
	if (heap->cantidad == heap->capacidad) {
		if (!redimensionar_heap(heap, heap->capacidad * CONSTANTE_REDIMENSION)) {
			return false;
		}
	}
	
	heap->datos[heap->cantidad] = elem;
	upheap(heap->datos, heap->cmp, heap->cantidad);
	heap->cantidad++;
	return true;
}

void *heap_ver_max(const heap_t *heap) {
	if (heap_esta_vacio(heap)) {
		return NULL;
	}
	
	return heap->datos[0];
}

void *heap_desencolar(heap_t *heap) {
	if (heap_esta_vacio(heap)) {
		return NULL;
	}
	
	if ((heap->cantidad <= (heap->capacidad / CANTIDAD_MINIMA_REDIMENSION)) && ((heap->capacidad / CONSTANTE_REDIMENSION) >= CAPACIDAD_INICIAL)) {
		redimensionar_heap(heap, heap->capacidad / CONSTANTE_REDIMENSION);
	}
	
	void* temp_dato = heap->datos[0];
	swap(heap->datos, 0, heap->cantidad - 1);
	heap->cantidad--;
	downheap(heap->datos, heap->cmp, heap->cantidad, 0);
	return temp_dato;
}

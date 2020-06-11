#include "heap.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 50
#define CONSTANTE_REDIMENSION 2

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

void heap_swap(void** datos, size_t pos1, size_t pos2) {
	void* dato_aux = datos[pos1];
	datos[pos1] = datos[pos2];
	datos[pos2] = dato_aux;
}

bool heap_redimensionar(heap_t* heap, size_t capacidad) {
	void** temp_datos = realloc(heap->datos, sizeof(void*) * capacidad);
	
	if (temp_datos == NULL) {
		return false;
	}
	
	heap->capacidad = capacidad;
	heap->datos = temp_datos;
	return true;
}

void heap_upheap(void** datos, cmp_func_t cmp, size_t pos_elem, size_t pos_padre) {
	if ((pos_elem == 0) || (cmp(datos[pos_elem], datos[pos_padre]) <= 0)) {
		return;
	}
	
	heap_swap(datos, pos_elem, pos_padre);
	heap_upheap(datos, cmp, pos_padre, (pos_padre - 1) / 2); 
}

void heap_downheap(void** datos, cmp_func_t cmp, size_t n, size_t pos_elem) {
	size_t pos_padre = pos_elem, pos_hijo_mayor = (pos_elem * 2) + 1;
	
	while (pos_hijo_mayor < n) {
		if (((pos_hijo_mayor + 1) < n) && (cmp(datos[pos_hijo_mayor + 1], datos[pos_hijo_mayor]) > 0)) {
			pos_hijo_mayor++;
		}
		if (cmp(datos[pos_padre], datos[pos_hijo_mayor]) >= 0) {
			return;
		}
		heap_swap(datos, pos_padre, pos_hijo_mayor);
		pos_padre = pos_hijo_mayor;
		pos_hijo_mayor = (pos_padre * 2) + 1;
	}
}

void heap_heapify(void** datos, cmp_func_t cmp, size_t n, size_t pos_ult_padre) {
    size_t i = pos_ult_padre;
	
	while (i != -1) {
		heap_downheap(datos, cmp, n, i);
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
	
	heap_heapify(elementos, cmp, cant, (cant - 2) / 2);
	for (size_t i = cant - 1; i > 0; i--) {
		heap_swap(elementos, 0, i);
		heap_downheap(elementos, cmp, i, 0);
	}
}
 
/* ******************************************************************
 *                        PRIMITIVAS DEL HEAP
 * *****************************************************************/

heap_t *heap_crear(cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
	
	if (heap == NULL) {
		return NULL;
	}
	
	void** datos = malloc(sizeof(void*) * CAPACIDAD_INICIAL);
	if (datos == NULL) {
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
	if (heap == NULL) {
		return NULL;
	}
	
	while (heap->capacidad < n) {
		heap->capacidad *= CONSTANTE_REDIMENSION;
	}
	
	void** arreglo_copia = malloc(sizeof(void*) * heap->capacidad);
	if (arreglo_copia == NULL) {
		free(heap->datos);
		free(heap);
		return NULL;
	}
	
	for (size_t i = 0; i < n; i++) {
		arreglo_copia[i] = arreglo[i];
	}
	
	heap_heapify(arreglo_copia, cmp, n, (n - 2) / 2);
	heap->cantidad = n;
	free(heap->datos);
	heap->datos = arreglo_copia;
	return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
	while ((heap->cantidad > 0) && (destruir_elemento != NULL)) {
		destruir_elemento(heap_desencolar(heap));
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
		if (heap_redimensionar(heap, heap->capacidad * CONSTANTE_REDIMENSION) == false) {
			return false;
		}
	}
	
	heap->datos[heap->cantidad] = elem;
	heap_upheap(heap->datos, heap->cmp, heap->cantidad, (heap->cantidad - 1) / 2);
	heap->cantidad++;
	return true;
}

void *heap_ver_max(const heap_t *heap) {
	if (heap_esta_vacio(heap) == true) {
		return NULL;
	}
	
	return heap->datos[0];
}

void *heap_desencolar(heap_t *heap) {
	if (heap_esta_vacio(heap) == true) {
		return NULL;
	}
	
	if ((heap->cantidad <= (heap->capacidad / 4)) && ((heap->capacidad / CONSTANTE_REDIMENSION) >= CAPACIDAD_INICIAL)) {
		heap_redimensionar(heap, heap->capacidad / CONSTANTE_REDIMENSION);
	}
	
	void* temp_dato = heap->datos[0];
	heap_swap(heap->datos, 0, heap->cantidad - 1);
	heap->cantidad--;
	heap_downheap(heap->datos, heap->cmp, heap->cantidad, 0);
	return temp_dato;
}

#include "pila.h"
#include <stdlib.h>

#define CAPACIDAD_INICIAL 4
#define CONSTANTE_REDIMENSION 2
#define CANTIDAD_MINIMA_REDIMENSION 4

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/

struct pila {
    void** datos;
    size_t cantidad;
    size_t capacidad;
};

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/
 
bool pila_redimensionar(pila_t *pila, size_t capacidad) {
	void** temp_datos = realloc(pila->datos, sizeof(void*) * capacidad);
	
	if (temp_datos == NULL) {
		return false;
	}
	
	pila->capacidad = capacidad;
	pila->datos = temp_datos;
	return true;
}

/* ******************************************************************
 *                        PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void) {
	pila_t* pila = malloc(sizeof(pila_t));
	
	if (pila == NULL) {
		return NULL;
	}
	
	pila->cantidad = 0;
	pila->capacidad = CAPACIDAD_INICIAL;
	pila->datos = malloc(sizeof(void*) * pila->capacidad);
	if (pila->datos == NULL) {
		free(pila);
		return NULL;
	}
	
	return pila;
}

void pila_destruir(pila_t *pila) {
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila) {
	if (pila->cantidad == 0) {
		return true;
	}
	
	return false;
}

bool pila_apilar(pila_t *pila, void* valor) {
	if (pila->cantidad == pila->capacidad) {
		if (pila_redimensionar(pila, pila->capacidad * CONSTANTE_REDIMENSION) == false) {
			return false;
		}
	}
	
	pila->datos[pila->cantidad] = valor;
	pila->cantidad++;
	return true;
}

void* pila_ver_tope(const pila_t *pila) {
	if (pila_esta_vacia(pila) == false) {
		return pila->datos[pila->cantidad - 1];
	}
	
	return NULL;
}

void* pila_desapilar(pila_t *pila) {
	if (pila_esta_vacia(pila) == true) {
		return NULL;
	}
	
	if ((pila->cantidad <= (pila->capacidad / CANTIDAD_MINIMA_REDIMENSION)) && ((pila->capacidad / CONSTANTE_REDIMENSION) >= CAPACIDAD_INICIAL)) {
		pila_redimensionar(pila, pila->capacidad / CONSTANTE_REDIMENSION);
	}
	
	void* temp_ptr = pila->datos[pila->cantidad - 1];
	pila->cantidad--;
	return temp_ptr;
}

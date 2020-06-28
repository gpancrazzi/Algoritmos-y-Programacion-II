#include "cola.h"
#include <stdlib.h>

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/

struct nodo {
	void* dato;
	struct nodo* prox;
};

typedef struct nodo nodo_t;

struct cola {
	struct nodo* prim;
	struct nodo* ult;
};

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* crear_nodo(void* valor) {
	nodo_t* nodo = malloc(sizeof(nodo_t));
	
	if (!nodo) {
		return NULL;
	}
	
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}

/* ******************************************************************
 *                        PRIMITIVAS DE LA COLA
 * *****************************************************************/

cola_t* cola_crear(void) {
	cola_t* cola = malloc(sizeof(cola_t));
	
	if (!cola) {
		return NULL;
	}
	
	cola->prim = NULL;
	cola->ult = NULL;
	return cola;
}

void cola_destruir(cola_t *cola, void destruir_dato(void*)) {
	while (!cola_esta_vacia(cola)) {
		if (destruir_dato) {
			destruir_dato(cola_desencolar(cola));
		} else {
			cola_desencolar(cola);
		}
	}
	
	free(cola);
}

bool cola_esta_vacia(const cola_t *cola) {
	return ((!cola->prim) && (!cola->ult));
}

bool cola_encolar(cola_t *cola, void* valor) {
	nodo_t* nodo = crear_nodo(valor);
	
	if (!nodo) {
		return false;
	} 
	
	if (cola_esta_vacia(cola)) {
		cola->prim = nodo;
	} else {
		cola->ult->prox = nodo;
	}
	
	cola->ult = nodo;
	return true;
}

void* cola_ver_primero(const cola_t *cola) {
	if (!cola_esta_vacia(cola)) {
		return cola->prim->dato;
	}
	
	return NULL;
}

void* cola_desencolar(cola_t *cola) {
	if (cola_esta_vacia(cola)) {
		return NULL;
	}
	
	void* temp_ptr = cola->prim->dato;
	nodo_t* temp_nodo = cola->prim;
    if (cola->prim == cola->ult) {
		cola->ult = NULL;
	}
	
	cola->prim = cola->prim->prox;
	free(temp_nodo);
	return temp_ptr;
}

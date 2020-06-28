#define _POSIX_C_SOURCE 200809L
#include "abb.h"
#include "pila.h"
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/

struct nodo_abb {
    struct nodo_abb* izq;
    struct nodo_abb* der;
    void* dato;
    const char* clave;
};

typedef struct nodo_abb nodo_abb_t;

struct abb {
	nodo_abb_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;
};

struct abb_iter {
	const abb_t* arbol;
	pila_t* pila;
};

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_abb_t* crear_nodo(const char *clave, void *dato) {
	nodo_abb_t* nodo_arbol = malloc(sizeof(nodo_abb_t));
	
	if (!nodo_arbol) {
		return NULL;
	}
	
	char* clave_dup = strdup(clave);
	if (!clave_dup) {
		free(nodo_arbol);
		return NULL;
	}
	
	nodo_arbol->der = NULL;
	nodo_arbol->izq = NULL;
	nodo_arbol->clave = clave_dup;
	nodo_arbol->dato = dato;
	return nodo_arbol;
}

nodo_abb_t** obtener_puntero_nodo(nodo_abb_t** nodo_ptr, abb_comparar_clave_t cmp, const char* clave) {
	nodo_abb_t* nodo_arbol = *nodo_ptr;
	
	if (!nodo_arbol) {
		return nodo_ptr;
	}
	
	if (cmp(nodo_arbol->clave, clave) == 0) {
		return nodo_ptr;
	}
	
	if (cmp(nodo_arbol->clave, clave) > 0) {
		return obtener_puntero_nodo(&nodo_arbol->izq, cmp, clave);
	}
	
	return obtener_puntero_nodo(&nodo_arbol->der, cmp, clave);
}

nodo_abb_t* buscar_reemplazante(nodo_abb_t* nodo_arbol) {
	if (!nodo_arbol->der) {
		return nodo_arbol;
	}
	
	return buscar_reemplazante(nodo_arbol->der);
}

void destruir_nodos(nodo_abb_t* nodo_arbol, abb_destruir_dato_t destruir_dato) {
	if (!nodo_arbol) {
		return;
	}
	
	destruir_nodos(nodo_arbol->izq, destruir_dato);
	destruir_nodos(nodo_arbol->der, destruir_dato);
	free((char*)nodo_arbol->clave);
	if (destruir_dato) {
		destruir_dato(nodo_arbol->dato);
	}
	
	free(nodo_arbol);
}

bool iterar_in_order(nodo_abb_t* nodo_arbol, bool visitar(const char *, void *, void *), void *extra) {
	if (!nodo_arbol) {
		return true;
	}
	
	if (!iterar_in_order(nodo_arbol->izq, visitar, extra)) {
		return false;
	}
	
	if (!visitar(nodo_arbol->clave, nodo_arbol->dato, extra)) {
		return false;
	}
	
	return iterar_in_order(nodo_arbol->der, visitar, extra);
}

bool apilar_nodos(nodo_abb_t* nodo_arbol, pila_t* pila) {
	if (!nodo_arbol) {
		return true;
	}
	
	if (!pila_apilar(pila, nodo_arbol)) {
		return false;
	}
	
	return apilar_nodos(nodo_arbol->izq, pila);
}

void* borrar_nodo(abb_t* arbol, nodo_abb_t** ptr_nodo, nodo_abb_t* nodo_arbol, nodo_abb_t* nodo_hijo) {
	void* dato = nodo_arbol->dato;
	
	free((char*)nodo_arbol->clave);
	free(nodo_arbol);
	arbol->cantidad--;
	*ptr_nodo = nodo_hijo;
	return dato;
}

void* borrar_nodo_con_dos_hijos(abb_t* arbol, nodo_abb_t** ptr_nodo, nodo_abb_t* nodo_arbol) {
	void* dato = nodo_arbol->dato;
	nodo_abb_t* nodo_reemplazante = buscar_reemplazante(nodo_arbol->izq);
	
	char* clave_aux = strdup(nodo_reemplazante->clave);
	if (!clave_aux) {
		return NULL;
	}
	
	nodo_arbol->dato = abb_borrar(arbol, nodo_reemplazante->clave);
	free((char*)nodo_arbol->clave);
	nodo_arbol->clave = clave_aux;
	return dato;
}

/* ******************************************************************
 *                        PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
	abb_t* abb = malloc(sizeof(abb_t));
	
	if (!abb) {
		return NULL;
	}
	
	abb->raiz = NULL;
	abb->cmp = cmp;
	abb->destruir_dato = destruir_dato;
	abb->cantidad = 0;
	return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
	nodo_abb_t** ptr_nodo = obtener_puntero_nodo(&arbol->raiz, arbol->cmp, clave);
	nodo_abb_t* nodo_arbol_temp = *ptr_nodo;
	
	if (nodo_arbol_temp) {
		if (arbol->destruir_dato) {
			arbol->destruir_dato(nodo_arbol_temp->dato);
		}
		nodo_arbol_temp->dato = dato;
		return true;
	}
	
	nodo_abb_t* nodo_arbol = crear_nodo(clave, dato);
	if (!nodo_arbol) {
		return false;
	}
	
	*ptr_nodo = nodo_arbol;
	arbol->cantidad++;
	return true;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
	nodo_abb_t** ptr_nodo = obtener_puntero_nodo(&arbol->raiz, arbol->cmp, clave);
	nodo_abb_t* nodo_arbol_temp = *ptr_nodo;
	
	if (!nodo_arbol_temp) {
		return NULL;
	}
	
	if (nodo_arbol_temp->der && nodo_arbol_temp->izq) {
		return borrar_nodo_con_dos_hijos(arbol, ptr_nodo, nodo_arbol_temp);
	}
	
	if (nodo_arbol_temp->der && !nodo_arbol_temp->izq) {
		return borrar_nodo(arbol, ptr_nodo, nodo_arbol_temp, nodo_arbol_temp->der);
	} 
	
	if (!nodo_arbol_temp->der && nodo_arbol_temp->izq) {
		return borrar_nodo(arbol, ptr_nodo, nodo_arbol_temp, nodo_arbol_temp->izq);
	}
	
	return borrar_nodo(arbol, ptr_nodo, nodo_arbol_temp, NULL);
}

void *abb_obtener(const abb_t *arbol, const char *clave) {
	abb_t* arbol_temp = (abb_t*)arbol;
	nodo_abb_t** ptr_nodo = obtener_puntero_nodo(&arbol_temp->raiz, arbol->cmp, clave);
	nodo_abb_t* nodo_arbol_temp = *ptr_nodo;
	
	if (!nodo_arbol_temp) {
		return NULL;
	}
	
	return nodo_arbol_temp->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {
	abb_t* arbol_temp = (abb_t*)arbol;
	nodo_abb_t** ptr_nodo = obtener_puntero_nodo(&arbol_temp->raiz, arbol->cmp, clave);
	nodo_abb_t* nodo_arbol_temp = *ptr_nodo;
	
	if (!nodo_arbol_temp) {
		return false;
	}
	
	return true;
}

size_t abb_cantidad(abb_t *arbol) {
	return arbol->cantidad;
}

void abb_destruir(abb_t *arbol) {
	destruir_nodos(arbol->raiz, arbol->destruir_dato);
	free(arbol);
}

/* ******************************************************************
 *                        PRIMITIVA DEL ABB ITERADOR INTERNO
 * *****************************************************************/
 
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
	iterar_in_order(arbol->raiz, visitar, extra);
}
 
 /* ******************************************************************
 *                        PRIMITIVAS DEL ABB ITERADOR EXTERNO
 * *****************************************************************/
 
abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	
	if (!iter) {
		return NULL;
	}
	
	pila_t* pila = pila_crear();
	if (!pila) {
		free(iter);
		return NULL;
	}
	
	if (!apilar_nodos(arbol->raiz, pila)) {
		pila_destruir(pila);
		free(iter);
		return NULL;
	}
	
	iter->arbol = arbol;
	iter->pila = pila;
	return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {
	if (abb_iter_in_al_final(iter)) {
		return false;
	}
	
	nodo_abb_t* nodo_tope = (nodo_abb_t*)pila_desapilar(iter->pila);
	return apilar_nodos(nodo_tope->der, iter->pila);
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {
	if (abb_iter_in_al_final(iter)) {
		return NULL;
	}
	
	nodo_abb_t* nodo_actual = (nodo_abb_t*)pila_ver_tope(iter->pila);
	return nodo_actual->clave;
}

bool abb_iter_in_al_final(const abb_iter_t *iter) {
	return pila_esta_vacia(iter->pila);
}

void abb_iter_in_destruir(abb_iter_t* iter) {
	pila_destruir(iter->pila);
	free(iter);
}

#include "lista.h"
#include <stdlib.h>

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/

struct nodo {
	void* dato;
	struct nodo* prox;
};

typedef struct nodo nodo_t;

struct lista {
	struct nodo* prim;
	struct nodo* ult;
	size_t largo;
};

struct lista_iter {
	struct nodo* act;
	struct nodo* ant;
	lista_t* lista;
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
 *                        PRIMITIVAS DE LA LISTA
 * *****************************************************************/
 
lista_t *lista_crear(void) {
	lista_t* lista = malloc(sizeof(lista_t));
	
	if (!lista) {
		return NULL;
	}
	
	lista->prim = NULL;
	lista->ult = NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista) {
	return ((!lista->prim) && (!lista->ult));
}

bool lista_insertar_primero(lista_t *lista, void *dato) {
	nodo_t* nodo = crear_nodo(dato);
	
	if (!nodo) {
		return false;
	}
	
	if (lista_esta_vacia(lista)) {
		lista->ult = nodo;
    } else {
    	nodo->prox = lista->prim;
	}
    
	lista->prim = nodo;
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
	nodo_t* nodo = crear_nodo(dato);
	
	if (!nodo) {
		return false;
	}
	
	if (lista_esta_vacia(lista)) {
		lista->prim = nodo;
	} else {
		lista->ult->prox = nodo;
	}
	
	lista->ult = nodo;
	lista->largo++;
	return true;
}

void *lista_borrar_primero(lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	
	void* temp_ptr = lista->prim->dato;
	nodo_t* temp_nodo = lista->prim;
	lista->prim = lista->prim->prox;
	lista->largo--;
	if (lista->largo == 0) {
		lista->ult = NULL;
	}
	
	free(temp_nodo);
	return temp_ptr;
}

void *lista_ver_primero(const lista_t *lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) {
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	while (!lista_esta_vacia(lista)) {
		if (destruir_dato) {
			destruir_dato(lista_borrar_primero(lista));
		} else {
			lista_borrar_primero(lista);
		}
	}
	
	free(lista);
}

/* ******************************************************************
 *              PRIMITIVA DE LA LISTA ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
	nodo_t* temp_nodo = lista->prim;
	
	while ((temp_nodo) && (visitar(temp_nodo->dato, extra))) {
		temp_nodo = temp_nodo->prox;
	}
}

/* ******************************************************************
 *             PRIMITIVAS DE LA LISTA ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista) {
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	
	if (!iter) {
		return NULL;
	}
	
	iter->act = lista->prim;
	iter->ant = NULL;
	iter->lista = lista;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
	if (!iter->act) {
		return false;
	}
	
	iter->ant = iter->act;
	iter->act = iter->act->prox;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
	if (!iter->act) {
		return NULL;
	}
	
	return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
	return (!iter->act);
}

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	if (lista_iter_al_final(iter)) {
		if (lista_insertar_ultimo(iter->lista, dato)) {
			iter->act = iter->lista->ult;
			return true;
		}
		return false;
	}
	
	if (iter->act == iter->lista->prim) {
		if (lista_insertar_primero(iter->lista, dato)) {
			iter->act = iter->lista->prim;
			return true;
		}
		return false;
	}
	
	nodo_t* nodo = crear_nodo(dato);
	if (!nodo) {
		return false;
	}
	
	nodo->prox = iter->act;
	iter->ant->prox = nodo;
	iter->act = nodo;
	iter->lista->largo++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
	if (lista_iter_al_final(iter)) {
		return NULL;
	}
	
	if (iter->act == iter->lista->prim) {
		iter->act = iter->act->prox;
		return lista_borrar_primero(iter->lista);
	}
	
	if (iter->act == iter->lista->ult) {
		iter->lista->ult = iter->ant;
	}
	
	void* temp_dato = iter->act->dato;
	nodo_t* temp_nodo = iter->act;
	iter->ant->prox = iter->act->prox;
	iter->act = iter->act->prox;
	iter->lista->largo--;
	free(temp_nodo);
	return temp_dato;
}

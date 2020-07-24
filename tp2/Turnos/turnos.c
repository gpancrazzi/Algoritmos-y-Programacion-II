#include "turnos.h"
#include "heap.h"
#include "lista.h"
#include <stdlib.h>

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/

struct turnos {
	lista_t* urgentes;
	heap_t* regulares;
	turnos_destruir_dato_t destruir_dato;
};

/* ******************************************************************
 *                        PRIMITIVAS DE TURNOS
 * *****************************************************************/

turnos_t* turnos_crear(cmp_fun_t cmp, turnos_destruir_dato_t destruir_dato) {
	turnos_t* turnos = malloc(sizeof(turnos_t));
	
	if (!turnos) {
		return NULL;
	}
	
	turnos->urgentes = lista_crear();
	if (!turnos->urgentes) {
		free(turnos);
		return NULL;
	}
	
	turnos->regulares = heap_crear(cmp);
	if (!turnos->regulares) {
		free(turnos);
		lista_destruir(turnos->urgentes, NULL);
		return NULL;
	}
	
	turnos->destruir_dato = destruir_dato;
	return turnos;
}

void turnos_destruir(turnos_t* turnos) {
	lista_destruir(turnos->urgentes, turnos->destruir_dato);
	heap_destruir(turnos->regulares, turnos->destruir_dato);
	free(turnos);
}

bool turnos_encolar(turnos_t* turnos, void *elem, bool es_prioritario) {
	if (es_prioritario) {
		return lista_insertar_ultimo(turnos->urgentes, elem);
	}
	
	return heap_encolar(turnos->regulares, elem);
}

void *turnos_desencolar(turnos_t *turnos) {
	if (lista_esta_vacia(turnos->urgentes)) {
		return heap_desencolar(turnos->regulares);
	}
	
	return lista_borrar_primero(turnos->urgentes);
}

void *turnos_ver_mas_prioritario(const turnos_t *turnos) {
	if (lista_esta_vacia(turnos->urgentes)) {
		return heap_ver_max(turnos->regulares);
	}
	
	return lista_ver_primero(turnos->urgentes);
}

size_t turnos_cantidad(const turnos_t *turnos) {
	return lista_largo(turnos->urgentes) + heap_cantidad(turnos->regulares);
}

bool turnos_esta_vacio(const turnos_t *turnos) {
	return lista_esta_vacia(turnos->urgentes) && heap_esta_vacio(turnos->regulares);
}

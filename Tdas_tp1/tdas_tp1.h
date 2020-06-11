#ifndef TDAS_TP1_H
#define TDAS_TP1_H

#include "pila.h"
#include "cola.h"
#include "lista.h"
#include <stdbool.h>
#include <stddef.h>

struct lista2;
typedef struct lista2 lista2_t;

/* 
Devuelve un arreglo de tamaño n con los n topes de la pila 
(los primeros n elementos si estos fueran desapilados).
Completar el arreglo a devolver con NULL cuando el n recibido por parámetro sea mayor a la cantidad de elementos de la pila.
*/
void** pila_multitop(const pila_t* pila, size_t n);

/*
*/
void* lista_obtener_kultimo(lista2_t* lista, size_t k);

/*
*/
bool orden_ascendente_pila(pila_t* pila);

/*
*/
void** cola_multiprimeros(const cola_t* cola, size_t k);

/*
*/
void** fcola_multiprimeros(cola_t* cola, size_t k);

/*
*/
void lista_invertir(lista_t* lista);

/*
*/
pila_t* invertir_pila(pila_t* pila);

/*
*/
void cola_filtrar(cola_t* cola, bool (*filtro)(void*));

#endif // TDAS_TP1_H

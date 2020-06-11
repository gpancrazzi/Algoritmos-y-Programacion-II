//Ejercicio 5 de la Guia
/*
Implementar en C el TDA ComposiciónFunciones que emula la composición de funciones (i.e. f(g(h(x))).
*/
#include "composicion_funciones.h"
#include "pila.h"
#include <stdlib.h>

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/
 
struct composicion {
	pila_t* funciones;
};

/* ******************************************************************
 *             PRIMITIVAS DE LA COMPOSICION DE FUNCIONES
 * *****************************************************************/
 
composicion_t* composicion_crear() {
	composicion_t* composicion = malloc(sizeof(composicion_t));
	
	if (!composicion) {
		return NULL;
	}
	
	composicion->funciones = pila_crear();
	if (!composicion->funciones) {
		free(composicion);
		return NULL;
	}
	
	return composicion;
}
/*
La complejidad temporal de la primitiva es O(1).
*/

void composicion_destruir(composicion_t* composicion) {
	pila_destruir(composicion->funciones);
	free(composicion);
}
/*
La complejidad temporal de la primitiva es O(1).
*/

bool composicion_agregar_funcion(composicion_t* composicion, double (*f)(double)) {
	return pila_apilar(composicion->funciones, f);
}
/*
La complejidad temporal de la primitiva es O(1).
*/

double composicion_aplicar(composicion_t* composicion, double valor) {
	double resultado = valor;
	funcion_t funcion = NULL;
	
	while (!pila_esta_vacia(composicion->funciones)) {
		funcion = pila_desapilar(composicion->funciones);
		resultado = funcion(resultado);
	}
	
	return resultado;
}
/*
La complejidad temporal de la primitiva es O(n). Siendo n la cantidad de funciones apiladas.
*/

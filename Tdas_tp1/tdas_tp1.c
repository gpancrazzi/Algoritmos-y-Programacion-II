#include "tdas_tp1.h"
#include <stdlib.h>

//Ejercicio propuesto
/*
Implementar la primitiva de la pila void** pila_multitop(const pila_t* pila, size_t n), que devuelve un arreglo de tamaño n con los n topes de la pila 
(los primeros n elementos si estos fueran desapilados), sin utilizar estructuras auxiliares. Completar el arreglo a devolver con NULL cuando el n 
recibido por parámetro sea mayor a la cantidad de elementos de la pila.
Indicar el orden de complejidad de la primitiva.
*/
struct pila {
    void** datos;
    size_t cantidad;
    size_t capacidad;
};

void** pila_multitop(const pila_t* pila, size_t n) {
	if ((pila == NULL) || (n <= 0)) {
		return NULL;
	}
	
	void** arreglo = malloc(sizeof(void*) * n);
	if (arreglo == NULL) {
		return NULL;
	}
	
	for (size_t i = 0; i < n; i++) {
		if (pila_esta_vacia(pila)) {
			arreglo[i] = NULL;
		} else {
			arreglo[i] = pila->datos[pila->cantidad - 1 - i];
		}
	}
	
	return arreglo;
}
//Complejidad temporal del algoritmo es O(n).

//Ejercicio 6 de la Guia
/*
Escribir una primitiva que reciba una lista y devuelva el elemento que esté a k posiciones del final (el ante-k-último), recorriendo la lista una sola vez 
y sin usar estructuras auxiliares. Considerar que k es siempre menor al largo de la lista. 
Por ejemplo, si se recibe la lista [ 1, 5, 10, 3, 6, 8 ], y k = 4, debe devolver 10. 
Indicar el orden de complejidad de la primitiva.
*/
typedef struct nodo_lista {
    struct nodo_lista* prox;
    void* dato;
} nodo_lista_t;

struct lista2 {
    nodo_lista_t* prim;
};

void* lista_obtener_kultimo(lista2_t* lista, size_t k) {
	if (k == 0) {
		return NULL;
	}
	
	nodo_lista_t* nodo_iterador = lista->prim;
	nodo_lista_t* nodo_auxiliar = lista->prim;
	for (size_t i = 0; i < k; i++) {
		nodo_iterador = nodo_iterador->prox;
	}
	
	while (nodo_iterador) {
		nodo_auxiliar = nodo_auxiliar->prox;
		nodo_iterador = nodo_iterador->prox;
	}
	
	return nodo_auxiliar->dato;
}
//La complejidad temporal del algoritmo es O(n), siendo n, la cantidad de elementos de la lista.

//Ejercicio 7 de la Guia
/*
Dada una pila de enteros, escribir una función que determine si sus elementos están ordenados de manera ascendente. 
Una pila de enteros está ordenada de manera ascendente si, en el sentido que va desde el tope de la pila hacia el resto de elementos, 
cada elemento es menor al elemento que le sigue. La pila debe quedar en el mismo estado que al invocarse la función. 
Indicar y justificar el orden del algoritmo propuesto.
*/
void rearmar_pila(pila_t* pila, pila_t* pila_auxiliar) {
	while (!pila_esta_vacia(pila_auxiliar)) {
		pila_apilar(pila, pila_desapilar(pila_auxiliar));
	}
	
	pila_destruir(pila_auxiliar);
}

bool orden_ascendente_pila(pila_t* pila) {
	pila_t* pila_aux = pila_crear();
	
	if (!pila_aux) {
		return false;
	}
	
	void* num_ant = NULL;
	while (!pila_esta_vacia(pila)) {
		num_ant = pila_desapilar(pila);
		if ((!pila_ver_tope(pila)) && (pila_esta_vacia(pila_aux))) {
			pila_apilar(pila_aux, num_ant);
			rearmar_pila(pila, pila_aux);
	        return true;
		}
		if (((!pila_ver_tope(pila)) && (!pila_esta_vacia(pila_aux)) && (*(int*)num_ant < *(int*)pila_ver_tope(pila_aux))) 
		|| (*(int*)num_ant > *(int*)pila_ver_tope(pila))) {
			pila_apilar(pila_aux, num_ant);
			rearmar_pila(pila, pila_aux);
			return false;
		}
		pila_apilar(pila_aux, num_ant);
	}
	
	rearmar_pila(pila, pila_aux);
	return true;
}
//La complejidad temporal del algoritmo es O(n), siendo n la cantidad de enteros apilados.

//Ejercicio 8 de la Guia
/*
Implementar la primitiva void** cola_multiprimeros(const cola_t* cola, size_t k) que dada una cola y un número k, devuelva los primeros k elementos de la cola, 
en el mismo orden en el que habrían salido de la cola. En caso que la cola tenga menos de k elementos, rellenar con NULL. 
Indicar y justificar el orden de ejecución del algoritmo.
*/
struct nodo {
	void* dato;
	struct nodo* prox;
};

typedef struct nodo nodo_t;

struct cola {
	struct nodo* prim;
	struct nodo* ult;
};

void** cola_multiprimeros(const cola_t* cola, size_t k) {
	void** arreglo = malloc(sizeof(void*) * k);
	
	if (!arreglo) {
		return NULL;
	}
	
	nodo_t* nodo_auxiliar = cola->prim;
	for (size_t i = 0; i < k; i++) {
		if (!nodo_auxiliar) {
			arreglo[i] = NULL;
		} else {
			arreglo[i] = nodo_auxiliar->dato;
			nodo_auxiliar = nodo_auxiliar->prox;
		}
	}
	
	return arreglo;
}
//La complejidad temporal del algoritmo es O(k), siendo k la cantidad de elementos pedidos.

//Ejercicio 9 de la Guia
/*
Implementar la función void** cola_multiprimeros(cola_t* cola, size_t k) con el mismo comportamiento de la primitiva anterior.
*/
void** fcola_multiprimeros(cola_t* cola, size_t k) {
	void** arreglo = malloc(sizeof(void*) * k);
	
	if (!arreglo) {
		return NULL;
	}
	
	for (size_t i = 0; i < k; i++) {
		arreglo[i] = cola_desencolar(cola);
	}
	
	return arreglo;
}
//La complejidad temporal del algoritmo es O(k), siendo k la cantidad de elementos pedidos.

//Ejercicio 10 de la Guia
/*
Implementar en C una primitiva void lista_invertir(lista_t* lista) que invierta la lista recibida por parámetro, sin utilizar estructuras auxiliares. 
Indicar y justificar el orden de la primitiva.
*/
void lista_invertir(lista_t* lista) {
	nodo_t* nodo_auxiliar = lista->prim;
	nodo_t* nodo_actual = lista->ult;
	
	for (size_t i = 1; i < lista->largo; i++) {   //O(n) siendo n la cantidad de nodos enlistados.
		for (size_t j = 1; j < lista->largo - i; j++) {  //O(n - k) k tiende a n.
			nodo_auxiliar = nodo_auxiliar->prox;
		}
		nodo_actual->prox = nodo_auxiliar;
		nodo_actual = nodo_auxiliar;
		nodo_auxiliar = lista->prim;
	}
	
	lista->prim->prox = NULL;
	lista->prim = lista->ult;
	lista->ult = nodo_auxiliar;
}
//La complejidad temporal del algoritmo es O(n^2).

//Ejercicio 11 de la Guia
/*
Se quiere implementar un TDA ColaAcotada sobre un arreglo. Dicho TDA tiene un espacio para k elementos (que se recibe por parámetro al crear la estructura). 
Explicar cómo deberían implementarse las primitivas encolar y desencolar de tal manera que siempre sean operaciones de tiempo constante.
*/
/*
Mantendria en la estructura del tda dos datos size_t: uno con la posicion del dato inicial y otro con la posicion del ultimo dato.
Al desencolar, sumo 1 a la posicion inicial y para encolar, encolo + 1 desde la posicion del ultimo dato.
*/

//Ejercicio 12 de la Guia
/*
Implementar una función que ordene de manera ascendente una pila de enteros sin conocer su estructura interna y utilizando como estructura auxiliar 
sólo otra pila auxiliar. Por ejemplo, la pila [ 4, 1, 5, 2, 3 ] debe quedar como [ 1, 2, 3, 4, 5 ] (siendo el último elemento el tope de la pila, en ambos casos). 
Indicar y justificar el orden de la función.
*/
void* destruir_pila_auxiliar(pila_t* pila) {
	pila_destruir(pila);
	return NULL;
}

pila_t* invertir_pila(pila_t* pila) {
	void* numero = pila_desapilar(pila);
	pila_t* pila_auxiliar = pila_crear();
	
	if (!pila_auxiliar) {
		return NULL;
	}
	
	while (!pila_esta_vacia(pila)) {
		if (*(int*)pila_ver_tope(pila) < *(int*)numero) {
			if ((!pila_esta_vacia(pila_auxiliar)) && (*(int*)pila_ver_tope(pila) < *(int*)pila_ver_tope(pila_auxiliar))) {
				if (!pila_apilar(pila_auxiliar, numero)) {
					return destruir_pila_auxiliar(pila_auxiliar);
				}
				numero = pila_desapilar(pila);
				while (!pila_esta_vacia(pila_auxiliar)) {
					if (!pila_apilar(pila, pila_desapilar(pila_auxiliar))) {
						return destruir_pila_auxiliar(pila_auxiliar);
					}
				}
			} else {
				if (!pila_apilar(pila_auxiliar, pila_desapilar(pila))) {
					return destruir_pila_auxiliar(pila_auxiliar);
				}
			}
		} else {
			if (!pila_apilar(pila_auxiliar, numero)) {
				return destruir_pila_auxiliar(pila_auxiliar);
			}
			numero = pila_desapilar(pila);
		}
	}
	
	if ((numero != pila_ver_tope(pila_auxiliar)) && (!pila_apilar(pila_auxiliar, numero))) {
		return destruir_pila_auxiliar(pila_auxiliar);
	}
	
	return pila_auxiliar;
}
/*
Para el peor caso, es decir, que la pila ya este ordenada, el algoritmo se comporta como O(n^2), ya que pasa por cada bucle
iterando todos los elementos de una pila hacia la otra.
*/

//Ejercicio 13 de la Guia
/*
Implementar una función void cola_filtrar(cola_t* cola, bool (*filtro)(void*)), 
que elimine los elementos encolados para los cuales la función filtro devuelve false. 
Aquellos elementos que no son eliminados deben permanecer en el mismo orden en el que estaban antes de invocar a la función. 
No es necesario destruir los elementos que sí fueron eliminados. Se pueden utilizar las estructuras auxiliares que se 
consideren necesarias y no está permitido acceder a la estructura interna de la cola (es una función). ¿Cuál es el orden del algoritmo implementado?
*/
bool filtro(void* dato) {
	return (*(int*)dato == 7);
}

void rearmar_cola(cola_t* cola, cola_t* cola_auxiliar) {
	while (!cola_esta_vacia(cola_auxiliar)) {
		if (!cola_encolar(cola, cola_desencolar(cola_auxiliar))) {
			return;
		}
	}
}

void cola_filtrar(cola_t* cola, bool (*filtro)(void*)) {
	cola_t* cola_auxiliar = cola_crear();
	
	if (!cola_auxiliar) {
		return;
	}
	
	while (!cola_esta_vacia(cola)) {
		if (filtro(cola_ver_primero(cola))) {
			if (!cola_encolar(cola_auxiliar, cola_ver_primero(cola))) {
				return cola_destruir(cola_auxiliar, NULL);
			}
		}
		cola_desencolar(cola);
	}
	
	rearmar_cola(cola, cola_auxiliar);
	cola_destruir(cola_auxiliar, NULL);
}
//La complejidad temporal del algoritmo es O(n).

//Ejercicio 14 de la Guia
/*
Sabiendo que la firma del iterador interno de la lista enlazada es:
void lista_iterar(lista_t* lista, bool (*visitar)(void* dato, void* extra), void* extra);
Se tiene una lista en donde todos los elementos son punteros a números enteros. Implementar la función visitar para que calcule la suma de todos los números pares. 
Mostrar, además, una invocación completa a lista_iterar() que haga uso del visitar implementado.
*/
bool sumar_todos(void* dato, void* extra) {
	if ((*(int*)dato % 2) == 0) {
		*(int*)extra = *(int*)extra + *(int*)dato;
	}
	
	return true;
}

void prueba_lista_iterar(lista_t* lista) {
	int total = 0;
	
	lista_iterar(lista, sumar_todos, &total);
}

//Ejercicio 15 de la Guia
/*
Diseñar un TDA PilaConMáximo, que tenga las mismas primitivas de la pila convencional (en este caso, sólo para números), 
y además permita obtener el máximo de la pila. Todas las primitivas deben funcionar en O(1). 
Explicar cómo implementarías el TDA para que cumpla con todas las restricciones.
*/
/*
Lo dejo para preparar el final.
*/

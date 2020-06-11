#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdbool.h>

// Definicion de las estructuras.

struct lista;
typedef struct lista lista_t;

struct lista_iter;
typedef struct lista_iter lista_iter_t;

// Primitivas de la lista.

// Crea una lista.
// Post: devuelve una nueva lista vacia. 
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos enlazados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agrega un nuevo elemento a la lista, el valor se encuentra al inicio de la misma.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agrega un nuevo elemento a la lista, el valor se encuentra al final de la misma.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista y se devuelve su valor, si esta vacia, devuelve NULL.
// Pre: la lista fue creada.
// Post: la lista contiene un elemento menos, si es que la lista no estaba vacia.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si esta vacia devuelve NULL.
// Pre: la lista fue creada.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si esta vacia devuelve NULL.
// Pre: la lista fue creada.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene la cantidad de elementos enlistados.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la funcion destruir_dato por parametro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada, destruir_dato es una funcion capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Primitivas del iterador interno.

// Recorre cada elemento de la lista, desde el primero hasta el ultimo o hasta el indicado por la funcion visitar  
// y realiza las acciones que se especifiquen en dicha funcion. 
// Pre: la lista fue creada, extra es una variable o NULL segun el caso.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

// Primitivas del interador externo.

// Crea un iterador externo.
// Pre: la lista fue creada.
// Post: devuelve un iterador externo que apunta al primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Devuelve verdadero si el iterador avanzo un elemento, false en caso contrario.
// Pre: el iterador externo fue creado.
// Post: si el iterador no esta al final de la lista, avanza un elemento.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del elemento de la lista al que apunta el iterador. Si la lista tiene
// elementos, se devuelve el valor, si esta vacia devuelve NULL.
// Pre: la lista fue creada.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero si el iterador apunta al final de la lista, false en caso contrario.
// Pre: el iterador externo fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador externo.
// Pre: el iterador externo fue creado.
// Post: el iterador fue destruido.
void lista_iter_destruir(lista_iter_t *iter);

// Devuelve verdadero si se inserta el elemento en la posicion a la que apunta el iterador externo, 
// en caso contrario se devuelve false.
// Pre: el iterador externo fue creado.
// Post: se inserta un nuevo elemento a la lista.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Saca el elemento de la lista al que apunta el iterador, si es que el iterador no esta al final
// de la lista, en ese caso, devuelve NULL.
// Pre: el iterador externo fue creado.
// Post: la lista contiene un elemento menos, si es que el iterador no se encuentra al final de la lista.
void *lista_iter_borrar(lista_iter_t *iter);

#endif

#ifndef TURNOS_H
#define TURNOS_H

/*
Definicion TDA turnos:
TDA que funciona como cola de prioridad, con elementos urgentes y no urgentes.
Los elementos urgentes tienen maxima prioridad y se ordenan por orden de llegada.
Los elementos no urgentes se ordenan mediante la funcion de comparacion definida por el usuario del TDA. 
*/

#include <stdbool.h>
#include <stddef.h>

/* 
Prototipo de funcion de comparacion que se le pasa como parametro a las
diversas funciones.
Debe recibir dos punteros del tipo de dato utilizado, y
debe devolver:
menor a 0  si  a < b
0      si  a == b
mayor a 0  si  a > b
*/
typedef int (*cmp_fun_t) (const void *a, const void *b);

//Tipo utilizado para TDA turnos.
typedef struct turnos turnos_t;

/*
Crea un TDA turnos. Recibe como unico parametro la funcion de comparacion a
utilizar. Devuelve un puntero a turnos, el cual debe ser destruido con turnos_destruir().
*/
turnos_t* turnos_crear(cmp_fun_t cmp);

/*
Elimina el TDA turnos, llamando a la funcion dada para cada elemento del mismo.
El puntero a la funcion puede ser NULL, en cuyo caso no se llamara.
Post: se llama a la funcion indicada con cada elemento del TDA. El mismo deja de ser valido.
*/
void turnos_destruir(turnos_t* turnos, void destruir_dato(void*));

/*
Agrega un elemento al TDA turnos. El elemento no puede ser NULL.
Se recibe un parametro que indica true si el elemento es prioritario o false en caso contrario.
Devuelve true si fue una operacion exitosa, o false en caso de error.
Pre: el TDA turnos fue creado.
Post: se agrega un nuevo elemento al TDA turnos.
*/
bool turnos_encolar(turnos_t* turnos, void *elem, bool es_prioritario);

/*
Elimina el elemento con maxima prioridad, y lo devuelve.
Si el TDA turnos esta vacio, devuelve NULL.
Pre: el TDA turnos fue creado.
Post: el elemento desencolado ya no se encuentra en la estructura.
*/
void *turnos_desencolar(turnos_t *turnos);

/*
Devuelve el elemento con maxima prioridad. Si el TDA turnos esta vacio, devuelve NULL.
Pre: el TDA turnos fue creado.
*/
void *turnos_ver_mas_prioritario(const turnos_t *turnos);

//Devuelve la cantidad de elementos que hay en el TDA turnos.
size_t turnos_cantidad(const turnos_t *turnos);

//Devuelve true si la cantidad de elementos que hay en el TDA turnos es 0, false en caso contrario.
bool turnos_esta_vacio(const turnos_t *turnos);

#endif // TURNOS_H

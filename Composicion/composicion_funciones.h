#ifndef __COMP_H_
#define __COMP_H_

#include <stdbool.h>

//Estructura del tipo de dato 
typedef struct composicion composicion_t;

// Definicion abstracta de la funcion.
typedef double (*funcion_t) (double);

/* 
Crea una composicion de funciones.
Retorna un puntero a la estructura, en caso que algo falle, retorna un puntero nulo.
*/
composicion_t* composicion_crear();

/*
Destruye la composicion de funciones.
*/
void composicion_destruir(composicion_t* composicion);

/*
Agrega a la composicion de funciones la funcion que se recibe por parametro.
Retorna true si se puedo agregar la funcion, en caso contrario, retorna false.
*/
bool composicion_agregar_funcion(composicion_t* composicion, double (*f)(double));

/*
Aplica la composicion de funciones, tomando como valor de la variable, el numero recibido por parametro.
Se aplican las funciones desde la ultima hasta la primera que se fueron agregando.
Retorna el resultado de aplicar las funciones.
*/
double composicion_aplicar(composicion_t* composicion, double valor);

#endif

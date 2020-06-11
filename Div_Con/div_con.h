#ifndef DIV_CON_H
#define DIV_CON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* 
Recibe un arreglo de n enteros (ordenado de forma ascendente y sin numeros repetidos)
y retorna true si el arreglo es magico o retorna false en el caso contrario. 
Un arreglo es magico si, en al menos una posicion, coincide el numero del dato con el de la posicion.
*/
bool es_arreglo_magico(int arreglo[], int n);

/* 
Determina si un elemento se encuentra en un arreglo desordenado. 
Retorna true si el elemento existe y false en caso contrario.
*/
bool elemento_existe(int arreglo[], int n, int dato);

/* 
Recibe un arreglo de n enteros (ordenados de forma descendente unicamente con unos y ceros)
y retorna la posicion del primer cero, de no haber ningun cero, la funcion retorna -1.
*/
int buscar_primer_cero(int arreglo[], int n);

/* 
Recibe un numero natural y retorna la raiz cuadrada natural correspondiente.
*/
int calcular_raiz_cuadrada(int radicando);

/*
Recibe un arreglo de n enteros y verifica si esta ordenado de forma ascendente.
Retorna true si es asi y false en caso contrario.
*/
bool arreglo_orden_ascendente(int arreglo[], int n);

/*
Devuelve la posicion del menor elemento del arreglo, o -1 si el
el vector es de largo 0.
*/
int minimo(int arreglo[], int n);

/*
Recibe un arreglo y su tamaño, con casi todos los elementos ordenados de forma ascendente excepto uno.
Retorna la posicion del elemento desordenado o retorna -1 si el arreglo tiene un solo elemento.
*/
int elemento_desordenado(int arreglo[], int n);

/*
pos: arreglo en forma de pico.
Recibe una posicion inicial, una final y un arreglo ordenado en forma de pico, es decir, 
creciente hasta cierta posicion (el pico) y luego decreciente.
Retorna la posicion del pico.
*/
size_t posicion_pico(int v[], size_t ini, size_t fin);

/*
Recibe el valor n de una moneda en bytelandés 
y devuelve la cantidad máxima de pesos argentinos que se podría obtener realizando los intercambios.
*/
size_t intercambiar_bytelandes_por_pesos(size_t bytelandes);

/*
Dado un arreglo de n números enteros 
devuelve true o false según si existe algún elemento que aparezca más de la mitad de las veces.
*/
bool elemento_se_repite_mas_de_la_mitad(int arreglo[], size_t n);

#endif // DIV_CON_H

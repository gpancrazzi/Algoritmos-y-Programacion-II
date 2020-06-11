#ifndef SORT_H
#define SORT_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/* 
Recibe un arreglo de n enteros
y ordena el arreglo con los elementos ubicados de forma ascendente. 
*/
void merge_sort(int arreglo[], int n);

/*
Recibe un arreglo de n enteros, un rango acotado de valores
y ordena el arreglo con los elementos ubicados de forma ascendente.
Retorna un nuevo arreglo ordenaado. 
*/
int* counting_sort(int arreglo[], size_t n, size_t minimo, size_t maximo, int cifra_significativa(int dato));

/* 
Recibe un arreglo de n enteros
y ordena el arreglo con los elementos ubicados de forma ascendente. 
*/
void seleccion_sort(int vector[], int n);

/*
*/
int* radix_sort(int arreglo[], size_t n);

/*
*/
void quick_sort(int vector[], int inicio, int fin);

/*
*/
void bucket_sort(double arreglo[], int n);

#endif // SORT_H

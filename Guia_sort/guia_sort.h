#ifndef GUIA_SORT_H
#define GUIA_SORT_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char** counting_sort(char** arreglo, size_t n, size_t minimo, size_t maximo, size_t cifra_significativa(char* dato, int posicion), int posicion);

char** radix_sort(char** arreglo, size_t n);

#endif // GUIA_SORT_H

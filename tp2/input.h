#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

/*
Recibe la cantidad de argumentos validos a recibir y los recibidos efectivamente.
Retorna true si las cantidades coinciden o false en caso contrario.
*/
bool validar_cantidad_de_parametros(int cant_valida, int cant_arg);

/*
Recibe una cadena de texto y un puntero a su largo.
Retorna una cadena que elimina del final de la cadena los caracteres de salto de linea y de espacio. 
Se actualiza el largo teniendo en cuenta los caracteres eliminados.
En caso de falla, se retorna NULL.
Pos: se crea una cadena de texto en memoria dinamica.
*/
char* obtener_cadena_limpia(char* str, size_t* n);

/*
Pre: se recibe una cadena que representa una operacion matematica en notacion infija con dicha expresion bien formada 
(paréntesis balanceados, espaciado conforme a norma, numeros enteros positivos y operadores de suma, resta, multiplicacion, division, potencia o parentesis).
Recibe una cadena de texto, su largo y un puntero a un booleano.
Retorna una cadena de texto con espacios entre numeros y operadores. Si no hay necesidad de agregar espacios o en caso de falla, se retorna NULL.
Si se se necesitan agregar espacios en la cadena original se modifica a true el booleano, en caso contrario, se modifica a false.
Pos: se crea una cadena de texto en memoria dinamica.
*/
char* obtener_cadena_espaciada(char* str, size_t n, bool* str_se_modifica);

/*
Se recibe una cadena de texto y su largo.
Pos: se elimina el caracter de salto de linea.
*/
void eliminar_fin_linea(char* linea, size_t len);

/*
Recibe una cadena de texto por parametro.
Retorna true si se trata de un numero o false en caso contrario.
*/
bool validar_numero(char* elem);

/*
Recibe una cadena de texto, un puntero a una posicion, la cantidad de operadores validos y un arreglo de cadenas con la representacion de los operadores.
Retorna true si el elemento se corresponde con un operador valido, ademas se actualiza el puntero con la posicion correspondiente.
En caso que el elemento no se corresponda con un operador valido se retorna false.
*/
bool validar_operador(char* elem, int* op, int cant_operadores, char** operv);

/*
*/
bool validar_cantidad_de_cadenas(char** cadenas, size_t n);

/*
*/
bool csv_crear_estructura(FILE* archivo, char separador, bool creador(char**, void*), void* extra);

#endif  // INPUT_H

#define _POSIX_C_SOURCE 200809L
#include "input.h"
#include "strutil.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

//Funcion que calcula cuantos espacios faltan agregar a la cadena.
size_t calcular_cantidad_espacios(char *str, size_t largo) {
	size_t cantidad = 0;
	
	for (size_t i = 0; i < largo; i++) {
		if (((isdigit(str[i]) == 0) && (str[i] != ' ') && (str[i + 1] != ' ')) || 
		((isdigit(str[i]) != 0) && (str[i + 1] != ' ') && (isdigit(str[i + 1]) == 0))) {
			cantidad++;
		}
	}
	
	return cantidad;
}

//Funcion que determina en que posiciones deberia ir cada espacio a agregar.
void obtener_posiciones_espacio(char *str, size_t largo, size_t posv[]) {
	size_t pos = 0;
	
	for (size_t i = 0; i < largo; i++) {
		if (((isdigit(str[i]) == 0) && (str[i] != ' ') && (str[i + 1] != ' ')) || 
		((isdigit(str[i]) != 0) && (str[i + 1] != ' ') && (isdigit(str[i + 1]) == 0))) {
		    posv[pos] = i + pos + 1;
			pos++;
		}
	}
}

/* ******************************************************************
 *                        FUNCIONES INPUT
 * *****************************************************************/

bool validar_cantidad_de_parametros(int cant_valida, int cant_arg) {
	return cant_arg == cant_valida;
}

char* obtener_cadena_limpia(char* str, size_t* n) {
	size_t i = *n - 1;
	
	while ((i > 0) && ((str[i] == ' ') || (str[i] == '\r') || (str[i] == '\n') || (str[i] == '\0'))) {
		i--;
	}
	
	size_t largo = *n - (*n - (i + 1));
	char* str_aux = substr(str, largo);
	if (!str_aux) {
		return NULL;
	}

	*n = largo;
	return str_aux;
}

char* obtener_cadena_espaciada(char* str, size_t n, bool* str_se_modifica) {
	size_t cant_espacios = calcular_cantidad_espacios(str, n - 1);
	*str_se_modifica = false;
	
	if (cant_espacios > 0) {
		*str_se_modifica = true;
		size_t posv[cant_espacios];
		obtener_posiciones_espacio(str, n - 1, posv);
		char* str_aux = malloc(sizeof(char) * (cant_espacios + n + 1));
		if (!str_aux) {
			return NULL;
		}
		size_t pos = 0, j = 0;
		for (size_t i = 0; i < (n + cant_espacios + 1); i++) {
			if ((pos < (cant_espacios)) && (i == posv[pos])) {
				str_aux[posv[pos]] = ' ';
				pos++;
			} else {
				str_aux[i] = str[j];
				j++;
			}
		}
		str_aux[cant_espacios + n] = '\0';
		return str_aux;
	}
	
	return NULL;
}

void eliminar_fin_linea(char* linea, size_t len) {
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
	if (linea[len - 2] == '\r') {
		linea[len - 2] = '\0';
	}
}

bool validar_numero(char* elem) {
	size_t inicio = 0, largo = strlen(elem);
	
	if ((elem[inicio] == '-') && (largo > 1)) {
		inicio++;
	}
	
	for (size_t i = inicio; i < largo; i++) {
		if (isdigit(elem[i]) == 0) {
			return false;
		}
	}
	
	return true;
}

bool validar_operador(char* elem, int* op, int cant_operadores, char** operv) {
	for (int i = 0; i < cant_operadores; i++) {
		if (strcmp(elem, operv[i]) == 0) {
			*op = i;
			return true;
		}
	}
	
	return false;
}

bool validar_cantidad_de_cadenas(char** cadenas, size_t n) {
	if (!cadenas) return false;
	
	size_t i = 0;
	while (cadenas[i]) {
		if (i == n) return false;
		i++;
	}
	
	return i == n;
}

bool csv_crear_estructura(FILE* archivo, bool creador(char**, void*), void* extra) {
	char* linea = NULL;
	size_t c = 0;
	
	rewind(archivo);
	ssize_t len = 0;
	while (len != -1) {
		len = getline(&linea, &c, archivo);
		if (len != -1) {
			eliminar_fin_linea(linea, len);
			char** campos = split(linea, ',');
			if (!campos) {
				free(linea);
				return false;
			}
			if (!creador(campos, extra)) {
				free(linea);
				free_strv(campos);
				return false;
			}
			creador(campos, extra);
			free_strv(campos);
		}
	}
	
	free(linea);
	return true;
}

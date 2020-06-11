#include "strutil.h"
#include <stdlib.h>
#include <string.h>

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

size_t contar_separadores(const char *str, char sep) {
	size_t i = 0, cantidad = 0;
	
	while (str[i] != '\0') {
		if (str[i] == sep) {
			cantidad++;
		}
		i++;
	}
	
	return cantidad + 2;
}

void obtener_posiciones_del_separador(const char *str, char sep, size_t posv[]) {
	size_t pos = 0, i = 0;
	
	while (str[i] != '\0') {
		if (str[i] == sep) {
			posv[pos] = i;
			pos++;
		}
		i++;
	}
	
	posv[pos] = i;
}

size_t cantidad_de_cadenas(char **strv) {
	size_t contador = 0;
	
	while (strv[contador]) {
		contador++;
	}
	
	return contador;
}

size_t calcular_largo_de_cadenas(char **strv, size_t posv[], char sep, size_t contador) {
	size_t largo = 0;
	
	for (size_t i = 0; i < contador; i++) {
		largo += strlen(strv[i]);
		if (sep != '\0') {
			posv[i] = largo + i;
		} else {
			posv[i] = largo;
		}
	}
	
	if (sep != '\0') {
		largo += contador;
	} else {
		largo++;
	}
	
	return largo;
}

/* ******************************************************************
 *                        FUNCIONES STRUTIL
 * *****************************************************************/

char *substr(const char *str, size_t n) {
	char* sub_str = malloc((n + 1) * sizeof(char));
	
	if (!sub_str) {
		return NULL;
	}
	
	size_t i = 0;
	while ((i < n) && (str[i] != '\0')) {
		sub_str[i] = str[i];
		i++;
	}
	
	sub_str[i] = '\0';
	return sub_str;
}

char **split(const char *str, char sep) {
	size_t cant_sep = contar_separadores(str, sep);
	size_t posv[cant_sep - 1];
	obtener_posiciones_del_separador(str, sep, posv);
	char** strv = malloc(cant_sep * sizeof(char*));
	
	if (!strv) {
		return NULL;
	}
	
	strv[cant_sep - 1] = NULL;
	size_t pos_ant = 0;
	for (size_t i = 0; i < (cant_sep - 1); i++) {
		strv[i] = substr(str + pos_ant, posv[i] - pos_ant);
		if (!strv[i]) {
			free_strv(strv);
			return NULL;
		}
		pos_ant = posv[i] + 1;
	}
	
	return strv;
}

char *join(char **strv, char sep) {
	if ((!strv) || (!strv[0])) {
		return calloc(1, sizeof(char));
	}
	
	size_t contador = cantidad_de_cadenas(strv);
	size_t posv[contador];
	size_t largo = calcular_largo_de_cadenas(strv, posv, sep, contador);
	char* str = malloc(largo * sizeof(char));
	if (!str) {
		return NULL;
	}
	
	strcpy(str, strv[0]);
	str[largo - 1] = '\0';
	size_t pos = 0;
	for (size_t i = 1; i < contador; i++) {
		if (sep != '\0') {
			str[posv[i - 1]] = sep;
			pos = posv[i - 1] + 1;
		} else {
			pos = posv[i - 1];
		}
		strcpy(str + pos, strv[i]);
	}
	
	return str;
}

void free_strv(char *strv[]) {
	size_t i = 0;
	
	while (strv[i]) {
		free(strv[i]);
		i++;
	}
	
	free(strv);
}

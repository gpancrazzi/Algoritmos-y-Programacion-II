#include "strutil.h"
#include <stdlib.h>
#include <string.h>

#define CARAC_FIN '\0'
#define POS_INI 0

char *substr(const char *str, size_t n) {
	char* sub_str = malloc((n + 1) * sizeof(char));
	
	if (sub_str == NULL) {
		return NULL;
	}
	
	size_t i = POS_INI;
	while ((i < n) && (str[i] != CARAC_FIN)) {
		sub_str[i] = str[i];
		i++;
	}
	sub_str[i] = CARAC_FIN;
	return sub_str;
}

size_t contar_separadores(const char *str, char sep) {
	size_t i = POS_INI, cantidad = 0;
	
	while (str[i] != CARAC_FIN) {
		if (str[i] == sep) {
			cantidad++;
		}
		i++;
	}
	return cantidad + 2;
}

void obtener_posiciones_del_separador(const char *str, char sep, size_t posv[]) {
	size_t pos = POS_INI, i = POS_INI;
	
	while (str[i] != CARAC_FIN) {
		if (str[i] == sep) {
			posv[pos] = i;
			pos++;
		}
		i++;
	}
	posv[pos] = i;
}

char **split(const char *str, char sep) {
	size_t cant_sep = contar_separadores(str, sep);
	size_t posv[cant_sep - 1];
	obtener_posiciones_del_separador(str, sep, posv);
	char** strv = malloc(cant_sep * sizeof(char*));
	
	if (strv == NULL) {
		return NULL;
	}
	
	strv[cant_sep - 1] = NULL;
	size_t pos_ant = 0;
	for (size_t i = POS_INI; i < (cant_sep - 1); i++) {
		strv[i] = substr(str + pos_ant, posv[i] - pos_ant);
		if (strv[i] == NULL) {
			free_strv(strv);
			return NULL;
		}
		pos_ant = posv[i] + 1;
	}
	return strv;
}

char *join(char **strv, char sep) {
	if ((strv == NULL) || (strv[POS_INI] == NULL)) {
		return calloc(1, sizeof(char));
	}
	
	size_t contador = 0;
	while (strv[contador] != NULL) {
		contador++;
	}
	
	size_t posv[contador];
	size_t largo = 0, i;
	for (i = POS_INI; i < contador; i++) {
		largo += strlen(strv[i]);
		if (sep != CARAC_FIN) {
			posv[i] = largo + i;
		} else {
			posv[i] = largo;
		}
	}
	
	if (sep != CARAC_FIN) {
		largo += contador;
	} else {
		largo++;
	}
	
    char* str = malloc(largo * sizeof(char));
	if (str == NULL) {
		return NULL;
	}
	
	strcpy(str, strv[POS_INI]);
	str[largo - 1] = CARAC_FIN;
	size_t pos;
	for (i = 1; i < contador; i++) {
		if (sep != CARAC_FIN) {
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
	size_t i = POS_INI;
	
	while (strv[i] != NULL) {
		free(strv[i]);
		i++;
	}
	free(strv);
}

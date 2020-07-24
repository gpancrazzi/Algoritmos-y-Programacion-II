#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "csv.h"
#include "input.h"
#define SEPARADOR ','

bool csv_crear_estructura(FILE* archivo, bool* (*creador) (char**, void*), void* extra) {
	char* linea = NULL;
	size_t c = 0;
	
	rewind(archivo);
	ssize_t len = 0;
	while (len != -1) {
		len = getline(&linea, &c, archivo);
		if (len != -1) {
			eliminar_fin_linea(linea, len);
			char** campos = split(linea, SEPARADOR);
			if (!campos) {
				free(linea);
				fclose(archivo);
				return false;
			}
			if (!creador(campos, extra)) {
				free(linea);
				free_strv(campos);
				fclose(archivo);
				return false;
			}
			creador(campos, extra);
			free_strv(campos);
		}
	}
	
	free(linea);
	fclose(archivo);
	return true;
}

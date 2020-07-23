#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include "cola.h"
#include "heap.h"
#include "hash.h"
#include "strutil.h"
#include "mensajes.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"
#define ARGUMENTOS_VALIDOS 2

void procesar_comando(const char* comando, const char** parametros) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {

	} else if (strcmp(comando, COMANDO_INFORME) == 0) {

	} else {

	}
}

void procesar_entrada() {
	char* linea = NULL;
	size_t c = 0;
	ssize_t len = 0;
	
	while (len != -1) {
		len = getline(&linea, &c, stdin);
		if (len != -1) {
			eliminar_fin_linea(linea, len);
			char** campos = split(linea, ':');
			if (!campos[1]) {
				printf(ENOENT_FORMATO, linea);
				free_strv(campos);
				continue;
			}
			char** parametros = split(campos[1], ',');
			procesar_comando(campos[0], parametros);
			free_strv(parametros);
			free_strv(campos);
		}
	}
	
	free(linea);
}



int main(int argc, char** argv) {
	return 0;
}

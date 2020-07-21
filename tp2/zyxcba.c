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

void procesar_comando(const char* comando, const char** parametros) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {

	} else if (strcmp(comando, COMANDO_INFORME) == 0) {

	} else {

	}
}

void eliminar_fin_linea(char* linea, size_t len) {
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
	if (linea[len - 2] == '\r') {
		linea[len - 2] = '\0';
	}
}

void procesar_entrada() {
	cola_t* urgencias = cola_crear();
	if (!urgencias) return;
	
	hash_t* especialidades = hash_crear(NULL);
	if (!especialidades) {
		cola_destruir(urgencias, NULL);
		return;
	}
	
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
	cola_destruir(urgencias, free);
	hash_destruir(especialidades);
}



int main(int argc, char** argv) {
	return 0;
}

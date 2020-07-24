#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "abb.h"
#include "hash.h"
#include "strutil.h"
#include "mensajes.h"
#include "input.h"
#include "turnos.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"
#define ARGUMENTOS_VALIDOS 2
#define SEPARADOR ','
#define SEPARADOR_COMANDO ':'

void procesar_comando(const char* comando, const char** parametros) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {

	} else if (strcmp(comando, COMANDO_INFORME) == 0) {

	} else {

	}
}

void procesar_entrada(hash_t* pacientes, hash_t* especialidades, abb_t* doctores) {
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

/* ******************************************************************
 *      FUNCIONES PARA PROCESAR LOS ARCHIVOS DE ENTRADA
 * *****************************************************************/

bool validar_cantidad_campos(char** campos) {
	if (!campos) return false;
	
	size_t i = 0;
	while (campos[i]) {
		if (i == 2) return false;
		i++;
	}
	
	return i == 2;
}

bool identificar_archivos(char** campos1, char** campos2, FILE* archivo1, FILE* archivo2, FILE** pacientes, FILE** doctores) {
	if (validar_numero(campos1[1])) {
		*pacientes = archivo1;
		*doctores = archivo2;
		return true;
	}
	
	if (validar_numero(campos2[1])) {
		*pacientes = archivo2;
		*doctores = archivo1;
		return true;
	}
	
	return false;
}

bool validar_archivos(char** argumentos, FILE** pacientes, FILE** doctores) {
	FILE* archivo1 = fopen(argumentos[0], "r");
	if (!archivo1) return false;
	
	FILE* archivo2 = fopen(argumentos[1], "r");
	if (!archivo2) {
		fclose(archivo1);
		return false;
	}
	
	rewind(archivo1);
	rewind(archivo2);
	char* linea1 = NULL;
	char* linea2 = NULL;
	size_t tam = 0;
	ssize len1 = getline(&linea1, &tam, archivo1);
	ssize len2 = getline(&linea2, &tam, archivo2);
	if ((len1 != -1) && (len2 != -1)) {
		eliminar_fin_linea(linea1, len1);
		eliminar_fin_linea(linea2, len2);
		char** campos1 = split(linea1, SEPARADOR);
		char** campos2 = split(linea2, SEPARADOR);
		if ((validar_cantidad_campos(campos1)) && (validar_cantidad_campos(campos2))) {
			if (identificar_archivos(campos1, campos2, archivo1, archivo2, pacientes, doctores)) {
				free_strv(campos1);
				free_strv(campos2);
				return true;
			}
		}
	}
	
	fclose(archivo1);
	fclose(archivo2);
	free_strv(campos1);
	free_strv(campos2);
	return false;
}

bool validar_campo_numerico(char* campo) {
	
}

bool crear_estructura_pacientes(char** campos, void* estructura) {
	
}

bool crear_estructura_doctores(char** campos, void* estructura) {
	
}

int zyxcba(int cantidad_argumentos, char** argumentos) {
	if (!validar_cantidad_de_parametros(ARGUMENTOS_VALIDOS, cantidad_argumentos)) {
		fprintf(stdout, ENOENT_CANT_PARAMS);
		return 1;
	}
	
	FILE* paciente = NULL;
	FILE* doctor = NULL;
	if (!validar_archivos(argumentos, &paciente, &doctor)) {
		fprintf(stdout, ENOENT_ARCHIVO);
		return 1;
	}
	
	hash_t* pacientes = hash_crear(free);
	if (!pacientes) {
		fclose(paciente);
		fclose(doctor);
		fprintf(stdout, ENOENT_ARCHIVO);
		return 1;
	}
	
	hash_t* especialidades = hash_crear(turnos_destruir);
	if (!especialidades) {
		hash_destruir(pacientes);
		fclose(paciente);
		fclose(doctor);
		fprintf(stdout, ENOENT_ARCHIVO);
		return 1;
	}
	
	abb_t* doctores = abb_crear(strcmp, NULL); //Modificar el NULL por una funcion de destruccion del struct.
	if (!doctores) {
		hash_destruir(especialidades);
		hash_destruir(pacientes);
		fclose(paciente);
		fclose(doctor);
		fprintf(stdout, ENOENT_ARCHIVO);
		return 1;
	}
	
	if ((!csv_crear_estructura(paciente, crear_estructura_pacientes)) || (!csv_crear_estructura(doctor, crear_estructura_doctores))) {
		hash_destruir(especialidades);
		hash_destruir(pacientes);
		abb_destruir(doctores);
		fclose(paciente);
		fclose(doctor);
		fprintf(stdout, ENOENT_ARCHIVO);
		return 1;
	}
	
	procesar_entrada(pacientes, especialidades, doctores);
	return 0;
}

/* ******************************************************************
 *                   FUNCION PRINCIPAL 
 * *****************************************************************/

int main(int argc, char** argv) {
	return zyxcba(argc, argv);
}

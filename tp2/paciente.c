#define _POSIX_C_SOURCE 200809L
#include "paciente.h"
#include <string.h>
#include <stdlib.h>

/* ******************************************************************
 *                   ESTRUCTURA DE PACIENTE
 * *****************************************************************/

struct paciente {
	char* nombre;
	char* anio_inscripcion;
};

/* ******************************************************************
 *                   FUNCIONES PARA PACIENTE
 * *****************************************************************/

paciente_t* paciente_crear(char* nombre, char* anio_inscripcion) {
	paciente_t* paciente = malloc(sizeof(paciente_t));
	
	if (!paciente) return NULL;
	paciente->nombre = strdup(nombre);
	if (!paciente->nombre) {
		free(paciente);
		return NULL;
	}
	
	paciente->anio_inscripcion = strdup(anio_inscripcion);
	if (!paciente->anio_inscripcion) {
		free(paciente->nombre);
		free(paciente);
		return NULL;
	}
	
	return paciente;
}

char* paciente_ver_nombre(paciente_t* paciente) {
	return paciente->nombre;
}

char* paciente_ver_anio(paciente_t* paciente) {
	return paciente->anio_inscripcion;
}

void paciente_destruir(paciente_t* paciente) {
	free(paciente->nombre);
	free(paciente->anio_inscripcion);
	free(paciente);
}

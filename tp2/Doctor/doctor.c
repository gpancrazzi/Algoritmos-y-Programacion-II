#define _POSIX_C_SOURCE 200809L
#include "paciente.h"
#include "doctor.h"
#include <string.h>
#include <stdlib.h>

/* ******************************************************************
 *                   ESTRUCTURA DE DOCTOR
 * *****************************************************************/

struct doctor {
	char* nombre;
	char* especialidad;
	size_t pacientes_atendidos;
};

/* ******************************************************************
 *                   FUNCIONES PARA DOCTOR
 * *****************************************************************/

doctor_t* doctor_crear(char* nombre, char* especialidad) {
	doctor_t* doctor = malloc(sizeof(doctor_t));
	
	if (!doctor) return NULL;
	doctor->nombre = strdup(nombre);
	if (!doctor->nombre) {
		free(doctor);
		return NULL;
	}
	
	doctor->especialidad = strdup(especialidad);
	if (!doctor->especialidad) {
		free(doctor->nombre);
		free(doctor);
		return NULL;
	}
	
	doctor->pacientes_atendidos = 0;
	return doctor;
}

const char* doctor_ver_nombre(doctor_t* doctor) {
	return doctor->nombre;
}

const char* doctor_ver_especialidad(doctor_t* doctor) {
	return doctor->especialidad;
}

size_t doctor_atendidos(doctor_t* doctor) {
	return doctor->pacientes_atendidos;
}

void doctor_atender_paciente(doctor_t* doctor, paciente_t* paciente) {
	doctor->pacientes_atendidos++;
	paciente_destruir(paciente);
}

void doctor_destruir(doctor_t* doctor) {
	free(doctor->nombre);
	free(doctor->especialidad);
	free(doctor);
}

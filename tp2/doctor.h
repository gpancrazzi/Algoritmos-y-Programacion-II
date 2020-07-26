#ifndef DOCTOR_H
#define DOCTOR_H

#include <string.h>
#include <stdlib.h>
#include "paciente.h"

struct doctor;

typedef struct doctor doctor_t;

/*
*/
doctor_t* doctor_crear(char* nombre, char* especialidad);

/*
*/
char* doctor_ver_nombre(doctor_t* doctor);

/*
*/
char* doctor_ver_especialidad(doctor_t* doctor);

/*
*/
size_t doctor_atendidos(doctor_t* doctor);

/*
*/
void doctor_atender_paciente(doctor_t* doctor, paciente_t* paciente);

/*
*/
void doctor_destruir(doctor_t* doctor);

#endif // DOCTOR_H

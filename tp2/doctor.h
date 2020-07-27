#ifndef DOCTOR_H
#define DOCTOR_H

#include <string.h>
#include <stdlib.h>
#include "paciente.h"

struct doctor;

typedef struct doctor doctor_t;

/*
Crea un doctor.
Retorna un puntero al doctor. El doctor debe ser destruido con doctor_destruir.
*/
doctor_t* doctor_crear(char* nombre, char* especialidad);

/*
Pre: el doctor fue creado.
Devuelve el nombre del doctor, ese nombre no se puede modificar ni liberar.
*/
const char* doctor_ver_nombre(doctor_t* doctor);

/*
Pre: el doctor fue creado.
Devuelve la especialidad del doctor, esa especialidad no se puede modificar ni liberar.
*/
const char* doctor_ver_especialidad(doctor_t* doctor);

/*
Pre: el doctor fue creado.
Devuelve la cantidad de pacientes atendidos por el doctor.
*/
size_t doctor_atendidos(doctor_t* doctor);

/*
Pre: el doctor y el paciente fueron creados.
Agrega un paciente atendido por el doctor y libera la memoria asociada al paciente.
*/
void doctor_atender_paciente(doctor_t* doctor, paciente_t* paciente);

/*
Destruye el doctor liberando la memoria pedida.
*/
void doctor_destruir(doctor_t* doctor);

#endif // DOCTOR_H

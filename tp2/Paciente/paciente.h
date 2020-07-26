#ifndef PACIENTE_H
#define PACIENTE_H

#include <string.h>
#include <stdlib.h>

struct paciente;

typedef struct paciente paciente_t;

/*
*/
paciente_t* paciente_crear(char* nombre, char* anio_inscripcion);

/*
*/
char* paciente_ver_nombre(paciente_t* paciente);

/*
*/
char* paciente_ver_anio(paciente_t* paciente);

/*
*/
void paciente_destruir(paciente_t* paciente);

#endif // PACIENTE_H

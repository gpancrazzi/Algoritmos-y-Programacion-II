#ifndef PACIENTE_H
#define PACIENTE_H

#include <string.h>
#include <stdlib.h>

struct paciente;

typedef struct paciente paciente_t;

/*
Crea un paciente.
Retorna un puntero al paciente. El paciente debe ser destruido con paciente_destruir.
*/
paciente_t* paciente_crear(char* nombre, char* anio_inscripcion);

/*
Pre: el paciente fue creado.
Devuelve el nombre del paciente, ese nombre no se puede modificar ni liberar.
*/
const char* paciente_ver_nombre(paciente_t* paciente);

/*
Pre: el paciente fue creado.
Devuelve el año de inscripcion del paciente, ese año no se puede modificar ni liberar.
*/
const char* paciente_ver_anio(paciente_t* paciente);

/*
Destruye el paciente liberando la memoria pedida.
*/
void paciente_destruir(paciente_t* paciente);

#endif // PACIENTE_H

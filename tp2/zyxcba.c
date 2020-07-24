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
#define PARAMETROS_PEDIR_TURNO 3
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define PARAMETROS_ATENDER 1
#define COMANDO_INFORME "INFORME"
#define PARAMETROS_INFORME 2
#define ARGUMENTOS_VALIDOS 2
#define SEPARADOR ','
#define SEPARADOR_COMANDO ':'
#define CANTIDAD_CAMPOS 2
#define CANTIDAD_URGENCIAS 2

/* ******************************************************************
 *                   ESTRUCTURAS DE DATOS
 * *****************************************************************/

typedef struct {
	char* nombre;
	char* anio_inscripcion;
} paciente_t;

typedef struct {
	char* nombre;
	char* especialidad;
	size_t pacientes_atendidos;
} doctor_t;

typedef struct {
	hash_t* paciente;
	bool* es_numero;
} estructura_paciente_t;

typedef struct {
	hash_t* especialidades;
	abb_t* doctores;
} estructura_doctor_t;

typedef enum {URGENTE, REGULAR} prioridad_t;

/* ******************************************************************
 *      FUNCIONES PARA VALIDAR Y PROCESAR LOS COMANDOS
 * *****************************************************************/

bool validar_pedir_turno(const char** parametros, hash_t* pacientes, hash_t* especialidades, int* prioridad) {
	bool entrada_valida = true;
	char* grados_de_urgencia[] = {"URGENTE", "REGULAR"};
	
	if (!validar_cantidad_de_cadenas(parametros, PARAMETROS_PEDIR_TURNO)) {
		fprintf(stdout, ENOENT_PARAMS, COMANDO_PEDIR_TURNO);
		return false;
	}
	
	if (!hash_pertenece(pacientes, parametros[0])) {
		entrada_valida = false;
		fprintf(stdout, ENOENT_PACIENTE, parametros[0]);
	}
	
	if (!hash_pertenece(especialidades, parametros[1])) {
		entrada_valida = false;
		fprintf(stdout, ENOENT_ESPECIALIDAD, parametros[1]);
	}
	
	if (!validar_operador(parametros[2], prioridad, CANTIDAD_URGENCIAS, grados_de_urgencia)) {
		entrada_valida = false;
		fprintf(stdout, ENOENT_URGENCIA, parametros[2]);
	}
	
	return entrada_valida;
}

paciente_t* crear_paciente(char* nombre, char* anio_inscripcion) {
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

void procesar_pedir_turno(const char** parametros, hash_t* pacientes, hash_t* especialidades, int prioridad) {
	bool es_urgente = true;
	
	if (prioridad == REGULAR) {
		es_urgente = false;
	}
	
	paciente_t* paciente_auxiliar = hash_obtener(pacientes, parametros[0]);
	paciente_t* paciente = crear_paciente(paciente_auxiliar->nombre, paciente_auxiliar->anio_inscripcion);
	if (!paciente) return;
	turnos_t* turnos = hash_obtener(especialidades, parametros[1]);
	if (!turnos_encolar(turnos, paciente, es_urgente)) {
		destruir_paciente(paciente);
		return;
	}
	
	fprintf(stdout, PACIENTE_ENCOLADO, paciente->nombre);
	fprintf(stdout, CANT_PACIENTES_ENCOLADOS, turnos_cantidad(turnos), parametros[1]);
}

bool validar_atender_paciente(const char** parametros, abb_t* doctores) {
	if (!validar_cantidad_de_cadenas(parametros, PARAMETROS_ATENDER)) {
		fprintf(stdout, ENOENT_PARAMS, COMANDO_ATENDER);
		return false;
	}
	
	if (!abb_pertenece(doctores, parametros[0])) {
		fprintf(stdout, ENOENT_DOCTOR, parametros[0]);
		return false;
	}
	
	return true;
}

void procesar_atender_paciente(const char** parametros, hash_t* especialidades, abb_t* doctores) {
	doctor_t* doctor = abb_obtener(doctores, parametros[0]);
	
	turnos_t* turnos = hash_obtener(especialidades, doctor->especialidad);
	if (turnos_esta_vacio(turnos)) {
		fprintf(stdout, SIN_PACIENTES);
		return;
	}
	
	paciente_t* paciente = turnos_desencolar(turnos);
	fprintf(stdout, PACIENTE_ATENDIDO, paciente->nombre);
	if (turnos_esta_vacio(turnos)) {
		fprintf(stdout, SIN_PACIENTES);
	} else {
		fprintf(stdout, CANT_PACIENTES_ENCOLADOS, turnos_cantidad(turnos), doctor->especialidad);
	}
	
	doctor->pacientes_atendidos++;
	destruir_paciente(paciente);
}

bool validar_informe_doctores(const char** parametros, abb_t* doctores) {
	if (!validar_cantidad_de_cadenas(parametros, PARAMETROS_INFORME)) {
		fprintf(stdout, ENOENT_PARAMS, COMANDO_INFORME);
		return false;
	}
	
	return true;
}

void procesar_informe_doctores(const char** parametros, abb_t* doctores) {
	
}

void procesar_comando(const char* comando, const char** parametros, hash_t* pacientes, hash_t* especialidades, abb_t* doctores) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		int grado_de_prioridad = URGENTE;
		if (!validar_pedir_turno(parametros, pacientes, especialidades, &grado_de_prioridad)) return;
		procesar_pedir_turno(parametros, pacientes, especialidades, grado_de_prioridad);
	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {
		if (!validar_atender_paciente(parametros, doctores)) return;
		procesar_atender_paciente(parametros, especialidades, doctores);
	} else if (strcmp(comando, COMANDO_INFORME) == 0) {
		if (!validar_informe_doctores(parametros, doctores)) return;
		procesar_informe_doctores(parametros, doctores);
	} else {
		fprintf(stdout, ENOENT_CMD, comando);
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
			char** campos = split(linea, SEPARADOR_COMANDO);
			if (!campos[1]) {
				fprintf(stdout, ENOENT_FORMATO, linea);
				free_strv(campos);
				continue;
			}
			char** parametros = split(campos[1], SEPARADOR);
			procesar_comando(campos[0], parametros, pacientes, especialidades, doctores);
			free_strv(parametros);
			free_strv(campos);
		}
	}
	
	free(linea);
}

/* ******************************************************************
 *         FUNCIONES DE COMPARACION Y DESTRUCCION
 * *****************************************************************/

int wrapper_strcmp(const void *a, const void *b) {
	return strcmp((char*)a, (char*)b);
}

void destruir_doctor(void* doctor) {
	doctor_t* doctor_auxiliar = doctor;
	free(doctor_auxiliar->nombre);
	free(doctor_auxiliar->especialidad);
	free(doctor_auxiliar);
}

int comparar_anio(paciente_t* a, paciente_t* b) {
	return strcmp(a->anio_inscripcion, b->anio_inscripcion) * (-1);
}

int wrapper_aniocmp(const void *a, const void *b) {
	return comparar_anio((paciente_t*)a, (paciente_t*)b);
}

void destruir_paciente(void* paciente) {
	paciente_t* paciente_auxiliar = paciente;
	free(paciente_auxiliar->nombre);
	free(paciente_auxiliar->anio_inscripcion);
	free(paciente_auxiliar);
}

/* ******************************************************************
 *      FUNCIONES PARA VALIDAR LOS ARCHIVOS DE ENTRADA
 * *****************************************************************/

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
	if (!archivo1) {
		fprintf(stdout, ENOENT_ARCHIVO, argumentos[0]);
		return false;
	}
	
	FILE* archivo2 = fopen(argumentos[1], "r");
	if (!archivo2) {
		fprintf(stdout, ENOENT_ARCHIVO, argumentos[1]);
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
		if ((validar_cantidad_de_cadenas(campos1, CANTIDAD_CAMPOS)) && (validar_cantidad_de_cadenas(campos2, CANTIDAD_CAMPOS))) {
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

/* ******************************************************************
 *   FUNCIONES PARA VALIDAR Y CREAR LAS ESTRUCTURAS DE DATOS
 * *****************************************************************/

bool crear_estructura_pacientes(char** campos, void* estructura) {
	estructura_paciente_t* estructura_auxiliar = estructura;
	
	if (!validar_numero(campos[1])) {
		fprintf(stdout, ENOENT_ANIO, campos[1]);
		estructura_auxiliar->es_numero = false;
		return false;
	}
	
	paciente_t* paciente = crear_paciente(campos[0], campos[1]);
	if (!paciente) return false;
	
	if (!hash_guardar(estructura_auxiliar->paciente, paciente->nombre, paciente)) {
		destruir_paciente(paciente);
		return false;
	}
	
	return true;
}

doctor_t* crear_doctor(char* nombre, char* especialidad) {
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

bool crear_estructura_doctores(char** campos, void* estructura) {
	estructura_doctor_t* estructura_auxiliar = estructura;
	
	doctor_t* doctor = crear_doctor(campos[0], campos[1]);
	if (!doctor) return false;
	if (!abb_guardar(estructura_auxiliar->doctores, doctor->nombre, doctor)) {
		destruir_doctor(doctor);
		return false;
	}
	
	if (hash_pertenece(estructura_auxiliar->especialidades, doctor->especialidad)) return true;
	turnos_t* turnos = turnos_crear(wrapper_aniocmp, destruir_paciente);
	if (!turnos) return false;
	if (!hash_guardar(estructura_auxiliar->especialidades, doctor->especialidad, turnos)) {
		turnos_destruir(turnos);
		return false;
	}
	
	return true;
}

/* ******************************************************************
 *                   FUNCIONES PRINCIPALES
 * *****************************************************************/

int zyxcba(int cantidad_argumentos, char** argumentos) {
	if (!validar_cantidad_de_parametros(ARGUMENTOS_VALIDOS, cantidad_argumentos)) {
		fprintf(stdout, ENOENT_CANT_PARAMS);
		return 1;
	}
	
	FILE* archivo_paciente = NULL;
	FILE* archivo_doctor = NULL;
	if (!validar_archivos(argumentos, &archivo_paciente, &archivo_doctor)) {
		return 1;
	}
	
	hash_t* pacientes = hash_crear(destruir_paciente);
	if (!pacientes) {
		fclose(archivo_paciente);
		fclose(archivo_doctor);
		return 0;
	}
	
	hash_t* especialidades = hash_crear(turnos_destruir);
	if (!especialidades) {
		hash_destruir(pacientes);
		fclose(archivo_paciente);
		fclose(archivo_doctor);
		return 0;
	}
	
	abb_t* doctores = abb_crear(wrapper_strcmp, destruir_doctor);
	if (!doctores) {
		hash_destruir(especialidades);
		hash_destruir(pacientes);
		fclose(archivo_paciente);
		fclose(archivo_doctor);
		return 0;
	}
	
	estructura_paciente_t* paciente_estructura;
	paciente_estructura->es_numero = true;
	paciente_estructura->paciente = pacientes;
	estructura_doctor_t* doctor_estructura;
	doctor_estructura->doctores = doctores;
	doctor_estructura->especialidades = especialidades;
	if ((!csv_crear_estructura(archivo_paciente, SEPARADOR, crear_estructura_pacientes, paciente_estructura)) || 
	(!csv_crear_estructura(archivo_doctor, SEPARADOR, crear_estructura_doctores, doctor_estructura))) {
		hash_destruir(especialidades);
		hash_destruir(pacientes);
		abb_destruir(doctores);
		fclose(archivo_paciente);
		fclose(archivo_doctor);
		if (paciente_estructura->es_numero) {
			return 0;
		}
		return 1;
	}
	
	fclose(archivo_paciente);
	fclose(archivo_doctor);
	procesar_entrada(pacientes, especialidades, doctores);
	hash_destruir(especialidades);
	hash_destruir(pacientes);
	abb_destruir(doctores);
	return 0;
}

int main(int argc, char** argv) {
	return zyxcba(argc, argv);
}

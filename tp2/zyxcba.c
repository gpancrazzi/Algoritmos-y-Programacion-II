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
#include "paciente.h"
#include "doctor.h"

#define ARGUMENTOS_VALIDOS 3
#define CANTIDAD_CAMPOS 2
#define SEPARADOR_PARAMETROS ','
#define SEPARADOR_COMANDO ':'

/* ******************************************************************
 *      FUNCIONES PARA VALIDAR Y PROCESAR CMD PEDIR TURNO
 * *****************************************************************/

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define PARAMETROS_PEDIR_TURNO 3
#define CANTIDAD_URGENCIAS 2

typedef enum {URGENTE, REGULAR} prioridad_t;

bool validar_pedir_turno(char** parametros, hash_t* pacientes, hash_t* especialidades, int* prioridad) {
	char* grados_de_urgencia[] = {"URGENTE", "REGULAR"};
	
	if (!validar_cantidad_de_cadenas(parametros, PARAMETROS_PEDIR_TURNO)) {
		fprintf(stdout, ENOENT_PARAMS, COMANDO_PEDIR_TURNO);
		return false;
	}
	
	bool entrada_valida = true;
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

void procesar_pedir_turno(char** parametros, hash_t* pacientes, hash_t* especialidades, int prioridad) {
	bool es_urgente = true;
	
	if (prioridad == REGULAR) {
		es_urgente = false;
	}
	
	paciente_t* paciente_auxiliar = hash_obtener(pacientes, parametros[0]);
	paciente_t* paciente = paciente_crear((char*)paciente_ver_nombre(paciente_auxiliar), (char*)paciente_ver_anio(paciente_auxiliar));
	if (!paciente) return;
	turnos_t* turnos = hash_obtener(especialidades, parametros[1]);
	if (!turnos_encolar(turnos, paciente, es_urgente)) {
		paciente_destruir(paciente);
		return;
	}
	
	fprintf(stdout, PACIENTE_ENCOLADO, paciente_ver_nombre(paciente));
	fprintf(stdout, CANT_PACIENTES_ENCOLADOS, turnos_cantidad(turnos), parametros[1]);
}

/* ******************************************************************
 *      FUNCIONES PARA VALIDAR Y PROCESAR CMD ATENDER PACIENTE
 * *****************************************************************/

#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define PARAMETROS_ATENDER 1

bool validar_atender_paciente(char** parametros, abb_t* doctores) {
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

void procesar_atender_paciente(char** parametros, hash_t* especialidades, abb_t* doctores) {
	doctor_t* doctor = abb_obtener(doctores, parametros[0]);
	
	turnos_t* turnos = hash_obtener(especialidades, doctor_ver_especialidad(doctor));
	if (turnos_esta_vacio(turnos)) {
		fprintf(stdout, SIN_PACIENTES);
		return;
	}
	
	paciente_t* paciente = turnos_desencolar(turnos);
	fprintf(stdout, PACIENTE_ATENDIDO, paciente_ver_nombre(paciente));
	fprintf(stdout, CANT_PACIENTES_ENCOLADOS, turnos_cantidad(turnos), doctor_ver_especialidad(doctor));
	doctor_atender_paciente(doctor, paciente);
}

/* ******************************************************************
 *      FUNCIONES PARA VALIDAR Y PROCESAR CMD INFORME DOCTORES
 * *****************************************************************/

#define COMANDO_INFORME "INFORME"
#define PARAMETROS_INFORME 2
#define SIN_RANGO ""

bool validar_informe_doctores(char** parametros) {
	if (!validar_cantidad_de_cadenas(parametros, PARAMETROS_INFORME)) {
		fprintf(stdout, ENOENT_PARAMS, COMANDO_INFORME);
		return false;
	}
	
	return true;
}

bool imprimir_informe(void *dato, void *extra) {
	doctor_t* doctor = dato;
	size_t numero_de_doctor = *(size_t*)extra;
	
	fprintf(stdout, INFORME_DOCTOR, numero_de_doctor, doctor_ver_nombre(doctor), doctor_ver_especialidad(doctor), doctor_atendidos(doctor));
	*(size_t*)extra += 1;
	return true;
}

void procesar_informe_doctores(char** parametros, abb_t* doctores) {
	lista_t* informe = abb_obtener_rango(doctores, parametros[0], parametros[1], SIN_RANGO);
	size_t inicio = 0;
	if (!informe) {
		fprintf(stdout, DOCTORES_SISTEMA, inicio);
		return;
	}
	
	inicio = 1;
	fprintf(stdout, DOCTORES_SISTEMA, lista_largo(informe));
	lista_iterar(informe, imprimir_informe, &inicio);
	lista_destruir(informe, NULL);
}

/* ******************************************************************
 *   FUNCIONES PARA VALIDAR Y PROCESAR LA ENTRADA DE LOS COMANDOS
 * *****************************************************************/

void procesar_comando(const char* comando, char** parametros, hash_t* pacientes, hash_t* especialidades, abb_t* doctores) {
	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
		int grado_de_prioridad = URGENTE;
		if (!validar_pedir_turno(parametros, pacientes, especialidades, &grado_de_prioridad)) return;
		procesar_pedir_turno(parametros, pacientes, especialidades, grado_de_prioridad);
		return;
	} 
	
	if (strcmp(comando, COMANDO_ATENDER) == 0) {
		if (!validar_atender_paciente(parametros, doctores)) return;
		procesar_atender_paciente(parametros, especialidades, doctores);
		return;
	} 
	
	if (strcmp(comando, COMANDO_INFORME) == 0) {
		if (!validar_informe_doctores(parametros)) return;
		procesar_informe_doctores(parametros, doctores);
		return;
	}
	
	fprintf(stdout, ENOENT_CMD, comando);
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
			char** parametros = split(campos[1], SEPARADOR_PARAMETROS);
			procesar_comando(campos[0], parametros, pacientes, especialidades, doctores);
			free_strv(parametros);
			free_strv(campos);
		}
	}
	
	free(linea);
}

/* ******************************************************************
 *      FUNCIONES PARA VALIDAR LOS ARCHIVOS DE ENTRADA
 * *****************************************************************/

void identificar_archivos(char** campos1, char** campos2, FILE* archivo1, FILE* archivo2, FILE** pacientes, FILE** doctores) {
	if (((campos1) && (campos1[0]) && (campos1[1]) && (validar_numero(campos1[1]))) ||
	((campos2) && (campos2[0]) && (campos2[1]) && (!validar_numero(campos2[1])))) {
		*pacientes = archivo1;
		*doctores = archivo2;
	} else if (((campos1) && (campos1[0]) && (campos1[1]) && (!validar_numero(campos1[1]))) ||
	((campos2) && (campos2[0]) && (campos2[1]) && (validar_numero(campos2[1])))) {
		*pacientes = archivo2;
		*doctores = archivo1;
	} else {
		*pacientes = archivo1;
		*doctores = archivo2;
	}
}

bool validar_archivos(char** argumentos, FILE** pacientes, FILE** doctores) {
	FILE* archivo1 = fopen(argumentos[1], "r");
	if (!archivo1) {
		fprintf(stdout, ENOENT_ARCHIVO, argumentos[1]);
		return false;
	}
	
	FILE* archivo2 = fopen(argumentos[2], "r");
	if (!archivo2) {
		fprintf(stdout, ENOENT_ARCHIVO, argumentos[2]);
		fclose(archivo1);
		return false;
	}
	
	rewind(archivo1);
	rewind(archivo2);
	char* linea1 = NULL;
	char* linea2 = NULL;
	char** campos1 = NULL;
	char** campos2 = NULL;
	size_t tam = 0;
	ssize_t len1 = getline(&linea1, &tam, archivo1);
	if (len1 != -1) {
		eliminar_fin_linea(linea1, len1);
		campos1 = split(linea1, ',');
	}
	
	ssize_t len2 = getline(&linea2, &tam, archivo2);
	if (len2 != -1) {
		eliminar_fin_linea(linea2, len2);
		campos2 = split(linea2, ',');
	}
	
	identificar_archivos(campos1, campos2, archivo1, archivo2, pacientes, doctores);
	if (len1 != -1) free_strv(campos1);
	if (len2 != -1) free_strv(campos2);
	free(linea1);
	free(linea2);
	return true;
}

/* ******************************************************************
 *       FUNCIONES ENMASCARADAS PARA COMPARAR Y DESTRUIR
 * *****************************************************************/

int comparar_anio(paciente_t* a, paciente_t* b) {
	return strcmp(paciente_ver_anio(a), paciente_ver_anio(b)) * (-1);
}

int wrapper_aniocmp(const void *a, const void *b) {
	return comparar_anio((paciente_t*)a, (paciente_t*)b);
}

void wrapper_turnos_destruir(void* elem) {
	turnos_t* turnos = elem;
	turnos_destruir(turnos);
}

void wrapper_paciente_destruir(void* elem) {
	paciente_t* paciente = elem;
	paciente_destruir(paciente);
}

void wrapper_doctor_destruir(void* elem) {
	doctor_t* doctor = elem;
	doctor_destruir(doctor);
}

/* **************************************************************************
 * FUNCIONES PARA VALIDAR Y CREAR LAS ESTRUCTURAS DE DATOS DE LOS PACIENTES
 * *************************************************************************/

typedef struct {
	hash_t* paciente;
	bool es_numero;
} estructura_paciente_t;

estructura_paciente_t* crear_estructura_paciente(hash_t* pacientes) {
	estructura_paciente_t* estructura = malloc(sizeof(estructura_paciente_t));
	
	if (!estructura) return NULL;
	estructura->paciente = pacientes;
	estructura->es_numero = true;
	return estructura;
}

bool crear_estructura_pacientes(char** campos, void* estructura) {
	estructura_paciente_t* estructura_auxiliar = estructura;
	
	if (!validar_numero(campos[1])) {
		fprintf(stdout, ENOENT_ANIO, campos[1]);
		estructura_auxiliar->es_numero = false;
		return false;
	}
	
	paciente_t* paciente = paciente_crear(campos[0], campos[1]);
	if (!paciente) return false;
	if (!hash_guardar(estructura_auxiliar->paciente, paciente_ver_nombre(paciente), paciente)) {
		paciente_destruir(paciente);
		return false;
	}
	
	return true;
}

/* *************************************************************************
 * FUNCIONES PARA VALIDAR Y CREAR LAS ESTRUCTURAS DE DATOS DE LOS DOCTORES
 * ************************************************************************/

typedef struct {
	hash_t* especialidades;
	abb_t* doctores;
} estructura_doctor_t;

estructura_doctor_t* crear_estructura_doctor(hash_t* especialidades, abb_t* doctores) {
	estructura_doctor_t* estructura = malloc(sizeof(estructura_doctor_t));
	
	if (!estructura) return NULL;
	estructura->doctores = doctores;
	estructura->especialidades = especialidades;
	return estructura;
}

bool crear_estructura_doctores(char** campos, void* estructura) {
	estructura_doctor_t* estructura_auxiliar = estructura;
	
	doctor_t* doctor = doctor_crear(campos[0], campos[1]);
	if (!doctor) return false;
	if (!abb_guardar(estructura_auxiliar->doctores, doctor_ver_nombre(doctor), doctor)) {
		doctor_destruir(doctor);
		return false;
	}
	
	if (hash_pertenece(estructura_auxiliar->especialidades, doctor_ver_especialidad(doctor))) return true;
	turnos_t* turnos = turnos_crear(wrapper_aniocmp, wrapper_paciente_destruir);
	if (!turnos) return false;
	if (!hash_guardar(estructura_auxiliar->especialidades, doctor_ver_especialidad(doctor), turnos)) {
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
	
	hash_t* pacientes = hash_crear(wrapper_paciente_destruir);
	if (!pacientes) {
		fclose(archivo_paciente);
		fclose(archivo_doctor);
		return 0;
	}
	
	hash_t* especialidades = hash_crear(wrapper_turnos_destruir);
	if (!especialidades) {
		hash_destruir(pacientes);
		fclose(archivo_paciente);
		fclose(archivo_doctor);
		return 0;
	}
	
	abb_t* doctores = abb_crear(strcmp, wrapper_doctor_destruir);
	if (!doctores) {
		hash_destruir(especialidades);
		hash_destruir(pacientes);
		fclose(archivo_paciente);
		fclose(archivo_doctor);
		return 0;
	}
	
	estructura_paciente_t* paciente_estructura = crear_estructura_paciente(pacientes);
	estructura_doctor_t* doctor_estructura = crear_estructura_doctor(especialidades, doctores);
	if ((!paciente_estructura) || (!doctor_estructura) || 
	(!csv_crear_estructura(archivo_paciente, crear_estructura_pacientes, paciente_estructura)) || 
	(!csv_crear_estructura(archivo_doctor, crear_estructura_doctores, doctor_estructura))) {
		hash_destruir(especialidades);
		hash_destruir(pacientes);
		abb_destruir(doctores);
		fclose(archivo_paciente);
		fclose(archivo_doctor);
		if (doctor_estructura) {
			free(doctor_estructura);
		}
		if ((paciente_estructura) && (paciente_estructura->es_numero)) {
			free(paciente_estructura);
			return 0;
		}
		if (paciente_estructura) {
			free(paciente_estructura);
		}
		return 1;
	}
	
	free(paciente_estructura);
	free(doctor_estructura);
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

#define _POSIX_C_SOURCE 200809L
#include "pila.h"
#include "cola.h"
#include "strutil.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CANTIDAD_OPERADORES 7
#define MENSAJE_ERROR "ERROR\n"
#define ARGUMENTOS_VALIDOS 1

typedef enum {suma, resta, multiplicacion, division, potencia, parentesis_izq, parentesis_der} operador_t;

/* ******************************************************************
 *   FUNCION PARA EVALUAR PRECEDENCIA Y ASOCIATIVIDAD DE OPERADORES
 * *****************************************************************/

//Basada en el algoritmo "shunting yard"
bool evaluar_operador(char* elem, pila_t* pila, cola_t* cola) {
	char* strv[] = {"+", "-", "*", "/", "^", "(", ")"};
	int op = suma;
	
	validar_operador(elem, &op, CANTIDAD_OPERADORES, strv);
	switch (op) {
		case suma:
		case resta:
			while ((!pila_esta_vacia(pila)) && (strcmp(pila_ver_tope(pila), "(") != 0)) {
				if (!cola_encolar(cola, pila_desapilar(pila))) {
					return false;
				}
			}
			break;
		case multiplicacion:
		case division:
			while ((!pila_esta_vacia(pila)) && (strcmp(pila_ver_tope(pila), "(") != 0) && 
			(strcmp((char*)pila_ver_tope(pila), "+") != 0) && (strcmp((char*)pila_ver_tope(pila), "-") != 0)) {
				if (!cola_encolar(cola, pila_desapilar(pila))) {
					return false;
				}
			}
			break;
		case parentesis_der:
			while (strcmp(pila_ver_tope(pila), "(") != 0) {
				if (!cola_encolar(cola, pila_desapilar(pila))) {
					return false;
				}
			}
			pila_desapilar(pila);
			return true;
		default:
			break;
	}
	
	return pila_apilar(pila, elem);
}

/* ******************************************************************
 *   FUNCIONES PARA REPRESENTAR EN NOTACION POSFIJA LA OPERACION
 * *****************************************************************/

void imprimir_representacion(cola_t* cola) {
	while (!cola_esta_vacia(cola)) {
		fprintf(stdout, "%s", (char*)cola_desencolar(cola));
		if (!cola_esta_vacia(cola)) {
			fprintf(stdout, " ");
		} else {
			fprintf(stdout, "\n");
		}
	}
}

bool apilar_elementos_restantes(pila_t* pila, cola_t* cola) {
	bool representacion_valida = true;
	
	while (!pila_esta_vacia(pila)) {
		representacion_valida = cola_encolar(cola, pila_desapilar(pila));
		if (!representacion_valida) {
			fprintf(stdout, MENSAJE_ERROR);
			return false;
		}
	}
	
	return representacion_valida;
}

void obtener_representacion(char* str) {
	char** strv = split(str, ' ');
	
	if (!strv) {
		fprintf(stdout, MENSAJE_ERROR);
		return;
	}
	
	pila_t* pila = pila_crear();
	if (!pila) {
		free_strv(strv);
		fprintf(stdout, MENSAJE_ERROR);
		return;
	}
	
	cola_t* cola = cola_crear();
	if (!cola) {
		free_strv(strv);
		pila_destruir(pila);
		fprintf(stdout, MENSAJE_ERROR);
		return;
	}
	
	bool representacion_valida = false;
	size_t i = 0;
	while (strv[i]) {
		if (strcmp(strv[i], "\0") != 0) {
			if (validar_numero(strv[i])) {
				representacion_valida = cola_encolar(cola, strv[i]);
				if (!representacion_valida) {
					break;
				}
			} else {
				representacion_valida = evaluar_operador(strv[i], pila, cola);
				if (!representacion_valida) {
					break;
				}
			}
		}
		i++;
	}
	
	if (!representacion_valida) {
		fprintf(stdout, MENSAJE_ERROR);
	} else {
		representacion_valida = apilar_elementos_restantes(pila, cola);
	}
	
	if (representacion_valida) {
		imprimir_representacion(cola);
	}
	
	free_strv(strv);
	cola_destruir(cola, NULL);
	pila_destruir(pila);
}

/* ******************************************************************
 *                   FUNCIONES PRINCIPALES 
 * *****************************************************************/

void infix(int cantidad_de_argumentos) {
	if (!validar_cantidad_de_parametros(ARGUMENTOS_VALIDOS, cantidad_de_argumentos)) {
		fprintf(stdout, "Cantidad de parametros erronea.\n");
		return;
	}
	
	ssize_t fin_arch = 0;
	size_t tam = 0;
	char* str = NULL;
	char* str_limpia = NULL;
	char* str_espaciada = NULL;
	while (fin_arch != -1) {
		fin_arch = getline(&str, &tam, stdin);
		if (fin_arch != -1) {
			tam = fin_arch;
			str_limpia = obtener_cadena_limpia(str, &tam);
			if (str_limpia) {
				bool str_se_modifica = true;
				str_espaciada = obtener_cadena_espaciada(str_limpia, tam, &str_se_modifica);
				if (str_se_modifica) {
					if (str_espaciada) {
						obtener_representacion(str_espaciada);
						free(str_espaciada);
					} else {
						fprintf(stdout, MENSAJE_ERROR);
					}
				} else {
					obtener_representacion(str_limpia);
				}
				free(str_limpia);
			} else {
				fprintf(stdout, MENSAJE_ERROR);
			}
		}
	}
	
	free(str);
}

int main(int argc, char* argv[]) {
	infix(argc);
	return 0;
}

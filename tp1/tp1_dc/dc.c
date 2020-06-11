#define _POSIX_C_SOURCE 200809L
#include "pila.h"
#include "cola.h"
#include "strutil.h"
#include "input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define CANTIDAD_OPERADORES 8
#define MENSAJE_ERROR "ERROR\n"
#define ARGUMENTOS_VALIDOS 1

typedef enum {suma, resta, multiplicacion, division, raiz, potencia, logaritmo, ternario} operador_t;

/* ******************************************************************
 *     FUNCIONES PARA CALCULAR EL RESULTADO DE LA OPERACION
 * *****************************************************************/

long calcular_aproximacion_radicando(long numero, long digito, long resultado) {
	if ((numero * digito) == resultado) {
		return numero;
	}
	
	if ((numero * digito) > resultado) {
		return numero - 1;
	}
	
	return calcular_aproximacion_radicando(numero + 1, digito + 1, resultado);
}

long calcular_raiz_cuadrada_entera(long radicando, long* radicando_parcial) {
	if (radicando == 0) {
		return 0;
	}
	
	long par_numerico = radicando % 100;
	long raiz_parcial = calcular_raiz_cuadrada_entera(radicando / 100, radicando_parcial);
	long radicando_nuevo = *radicando_parcial + par_numerico;
	long aproximacion_radicando_parcial = calcular_aproximacion_radicando(raiz_parcial * 20, 0, radicando_nuevo);
	long radicando_ultimo_digito = aproximacion_radicando_parcial % 10;
	raiz_parcial = raiz_parcial * 10 + radicando_ultimo_digito;
	*radicando_parcial = (radicando_nuevo - aproximacion_radicando_parcial * radicando_ultimo_digito) * 100;
	return raiz_parcial;
}

long calcular_raiz(long radicando) {
	long radicando_parcial = 0;
	return calcular_raiz_cuadrada_entera(radicando, &radicando_parcial);
}

long calcular_potencia(long base, long exp) {
	if (exp == 0) {
		return 1;
	}  
    
	if ((exp % 2) != 0) {
    	return base * calcular_potencia(base * base, exp / 2);
	} 
	
	return calcular_potencia(base * base, exp / 2);
}

long calcular_logaritmo(long num, long base) {
	long log = 0;
	
	while (num > 0) {
		num = num / base;
		log++;
	}
	
	return log - 1;
}
//Funcion para determinar la cantidad de caracteres que se necesitan para expresar el resultado como string.
int calcular_cantidad_de_digitos(long numero) {
	int cant_digitos = 0;
	
	if (numero < 0) {
		numero *= -1;
		cant_digitos++;
	}
	
	while (numero > 0) {
		numero = numero / 10;
		cant_digitos++;
	}
	
	return cant_digitos;
}

bool calcular_resultado(pila_t* pila, long numv[], operador_t op) {
	long resultado = 0;
	
	switch (op) {
		case suma:
			resultado = numv[0] + numv[1];
			break;
		case resta:
			resultado = numv[1] - numv[0];
			break;
		case multiplicacion:
			resultado = numv[0] * numv[1];
			break;
		case division:
			if (numv[0] == 0) {
				return false;
			}
			resultado = numv[1] / numv[0];
			break;
		case raiz:
			if (numv[0] < 0) {
				return false;
			}
			resultado = calcular_raiz(numv[0]);
			break;
		case potencia:
			if (numv[0] < 0) {
				return false;
			}
			resultado = calcular_potencia(numv[1], numv[0]);
			break;
		case logaritmo:
			if (numv[0] <= 1) {
				return false;
			}
			resultado = calcular_logaritmo(numv[1], numv[0]);
			break;
		case ternario:
			if (numv[2] != 0) {
				resultado = numv[1];
			} else {
				resultado = numv[0];
			}
			break;
	}
	 
	int cant_digitos = 1;
	if (resultado != 0) {
		cant_digitos = calcular_cantidad_de_digitos(resultado);
	}
	
	char* numero = calloc(cant_digitos + 1, sizeof(char));
	if (!numero) {
		return false;
	}
	
	sprintf(numero, "%ld", resultado);
	if (!pila_apilar(pila, numero)) {
		free(numero);
		return false;
	}
	
	return true;
}

/* ******************************************************************
 *     FUNCIONES PARA DETERMINAR LA OPERACION A REALIZAR
 * *****************************************************************/

bool calcular_operacion(pila_t* pila, char* elem) {
	char* strv[] = {"+", "-", "*", "/", "sqrt", "^", "log", "?"};
	int op = suma;
	
	if (!validar_operador(elem, &op, CANTIDAD_OPERADORES, strv)) {
		return false;
	}
	
	int cant_elem = 0;
	if (op == ternario) {
		cant_elem = 3;
	} else if (op == raiz){
		cant_elem = 1;
	} else {
		cant_elem = 2;
	}
	
	long numv[cant_elem];
	for (size_t i = 0; i < cant_elem; i++) {
		if (pila_esta_vacia(pila)) {
			return false;
		}
		numv[i] = atol((char*)pila_desapilar(pila));
	}
	
	return calcular_resultado(pila, numv, op);
}

void obtener_resultado(char* str) {
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
	
	size_t i = 0;
	bool elemento_valido = false;
	while (strv[i]) {
		if (strcmp(strv[i], "\0") != 0) {
			if (validar_numero(strv[i])) {
			    if (!pila_apilar(pila, strv[i])) {
			    	elemento_valido = false;
					break;
				}
		    } else {
			    elemento_valido = calcular_operacion(pila, strv[i]);
			    if (!elemento_valido) {
				    break;
			    }
			    elemento_valido = cola_encolar(cola, pila_ver_tope(pila));
			    if (!elemento_valido) {
				    free(pila_desapilar(pila));
					break;
			    }
		    }
	    }
	    i++;
	}
	
	char* resultado = (char*)pila_desapilar(pila);
	if ((elemento_valido) && (pila_esta_vacia(pila))) {
		fprintf(stdout, "%s\n", resultado);
	} else {
		fprintf(stdout, MENSAJE_ERROR);
	}
	
	free_strv(strv);
	cola_destruir(cola, free);
	pila_destruir(pila);
}

/* ******************************************************************
 *                   FUNCIONES PRINCIPALES 
 * *****************************************************************/

void dc(int cantidad_de_argumentos) {
	if (!validar_cantidad_de_parametros(ARGUMENTOS_VALIDOS, cantidad_de_argumentos)) {
		fprintf(stdout, "Cantidad de parametros erronea.\n");
		return;
	}
	
	ssize_t fin_arch = 0;
	size_t tam = 0;
	char* str = NULL;
	char* str_limpia = NULL;
	while (fin_arch != -1) {
		fin_arch = getline(&str, &tam, stdin);
		if (fin_arch != -1) {
			tam = fin_arch;
			str_limpia = obtener_cadena_limpia(str, &tam);
			if (str_limpia) {
				obtener_resultado(str_limpia);
			    free(str_limpia);
			} else {
				fprintf(stdout, MENSAJE_ERROR);
			}
		}
	}
	
	free(str);
}

int main (int argc, char* argv[]) {
	dc(argc);
	return 0;
}

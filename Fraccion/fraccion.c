//Ejercicio 1 de la Guia.
/*
Implementar el TDA Fracción.
*/
#include "fraccion.h"
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/
 
struct fraccion {
	int numerador;
	int denominador;
};

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/
 
int calcular_denominador_en_suma(int denominador1, int denominador2) {
	if (denominador1 == denominador2) {
		return denominador1;
	}
	
	if ((denominador1 > denominador2) && ((denominador1 % denominador2) == 0)) {
		return denominador1;
	}
	
	if ((denominador1 < denominador2) && ((denominador2 % denominador1) == 0)) {
		return denominador2;
	}
	
	return denominador1 * denominador2;
}

int calcular_maximo_comun_divisor(int dividendo, int divisor) {
	if (divisor == 0) {
		return dividendo;
	}
	
	return calcular_maximo_comun_divisor(divisor, dividendo % divisor);
}

void simplificar_fraccion(fraccion_t* fraccion) {
	if (fraccion->numerador == 0) {
		fraccion->denominador = 1;
		return;
	}
	
	int maximo_comun_divisor = 0, numerador = fraccion->numerador, denominador = fraccion->denominador;
	if (numerador < 0) {
		numerador = numerador * (-1);
	}
	
	if (numerador > denominador) {
		maximo_comun_divisor = calcular_maximo_comun_divisor(numerador, denominador);
	} else {
		maximo_comun_divisor = calcular_maximo_comun_divisor(denominador, numerador);
	}
	
	fraccion->numerador = fraccion->numerador / maximo_comun_divisor;
	fraccion->denominador = fraccion->denominador / maximo_comun_divisor;
}

int calcular_cantidad_de_caracteres(fraccion_t* fraccion) {
	if (fraccion->numerador == 0) {
		return 1;
	}
	
	int cantidad_caracteres = 0, numerador = fraccion->numerador, denominador = fraccion->denominador;
	if (numerador < 0) {
		cantidad_caracteres = 1;
		numerador = numerador * (-1);
	}
	
	while (numerador > 0) {
		numerador = numerador / 10;
		cantidad_caracteres++;
	}
	
	if (denominador == 1) {
		return cantidad_caracteres;
	}
	
	cantidad_caracteres++;
	while (denominador > 0) {
		denominador = denominador / 10;
		cantidad_caracteres++;
	}
	
	return cantidad_caracteres;
}

/* ******************************************************************
 *                        PRIMITIVAS DE LA FRACCION
 * *****************************************************************/
 
fraccion_t* fraccion_crear(int numerador, int denominador) {
	if (denominador == 0) {
		return NULL;
	}
	
	fraccion_t* fraccion = malloc(sizeof(fraccion_t));
	if (fraccion == NULL) {
		return NULL;
	}
	
	if (((numerador < 0) && (denominador < 0)) || ((numerador > 0) && (denominador < 0))) {
		numerador = numerador * (-1);
		denominador = denominador * (-1);
	}
	
	fraccion->numerador = numerador;
	fraccion->denominador = denominador;
	simplificar_fraccion(fraccion);
	return fraccion;
}

fraccion_t* fraccion_sumar(fraccion_t* f1, fraccion_t* f2) {
	if ((f1 == NULL) || (f2 == NULL)) {
		return NULL;
	}
	
	int denominador = calcular_denominador_en_suma(f1->denominador, f2->denominador);
	fraccion_t* fraccion = fraccion_crear((denominador / f1->denominador) * f1->numerador + (denominador / f2->denominador) * f2->numerador, denominador);
	if (fraccion == NULL) {
		return NULL;
	}
	
	fraccion_destruir(f1);
	fraccion_destruir(f2);
	return fraccion;
}

fraccion_t* fraccion_mul(fraccion_t* f1, fraccion_t* f2) {
	if ((f1 == NULL) || (f2 == NULL)) {
		return NULL;
	}
	
	fraccion_t* fraccion = fraccion_crear(f1->numerador * f2->numerador, f1->denominador * f2->denominador);
	if (fraccion == NULL) {
		return NULL;
	}
	
	fraccion_destruir(f1);
	fraccion_destruir(f2);
	return fraccion;
}

int fraccion_parte_entera(fraccion_t* fraccion) {
	return fraccion->numerador / fraccion->denominador;
}

char* fraccion_representacion(fraccion_t* fraccion) {
	if (fraccion == NULL) {
		return NULL;
	}
	
	int cantidad_caracteres = calcular_cantidad_de_caracteres(fraccion) + 1;
	char* representacion = calloc(cantidad_caracteres, sizeof(char));
	if (representacion == NULL) {
		return NULL;
	}
	
	if (fraccion->denominador == 1) {
		sprintf(representacion, "%d", fraccion->numerador);
		return representacion;
	}
	
	sprintf(representacion, "%d/%d", fraccion->numerador, fraccion->denominador);
	return representacion;
}

void fraccion_destruir(fraccion_t* fraccion) {
	free(fraccion);
}

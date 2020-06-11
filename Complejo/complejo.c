#include "complejo.h"
#include <stdlib.h>
#include <math.h>

#define PI 3.1415926535

/* ******************************************************************
 *                        ESTRUCTURA DE DATOS
 * *****************************************************************/
 
struct complejo {
	double real;
	double img;
};

/* ******************************************************************
 *                        PRIMITIVAS DE COMPLEJO
 * *****************************************************************/
 
complejo_t* complejo_crear(double real, double img) {
	complejo_t* complejo = malloc(sizeof(complejo_t));
	
	if (!complejo) {
		return NULL;
	}
	
	complejo->real = real;
	complejo->img = img;
	return complejo;
}

void complejo_destruir(complejo_t* complejo) {
	free(complejo);
}

void complejo_multiplicar(complejo_t* c1, complejo_t* c2) {
	double real_auxiliar = c1->real;
	
	c1->real = c1->real * c2->real - c1->img * c2->img;
	c1->img = c1->img * c2->real + real_auxiliar * c2->img;
}

void complejo_sumar(complejo_t* c1, complejo_t* c2) {
	c1->real = c1->real + c2->real;
	c1->img = c1->img + c2->img;
}

double complejo_obtener_real(const complejo_t* complejo) {
	return complejo->real;
}

double complejo_obtener_imaginaria(const complejo_t* complejo) {
	return complejo->img;
}

double complejo_obtener_modulo(const complejo_t* complejo) {
	return sqrt(pow(complejo->real, 2) + pow(complejo->img, 2));
}

double complejo_obtener_angulo(const complejo_t* complejo) {
	if ((complejo->real == 0) && (complejo->img > 0)) {
		return PI / 2;
	}
	
	if ((complejo->real == 0) && (complejo->img < 0)) {
		return PI * 1.5;
	}
	
	return atan(complejo->img / complejo->real);
}

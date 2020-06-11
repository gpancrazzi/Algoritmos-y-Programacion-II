#include "composicion_funciones.h"
#include "testing.h"
#include <stdlib.h>

void prueba_composicion_crear(void) {
	composicion_t* composicion1 = composicion_crear();
	
	print_test("Prueba composicion de funciones se crea la composicion correctamente", composicion1 != NULL);
	composicion_destruir(composicion1);
}

double funcion_lineal(double numero) {
	return numero * 5 + 13;
}

double funcion_cuadratica(double numero) {
	return numero * numero * 2 + 3 * numero - 2;
}

void prueba_composicion_agregar(void) {
	composicion_t* composicion1 = composicion_crear();
	
	print_test("Prueba composicion de funciones se agrega una funcion correctamente", composicion_agregar_funcion(composicion1, funcion_lineal) == true);
	print_test("Prueba composicion de funciones se agrega una funcion correctamente", composicion_agregar_funcion(composicion1, funcion_cuadratica) == true);
	composicion_destruir(composicion1);
}

void prueba_composicion_aplicar(void) {
	composicion_t* composicion1 = composicion_crear();
	
	composicion_agregar_funcion(composicion1, funcion_lineal);
	composicion_agregar_funcion(composicion1, funcion_cuadratica);
	print_test("Prueba composicion de funciones aplicar las funciones retorna el valor correcto", composicion_aplicar(composicion1, 7) == 598);
	print_test("Prueba composicion de funciones aplicar las funciones retorna el valor correcto (sin funciones)", composicion_aplicar(composicion1, 7) == 7);
	composicion_destruir(composicion1);
}

void pruebas_composicion_funciones(void) {
	prueba_composicion_crear();
	prueba_composicion_agregar();
	prueba_composicion_aplicar();
}

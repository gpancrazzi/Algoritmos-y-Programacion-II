#include "turnos.h"
#include "testing.h"
#include <stdlib.h>
#include <string.h>

#define CONSTANTE_VOLUMEN 10000

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

int strcmp_wrapper(const void *a, const void *b) {
	return strcmp((char*)a, (char*)b);
}

bool encolar_varios_elementos(turnos_t* turnos, void** valores, size_t inicio, size_t fin, bool es_prioritario) {
	for (size_t i = inicio; i < fin; i++) {
		if (!turnos_encolar(turnos, valores[i], es_prioritario)) return false;
	}
	
	return true;
}

void desencolar_elementos(turnos_t* turnos, void** valores, size_t fin) {
	for (size_t i = 0; i < fin; i++) {
		valores[i] = turnos_desencolar(turnos);
	}
}

bool comparar_orden(void** valores1, void** valores2, size_t inicio, size_t fin) {
	for (size_t i = inicio, j = 0; i < fin; i++, j++) {
		if (valores1[i] != valores2[j]) return false;
	}
	
	return true;
}

int comparar_enteros (size_t x, size_t y) {
	if (x > y) {
		return -1;
	}
		
	if (x < y) {
		return 1;
	}
	
	return 0;
}

int comparar_enteros_wrapper(const void *a, const void *b) {
	return comparar_enteros(*(size_t*)a, *(size_t*)b);
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_turnos_crear(void) {
	turnos_t* turnos1 = turnos_crear(strcmp_wrapper);
	
	print_test("Prueba turnos crear turnos vacio", turnos1);
	print_test("Prueba turnos la cantidad de elementos es 0", turnos_cantidad(turnos1) == 0);
	print_test("Prueba turnos obtener mas prioritario, es NULL, no existe", !turnos_ver_mas_prioritario(turnos1));
	print_test("Prueba turnos esta vacio es true", turnos_esta_vacio(turnos1));
    print_test("Prueba turnos desencolar es NULL", !turnos_desencolar(turnos1));
	
	turnos_destruir(turnos1, NULL);
}

void prueba_turnos_encolar_desencolar(void) {
	turnos_t* turnos1 = turnos_crear(strcmp_wrapper);
	char* valor1[] = {"guau", "miau", "mu", "pio", "grr", "fiu"};
	size_t n1 = 6;
    bool es_prioritario = true;
	
	print_test("Prueba turnos encolar un elemento no prioritario es true", turnos_encolar(turnos1, valor1[0], !es_prioritario));
	print_test("Prueba turnos la cantidad de elementos es correcta", turnos_cantidad(turnos1) == 1);
	print_test("Prueba turnos obtener mas prioritario retorna el valor correcto", turnos_ver_mas_prioritario(turnos1) == valor1[0]);
	print_test("Prueba turnos esta vacio es false", !turnos_esta_vacio(turnos1));
	
	print_test("Prueba turnos encolar un elemento prioritario es true", turnos_encolar(turnos1, valor1[1], es_prioritario));
	print_test("Prueba turnos la cantidad de elementos es correcta", turnos_cantidad(turnos1) == 2);
	print_test("Prueba turnos obtener mas prioritario retorna el valor correcto", turnos_ver_mas_prioritario(turnos1) == valor1[1]);
	print_test("Prueba turnos esta vacio es false", !turnos_esta_vacio(turnos1));
	
	print_test("Prueba turnos encolar otro elemento no prioritario es true", turnos_encolar(turnos1, valor1[2], !es_prioritario));
	print_test("Prueba turnos la cantidad de elementos es correcta", turnos_cantidad(turnos1) == 3);
	print_test("Prueba turnos obtener mas prioritario sigue siendo el mismo valor", turnos_ver_mas_prioritario(turnos1) == valor1[1]);
	print_test("Prueba turnos esta vacio es false", !turnos_esta_vacio(turnos1));
	
	print_test("Prueba turnos encolar otro elemento prioritario es true", turnos_encolar(turnos1, valor1[3], es_prioritario));
	print_test("Prueba turnos la cantidad de elementos es correcta", turnos_cantidad(turnos1) == 4);
	print_test("Prueba turnos obtener mas prioritario no cambio de valor", turnos_ver_mas_prioritario(turnos1) == valor1[1]);
	print_test("Prueba turnos esta vacio es false", !turnos_esta_vacio(turnos1));
	
	size_t inicio1 = 4;
	size_t fin1 = 6;
	bool ok = encolar_varios_elementos(turnos1, (void**)valor1, inicio1, fin1, !es_prioritario);
	print_test("Prueba turnos encolar varios elementos no prioritarios es true", ok);
	print_test("Prueba turnos la cantidad de elementos es correcta", turnos_cantidad(turnos1) == 6);
	print_test("Prueba turnos obtener mas prioritario no cambio de valor", turnos_ver_mas_prioritario(turnos1) == valor1[1]);
	print_test("Prueba turnos esta vacio es false", !turnos_esta_vacio(turnos1));
	
	ok = true;
	void* valor2[n1];
	void* orden1[] = {valor1[1], valor1[3], valor1[2], valor1[0], valor1[4], valor1[5]};
	desencolar_elementos(turnos1, valor2, n1);
	ok = comparar_orden(valor2, orden1, 0, n1);
	print_test("Prueba turnos desencolar retorna los valores en el orden correcto", ok);
	print_test("Prueba turnos la cantidad de elementos es 0", turnos_cantidad(turnos1) == 0);
	print_test("Prueba turnos obtener mas prioritario, es NULL, no existe", !turnos_ver_mas_prioritario(turnos1));
	print_test("Prueba turnos esta vacio es true", turnos_esta_vacio(turnos1));
    print_test("Prueba turnos desencolar es NULL", !turnos_desencolar(turnos1));
	
	turnos_destruir(turnos1, NULL);
}

void prueba_turnos_volumen(void) {
	size_t valores1[CONSTANTE_VOLUMEN];
	size_t inicio_prioritario = 9000;
	void* valores2[CONSTANTE_VOLUMEN];
	turnos_t* turnos1 = turnos_crear(comparar_enteros_wrapper);
	bool ok = true, es_prioritario = true;
	
	for (size_t i = 0; i < CONSTANTE_VOLUMEN; i++) {
		valores1[i] = i;
	}
	
	for (size_t i = 0; i < CONSTANTE_VOLUMEN; i++) {
		if (i < inicio_prioritario) {
			ok = turnos_encolar(turnos1, &valores1[i], !es_prioritario);
		} else {
			ok = turnos_encolar(turnos1, &valores1[i], es_prioritario);
		}
		if (!ok) break;
	}
	print_test("Prueba turnos encolar elementos en volumen retorna true", ok);
	print_test("Prueba turnos la cantidad de elementos es la correcta", turnos_cantidad(turnos1) == CONSTANTE_VOLUMEN);
	
	void* orden1_prioritario[CONSTANTE_VOLUMEN - inicio_prioritario];
	for (size_t i = inicio_prioritario, j = 0; i < CONSTANTE_VOLUMEN; i++, j++) {
		orden1_prioritario[j] = &valores1[i];
	}
	
	void* orden1_no_prioritario[inicio_prioritario];
	for (size_t i = 0; i < inicio_prioritario; i++) {
		orden1_no_prioritario[i] = &valores1[i];
	}
	
	ok = true;
	desencolar_elementos(turnos1, valores2, CONSTANTE_VOLUMEN);
	ok = comparar_orden(valores2, orden1_prioritario, 0, CONSTANTE_VOLUMEN - inicio_prioritario);
	ok = true;
	ok = comparar_orden(valores2, orden1_no_prioritario, CONSTANTE_VOLUMEN - inicio_prioritario, CONSTANTE_VOLUMEN);
	print_test("Prueba turnos desencolar en volumen retorna los valores en el orden correcto", ok);
	print_test("Prueba turnos la cantidad de elementos es 0", turnos_cantidad(turnos1) == 0);
	print_test("Prueba turnos obtener mas prioritario, es NULL, no existe", !turnos_ver_mas_prioritario(turnos1));
	print_test("Prueba turnos esta vacio es true", turnos_esta_vacio(turnos1));
    print_test("Prueba turnos desencolar es NULL", !turnos_desencolar(turnos1));
    
    turnos_destruir(turnos1, NULL);
}

void prueba_turnos_destruir(void) {
	turnos_t* turnos1 = turnos_crear(strcmp_wrapper);
	char* valor1[] = {"guau", "miau", "mu", "pio", "grr", "fiu"};
	size_t inicio1 = 3, fin1 = 6;
	bool ok = true, es_prioritario = true;
	
	ok = encolar_varios_elementos(turnos1, (void**)valor1, 0, inicio1, !es_prioritario);
	ok = encolar_varios_elementos(turnos1, (void**)valor1, inicio1, fin1, es_prioritario);
	print_test("Prueba turnos encolar varios elementos de memoria estatica retorna true", ok);
	turnos_destruir(turnos1, NULL);
	print_test("Prueba turnos destruir con funcion NULL", true);
	
	turnos_t* turnos2 = turnos_crear(strcmp_wrapper);
	size_t inicio2 = 2, fin2 = 3;
	char** valor2 = malloc(sizeof(char*) * fin2);
	char* dato1 = malloc(sizeof(char));
	char* dato2 = malloc(sizeof(char));
	char* dato3 = malloc(sizeof(char));
	dato1[0] = 'A';
	dato2[0] = 'B';
	dato3[0] = 'C';
	valor2[0] = dato1;
	valor2[1] = dato2;
	valor2[2] = dato3;
	ok = true;
	
	ok = encolar_varios_elementos(turnos2, (void**)valor2, 0, inicio2, !es_prioritario);
	ok = encolar_varios_elementos(turnos2, (void**)valor2, inicio2, fin2, es_prioritario);
	print_test("Prueba turnos encolar varios elementos de memoria dinamica retorna true", ok);
	turnos_destruir(turnos2, free);
	free(valor2);
	print_test("Prueba turnos destruir con funcion distinta de NULL", true);
}

/* ******************************************************************
 *                        FUNCION PRINCIPAL
 * *****************************************************************/

void pruebas_turnos_alumno() {
	prueba_turnos_crear();
	prueba_turnos_encolar_desencolar();
	prueba_turnos_volumen();
	prueba_turnos_destruir();
}

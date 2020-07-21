#include "abb.h"
#include "testing.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ******************************************************************
 *                        FUNCIONES AUXILIARES
 * *****************************************************************/

bool guardar_en_abb(abb_t* abb, char** claves, void** datos, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (!abb_guardar(abb, claves[i], datos[i])) {
			return false;
		}
	}
	
	return true;
}

bool verificar_orden(lista_t* datos, void** valores, size_t n) {
	for (size_t i = 0; i < n; i++) {
		if (!(lista_borrar_primero(datos) == valores[i])) {
			return false;
		}
	}
	
	return true;
}

void guardar_claves_en_volumen(abb_t* abb, char* clave, size_t** arreglo, size_t inicio, size_t fin, bool* ok) {
	if (fin == inicio) {
		return;
	}
	
	size_t medio = (fin + inicio) / 2;
	sprintf(clave, "%ld", medio);
	if (!abb_guardar(abb, (const char*)clave, (void*)arreglo[medio])) {
		*ok = false;
		return;
	}
	
	guardar_claves_en_volumen(abb, clave, arreglo, inicio, medio, ok);
    guardar_claves_en_volumen(abb, clave, arreglo, medio + 1, fin, ok);
}

size_t calcular_cantidad_de_numeros(size_t base) {
	size_t cant_digitos = 0;
	
	while (base > 0) {
		base = base / 10;
		cant_digitos++;
	}
	
	return cant_digitos;
}

void obtener_rango(abb_iter_t* iter, char** claves, size_t inicio, size_t fin, size_t n) {
	size_t j = 0;
	
	for (size_t i = 0; i < fin; i++) {
		if (i >= inicio) {
			claves[j] = (char*)abb_iter_in_ver_actual(iter);
			j++;
		}
		abb_iter_in_avanzar(iter);
	}
}

void obtener_valores(abb_t* abb, char** claves, void** valores, size_t n) {
	for (size_t i = 0; i < n; i++) {
		valores[i] = abb_obtener(abb, claves[i]);
	}
}

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

void prueba_abb_obtener_rangos(void) {
	abb_t* abb1 = abb_crear(strcmp, NULL);
	char *claves[] = {"perro", "gato", "vaca", "elefante", "iguana", "zorro", "raton"};
	int num[] = {4, 45, -1, 12, 3, 6, 2};
	void* ptr[] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6]};
	size_t n = 7;
	bool ok = guardar_en_abb(abb1, claves, ptr, n);
	
	if (!ok) {
		return;
	}
	
	lista_t* datos1 = abb_obtener_rango(abb1, claves[4], claves[6]);
	void* ptr1[] = {&num[4], &num[0], &num[6]};
	size_t n1 = 3;
	ok = verificar_orden(datos1, ptr1, n1) && lista_esta_vacia(datos1);
	print_test("Prueba abb obtener_rango chico retorna el rango y orden correctos", ok);
	lista_destruir(datos1, NULL);
	
	lista_t* datos2 = abb_obtener_rango(abb1, NULL, NULL);
	ok = true;
	void* ptr2[] = {&num[3], &num[1], &num[4], &num[0], &num[6], &num[2], &num[5]};
	ok = verificar_orden(datos2, ptr2, n) && lista_esta_vacia(datos2);
	print_test("Prueba abb obtener_rango completo retorna el rango y orden correctos", ok);
	lista_destruir(datos2, NULL);
	
	lista_t* datos3 = abb_obtener_rango(abb1, NULL, claves[4]);
	ok = true;
	void* ptr3[] = {&num[3], &num[1], &num[4]};
	size_t n3 = 3;
	ok = verificar_orden(datos3, ptr3, n3) && lista_esta_vacia(datos3);
	print_test("Prueba abb obtener_rango sin inicio definido retorna el rango y orden correctos", ok);
	lista_destruir(datos3, NULL);
	
	lista_t* datos4 = abb_obtener_rango(abb1, claves[1], NULL);
	ok = true;
	void* ptr4[] = {&num[1], &num[4], &num[0], &num[6], &num[2], &num[5]};
	size_t n4 = 6;
	ok = verificar_orden(datos4, ptr4, n4) && lista_esta_vacia(datos4);
	print_test("Prueba abb obtener_rango sin fin definido retorna el rango y orden correctos", ok);
	lista_destruir(datos4, NULL);
	
	abb_destruir(abb1);
}

void prueba_abb_obtener_rango_casos_borde(void) {
	abb_t* abb1 = abb_crear(strcmp, NULL);
	char *claves[] = {"perro", "gato", "vaca", "elefante", "iguana", "zorro", "raton"};
	int num[] = {4, 45, -1, 12, 3, 6, 2};
	void* ptr[] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6]};
	size_t n = 7;
	bool ok = guardar_en_abb(abb1, claves, ptr, n);
	
	if (!ok) {
		return;
	}
	
	abb_t* abb2 = abb_crear(strcmp, NULL);
	lista_t* datos1 = abb_obtener_rango(abb2, NULL, NULL);
	print_test("Prueba abb obtener_rango en abb vacio retorna el valor correcto", !datos1);
	abb_destruir(abb2);
	
	lista_t* datos2 = abb_obtener_rango(abb1, claves[2], "auto");
	print_test("Prueba abb obtener_rango fin no se encuentra en el abb retorna el valor correcto", !datos2);
	
	lista_t* datos3 = abb_obtener_rango(abb1, "pera", claves[2]);
	print_test("Prueba abb obtener_rango inicio no se encuentra en el abb retorna el valor correcto", !datos3);
	
	lista_t* datos4 = abb_obtener_rango(abb1, "pera", "auto");
	print_test("Prueba abb obtener_rango rango no se encuentra en el abb retorna el valor correcto", !datos4);
	
	lista_t* datos5 = abb_obtener_rango(abb1, claves[6], claves[1]);
	print_test("Prueba abb obtener_rango rango incoherente retorna el valor correcto", !datos5);
	
	abb_destruir(abb1);
}

void prueba_abb_obtener_rango_volumen(size_t n) {
	abb_t* abb = abb_crear(strcmp, free);
	size_t cant_caracteres = calcular_cantidad_de_numeros(n) + 1;
	char clave[cant_caracteres];
	size_t* cantidad[n];
	bool ok = true;
	
	for (size_t i = 0; i < n; i++) {
        cantidad[i] = malloc(sizeof(size_t));
        *cantidad[i] = i;
    }
    
    guardar_claves_en_volumen(abb, clave, cantidad, 0, n, &ok);
    if (!ok) {
    	abb_destruir(abb);
		return;
	}
	
	ok = true;
	size_t n1 = 10, inicio1 = 4520, fin1 = 4530;
	char** claves1 = calloc(n1, sizeof(char*));
	void** valores1 = calloc(n1, sizeof(void*));
	abb_iter_t* iter1 = abb_iter_in_crear(abb);
	obtener_rango(iter1, claves1, inicio1, fin1, n1);
	obtener_valores(abb, claves1, valores1, n1);
	lista_t* datos1 = abb_obtener_rango(abb, claves1[0], claves1[n1 - 1]);
	ok = verificar_orden(datos1, valores1, n1) && lista_esta_vacia(datos1);
	print_test("Prueba abb obtener_rango en volumen, con rango acotado, retorna el rango y orden correctos", ok);
	abb_iter_in_destruir(iter1);
	lista_destruir(datos1, NULL);
	free(claves1);
	free(valores1);
	
	ok = true;
	size_t n2 = n, inicio2 = 0, fin2 = n;
	char** claves2 = calloc(n2, sizeof(char*));
	void** valores2 = calloc(n2, sizeof(void*));
	abb_iter_t* iter2 = abb_iter_in_crear(abb);
	obtener_rango(iter2, claves2, inicio2, fin2, n2);
	obtener_valores(abb, claves2, valores2, n2);
	lista_t* datos2 = abb_obtener_rango(abb, claves2[0], claves2[n2 - 1]);
	ok = verificar_orden(datos2, valores2, n2) && lista_esta_vacia(datos2);
	print_test("Prueba abb obtener_rango en volumen, con todos los elementos, retorna el rango y orden correctos", ok);
	abb_iter_in_destruir(iter2);
	lista_destruir(datos2, NULL);
	free(claves2);
	free(valores2);
	
	abb_destruir(abb);
}

/* ******************************************************************
 *                        FUNCION PRINCIPAL
 * *****************************************************************/
 
void pruebas_abb_obtener_rango() {
	prueba_abb_obtener_rango_casos_borde();
	prueba_abb_obtener_rangos();
	prueba_abb_obtener_rango_volumen(10000);
}

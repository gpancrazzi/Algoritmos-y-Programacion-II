#include "heap.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ******************************************************************
 *                        PRUEBAS UNITARIAS
 * *****************************************************************/

int wrapper_strcmp(const void *a, const void *b) {
	return strcmp((char*)a, (char*)b);
}

static void prueba_crear_heap_vacio() {
	heap_t* heap = heap_crear(wrapper_strcmp);
	
	print_test("Prueba heap crear heap vacio", heap);
	print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
	print_test("Prueba heap obtener maximo, es NULL, no existe", heap_ver_max(heap) == NULL);
	print_test("Prueba heap esta vacio es true", heap_esta_vacio(heap) == true);
    print_test("Prueba heap desencolar es NULL", heap_desencolar(heap) == NULL);
	
	heap_destruir(heap, NULL);
}

static void prueba_heap_encolar_algunos_elementos() {
	heap_t* heap = heap_crear(wrapper_strcmp);
	
	char *clave1 = "D";
    char *clave2 = "H";
    char *clave3 = "B";
    char *clave4 = "J";
    char *clave5 = "M";
    
    print_test("Prueba heap encolar clave1", heap_encolar(heap, clave1) == true);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap obtener maximo es clave1", heap_ver_max(heap) == clave1);
    print_test("Prueba heap esta vacio es false", heap_esta_vacio(heap) == false);
    print_test("Prueba heap desencolar maximo es clave1", heap_desencolar(heap) == clave1);
    print_test("Prueba heap obtener maximo, es NULL, no existe", heap_ver_max(heap) == NULL);
	print_test("Prueba heap esta vacio es true", heap_esta_vacio(heap) == true);
    print_test("Prueba heap desencolar es NULL", heap_desencolar(heap) == NULL);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    print_test("Prueba heap encolar clave2", heap_encolar(heap, clave2));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap obtener maximo es clave2", heap_ver_max(heap) == clave2);
    print_test("Prueba heap esta vacio es false", heap_esta_vacio(heap) == false);

    print_test("Prueba heap encolar clave3", heap_encolar(heap, clave3));
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap obtener maximo es clave2", heap_ver_max(heap) == clave2);
    print_test("Prueba heap esta vacio es false", heap_esta_vacio(heap) == false);
    
    print_test("Prueba heap encolar clave4", heap_encolar(heap, clave4));
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("Prueba heap obtener maximo es clave4", heap_ver_max(heap) == clave4);
    print_test("Prueba heap esta vacio es false", heap_esta_vacio(heap) == false);
    
    print_test("Prueba heap encolar clave5", heap_encolar(heap, clave5));
    print_test("Prueba heap la cantidad de elementos es 4", heap_cantidad(heap) == 4);
    print_test("Prueba heap obtener maximo es clave5", heap_ver_max(heap) == clave5);
    print_test("Prueba heap esta vacio es false", heap_esta_vacio(heap) == false);
    
    print_test("Prueba heap desencolar maximo es clave5", heap_desencolar(heap) == clave5);
    print_test("Prueba heap la cantidad de elementos es 3", heap_cantidad(heap) == 3);
    print_test("Prueba heap obtener maximo es clave4", heap_ver_max(heap) == clave4);
    
    print_test("Prueba heap desencolar maximo es clave4", heap_desencolar(heap) == clave4);
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap obtener maximo es clave2", heap_ver_max(heap) == clave2);
    
    print_test("Prueba heap desencolar maximo es clave2", heap_desencolar(heap) == clave2);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap obtener maximo es clave3", heap_ver_max(heap) == clave3);
    
    print_test("Prueba heap desencolar maximo es clave3", heap_desencolar(heap) == clave3);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap obtener maximo es NULL", heap_ver_max(heap) == NULL);
    print_test("Prueba heap esta vacio es true", heap_esta_vacio(heap) == true);
    print_test("Prueba heap desencolar es NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
}

static void prueba_heap_destruir() {
	heap_t* heap = heap_crear(wrapper_strcmp);
	
	char *clave1 = malloc(sizeof(char) * 2);
    char *clave2 = malloc(sizeof(char) * 2);
    char *clave3 = malloc(sizeof(char) * 2);
    char *clave4 = malloc(sizeof(char) * 2);
    char *clave5 = malloc(sizeof(char) * 2);
    
    char *clave6 = "D";
    char *clave7 = "H";
    char *clave8 = "B";
    char *clave9 = "J";
    char *clave10 = "M";
    
    sprintf(clave1, "%s", clave6);
    sprintf(clave2, "%s", clave7);
    sprintf(clave3, "%s", clave8);
    sprintf(clave4, "%s", clave9);
    sprintf(clave5, "%s", clave10);
    
    print_test("Prueba heap encolar clave1 de memoria dinamica", heap_encolar(heap, clave1) == true);
    print_test("Prueba heap encolar clave2 de memoria dinamica", heap_encolar(heap, clave2) == true);
    print_test("Prueba heap encolar clave3 de memoria dinamica", heap_encolar(heap, clave3) == true);
    print_test("Prueba heap encolar clave4 de memoria dinamica", heap_encolar(heap, clave4) == true);
    print_test("Prueba heap encolar clave5 de memoria dinamica", heap_encolar(heap, clave5) == true);
    
    heap_destruir(heap, free);
    print_test("Prueba heap destruir con funcion distinta de NULL", true);
}

int comparar_enteros (int x, int y) {
	if (x > y) {
		return 1;
	}
		
	if (x < y) {
		return -1;
	}
	
	return 0;
}

int wrapper_comparar_enteros(const void *a, const void *b) {
	return comparar_enteros(*(int*)a, *(int*)b);
}

static void prueba_heap_volumen(int largo) {
	heap_t* heap = heap_crear(wrapper_comparar_enteros);
	
	int datos[largo];
	void* datos_ptr[largo];
	for (int i = 0; i < largo; i++) {
		datos[i] = i;
		datos_ptr[i] = &datos[i];
	}
	
	bool ok = true;
	for (int i = 0; i < largo; i++) {
		ok = heap_encolar(heap, datos_ptr + i);
		ok = *(int*)heap_ver_max(heap) == *(datos + i);
		ok = heap_cantidad(heap) == (i + 1);
		if (ok == false) {
			break;
		}
	}
	
	print_test("Prueba heap encolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);
    
    ok = true;
    for (int i = largo - 1; i >= 0; i--) {
    	ok = *(int*)heap_desencolar(heap) == *(datos + i);
    	ok = heap_cantidad(heap) == i;
    	if (ok == false) {
    		break;
		}
	}
	
	print_test("Prueba heap desencolar muchos elementos", ok);
	print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == 0);
	
	heap_destruir(heap, NULL);
}

static void prueba_heap_heapsort() {
	int num[10] = {34, 4, -23, 11, 345, 7, 0, 3, -24, 145};
	void* arreglo_ptr[10] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6], &num[7], &num[8], &num[9]};
	int arreglo_ordenado[10] = {-24, -23, 0, 3, 4, 7, 11, 34, 145, 345};
	bool ok = true;
	
	heap_sort(arreglo_ptr, 10, wrapper_comparar_enteros);
	for (int i = 0; i < 10; i++) {
		ok = *(int*)arreglo_ptr[i] == arreglo_ordenado[i];
	}
	
	print_test("Prueba heap heapsort funciona correctamente", ok);
}

static void prueba_heap_crear_arreglo() {
	int num[10] = {34, 4, -23, 11, 345, 7, 0, 3, -24, 145};
	void* arreglo_ptr[10] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6], &num[7], &num[8], &num[9]};
	int arreglo_ordenado[10] = {-24, -23, 0, 3, 4, 7, 11, 34, 145, 345};
	bool ok = true;
	
	heap_t* heap = heap_crear_arr(arreglo_ptr, 10, wrapper_comparar_enteros);
	for (int i = 9; i >= 0; i--) {
		ok = *(int*)heap_desencolar(heap) == arreglo_ordenado[i];
		ok = heap_cantidad(heap) == i;
	}
	
	print_test("Prueba heap crear heap con un arreglo funciona correctamente", ok);
	heap_destruir(heap, NULL);
}

/* ******************************************************************
 *                        FUNCION PRINCIPAL
 * *****************************************************************/
 
void pruebas_heap_alumno() {
	prueba_crear_heap_vacio();
	prueba_heap_encolar_algunos_elementos();
	prueba_heap_destruir();
	prueba_heap_volumen(10000);
	prueba_heap_heapsort();
	prueba_heap_crear_arreglo();
}

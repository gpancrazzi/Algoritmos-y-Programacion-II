#include "lista.h"
#include "testing.h"
#include "pila.h"
#include <stdlib.h>
#include <stddef.h>

#define CONSTANTE_VOLUMEN 10000

void pruebas_lista_enlistar_desenlistar() {
	int num[] = {2, 4, 3, -1, 12,  67, 1};
	void* ptr[] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6]};
	lista_t* lista1 = lista_crear();
	
	print_test("Prueba lista crear lista", lista1 != NULL);
	print_test("Prueba lista el primer elemento de la lista es NULL", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es NULL", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista borrar el primer elemento de la lista es NULL", lista_borrar_primero(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 0", lista_largo(lista1) == 0);
	print_test("Prueba lista la lista esta vacia", lista_esta_vacia(lista1));
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[0]));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[0]);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == ptr[0]);
	print_test("Prueba lista la cantidad de elementos de la lista es 1", lista_largo(lista1) == 1);
	print_test("Prueba lista la lista no esta vacia", !lista_esta_vacia(lista1));
	print_test("Prueba lista enlistar un elemento al final de la lista es true", lista_insertar_ultimo(lista1, ptr[1]));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[0]);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == ptr[1]);
	print_test("Prueba lista la cantidad de elementos de la lista es 2", lista_largo(lista1) == 2);
	print_test("Prueba lista borrar el primer elemento de la lista devuelve el valor correcto", lista_borrar_primero(lista1) == ptr[0]);
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[1]);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == ptr[1]);
	print_test("Prueba lista la cantidad de elementos de la lista es 1", lista_largo(lista1) == 1);
	print_test("Prueba lista la lista no esta vacia", !lista_esta_vacia(lista1));
	print_test("Prueba lista borrar el primer elemento de la lista devuelve el valor correcto", lista_borrar_primero(lista1) == ptr[1]);
	print_test("Prueba lista el primer elemento de la lista es NULL", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es NULL", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista borrar el primer elemento de la lista es NULL", lista_borrar_primero(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 0", lista_largo(lista1) == 0);
	print_test("Prueba lista la lista esta vacia", lista_esta_vacia(lista1));
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[2]));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[2]);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == ptr[2]);
	print_test("Prueba lista la cantidad de elementos de la lista es 1", lista_largo(lista1) == 1);
	print_test("Prueba lista la lista no esta vacia", !lista_esta_vacia(lista1));
	print_test("Prueba lista enlistar un elemento al final de la lista es true", lista_insertar_ultimo(lista1, ptr[3]));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[2]);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == ptr[3]);
	print_test("Prueba lista la cantidad de elementos de la lista es 2", lista_largo(lista1) == 2);
	print_test("Prueba lista enlistar un elemento al final de la lista es true", lista_insertar_ultimo(lista1, ptr[4]));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[2]);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == ptr[4]);
	print_test("Prueba lista la cantidad de elementos de la lista es 3", lista_largo(lista1) == 3);
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[5]));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[5]);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == ptr[4]);
	print_test("Prueba lista la cantidad de elementos de la lista es 4", lista_largo(lista1) == 4);
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[6]));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[6]);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == ptr[4]);
	print_test("Prueba lista la cantidad de elementos de la lista es 5", lista_largo(lista1) == 5);
	//Pruebo destruir la lista.
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista fue destruida", true);
}

void pruebas_lista_elementos_NULL() {
	lista_t* lista1 = lista_crear();
	
	print_test("Prueba lista crear lista", lista1 != NULL);
	print_test("Prueba lista el primer elemento de la lista es NULL", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es NULL", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista borrar el primer elemento de la lista es NULL", lista_borrar_primero(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 0", lista_largo(lista1) == 0);
	print_test("Prueba lista la lista esta vacia", lista_esta_vacia(lista1));
	print_test("Prueba lista enlistar un elemento NULL al final de la lista es true", lista_insertar_ultimo(lista1, NULL));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 1", lista_largo(lista1) == 1);
	print_test("Prueba lista la lista no esta vacia", !lista_esta_vacia(lista1));
	print_test("Prueba lista enlistar un elemento NULL al principio de la lista es true", lista_insertar_primero(lista1, NULL));
	print_test("Prueba lista el primer elemento de la lista es el correcto", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es el correcto", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 2", lista_largo(lista1) == 2);
	//Pruebo destruir la lista.
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista fue destruida", true);
}

void pruebas_lista_iterador_externo() {
	int num[] = {4, 45, -1, 12, 3, 6, 2};
	void* ptr[] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6]};
	lista_t* lista1 = lista_crear();
	
	print_test("Prueba lista crear lista", lista1 != NULL);
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[0]));
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[1]));
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[2]));
	lista_iter_t* iter1 = lista_iter_crear(lista1);
	print_test("Prueba lista iterador crear iterador externo", iter1 != NULL);
	print_test("Prueba lista iterador el valor actual es el correcto", lista_iter_ver_actual(iter1) == ptr[2]);
	print_test("Prueba lista iterador el iterador no se encuentra al final de la lista", !lista_iter_al_final(iter1));
	print_test("Prueba lista iterador borrar un elemento devuelve el valor correcto", lista_iter_borrar(iter1) == ptr[2]);
	print_test("Prueba lista iterador el nuevo primer elemento de la lista es el correcto", lista_ver_primero(lista1) == ptr[1]);
	print_test("Prueba lista iterador insertar un elemento con el iterador externo es true", lista_iter_insertar(iter1, ptr[3]));
	print_test("Prueba lista iterador el elemento insertado se encuentra al principio de la lista", lista_ver_primero(lista1) == ptr[3]);
	print_test("Prueba lista iterador el valor actual del iterador es el correcto", lista_iter_ver_actual(iter1) == ptr[3]);
	print_test("Prueba lista la cantidad de elementos de la lista es 3", lista_largo(lista1) == 3);
	print_test("Prueba lista iterador avanzar un elemento es true", lista_iter_avanzar(iter1));
	print_test("Prueba lista iterador el valor actual del iterador es el correcto", lista_iter_ver_actual(iter1) == ptr[1]);
	print_test("Prueba lista iterador el iterador no se encuentra al final de la lista", !lista_iter_al_final(iter1));
	print_test("Prueba lista iterador insertar un elemento con el iterador externo es true", lista_iter_insertar(iter1, ptr[4]));
	print_test("Prueba lista iterador el valor actual del iterador es el correcto", lista_iter_ver_actual(iter1) == ptr[4]);
	print_test("Prueba lista la cantidad de elementos de la lista es 4", lista_largo(lista1) == 4);
	print_test("Prueba lista iterador borrar un elemento devuelve el valor correcto", lista_iter_borrar(iter1) == ptr[4]);
	print_test("Prueba lista iterador el valor actual del iterador es el correcto", lista_iter_ver_actual(iter1) == ptr[1]);
	print_test("Prueba lista la cantidad de elementos de la lista es 3", lista_largo(lista1) == 3);
	print_test("Prueba lista iterador avanzar un elemento es true", lista_iter_avanzar(iter1));
	print_test("Prueba lista iterador avanzar un elemento es true", lista_iter_avanzar(iter1));
	print_test("Prueba lista iterador el iterador se encuentra al final de la lista", lista_iter_al_final(iter1));
	print_test("Prueba lista iterador avanzar un elemento es false", !lista_iter_avanzar(iter1));
	print_test("Prueba lista iterador insertar un elemento con el iterador externo es true", lista_iter_insertar(iter1, ptr[5]));
	print_test("Prueba lista iterador el valor actual del iterador es el correcto", lista_iter_ver_actual(iter1) == ptr[5]);
	print_test("Prueba lista la cantidad de elementos de la lista es 4", lista_largo(lista1) == 4);
	print_test("Prueba lista iterador el elemento insertado se encuentra al final de la lista", lista_ver_ultimo(lista1) == ptr[5]);
	print_test("Prueba lista iterador borrar un elemento devuelve el valor correcto", lista_iter_borrar(iter1) == ptr[5]);
	print_test("Prueba lista iterador el valor actual del iterador es NULL", lista_iter_ver_actual(iter1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 3", lista_largo(lista1) == 3);
	print_test("Prueba lista iterador borrar un elemento devuelve NULL", lista_iter_borrar(iter1) == NULL);
	print_test("Prueba lista iterador el valor actual del iterador es NULL", lista_iter_ver_actual(iter1) == NULL);
	print_test("Prueba lista iterador el iterador se encuentra al final de la lista", lista_iter_al_final(iter1));
	print_test("Prueba lista iterador avanzar un elemento es false", !lista_iter_avanzar(iter1));
	lista_iter_destruir(iter1);
	print_test("Prueba lista iterador el iterador externo fue destruido", true);
	lista_iter_t* iter2 = lista_iter_crear(lista1);
	print_test("Prueba lista iterador crear otro iterador externo", iter2 != NULL);
	print_test("Prueba lista iterador el valor actual es el correcto", lista_iter_ver_actual(iter2) == ptr[3]);
	print_test("Prueba lista iterador avanzar un elemento es true", lista_iter_avanzar(iter2));
	print_test("Prueba lista iterador el valor actual es el correcto", lista_iter_ver_actual(iter2) == ptr[1]);
	print_test("Prueba lista iterador avanzar un elemento es true", lista_iter_avanzar(iter2));
	print_test("Prueba lista iterador el valor actual es el correcto", lista_iter_ver_actual(iter2) == ptr[0]);
	print_test("Prueba lista iterador avanzar un elemento es true", lista_iter_avanzar(iter2));
	print_test("Prueba lista iterador el iterador se encuentra al final de la lista", lista_iter_al_final(iter2));
	lista_iter_destruir(iter2);
	print_test("Prueba lista iterador el iterador externo fue destruido", true);
	lista_iter_t* iter3 = lista_iter_crear(lista1);
	print_test("Prueba lista iterador crear un tercer iterador externo", iter3 != NULL);
	print_test("Prueba lista iterador borrar un elemento devuelve el valor correcto", lista_iter_borrar(iter3) == ptr[3]);
	print_test("Prueba lista iterador borrar un elemento devuelve el valor correcto", lista_iter_borrar(iter3) == ptr[1]);
	print_test("Prueba lista iterador borrar un elemento devuelve el valor correcto", lista_iter_borrar(iter3) == ptr[0]);
	print_test("Prueba lista iterador el valor actual del iterador es NULL", lista_iter_ver_actual(iter3) == NULL);
	print_test("Prueba lista el primer elemento de la lista es NULL", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es NULL", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista borrar el primer elemento de la lista es NULL", lista_borrar_primero(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 0", lista_largo(lista1) == 0);
	print_test("Prueba lista la lista esta vacia", lista_esta_vacia(lista1));
	print_test("Prueba lista iterador insertar un elemento con el iterador externo es true", lista_iter_insertar(iter3, ptr[6]));
	print_test("Prueba lista iterador el valor actual del iterador es el correcto", lista_iter_ver_actual(iter3) == ptr[6]);
	lista_iter_destruir(iter3);
	print_test("Prueba lista iterador el iterador externo fue destruido", true);
	//Pruebo destruir la lista.
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista fue destruida", true);
}

bool sumar_elementos (void *dato, void *extra) {
	*(int*)extra += *(int*)dato;
	return true;
}

bool recorrer_2_elementos (void *dato, void *extra) {
	*(int*)extra += 1;
	
	if (*(int*)extra >= 2) {
		return false;
	}
	
	return true;
}

void pruebas_lista_iterador_interno() {
	int num[] = {4, 45, -1, 12, 3, 6, 2};
	void* ptr[] = {&num[0], &num[1], &num[2], &num[3], &num[4], &num[5], &num[6]};
	
	lista_t* lista1 = lista_crear();
	print_test("Prueba lista crear lista", lista1 != NULL);
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[0]));
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[1]));
	print_test("Prueba lista enlistar un elemento al principio de la lista es true", lista_insertar_primero(lista1, ptr[2]));
	int suma = 0;
	lista_iterar(lista1, sumar_elementos, &suma);
	print_test("Prueba lista iterador interno la funcion visitar es correcta", suma == 48);
	int contador = 0;
	lista_iterar(lista1, recorrer_2_elementos, &contador);
	print_test("Prueba lista iterador interno la cantidad de elementos iterados es la correcta",  contador == 2);
	//Pruebo destruir la lista.
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista fue destruida", true);
}

void pila_destruir_wrapper(void* dato) {
	pila_destruir((pila_t*)dato);
}

void pruebas_lista_destruir_memoria_dinamica() {
	int* num1 = malloc(sizeof(int));
	int* num2 = malloc(sizeof(int));
	int* num3 = malloc(sizeof(int));
	
	lista_t* lista1 = lista_crear();
	print_test("Prueba lista crear lista", lista1 != NULL);
	print_test("Prueba lista enlistar un elemento de memoria dinamica al principio de la lista es true", lista_insertar_primero(lista1, num1));
	print_test("Prueba lista enlistar un elemento de memoria dinamica al principio de la lista es true", lista_insertar_primero(lista1, num2));
	print_test("Prueba lista enlistar un elemento de memoria dinamica al principio de la lista es true", lista_insertar_primero(lista1, num3));
	lista_destruir(lista1, free);
	print_test("Prueba lista la lista fue destruida con parametro free", true);
}

void pruebas_lista_destruir_pila() {
	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_t* pila3 = pila_crear();
	
	lista_t* lista1 = lista_crear();
	print_test("Prueba lista crear lista", lista1 != NULL);
	print_test("Prueba lista enlistar una pila al principio de la lista es true", lista_insertar_primero(lista1, pila1));
	print_test("Prueba lista enlistar una pila al principio de la lista es true", lista_insertar_primero(lista1, pila2));
	print_test("Prueba lista enlistar una pila al principio de la lista es true", lista_insertar_primero(lista1, pila3));
	lista_destruir(lista1, pila_destruir_wrapper);
	print_test("Prueba lista la lista fue destruida con parametro pila_destruir", true);
}

void pruebas_lista_destruir_vacia() {
	lista_t* lista1 = lista_crear();
	
	print_test("Prueba lista crear lista", lista1 != NULL);
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista vacia fue destruida con parametro NULL", true);
}

void pruebas_lista_destruir_memoria_estatica() {
	int num4 = 2, num5 = 6;
	lista_t* lista1 = lista_crear();
	
	print_test("Prueba lista crear lista", lista1 != NULL);
	print_test("Prueba lista enlistar un elemento de memoria estatica al principio de la lista es true", lista_insertar_primero(lista1, &num4));
	print_test("Prueba lista enlistar un elemento de memoria estatica al principio de la lista es true", lista_insertar_primero(lista1, &num5));
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista con elementos de memoria estatica enlistados fue destruida", true);
}

void inicializar_vector_enteros(int vector[]) {
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		vector[i] = i;
	}
}

void inicializar_vector_punteros(int* vector1[], int vector2[]) {
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		vector1[i] = &vector2[i]; 
	}
}

void pruebas_lista_volumen_enlistar_primero() {
	lista_t* lista1 = lista_crear();
	int vector[CONSTANTE_VOLUMEN];
	int* vector_ptr[CONSTANTE_VOLUMEN];
	
	inicializar_vector_enteros(vector);
	inicializar_vector_punteros(vector_ptr, vector);
	bool ok = true;
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		ok &= lista_insertar_primero(lista1, vector_ptr[i]);
		ok &= vector_ptr[i] == (lista_ver_primero(lista1));
	}
	
	print_test("Prueba lista en volumen se pudieron enlistar al inicio todos los elementos", ok);
	ok = true;
	for (int i = (CONSTANTE_VOLUMEN - 1); i >= 0; i--) {
		ok &= vector_ptr[i] == (lista_ver_primero(lista1));
		ok &= vector_ptr[i] == (lista_borrar_primero(lista1));
	}
	
	print_test("Prueba lista en volumen se pudieron desenlistar todos los elementos", ok);
	print_test("Prueba lista el primer elemento de la lista es NULL", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es NULL", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista borrar el primer elemento de la lista es NULL", lista_borrar_primero(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 0", lista_largo(lista1) == 0);
	print_test("Prueba lista la lista esta vacia", lista_esta_vacia(lista1));
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista fue destruida", true);
}

void pruebas_lista_volumen_enlistar_ultimo() {
	lista_t* lista1 = lista_crear();
	int vector[CONSTANTE_VOLUMEN];
	int* vector_ptr[CONSTANTE_VOLUMEN];
	bool ok = true;
	
	inicializar_vector_enteros(vector);
	inicializar_vector_punteros(vector_ptr, vector);
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		ok &= lista_insertar_ultimo(lista1, vector_ptr[i]);
		ok &= vector_ptr[i] == (lista_ver_ultimo(lista1));
	}
	
	print_test("Prueba lista en volumen se pudieron enlistar al final todos los elementos", ok);
	ok = true;
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		ok &= vector_ptr[i] == (lista_ver_primero(lista1));
		ok &= vector_ptr[i] == (lista_borrar_primero(lista1));
	}
	
	print_test("Prueba lista en volumen se pudieron desenlistar todos los elementos", ok);
	print_test("Prueba lista el primer elemento de la lista es NULL", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es NULL", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista borrar el primer elemento de la lista es NULL", lista_borrar_primero(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 0", lista_largo(lista1) == 0);
	print_test("Prueba lista la lista esta vacia", lista_esta_vacia(lista1));
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista fue destruida", true);
}

void pruebas_lista_volumen_iterador_externo() {
	lista_t* lista1 = lista_crear();
	int vector[CONSTANTE_VOLUMEN];
	int* vector_ptr[CONSTANTE_VOLUMEN];
	lista_iter_t* iter1 = lista_iter_crear(lista1);
	bool ok = true;
	
	inicializar_vector_enteros(vector);
	inicializar_vector_punteros(vector_ptr, vector);
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		ok &= lista_iter_insertar(iter1, vector_ptr[i]);
		ok &= vector_ptr[i] == (lista_ver_primero(lista1));
	}
	
	print_test("Prueba lista en volumen se pudieron enlistar todos los elementos con iterador externo", ok);
	ok = true;
	for (int i = (CONSTANTE_VOLUMEN - 1); i >= 0; i--) {
		ok &= vector_ptr[i] == (lista_ver_primero(lista1));
		ok &= vector_ptr[i] == (lista_iter_borrar(iter1));
	}
	
	print_test("Prueba lista en volumen se pudieron desenlistar todos los elementos con iterador externo", ok);
	lista_iter_destruir(iter1);
	print_test("Prueba lista el iterador externo fue destruido", true);
	print_test("Prueba lista el primer elemento de la lista es NULL", lista_ver_primero(lista1) == NULL);
	print_test("Prueba lista el ultimo elemento de la lista es NULL", lista_ver_ultimo(lista1) == NULL);
	print_test("Prueba lista borrar el primer elemento de la lista es NULL", lista_borrar_primero(lista1) == NULL);
	print_test("Prueba lista la cantidad de elementos de la lista es 0", lista_largo(lista1) == 0);
	print_test("Prueba lista la lista esta vacia", lista_esta_vacia(lista1));
	lista_destruir(lista1, NULL);
	print_test("Prueba lista la lista fue destruida", true);
}

void pruebas_lista_alumno() {
	pruebas_lista_enlistar_desenlistar();
	pruebas_lista_elementos_NULL();
	pruebas_lista_iterador_interno();
	pruebas_lista_iterador_externo();
	pruebas_lista_destruir_memoria_dinamica();
	pruebas_lista_destruir_pila();
	pruebas_lista_destruir_vacia();
	pruebas_lista_destruir_memoria_estatica();
	pruebas_lista_volumen_enlistar_primero();
	pruebas_lista_volumen_enlistar_ultimo();
	pruebas_lista_volumen_iterador_externo();
}

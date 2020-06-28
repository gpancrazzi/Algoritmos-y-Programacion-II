#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>

#define CONSTANTE_VOLUMEN 10000

void pila_destruir_wrapper(void* dato) {
	pila_destruir((pila_t*)dato);
}

void pruebas_cola_encolar_desencolar() {
	int num[] = {2, 4, 3, -1, 12};
	void* ptr[] = {&num[0], &num[1], &num[2], &num[3], &num[4]};
	cola_t* cola1 = cola_crear();
	
	print_test("Prueba cola crear cola", cola1);
	print_test("Prueba cola el primer valor de la cola es NULL", !cola_ver_primero(cola1));
	print_test("Prueba cola desencolar devuelve NULL", !cola_desencolar(cola1));
	print_test("Prueba cola la cola esta vacia", cola_esta_vacia(cola1));
	print_test("Prueba cola encolar un elemento es true", cola_encolar(cola1, ptr[0]));
	print_test("Prueba cola el elemento es el primer valor de la cola", ptr[0] == cola_ver_primero(cola1));
	print_test("Prueba cola la cola no esta vacia", !cola_esta_vacia(cola1));
	print_test("Prueba cola desencolar devuelve el elemento correcto", cola_desencolar(cola1) == ptr[0]);
	print_test("Prueba cola la cola esta vacia", cola_esta_vacia(cola1));
	print_test("Prueba cola el primer elemento de la cola es NULL", !cola_ver_primero(cola1));
	print_test("Prueba cola desencolar es NULL", !cola_desencolar(cola1));
	print_test("Prueba cola la cola esta vacia", cola_esta_vacia(cola1));
	print_test("Prueba cola encolar un elemento es true", cola_encolar(cola1, ptr[1]));
	print_test("Prueba cola el elemento es el primer valor de la cola", ptr[1] == cola_ver_primero(cola1));
	print_test("Prueba cola encolar un segundo elemento es true", cola_encolar(cola1, ptr[2]));
	print_test("Prueba cola el primer valor de la cola es el correcto", ptr[1] == cola_ver_primero(cola1));
	print_test("Prueba cola encolar un tercer elemento es true", cola_encolar(cola1, ptr[3]));
	print_test("Prueba cola el primer valor de la cola es el correcto", ptr[1] == cola_ver_primero(cola1));
	print_test("Prueba cola desencolar devuelve el elemento correcto", cola_desencolar(cola1) == ptr[1]);
	print_test("Prueba cola el primer valor de la cola es el correcto", ptr[2] == cola_ver_primero(cola1));
	print_test("Prueba cola desencolar devuelve el elemento correcto", cola_desencolar(cola1) == ptr[2]);
	print_test("Prueba cola el primer valor de la cola es el correcto", ptr[3] == cola_ver_primero(cola1));
	print_test("Prueba cola encolar un segundo elemento es true", cola_encolar(cola1, ptr[4]));
	print_test("Prueba cola el primer valor de la cola es el correcto", ptr[3] == cola_ver_primero(cola1));
	print_test("Prueba cola desencolar devuelve el elemento correcto", cola_desencolar(cola1) == ptr[3]);
	print_test("Prueba cola el primer valor de la cola es el correcto", ptr[4] == cola_ver_primero(cola1));
	print_test("Prueba cola encolar un segundo elemento NULL es true", cola_encolar(cola1, NULL));
	print_test("Prueba cola el primer valor de la cola es el correcto", ptr[4] == cola_ver_primero(cola1));
	cola_destruir(cola1, NULL);
	print_test("Prueba cola la cola fue destruida", true); 
}

void pruebas_cola_destruir() {
	int* num1 = malloc(sizeof(int));
	int* num2 = malloc(sizeof(int));
	int* num3 = malloc(sizeof(int));
	cola_t* cola1 = cola_crear();
	
	print_test("Prueba cola crear cola", cola1);
	print_test("Prueba cola encolar un elemento de memoria dinamica es true", cola_encolar(cola1, num1));
	print_test("Prueba cola el primer valor de la cola es el correcto", num1 == cola_ver_primero(cola1));
	print_test("Prueba cola encolar un segundo elemento de memoria dinamica es true", cola_encolar(cola1, num2));
	print_test("Prueba cola el primer valor de la cola es el correcto", num1 == cola_ver_primero(cola1));
	print_test("Prueba cola encolar un tercer elemento de memoria dinamica es true", cola_encolar(cola1, num3));
	print_test("Prueba cola el primer valor de la cola es el correcto", num1 == cola_ver_primero(cola1));
	cola_destruir(cola1, free);
	print_test("Prueba cola la cola fue destruida con parametro free", true);
	
	pila_t* pila1 = pila_crear();
	pila_t* pila2 = pila_crear();
	pila_t* pila3 = pila_crear();
	cola_t* cola2 = cola_crear();
	print_test("Prueba cola crear cola", cola2);
	print_test("Prueba cola encolar una pila es true", cola_encolar(cola2, pila1));
	print_test("Prueba cola el primer valor de la cola es el correcto", pila1 == cola_ver_primero(cola2));
	print_test("Prueba cola encolar una segunda pila es true", cola_encolar(cola2, pila2));
	print_test("Prueba cola el primer valor de la cola es el correcto", pila1 == cola_ver_primero(cola2));
	print_test("Prueba cola encolar una tercer pila es true", cola_encolar(cola2, pila3));
	print_test("Prueba cola el primer valor de la cola es el correcto", pila1 == cola_ver_primero(cola2));
	cola_destruir(cola2, pila_destruir_wrapper);
	print_test("Prueba cola la cola fue destruida con parametro pila_destruir", true);
	
	cola_t* cola3 = cola_crear();
	print_test("Prueba cola crear cola", cola3);
	cola_destruir(cola3, NULL);
	print_test("Prueba cola la cola vacia fue destruida con parametro NULL", true);
	
	int num4 = 2, num5 = 6;
	void* num4_ptr = &num4;
	void* num5_ptr = &num5;
	cola_t* cola4 = cola_crear();
	print_test("Prueba cola encolar un elemento es true", cola_encolar(cola4, num4_ptr));
	print_test("Prueba cola el primer valor de la cola es el correcto", num4_ptr == cola_ver_primero(cola4));
	print_test("Prueba cola encolar un segundo elemento es true", cola_encolar(cola4, num5_ptr));
	print_test("Prueba cola el primer valor de la cola es el correcto", num4_ptr == cola_ver_primero(cola4));
	cola_destruir(cola4, NULL);
	print_test("Prueba cola la cola con elementos encolados fue destruida con parametro NULL", true);
}

void inicializar_vector_enteros(int vector[]) {
	for (int i = 0; i < CONSTANTE_VOLUMEN; i++) {
		vector[i] = i;
	}
}

void inicializar_vector_punteros(int* vector1[], int vector2[]) {
	for (size_t i = 0; i < CONSTANTE_VOLUMEN; i++) {
		vector1[i] = &vector2[i]; 
	}
}

void pruebas_cola_volumen() {
	cola_t* cola1 = cola_crear();
	int vector[CONSTANTE_VOLUMEN];
	int* vector_ptr[CONSTANTE_VOLUMEN];
	
	inicializar_vector_enteros(vector);
	inicializar_vector_punteros(vector_ptr, vector);
	bool ok = true;
	for (size_t i = 0; i < CONSTANTE_VOLUMEN; i++) {
		ok &= cola_encolar(cola1, vector_ptr[i]);
		ok &= vector_ptr[0] == (cola_ver_primero(cola1));
	}
	
	print_test("Prueba cola en volumen se pudieron encolar todos los elementos", ok);
	ok = true;
	for (size_t i = 0; i < CONSTANTE_VOLUMEN; i++) {
		ok &= (cola_ver_primero(cola1) == vector_ptr[i]);
		ok &= (cola_desencolar(cola1) == vector_ptr[i]);
	}
	
	print_test("Prueba cola en volumen se pudieron desencolar todos los elementos", ok);
	print_test("Prueba cola la cola esta vacia", cola_esta_vacia(cola1));
	print_test("Prueba cola el primer elemento de la cola es NULL", !cola_ver_primero(cola1));
	print_test("Prueba cola desencolar es NULL", !cola_desencolar(cola1));
	cola_destruir(cola1, NULL);
	print_test("Prueba cola la cola fue destruida", true);
}

void pruebas_cola_alumno() {
	pruebas_cola_encolar_desencolar();
	pruebas_cola_destruir();
	pruebas_cola_volumen();
}
